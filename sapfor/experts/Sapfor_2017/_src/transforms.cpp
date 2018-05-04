#include "leak_detector.h"

#include <cstdio>
#include <cstring>
#include <cstring>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include <omp.h>
#if _WIN32 && _DEBUG
#include <crtdbg.h>  
#endif

#include "ParallelizationRegions/ParRegions_func.h"

#include "Distribution/Distribution.h"
#include "Distribution/GraphCSR.h"
#include "Distribution/Arrays.h"
#include "Distribution/DvmhDirective.h"

#include "errors.h"
#include "SgUtils.h"
#include "LoopConverter/enddo_loop_converter.h"
#include "LoopAnalyzer/loop_analyzer.h"

#include "GraphCall/graph_calls_func.h"
#include "GraphLoop/graph_loops_func.h"

#include "DirectiveAnalyzer/DirectiveAnalyzer.h"
#include "VerificationCode/verifications.h"
#include "Distribution/CreateDistributionDirs.h"
#include "PrivateAnalyzer/private_analyzer.h"
#include "ExpressionTransform/expr_transform.h"
#include "LoopConverter/loop_transform.h"
#include "LoopConverter/array_assign_to_loop.h"
#include "Predictor/PredictScheme.h"

#include "SageAnalysisTool/depInterfaceExt.h"

#ifdef _WIN32
#include "VisualizerCalls/get_information.h"
#endif

#ifdef _ARBU
#include <SignalHandling.hpp>
#endif

#include "dvm.h"
#include "transform.h"
#include "PassManager.h"
#include "SgUtils.h"

using namespace std;
#define DEBUG_LVL1 true

int PASSES_DONE[EMPTY_PASS];
bool PASSES_DONE_INIT = false;

int *ALGORITHMS_DONE[EMPTY_ALGO] = { NULL };

#include "SapforData.h"

static SgProject *project = NULL;
// for pass temporary functions from DEF_USE_STAGE1 to SUBST_EXPR
static map<string, vector<FuncInfo*>> temporaryAllFuncInfo = map<string, vector<FuncInfo*>>();

void deleteAllAllocatedData()
{
#ifdef _WIN32
    for (int i = 0; i < parallelRegions.size(); ++i)
        delete parallelRegions[i];

    shortFileNames.clear();
    for (auto &it : allFuncInfo)
        for (auto &toDel : it.second)
            delete toDel;
    allFuncInfo.clear();

    for (auto &elem : temporaryAllFuncInfo)
        for (auto &toDel : elem.second)
            delete toDel;
    temporaryAllFuncInfo.clear();

    for (auto &loop : loopGraph)
        for (auto &toDel : loop.second)
            delete toDel;
    loopGraph.clear();

    for (auto &toDel : depInfoForLoopGraph)
        delete toDel.second;
    depInfoForLoopGraph.clear();

    for (auto &toDel : declaratedArrays)
    {
        delete toDel.second.first;
        delete toDel.second.second;
    }
    declaratedArrays.clear();

    commentsToInclude.clear();
    SPF_messages.clear();

    for (int i = 0; i < EMPTY_ALGO; ++i)
        delete []ALGORITHMS_DONE[i];
    delete project;

    deletePointerAllocatedData();
#endif
}

static vector<Messages>& getMessagesForFile(const char *fileName)
{
    auto it = SPF_messages.find(fileName);
    if (it == SPF_messages.end())
        it = SPF_messages.insert(it, make_pair(fileName, vector<Messages>()));
    return it->second;
}

extern "C" void printLowLevelWarnings(const char *fileName, const int line, const char *message, const int group)
{
    vector<Messages> &currM = getMessagesForFile(fileName);
    __spf_print(1, "WARR: line %d: %s\n", line, message);

    currM.push_back(Messages(WARR, line, message, group));
}

extern "C" void printLowLevelNote(const char *fileName, const int line, const char *message, const int group)
{
    vector<Messages> &currM = getMessagesForFile(fileName);
    __spf_print(1, "NOTE: line %d: %s\n", line, message);

    currM.push_back(Messages(NOTE, line, message, group));
}

static bool isDone(const int curr_regime)
{
    if (PASSES_DONE[curr_regime] == 0)
    {
        if (curr_regime < EMPTY_PASS)
            PASSES_DONE[curr_regime] = 1;
        else
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
    } // dont run passes twice
    else if (passesIgnoreStateDone.find((passes)curr_regime) == passesIgnoreStateDone.end())
        return true;

    return false;
}

static void updateStatsByLine(const int id)
{ 
    statsByLine[id].clear();
    for (SgStatement *st = current_file->firstStatement(); st; st = st->lexNext())
        statsByLine[id][make_pair(st->fileName(), st->lineNumber())] = st;

}

static void updateStatsExprs(const int id, const string &file)
{
    for (SgStatement *st = current_file->firstStatement(); st; st = st->lexNext())
        sgStats[st->thebif] = make_pair(file, id);
    for (SgExpression *ex = current_file->firstExpression(); ex; ex = ex->nextInExprTable())
        sgExprs[ex->thellnd] = make_pair(file, id);
}

pair<SgFile*, SgStatement*> currProcessing;
map<string, pair<SgFile*, int>> files;

static bool runAnalysis(SgProject &project, const int curr_regime, const bool need_to_unparce, const char *newVer = NULL, const char *folderName = NULL)
{    
    if (PASSES_DONE_INIT == false)
    {
        for (int i = 0; i < EMPTY_PASS; ++i)
            PASSES_DONE[i] = 0;
        PASSES_DONE_INIT = true;
    }

    if (isDone(curr_regime))
        return false;

    __spf_print(DEBUG_LVL1, "RUN PASS with name %s\n", passNames[curr_regime]);
    const int n = project.numberOfFiles();

    const bool need_to_save = false;
    char fout_name[128];
    bool veriyOK = true;

    int internalExit = 0;

    //for process include files
    set<string> allIncludeFiles;

    //for insert and extract dirs
    map<string, string> templateDeclInIncludes;

    // **********************************  ///
    /// FIRST STEP - RUN ANALYSIS BY FILES ///
    // **********************************  ///
#if _WIN32
    double timeForPass = omp_get_wtime();
#endif
    
    sgStats.clear();
    sgExprs.clear();
    for (int i = n - 1; i >= 0; --i)
    {
        SgFile *file = &(project.file(i));
        current_file_id = i;
        current_file = file;
        updateStatsByLine(current_file_id);
        updateStatsExprs(current_file_id, file->filename());
    }
    currProcessing.first = NULL; currProcessing.second = NULL;
    for (int i = n - 1; i >= 0; --i)
    {
#if _WIN32 && NDEBUG
        createNeededException();
#endif
        SgFile *file = &(project.file(i));
        current_file_id = i;
        current_file = file;

        currProcessing.first = file; currProcessing.second = NULL;

        const char *file_name = file->filename();
        __spf_print(DEBUG_LVL1, "  Analyzing: %s\n", file_name);

        if (curr_regime == CONVERT_TO_ENDDO)
            ConverToEndDo(file, getMessagesForFile(file_name));
        else if (curr_regime == UNROLL_LOOPS)
        {
            __spf_print(DEBUG_LVL1, "  it is not implemented yet\n");
            throw(-1);
        }
        else if (curr_regime == LOOP_ANALYZER_DATA_DIST_S1 || curr_regime == ONLY_ARRAY_GRAPH)
        {
            try
            {
                //save current state
                if (curr_regime == LOOP_ANALYZER_DATA_DIST_S1)
                    states.push_back(new SapforState());

                auto itFound = loopGraph.find(file_name);
                auto itFound2 = allFuncInfo.find(file_name);
                loopAnalyzer(file, parallelRegions, createdArrays, getMessagesForFile(file_name), DATA_DISTR, itFound2->second,
                             declaratedArrays, declaratedArraysSt, arrayLinksByFuncCalls, &(itFound->second));
            }
            catch (...)
            {
                internalExit = 1;
            }
        }
        else if (curr_regime == LOOP_ANALYZER_COMP_DIST)
        {
            auto itFound = loopGraph.find(file_name);
            auto itFound2 = allFuncInfo.find(file_name);
            loopAnalyzer(file, parallelRegions, createdArrays, getMessagesForFile(file_name), COMP_DISTR, itFound2->second,
                         declaratedArrays, declaratedArraysSt, arrayLinksByFuncCalls, &(itFound->second));

            currProcessing.second = NULL;
            UniteNestedDirectives(itFound->second);
        }
        else if (curr_regime == CALL_GRAPH)
        {
            auto it = allFuncInfo.find(file_name);
            if (it == allFuncInfo.end())
                functionAnalyzer(file, allFuncInfo);
        }
        else if (curr_regime == CALL_GRAPH2)
            checkForRecursion(file, allFuncInfo, getMessagesForFile(file_name));
        else if (curr_regime == LOOP_GRAPH)
        {
            auto it = loopGraph.find(file_name);
            if (it == loopGraph.end())
            {
                loopGraph[file_name] = vector<LoopGraph*>();
                loopGraphAnalyzer(file, loopGraph[file_name]);
            }
        }
        else if (curr_regime == VERIFY_ENDDO)
        {
            vector<int> errors;
            EndDoLoopChecker(file, errors);
            if (errors.size() != 0)
            {
                veriyOK = false;
                vector<Messages> &currMessages = getMessagesForFile(file_name);
                for (int z = 0; z < errors.size(); ++z)
                {
                    __spf_print(1, "  ERROR: Loop on line %d does not have END DO\n", errors[z]);
                    currMessages.push_back(Messages(ERROR, errors[z], "This loop does not have END DO format", 1018));
                }
            }
        }
        else if (curr_regime == VERIFY_INCLUDE)
        {
            set<pair<string, int>> errors;
            IncludeChecker(file, file_name, errors);
            if (errors.size() != 0)
            {
                veriyOK = false;
                vector<Messages> &currMessages = getMessagesForFile(file_name);
                for (auto z = errors.begin(); z != errors.end(); ++z)
                {
                    __spf_print(1, "  ERROR: include '%s' at line %d has executable operators\n", z->first.c_str(), z->second);

                    string currM;
                    __spf_printToBuf(currM, "Include '%s' has executable operators", z->first.c_str());
                    currMessages.push_back(Messages(ERROR, z->second, currM, 1019));
                }
            }
        }
        else if (curr_regime == VERIFY_DVM_DIRS)
        {
            if (keepDvmDirectives == 0)
            {
                map<string, vector<int>> errors; // file->lines
                if (ignoreDvmChecker == 0)
                    DvmDirectiveChecker(file, errors);

                __spf_print(1, "  ignoreDvmChecker = %d\n", ignoreDvmChecker);
                if (errors.size() != 0)
                {
                    veriyOK = false;
                    for (auto &err : errors)
                    {
                        vector<Messages> &currMessages = getMessagesForFile(err.first.c_str());
                        for (auto &code : err.second)
                        {
                            __spf_print(1, "  ERROR: at line %d: Active DVM directives are not supported yet\n", code);
                            currMessages.push_back(Messages(ERROR, code, "Active DVM directives are not supported yet", 1020));
                        }
                    }
                }
            }
        }
        else if (curr_regime == CREATE_PARALLEL_DIRS)
        {
            auto itFound = loopGraph.find(file_name);

            for (int z = 0; z < parallelRegions.size(); ++z)
            {
                vector<pair<int, pair<string, vector<Expression*>>>> toInsert;

                const DataDirective &dataDirectives = parallelRegions[z]->GetDataDir();
                const vector<int> &currentVariant = parallelRegions[z]->GetCurrentVariant();
                DIST::GraphCSR<int, double, attrType> &reducedG = parallelRegions[z]->GetReducedGraphToModify();
                DIST::Arrays<int> &allArrays = parallelRegions[z]->GetAllArraysToModify();

                auto &tmp = dataDirectives.distrRules;
                std::vector<std::pair<DIST::Array*, const DistrVariant*>> currentVar;
                for (int z1 = 0; z1 < currentVariant.size(); ++z1)
                    currentVar.push_back(make_pair(tmp[z1].first, &tmp[z1].second[currentVariant[z1]]));

                selectParallelDirectiveForVariant(file, parallelRegions[z], reducedG, allArrays, itFound->second, currentVar,
                                                  dataDirectives.alignRules, toInsert, parallelRegions[z]->GetId(), arrayLinksByFuncCalls,
                                                  depInfoForLoopGraph, getMessagesForFile(file_name));

                if (toInsert.size() > 0)
                {
                    auto it = createdDirectives.find(file_name);
                    if (it == createdDirectives.end())
                        createdDirectives.insert(it, make_pair(file_name, toInsert));
                    else
                        for (int m = 0; m < toInsert.size(); ++m)
                            it->second.push_back(toInsert[m]);
                }
            }
        }
        else if (curr_regime == INSERT_PARALLEL_DIRS || curr_regime == EXTRACT_PARALLEL_DIRS)
        {
            const bool extract = (curr_regime == EXTRACT_PARALLEL_DIRS);
            insertDirectiveToFile(file, file_name, createdDirectives[file_name], extract, getMessagesForFile(file_name));
            currProcessing.second = NULL;

            //clear shadow specs
            for (auto &array : declaratedArrays)
                array.second.first->ClearShadowSpecs();
            
            for (int z = 0; z < parallelRegions.size(); ++z)
            {
                ParallelRegion *currReg = parallelRegions[z];
                const DataDirective &dataDirectives = currReg->GetDataDir();
                const vector<int> &currentVariant = currReg->GetCurrentVariant();
                const DIST::Arrays<int> &allArrays = currReg->GetAllArrays();
                DIST::GraphCSR<int, double, attrType> &reducedG = currReg->GetReducedGraphToModify();

                set<string> distrArrays;
                for (int z = 0; z < dataDirectives.distrRules.size(); ++z)
                    distrArrays.insert(dataDirectives.distrRules[z].first->GetShortName());
                for (int z = 0; z < dataDirectives.alignRules.size(); ++z)
                    distrArrays.insert(dataDirectives.alignRules[z].alignArray->GetShortName());

                const vector<string> distrRules = dataDirectives.GenRule(currentVariant);
                const vector<string> alignRules = dataDirectives.GenAlignsRules();

                insertDistributionToFile(file, file_name, dataDirectives, distrArrays, distrRules, alignRules, loopGraph,
                                         allArrays, reducedG, commentsToInclude, templateDeclInIncludes, extract, getMessagesForFile(file_name),
                                         arrayLinksByFuncCalls, currReg->GetId());
            }

            if (curr_regime == INSERT_PARALLEL_DIRS)
            {
                // insert redistribution for regions
                if (parallelRegions.size() > 1 || (parallelRegions.size() == 1 && parallelRegions[0]->GetId() > 0))
                {
                    for (int z = 0; z < parallelRegions.size(); ++z)
                    {
                        ParallelRegion *currReg = parallelRegions[z];
                        const DataDirective &dataDirectives = currReg->GetDataDir();
                        const vector<int> &currentVariant = currReg->GetCurrentVariant();
                        vector<int> variantZero(currentVariant.size());
                        std::fill(variantZero.begin(), variantZero.end(), 0);

                        const std::vector<ParallelRegionLines> *currLines = currReg->GetLines(file_name);

                        if (currLines)
                        {
                            File *fileT = new File(file);
                            const vector<Statement*> &reDistrRulesBefore = dataDirectives.GenRule(fileT, currentVariant, (int)DVM_REDISTRIBUTE_DIR);
                            const vector<Statement*> &reDistrRulesAfter = dataDirectives.GenRule(fileT, variantZero, (int)DVM_REDISTRIBUTE_DIR);
                            const vector<Statement*> &reAlignRules = dataDirectives.GenAlignsRules(fileT, (int)DVM_REALIGN_DIR);

                            insertDistributeDirsToParallelRegions(currLines, reDistrRulesBefore, reDistrRulesAfter, reAlignRules);
                        }
                    }
                }
            }
            else
                createdDirectives[file_name].clear();
        }
        else if (curr_regime == INSERT_SHADOW_DIRS || curr_regime == EXTRACT_SHADOW_DIRS)
        {
            const bool extract = (curr_regime == EXTRACT_SHADOW_DIRS);

            for (int z = 0; z < parallelRegions.size(); ++z)
            {
                ParallelRegion *currReg = parallelRegions[z];
                DataDirective &dataDirectives = currReg->GetDataDirToModify();
                DIST::GraphCSR<int, double, attrType> &reducedG = parallelRegions[z]->GetReducedGraphToModify();

                set<string> distrArrays;
                for (int z = 0; z < dataDirectives.distrRules.size(); ++z)
                    distrArrays.insert(dataDirectives.distrRules[z].first->GetShortName());
                for (int z = 0; z < dataDirectives.alignRules.size(); ++z)
                    distrArrays.insert(dataDirectives.alignRules[z].alignArray->GetShortName());

                insertShadowSpecToFile(file, file_name, distrArrays, reducedG, commentsToInclude, extract, getMessagesForFile(file_name), declaratedArrays);
            }
        }
        else if (curr_regime == REVERT_SPF_DIRS)
        {
            if (keepSpfDirs)
                revertion_spf_dirs(file, declaratedArrays, declaratedArraysSt);
            else
                __spf_print(1, "   ignore SPF REVERT\n");
        }
        else if (curr_regime == CLEAR_SPF_DIRS)
        {
            if (keepSpfDirs)
            {
                vector<SgStatement*> toDel;
                for (SgStatement *st = file->firstStatement(); st; st = st->lexNext())
                {
                    if (isSPF_stat(st)) // except sapfor parallel regions
                        if (st->variant() != SPF_PARALLEL_REG_DIR && st->variant() != SPF_END_PARALLEL_REG_DIR)
                            toDel.push_back(st);
                }

                for (auto &elem : toDel)
                    elem->deleteStmt();
            }
            else
                __spf_print(1, "   ignore CLEAR SPF DIRS\n");
        }
        else if (curr_regime == PREPROC_SPF)
        {
            bool noError = preprocess_spf_dirs(file, commonBlocks, getMessagesForFile(file_name));
            if (!noError)
                internalExit = 1;
        }
        else if (curr_regime == PREPROC_ALLOCATES)
            preprocess_allocates(file);
        else if (curr_regime == CORRECT_VAR_DECL)
            VarDeclCorrecter(file);
        else if (curr_regime == CREATE_REMOTES)
        {
            auto itFound = loopGraph.find(file_name);
            auto itFound2 = allFuncInfo.find(file_name);
            loopAnalyzer(file, parallelRegions, createdArrays, getMessagesForFile(file_name), REMOTE_ACC, itFound2->second,
                         declaratedArrays, declaratedArraysSt, arrayLinksByFuncCalls, &(itFound->second));
        }
        else if (curr_regime == PRIVATE_CALL_GRAPH_STAGE1)
            FileStructure(file);
        else if (curr_regime == PRIVATE_CALL_GRAPH_STAGE2)
            doCallGraph(file);
        else if (curr_regime == PRIVATE_CALL_GRAPH_STAGE3)
        {
            auto itFound = loopGraph.find(file_name);
            if (itFound != loopGraph.end())
                insertSpfAnalysisBeforeParalleLoops(itFound->second);
        }
        else if (curr_regime == PRIVATE_CALL_GRAPH_STAGE4)
            arrayAccessAnalyzer(file, getMessagesForFile(file_name), declaratedArrays, PRIVATE_STEP4);
        else if (curr_regime == FILL_PAR_REGIONS_LINES)
            fillRegionLines(file, parallelRegions, loopGraph[file_name]);
        else if (curr_regime == FILL_COMMON_BLOCKS)
        {
            // fillCommonBlocks(file, commonBlocks);
            for (int i = 0; i < file->numberOfFunctions(); ++i)
            {
                map<string, vector<SgExpression*>> commonBlocksRef;
                SgStatement *iterator = file->functions(i);
                SgStatement *end = iterator->lastNodeOfStmt();

                getCommonBlocksRef(commonBlocksRef, iterator->lexNext(), end);

                for (auto &commonBlockRef : commonBlocksRef)
                {
                    auto it = commonBlocks.find(commonBlockRef.first);
                    if (it == commonBlocks.end())
                    {
                        CommonBlock newCommonBlock(commonBlockRef.first, vector<Variable>());
                        it = commonBlocks.insert(it, make_pair(commonBlockRef.first, newCommonBlock));
                    }

                    int position = 0;
                    for (auto &commonBlock : commonBlockRef.second)
                    {
                        vector<pair<SgSymbol*, int>> newVariables;
                        for (SgExpression *currCommon = commonBlock->lhs(); currCommon; currCommon = currCommon->rhs())
                            newVariables.push_back(make_pair(currCommon->lhs()->symbol(), position++));

                        it->second.addVariables(file, iterator, newVariables);
                    }
                }
            }

            // filling from BLOCK DATA
            SgStatement *st = file->firstStatement();

            while (st)
            {
                if (st->variant() == BLOCK_DATA) //BLOCK_DATA header
                {
                    map<string, vector<SgExpression*>> commonBlocksRef;
                    SgStatement *iterator = st->lexNext();
                    SgStatement *end = st->lastNodeOfStmt();

                    getCommonBlocksRef(commonBlocksRef, iterator->lexNext(), end);

                    for (auto &commonBlockRef : commonBlocksRef)
                    {
                        auto it = commonBlocks.find(commonBlockRef.first);
                        if (it == commonBlocks.end())
                        {
                            CommonBlock newCommonBlock(commonBlockRef.first, vector<Variable>());
                            it = commonBlocks.insert(it, make_pair(commonBlockRef.first, newCommonBlock));
                        }

                        int position = 0;
                        for (auto &commonBlock : commonBlockRef.second)
                        {
                            vector<pair<SgSymbol*, int>> newVariables;
                            for (SgExpression *currCommon = commonBlock->lhs(); currCommon; currCommon = currCommon->rhs())
                                newVariables.push_back(make_pair(currCommon->lhs()->symbol(), position++));

                            it->second.addVariables(file, st, newVariables);
                        }
                    }

                    st = st->lastNodeOfStmt();
                }

                st = st->lexNext();
            }
        }
        else if (curr_regime == LOOP_DATA_DEPENDENCIES)
            doDependenceAnalysisOnTheFullFile(file, 1, 1, 1);
        else if (curr_regime == REMOVE_DVM_DIRS || curr_regime == REMOVE_DVM_DIRS_TO_COMMENTS)
            removeDvmDirectives(file, curr_regime  == REMOVE_DVM_DIRS_TO_COMMENTS);
        else if (curr_regime == SUBST_EXPR)
            expressionAnalyzer(file, defUseByFunctions, commonBlocks, temporaryAllFuncInfo);
        else if (curr_regime == REVERT_SUBST_EXPR)
            revertReplacements(file->filename());
        else if (curr_regime == CREATE_NESTED_LOOPS)
        {
            auto itFound = loopGraph.find(file_name);
            if (itFound != loopGraph.end())
                for (int i = 0; i < itFound->second.size(); ++i)
                    createNestedLoops(itFound->second[i], depInfoForLoopGraph, getMessagesForFile(file_name));
        }
        else if (curr_regime == GET_ALL_ARRAY_DECL)
            getAllDeclaratedArrays(file, declaratedArrays, declaratedArraysSt);
        else if (curr_regime == FILE_LINE_INFO)
        {
            SgStatement *st = file->firstStatement();
            while (st)
            {
                string fName = st->fileName();
                int line = st->lineNumber();

                auto it = lineInfo.find(fName);
                if (it == lineInfo.end())
                    it = lineInfo.insert(it, make_pair(fName, 0));
                it->second = std::max(it->second, line);
                st = st->lexNext();
            }
        }
        else if (curr_regime == BUILD_INCLUDE_DEPENDENCIES)
        {
            auto fileIt = includeDependencies.find(file_name);
            if (fileIt == includeDependencies.end())
                fileIt = includeDependencies.insert(fileIt, make_pair(file_name, set<string>()));

            for (SgStatement *first = file->firstStatement(); first; first = first->lexNext())
            {
                if (strcmp(file_name, first->fileName()))
                    fileIt->second.insert(first->fileName());
            }
        }
        else if (curr_regime == REMOVE_AND_CALC_SHADOW)
        {
            for (SgStatement *first = file->firstStatement(); first; first = first->lexNext())
            {
                if (first->variant() == DVM_PARALLEL_ON_DIR)
                {
                    SgExpression *spec = first->expr(1);
                    if (spec)
                    {
                        SgExpression *shadow = NULL, *remote = NULL;
                        SgExpression *beforeSh = spec;

                        for (auto iter = spec, iterB = spec; iter; iter = iter->rhs())
                        {
                            if (iter->lhs()->variant() == SHADOW_RENEW_OP)
                            {
                                beforeSh = iterB;
                                shadow = iter->lhs();
                            }
                            else if (iter->lhs()->variant() == REMOTE_ACCESS_OP)
                                remote = iter->lhs();

                            if (iterB != iter)
                                iterB = iterB->rhs();
                        }

                        if (shadow && remote)
                        {
                            set<string> allRemoteWitDDOT;
                            for (auto iter = remote->lhs(); iter; iter = iter->rhs())
                            {
                                SgExpression *elem = iter->lhs();
                                if (elem->variant() == ARRAY_REF)
                                {
                                    bool allDDOT = true;
                                    for (auto iterL = elem->lhs(); iterL; iterL = iterL->rhs())
                                        if (iterL->lhs()->variant() != DDOT)
                                            allDDOT = false;

                                    if (allDDOT)
                                        allRemoteWitDDOT.insert(elem->symbol()->identifier());
                                }
                            }

                            auto currShadowP = shadow;
                            int numActiveSh = 0;

                            for (auto iter = shadow->lhs(); iter; iter = iter->rhs())
                            {
                                SgExpression *elem = iter->lhs();
                                //if shadow has CORNER
                                if (elem->variant() == ARRAY_OP)
                                    elem = elem->lhs();

                                if (elem->variant() == ARRAY_REF)
                                {
                                    if (allRemoteWitDDOT.find(elem->symbol()->identifier()) != allRemoteWitDDOT.end())
                                    {
                                        DIST::Array *currArray = NULL;
                                        for (int i = 0; i < elem->numberOfAttributes() && currArray == NULL; ++i)
                                            if (elem->attributeType(i) == ARRAY_REF)
                                                currArray = (DIST::Array *)(elem->getAttribute(i)->getAttributeData());                                        

                                        if (currArray == NULL)
                                            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

                                        vector<pair<int, int>> toDel;
                                        for (SgExpression *list = elem->lhs(); list; list = list->rhs())
                                            toDel.push_back(make_pair(list->lhs()->lhs()->valueInteger(), list->lhs()->rhs()->valueInteger()));                                        
                                        currArray->RemoveShadowSpec(toDel);

                                        if (currShadowP == shadow)
                                            shadow->setLhs(iter->rhs());
                                        else
                                            currShadowP->setRhs(iter->rhs());
                                    }
                                    else
                                    {
                                        ++numActiveSh;
                                        if (currShadowP == shadow)
                                            currShadowP = shadow->lhs();
                                        else
                                            currShadowP = currShadowP->rhs();
                                    }
                                }
                            }

                            //remove shadow dir
                            if (numActiveSh == 0)
                            {
                                if (spec->lhs()->variant() == SHADOW_RENEW_OP)
                                    first->setExpression(2, *(spec->rhs()));
                                else
                                    beforeSh->setRhs(beforeSh->rhs()->rhs());
                            }
                        }
                    }
                }
            }
        }
        else if (curr_regime == MACRO_EXPANSION)
            doMacroExpand(file, getMessagesForFile(file_name));    
        else if (curr_regime == REVERSE_CREATED_NESTED_LOOPS)
        {
            auto itFound = loopGraph.find(file_name);
            if (itFound != loopGraph.end())
                reverseCreatedNestedLoops(file->filename(), itFound->second);
        }
        else if (curr_regime == CONVERT_ASSIGN_TO_LOOP)
            convertFromAssignToLoop(file, getMessagesForFile(file_name));
        else if (curr_regime == CONVERT_LOOP_TO_ASSIGN)
            restoreAssignsFromLoop(file);
        else if (curr_regime == PREDICT_SCHEME)
        {
            auto itFound = loopGraph.find(file_name);
            if (itFound == loopGraph.end())
            {
                auto tmp = vector<LoopGraph*>();
                processFileToPredict(file, tmp);
            }
            else
                processFileToPredict(file, itFound->second);
        }
        else if (curr_regime == DEF_USE_STAGE1)
            constructDefUseStep1(file, defUseByFunctions, temporaryAllFuncInfo);
        else if (curr_regime == DEF_USE_STAGE2)
            constructDefUseStep2(file, defUseByFunctions);


        if (curr_regime == CORRECT_CODE_STYLE || need_to_unparce)
        {
            if (curr_regime == CORRECT_CODE_STYLE && newVer == NULL)
                newVer = "";

            if (newVer == NULL)
            {
                __spf_print(1, "  ERROR: null file addition name\n");
                getMessagesForFile(file_name).push_back(Messages(ERROR, 1, "Internal error during unparsing process has occurred", 2007));
                throw(-1);
            }

            if (folderName == NULL)
                sprintf(fout_name, "%s_%s.%s", OnlyName(file_name).c_str(), newVer, OnlyExt(file_name).c_str());
            else
            {
                if (strlen(newVer) == 0)
                    sprintf(fout_name, "%s/%s.%s", folderName, OnlyName(file_name).c_str(), OnlyExt(file_name).c_str());
                else
                    sprintf(fout_name, "%s/%s_%s.%s", folderName, OnlyName(file_name).c_str(), newVer, OnlyExt(file_name).c_str());
            }

            __spf_print(DEBUG_LVL1, "  Unparsing to <%s> file\n", fout_name);
            if (curr_regime == INSERT_INCLUDES)
            {
                __spf_print(1, "  try to find file <%s>\n", file_name);
                __spf_print(1, "  in set %d, result %d\n", (int)filesToInclude.size(), filesToInclude.find(file_name) != filesToInclude.end());
            }

            if (curr_regime == INSERT_INCLUDES && filesToInclude.find(file_name) != filesToInclude.end())
            {
                FILE *fOut = fopen(fout_name, "w");
                if (fOut)
                {
                    file->unparse(fOut);
                    fclose(fOut);
                }
                else
                {
                    __spf_print(1, "ERROR: can not create file '%s'\n", fout_name);
                    getMessagesForFile(file_name).push_back(Messages(ERROR, 1, "Internal error during unparsing process has occurred", 2007));
                    throw(-1);
                }
            }
            else
            {
                removeIncludeStatsAndUnparse(file, file_name, fout_name, allIncludeFiles);

                // copy includes that have not changed
                if (folderName != NULL)
                    copyIncludes(allIncludeFiles, commentsToInclude, folderName, curr_regime == REMOVE_DVM_DIRS ? 1 : curr_regime == REMOVE_DVM_DIRS_TO_COMMENTS ? 2 : 0);
            }
        }

        if (need_to_save)
        {
            sprintf(fout_name, "%s.dep", OnlyName(file_name).c_str());
            file->saveDepFile(fout_name);
            __spf_print(DEBUG_LVL1, "  Saving to <%s> file\n", fout_name);
        }
    } // end of FOR by files

    if (internalExit != 0)
        throw - 1;


    // **********************************  ///
    /// SECOND AGGREGATION STEP            ///
    // **********************************  ///
    currProcessing.first = NULL; currProcessing.second = NULL;
    if (curr_regime == LOOP_ANALYZER_DATA_DIST_S2 || curr_regime == ONLY_ARRAY_GRAPH)
    {
        if (curr_regime == ONLY_ARRAY_GRAPH)
            keepFiles = 1;

        set<DIST::Array*> usedArrays;
        for (int i = 0; i < parallelRegions.size(); ++i)
        {
            ParallelRegion *currReg = parallelRegions[i];
            DIST::GraphCSR<int, double, attrType> &G = currReg->GetGraphToModify();
            DIST::GraphCSR<int, double, attrType> &reducedG = currReg->GetReducedGraphToModify();
            DIST::Arrays<int> &allArrays = currReg->GetAllArraysToModify();

            usedArrays.insert(allArrays.GetArrays().begin(), allArrays.GetArrays().end());

            if (currReg->HasUserDvmDirs())
            {
                bool error = false;
                if (currReg->GetUsersDirecites(DVM_REALIGN_DIR)->size())
                {
                    bool ret = buildGraphFromUserDirectives(*(currReg->GetUsersDirecites(DVM_REALIGN_DIR)), G, allArrays, arrayLinksByFuncCalls);
                    error = error || ret;
                }
                else if (currReg->GetUsersDirecites(DVM_ALIGN_DIR)->size())
                {
                    bool ret = buildGraphFromUserDirectives(*(currReg->GetUsersDirecites(DVM_ALIGN_DIR)), G, allArrays, arrayLinksByFuncCalls);
                    error = error || ret;
                }
                else
                    error = true;

                if (error)
                {
                    string message;
                    __spf_printToBuf(message, "Can not build align graph from user's DVM directives in this region");
                    for (auto &lines : currReg->GetAllLines())
                    {
                        const auto &vecLines = lines.second;
                        const string &fileName = lines.first;

                        auto messages = getMessagesForFile(fileName.c_str());
                        for (auto &line : vecLines)
                        {
                            if (line.stats.first && line.stats.second)
                            {
                                messages.push_back(Messages(ERROR, line.stats.first->lineNumber(), message, 1036));

                                __spf_print(1, "Can not build align graph from user's DVM directives in this region in '%s': %d\n", 
                                            fileName.c_str(), line.stats.first->lineNumber());
                            }
                        }
                    }
                    printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
                }
            }
            
            G.SetMaxAvailMemory(currentAvailMemory);

            const int allArraysNum = allArrays.GetArrays().size();
            int newQuality = allArraysNum * QUALITY / 100;
            if (!consoleMode)
                printf("SAPFOR: arrays num %d, newFlag %d, quality %d\n", allArraysNum, newQuality, QUALITY);

            if (newQuality < 3)
                newQuality = 3;
            G.ChangeQuality(newQuality, newQuality);

            reducedG.SetMaxAvailMemory(currentAvailMemory);
            DIST::createOptimalDistribution<int, double, attrType>(G, reducedG, allArrays, i, (curr_regime == ONLY_ARRAY_GRAPH));

            set<DIST::Array*> usedArraysLocal;
            usedArraysLocal.insert(allArrays.GetArrays().begin(), allArrays.GetArrays().end());

            //add array that linked with used
            for (auto &used : usedArraysLocal)
            {
                set<DIST::Array*> allArrayRefs;
                getAllArrayRefs(used, used, allArrayRefs, arrayLinksByFuncCalls);

                for (auto &array : allArrayRefs)
                {
                    if (usedArraysLocal.find(array) == usedArraysLocal.end())
                    {
                        auto key = tableOfUniqNamesByArray.find(array);
                        if (key != tableOfUniqNamesByArray.end())
                        {
                            createdArrays.insert(make_pair(key->second, key->first));
                            allArrays.AddArrayToGraph(array);
                        }
                    }
                }
            }
        }

        //remove arrays that is not used
        map<tuple<int, string, string>, DIST::Array*> createdArraysNew;
        for (auto it = createdArrays.begin(); it != createdArrays.end(); ++it)
        {
            if (usedArrays.find(it->second) != usedArrays.end())
                createdArraysNew.insert(*it);
            else
            {
                set<DIST::Array*> realArrayRefs;
                getRealArrayRefs(it->second, it->second, realArrayRefs, arrayLinksByFuncCalls);

                for (auto &array : realArrayRefs)
                {
                    if (array == it->second)
                        continue;

                    if (usedArrays.find(array) != usedArrays.end())
                        createdArraysNew.insert(*it);
                }
            }
        }
        createdArrays = createdArraysNew;

        for (map<string, string>::iterator it = shortFileNames.begin(); it != shortFileNames.end(); it++)
            __spf_print(1, "  %s -> %s\n", it->first.c_str(), it->second.c_str());

        set<int> idxToDel;
        for (int z = 0; z < parallelRegions.size(); ++z)
        {
            if (parallelRegions[z]->GetAllArrays().GetArrays().size() == 0)
            {
                __spf_print(1, "  CAN NOT FIND ARRAYS FOR DISTRIBUTION for parallel region '%s'\n", parallelRegions[z]->GetName().c_str());
                idxToDel.insert(z);
            }
        }

        if (idxToDel.size() == parallelRegions.size())
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
        else if (idxToDel.size() > 0)
        {
            vector<ParallelRegion*> newParReg;
            for (int z = 0; z < parallelRegions.size(); ++z)
            {
                if (idxToDel.find(z) != idxToDel.end())
                {
                    ParallelRegion *regToDel = parallelRegions[z];
                    const map<string, vector<ParallelRegionLines>> &currLines = regToDel->GetAllLines();
                    for (auto it = currLines.begin(); it != currLines.end(); ++it)
                    {
                        vector<Messages> &currMessages = getMessagesForFile(it->first.c_str());
                        char buf[256];
                        sprintf(buf, "Can not find arrays for distribution for parallel region '%s', ignored", regToDel->GetName().c_str());
                        for (int k = 0; k < it->second.size(); ++k)
                        {
                            currMessages.push_back(Messages(ERROR, it->second[k].lines.first, buf, 3010));
                            __spf_print(1, "  Can not find arrays for distribution for parallel region '%s' on line %d, ignored\n", regToDel->GetName().c_str(), it->second[k].lines.first);
                        }
                    }
#ifdef _WIN32
                    removeFromCollection(parallelRegions[z]);
#endif
                    delete parallelRegions[z];
                }
                else
                    newParReg.push_back(parallelRegions[z]);
            }
            parallelRegions.clear();
            parallelRegions = newParReg;
        }
    }
    else if (curr_regime == CALL_GRAPH)
    {
        if (keepFiles)
            CreateCallGraphWiz("_callGraph.txt", allFuncInfo);
        findDeadFunctionsAndFillCallTo(allFuncInfo, SPF_messages);
        createLinksBetweenFormalAndActualParams(allFuncInfo, arrayLinksByFuncCalls, declaratedArrays);
        updateFuncInfo(allFuncInfo);
    }
    else if (curr_regime == INSERT_SHADOW_DIRS)
    {
        for (auto it = commentsToInclude.begin(); it != commentsToInclude.end(); ++it)
        {
            if (consoleMode)
            {
                __spf_print(1, "  write to <%s_%s> file\n", it->first.c_str(), newVer);
                insertDistributionToFile(it->first.c_str(), (string(it->first) + "_" + string(newVer)).c_str(), it->second);
            }
            else
            {
                if (folderName)
                {
                    __spf_print(1, "  write to <%s> file\n", (string(folderName) + "/" + string(it->first)).c_str());
                    insertDistributionToFile(it->first.c_str(), (string(folderName) + "/" + string(it->first)).c_str(), it->second);
                }
                else
                {
                    __spf_print(1, "  write to <%s> file\n", (string(it->first)).c_str());
                    insertDistributionToFile(it->first.c_str(), (string(it->first)).c_str(), it->second);
                }
            }
        }

        // copy includes that have not changed
        if (folderName != NULL)
            copyIncludes(allIncludeFiles, commentsToInclude, folderName);
    }
    else if (curr_regime == EXTRACT_SHADOW_DIRS)
        commentsToInclude.clear();
    else if (curr_regime == VERIFY_ENDDO ||
             curr_regime == VERIFY_INCLUDE ||
             curr_regime == VERIFY_DVM_DIRS)
    {
        if (veriyOK == false)
            throw(-1);
    }
    else if (curr_regime == PRIVATE_ANALYSIS_SPF)
    {
        SgStatement *mainUnit = findMainUnit(&project);
        if (mainUnit)
            Private_Vars_Analyzer(mainUnit);
        else
        {
            for (int i = n - 1; i >= 0; --i)
            {
#if _WIN32 && NDEBUG
                createNeededException();
#endif
                SgFile *file = &(project.file(i));
                current_file_id = i;
                current_file = file;

                auto funcForFile = allFuncInfo.find(file->filename());
                if (funcForFile != allFuncInfo.end())
                    PrivateAnalyzer(file, funcForFile->second);
            }
        }
    }
    else if (curr_regime == CREATE_TEMPLATE_LINKS)
    {
        vector<string> result;

        set<DIST::Array*> arraysDone;
        
        for (int z = 0; z < parallelRegions.size(); ++z)
        {
            DIST::GraphCSR<int, double, attrType> &reducedG = parallelRegions[z]->GetReducedGraphToModify();
            DIST::Arrays<int> &allArrays = parallelRegions[z]->GetAllArraysToModify();
            DataDirective &dataDirectives = parallelRegions[z]->GetDataDirToModify();

            if (ALGORITHMS_DONE[CREATE_DISTIBUTION][z] == 0)
            {
                //recalculate array sizes after expression substitution
                for (auto &array : allArrays.GetArrays())
                {
                    auto itF = arraysDone.find(array);
                    if (itF == arraysDone.end())
                    {
                        itF = arraysDone.insert(itF, array);
                        Symbol *symb = array->GetDeclSymbol();
                        if (symb)
                        {
                            auto &sizeInfo = array->GetSizes();
                            bool needToUpdate = false;
                            for (auto &elem : sizeInfo)
                            {
                                if (elem.first == elem.second)
                                {
                                    needToUpdate = true;
                                    break;
                                }
                            }

                            if (needToUpdate)
                            {
                                auto &declInfo = array->GetDeclInfo();
                                bool wasSelect = false;
                                for (auto &elem : declInfo)
                                {
                                    auto it = files.find(elem.first);
                                    if (it != files.end())
                                    {
                                        SgFile *tmpfile = &(CurrentProject->file(it->second.second));
                                        current_file = tmpfile;
                                        current_file_id = it->second.second;
                                        wasSelect = true;
                                        break;
                                    }
                                }
                                if (!wasSelect)
                                    printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

                                SgStatement *decl = declaratedInStmt(symb);
                                vector<pair<int, int>> sizes;
                                getArraySizes(sizes, symb, decl);
                                array->SetSizes(sizes);
                            }
                        }
                    }
                }

                createDistributionDirs(reducedG, allArrays, dataDirectives, SPF_messages, arrayLinksByFuncCalls);
                ALGORITHMS_DONE[CREATE_DISTIBUTION][z] = 1;
            }

            if (ALGORITHMS_DONE[CREATE_ALIGNS][z] == 0)
            {
                if (keepFiles)
                {
                    char fName[256];
                    sprintf(fName, "_reduced_graph_with_templ_reg%d.txt", z);
                    reducedG.CreateGraphWiz(fName, vector<tuple<int, int, attrType>>(), allArrays, true);
                }
                createAlignDirs(reducedG, allArrays, dataDirectives, parallelRegions[z]->GetId(), arrayLinksByFuncCalls);
                ALGORITHMS_DONE[CREATE_ALIGNS][z] = 1;
            }

            __spf_print(1, "*** FOR PARALLEL REGION '%s':\n", parallelRegions[z]->GetName().c_str());
            result = dataDirectives.GenAlignsRules();
            for (int i = 0; i < result.size(); ++i)
                __spf_print(1, "  %s\n", result[i].c_str());
        }
    }
    else if (curr_regime == FILE_LINE_INFO)
    {
        int allLineSum = 0;
        for (auto &elem : lineInfo)
            allLineSum += elem.second;
        __spf_print(1, "All lines in project %d\n", allLineSum);
    }
    else if (curr_regime == FILL_PAR_REGIONS_LINES)
    {
        fillRegionLinesStep2(parallelRegions, allFuncInfo, loopGraph);

        checkCountOfIter(loopGraph, SPF_messages);
        if (keepFiles)
        {
            printLoopGraph("_loopGraph.txt", loopGraph);
            printParalleRegions("_parallelRegions.txt", parallelRegions);
        }
    }
    else if (curr_regime == CHECK_PAR_REGIONS)
    {
        fillRegionArrays(parallelRegions, commonBlocks, allUsedCommonArrays);
        fillRegionFunctions(parallelRegions, allFuncInfo, allCommonFunctions);

        bool noError = checkRegions(parallelRegions, SPF_messages);
        if (!noError)
            internalExit = 1;
    }
    else if (curr_regime == RESOLVE_PAR_REGIONS)
    {
        resolveRegions(parallelRegions, allFuncInfo, allCommonFunctions);
    }
    else if (curr_regime == LOOP_GRAPH)
    {
        if (keepFiles)
            printLoopGraph("_loopGraph.txt", loopGraph);
    }
    else if (curr_regime == FILL_COMMON_BLOCKS)
    {
        if (keepFiles)
            printCommonBlocks("_commonBlocks.txt", commonBlocks);
    }
    else if (curr_regime == REVERT_SUBST_EXPR)
        PASSES_DONE[SUBST_EXPR] = 0;
    else if (curr_regime == INSERT_PARALLEL_DIRS || curr_regime == EXTRACT_PARALLEL_DIRS)
    {
        //insert template declaration to main program
        const bool extract = (curr_regime == EXTRACT_PARALLEL_DIRS);
        for (int i = n - 1; i >= 0; --i)
        {
#if _WIN32 && NDEBUG
            createNeededException();
#endif
            SgFile *file = &(project.file(i));
            current_file_id = i;
            current_file = file;

            if (file->mainProgram())
            {
                string fileName = file->filename();
                auto itDep = includeDependencies.find(fileName);

                //TODO: split by functions
                set<string> includedToThisFile;
                if (itDep != includeDependencies.end())
                {
                    for (auto &inclDep : itDep->second)
                    {
                        auto comm = commentsToInclude.find(inclDep);
                        if (comm != commentsToInclude.end())
                            for (auto &allComm : comm->second)
                                includedToThisFile.insert(allComm.second.begin(), allComm.second.end());
                    }
                }

                for (int z = 0; z < parallelRegions.size(); ++z)
                {
                    ParallelRegion *currReg = parallelRegions[z];
                    const DataDirective &dataDirectives = currReg->GetDataDir();
                    const vector<int> &currentVariant = currReg->GetCurrentVariant();
                    const DIST::Arrays<int> &allArrays = currReg->GetAllArrays();
                    const vector<string> distrRules = dataDirectives.GenRule(currentVariant);

                    insertTempalteDeclarationToMainFile(file, dataDirectives, templateDeclInIncludes, distrRules, allArrays, extract, currReg->GetId(), includedToThisFile);
                }
                break;
            }
        }
    }
    else if (curr_regime == DEF_USE_STAGE1)
    {
        if (keepFiles)
            printDefUseSets("_defUseList.txt", defUseByFunctions);        
    }

#if _WIN32
    timeForPass = omp_get_wtime() - timeForPass;
    __spf_print(1, "PROFILE: time for this pass = %f sec\n", timeForPass);
#endif

    return true;
}

static int countMaxValuesForParallelVariants(int &maxDims, int &maxDimsIdx, int &maxDimsIdxReg, vector<vector<int>> &currentVariants)
{
    int lastI;
    if (consoleMode)
    {
        for (int z = 0; z < parallelRegions.size(); ++z)
        {
            DataDirective &dataDirectives = parallelRegions[z]->GetDataDirToModify();
            for (int i = 0; i < dataDirectives.distrRules.size(); ++i)
            {
                const int currDim = (int)dataDirectives.distrRules[0].second.size();
                if (maxDims < currDim)
                {
                    maxDims = currDim;
                    maxDimsIdx = i;
                    maxDimsIdxReg = z;
                }
            }
        }

        for (int z = 0; z < parallelRegions.size(); ++z)
        {
            DataDirective &dataDirectives = parallelRegions[z]->GetDataDirToModify();

            currentVariants[z].resize(dataDirectives.distrRules.size());
            for (int i = 0; i < dataDirectives.distrRules.size(); ++i)
                currentVariants[z][i] = 0;
            parallelRegions[z]->SetCurrentVariant(currentVariants[z]);
        }
        lastI = (int)(parallelRegions[maxDimsIdxReg]->GetDataDir().distrRules[maxDimsIdx].second.size());
    }
    else
        lastI = 1;

    return lastI;
}

static string selectAddNameOfVariant(const int i, int maxDimsIdx, int maxDimsIdxReg, vector<vector<int>> &currentVariants)
{
    char buf[256];
    if (consoleMode)
    {
        sprintf(buf, "v%d", i + 1);
        currentVariants[maxDimsIdxReg][maxDimsIdx] = i;
        if (i != 0)
        {
            for (int p = 0; p < parallelRegions.size(); ++p)
            {
                DataDirective &dataDirectives = parallelRegions[p]->GetDataDirToModify();

                for (int z = 0; z < dataDirectives.distrRules.size(); ++z)
                {
                    if (z == maxDimsIdx && maxDimsIdxReg == p)
                        continue;
                    currentVariants[p][z] = (currentVariants[p][z] + 1) % dataDirectives.distrRules[z].second.size();
                }
            }
        }

        for (int z = 0; z < parallelRegions.size(); ++z)
            parallelRegions[z]->SetCurrentVariant(currentVariants[z]);
    }
    else
        sprintf(buf, "par");
    return buf;
}

static void findFunctionsToInclude(bool needToAddErrors)
{
    if (isDone(FIND_FUNC_TO_INCLUDE))
        return;

    __spf_print(1, "RUN PASS with name FindFunctionsToInclude\n");

    map<string, int> files;
    for (int i = 0; i < project->numberOfFiles(); ++i)
    {
        SgFile *file = &(project->file(i));
        files.insert(make_pair(file->filename(), i));
    }

    int failed = 0;
    if (keepFiles)
        failed += CheckFunctionsToInline(project, files, "_callGraph_withInc.txt", allFuncInfo, loopGraph, SPF_messages, needToAddErrors);
    else
        failed += CheckFunctionsToInline(project, files, NULL, allFuncInfo, loopGraph, SPF_messages, needToAddErrors);

    if (failed > 0 && needToAddErrors)
        throw -5;
}

static SgProject* createProject(const char *proj_name)
{
    sortFilesBySize(proj_name);
    SgProject *project = new SgProject(proj_name);
    addNumberOfFileToAttribute(project);

    ParallelRegion *defaultParRegion = new ParallelRegion(0, "DEFAULT");
    parallelRegions.push_back(defaultParRegion);
    return project;
}

void runPass(const int curr_regime, const char *proj_name, const char *folderName)
{
    // init math functions of FORTRAN
    initIntrinsicFunctionNames();
    initTags();
    InitPassesDependencies(passesDependencies, passesIgnoreStateDone);
    setPassValues();

    if (project == NULL)
        project = createProject(proj_name);
        
    //Run dep passes analysis before main pass
    auto itDep = passesDependencies.find((passes)curr_regime);
    if (itDep != passesDependencies.end())
        for (int k = 0; k < itDep->second.size(); ++k)
            runPass(itDep->second[k], proj_name, folderName);

    switch (curr_regime)
    {
    case FIND_FUNC_TO_INCLUDE:
        findFunctionsToInclude(false);
        break;
    case FILL_PAR_REGIONS_LINES:
        if (runAnalysis(*project, curr_regime, false))
        {
            // init flags for all parallel regions
            if (ALGORITHMS_DONE[0] == NULL)
            {
                for (int i = 0; i < EMPTY_ALGO; ++i)
                {
                    ALGORITHMS_DONE[i] = new int[parallelRegions.size()];
                    for (int k = 0; k < parallelRegions.size(); ++k)
                        ALGORITHMS_DONE[i][k] = 0;
                }
            }
        }
        break;
    case INSERT_PARALLEL_DIRS:
    {
        vector<vector<int>> currentVariants(parallelRegions.size());
        int maxDims = 0;
        int maxDimsIdx = -1;
        int maxDimsIdxReg = -1;

        int lastI = countMaxValuesForParallelVariants(maxDims, maxDimsIdx, maxDimsIdxReg, currentVariants);
        if (genAllVars == 0)
            lastI = 1;

        for (int i = 0; i < lastI; ++i)
        {
            //if specific variant number is requested, skip all others
            if (genSpecificVar >= 0 && i != genSpecificVar) 
                continue;

            string additionalName = selectAddNameOfVariant(i, maxDimsIdx, maxDimsIdxReg, currentVariants);

            runPass(CREATE_PARALLEL_DIRS, proj_name, folderName);

            runAnalysis(*project, INSERT_PARALLEL_DIRS, false, consoleMode ? additionalName.c_str() : NULL, folderName);

            runPass(REVERT_SUBST_EXPR, proj_name, folderName);

            runPass(CREATE_REMOTES, proj_name, folderName);

            runPass(REMOVE_AND_CALC_SHADOW, proj_name, folderName);
            runAnalysis(*project, INSERT_SHADOW_DIRS, false, consoleMode ? additionalName.c_str() : NULL, folderName);

            runPass(REVERT_SPF_DIRS, proj_name, folderName);
            runAnalysis(*project, UNPARSE_FILE, true, additionalName.c_str(), folderName);

            runAnalysis(*project, PREDICT_SCHEME, false, consoleMode ? additionalName.c_str() : NULL, folderName);

            runPass(EXTRACT_PARALLEL_DIRS, proj_name, folderName);
            runPass(EXTRACT_SHADOW_DIRS, proj_name, folderName);
            runPass(REVERSE_CREATED_NESTED_LOOPS, proj_name, folderName);
            runPass(CLEAR_SPF_DIRS, proj_name, folderName);
        }
    }
        break;
    case CREATE_NESTED_LOOPS: //arbu pass in loop_transform.cpp
    case CONVERT_TO_ENDDO:
    case CORRECT_CODE_STYLE:
    case INSERT_INCLUDES:
    case REMOVE_DVM_DIRS:
    case REMOVE_DVM_DIRS_TO_COMMENTS:
        runAnalysis(*project, curr_regime, true, "", folderName);
        break;
    case UNPARSE_FILE:
        if (folderName)
            runAnalysis(*project, curr_regime, true, "", folderName);
        else
            __spf_print(1, "can not run UNPARSE_FILE - folder name is null\n");
        break;
    case CHECK_FUNC_TO_INCLUDE:
        findFunctionsToInclude(true);
        break;
    case SUBST_EXPR_AND_UNPARSE:
        if (folderName)
            runAnalysis(*project, UNPARSE_FILE, true, "", folderName);
        else
            __spf_print(1, "can not run UNPARSE_FILE - folder name is null\n");
        break;
    case PRIVATE_ANALYSIS_SPF:
        if (staticPrivateAnalysis)
            runAnalysis(*project, curr_regime, false);
        break;
    default:
        runAnalysis(*project, curr_regime, false);
        break;
    }
}

int main(int argc, char**argv)
{
#if _WIN32 && _DEBUG
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
#ifdef _ARBU
    SageTransform::SignalHandling(); //init for stacktrace on sigserv on unix
#endif

    try
    {
        setPassValues();
        consoleMode = 1;
        QUALITY = 100;
        printVersion();
        const char *proj_name = "dvm.proj";
        const char *folderName = NULL;

        int curr_regime = EMPTY_PASS;
        int numVar = 0;

        out_free_form = 0; // F90 style out
        bool printText = false;

        for (int i = 0; i < argc; ++i)
        {
            const char *curr_arg = argv[i];
            switch (curr_arg[0])
            {
            case '-':
                if (string(curr_arg) == "-p")
                {
                    i++;
                    proj_name = argv[i];
                }
                else if (string(curr_arg) == "-pass")
                {
                    i++;
                    curr_regime = atoi(argv[i]);
                }
                else if (string(curr_arg) == "-q")
                {
                    i++;
                    QUALITY = atoi(argv[i]);
                    if (QUALITY <= 0 || QUALITY > 100)
                    {
                        __spf_print(1, "QUALITY must be in [0..100] interval, set default value 100");
                        QUALITY = 100;
                    }
                }
                else if (curr_arg[1] == 't')
                {
                    i++;
                    int par = atoi(argv[i]);
                    if (par == 1)
                        curr_regime = UNROLL_LOOPS;
                    else if (par == 2)
                        curr_regime = CONVERT_TO_ENDDO;
                    else if (par == 3)
                        curr_regime = CORRECT_CODE_STYLE;
                    else if (par == 4)
                        curr_regime = LOOP_ANALYZER_DATA_DIST_S2;
                    else if (par == 5)
                        curr_regime = CALL_GRAPH2;
                    else if (par == 6)
                        curr_regime = LOOP_GRAPH;
                    else if (par == 7)
                        curr_regime = LOOP_ANALYZER_COMP_DIST;
                    else if (par == 8)
                        curr_regime = VERIFY_ENDDO;
                    else if (par == 9)
                        curr_regime = VERIFY_INCLUDE;
                    else if (par == 10)
                        curr_regime = FIND_FUNC_TO_INCLUDE;
                    else if (par == 11)
                        curr_regime = CREATE_DISTR_DIRS;
                    else if (par == 12)
                        curr_regime = CREATE_PARALLEL_DIRS;
                    else if (par == 13)
                        curr_regime = INSERT_PARALLEL_DIRS;
                    else if (par == 14)
                        curr_regime = ONLY_ARRAY_GRAPH;
                    else if (par == 15)
                        curr_regime = PRIVATE_ANALYSIS_SPF;
                    else if (par == 16)
                        curr_regime = INSERT_INCLUDES;
                    else if (par == 17)
                        curr_regime = REMOVE_DVM_DIRS;
                    else if (par == 18)
                        curr_regime = CREATE_NESTED_LOOPS;
                }
                else if (curr_arg[1] == 'h')
                    printHelp();
                else if (string(curr_arg) == "-f90")
                    out_free_form = 1;
                /*else if (string(curr_arg) == "-sh")
                    staticShadowAnalysis = 1;*/
                else if (string(curr_arg) == "-priv")
                    staticPrivateAnalysis = 1;
                else if (string(curr_arg) == "-keep")
                    keepFiles = 1;
                else if (string(curr_arg) == "-keepSPF")
                    keepSpfDirs = 1;
                else if (string(curr_arg) == "-keepDVM")
                    keepDvmDirectives = 1;
                else if (string(curr_arg) == "-allVars")
                    genAllVars = 1;
                else if (string(curr_arg) == "-Var" || string(curr_arg) == "-var")
                {
                    //User sees variants starting from 1, internally they start from 0
                    i++;
                    genAllVars = 1;
                    genSpecificVar = atoi(argv[i]) - 1;
                }
                else if (string(curr_arg) == "-F")
                {
                    i++;
                    folderName = argv[i];
                }
                else if (string(curr_arg) == "-print")
                    printText = true;
                else if (string(curr_arg) == "-useDvm")
                    ignoreDvmChecker = 1;
                break;
            default:
                break;
            }
        }

        if (curr_regime == EMPTY_PASS)
            printHelp();

        runPass(curr_regime, proj_name, folderName);
        if (printText)
            runPass(UNPARSE_FILE, proj_name, folderName);

    }
    catch (...)
    {
        printf("exception occurred\n");
    }

    deleteAllAllocatedData();
#if _WIN32 && _DEBUG
    //_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
    //_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
    //_CrtDumpMemoryLeaks();
#endif

    return 0;
}
