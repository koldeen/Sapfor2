#include "Utils/leak_detector.h"

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

#define DEBUG_LVL1 true
#define RELEASE_CANDIDATE _WIN32

#include "ParallelizationRegions/ParRegions_func.h"

#include "Distribution/Distribution.h"
#include "Distribution/GraphCSR.h"
#include "Distribution/Arrays.h"
#include "Distribution/DvmhDirective.h"

#include "CreateInterTree/CreateInterTree.h"

#include "Utils/errors.h"
#include "Utils/SgUtils.h"
#include "LoopConverter/enddo_loop_converter.h"
#include "LoopAnalyzer/loop_analyzer.h"

#include "GraphCall/graph_calls_func.h"
#include "GraphLoop/graph_loops_func.h"
#include "DynamicAnalysis/gCov_parser_func.h"

#include "DirectiveAnalyzer/DirectiveAnalyzer.h"
#include "VerificationCode/verifications.h"
#include "Distribution/CreateDistributionDirs.h"
#include "PrivateAnalyzer/private_analyzer.h"
#include "ExpressionTransform/expr_transform.h"
#include "LoopConverter/loop_transform.h"
#include "LoopConverter/array_assign_to_loop.h"
#include "LoopConverter/private_arrays_breeder.h"
#include "LoopConverter/loops_splitter.h"
#include "Predictor/PredictScheme.h"
#include "ExpressionTransform/expr_transform.h"
#include "SageAnalysisTool/depInterfaceExt.h"

//#include "DEAR/dep_analyzer.h"

#if RELEASE_CANDIDATE
#include "Inliner/inliner.h"
#endif

#ifdef _WIN32
#include "VisualizerCalls/get_information.h"
#endif

#include "dvm.h"
#include "Sapfor.h"
#include "Utils/PassManager.h"

using namespace std;

int PASSES_DONE[EMPTY_PASS];
bool PASSES_DONE_INIT = false;

int *ALGORITHMS_DONE[EMPTY_ALGO] = { NULL };

#include "SapforData.h"

static SgProject *project = NULL;
// for pass temporary functions from DEF_USE_STAGE1 to SUBST_EXPR
static map<string, vector<FuncInfo*>> temporaryAllFuncInfo = map<string, vector<FuncInfo*>>();

void deleteAllAllocatedData(bool enable)
{
    if (enable)
    {
        for (int i = 0; i < parallelRegions.size(); ++i)
            delete parallelRegions[i];
        parallelRegions.clear();

        for (int i = 0; i < subs_parallelRegions.size(); ++i)
            delete subs_parallelRegions[i];
        subs_parallelRegions.clear();

        shortFileNames.clear();
        for (auto &it : allFuncInfo)
            for (auto &toDel : it.second)
                delete toDel;
        allFuncInfo.clear();

        for (auto &it : subs_allFuncInfo)
            for (auto &toDel : it.second)
                delete toDel;
        subs_allFuncInfo.clear();

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
            delete[]ALGORITHMS_DONE[i];
        delete project;

        deleteGraphsKeeper();
        deletePointerAllocatedData();
    }
}

template<typename objT>
static objT& getObjectForFileFromMap(const char *fileName, map<string, objT> &mapObject)
{
    auto it = mapObject.find(fileName);
    if (it == mapObject.end())
        it = mapObject.insert(it, make_pair(fileName, objT()));
    return it->second;
}

static inline void printDvmActiveDirsErrors()
{
    for (auto &err : dvmDirErrors)
    {
        vector<Messages> &currMessages = getObjectForFileFromMap(err.first.c_str(), SPF_messages);
        for (auto &code : err.second)
        {
            __spf_print(1, "  ERROR: at line %d: Active DVM directives are not supported yet\n", code);
            currMessages.push_back(Messages(ERROR, code, "Active DVM directives are not supported yet", 1020));
        }
    }
}

extern "C" void printLowLevelWarnings(const char *fileName, const int line, const char *message, const int group)
{
    vector<Messages> &currM = getObjectForFileFromMap(fileName, SPF_messages);
    __spf_print(1, "WARR: line %d: %s\n", line, message);

    currM.push_back(Messages(WARR, line, message, group));
}

extern "C" void printLowLevelNote(const char *fileName, const int line, const char *message, const int group)
{
    vector<Messages> &currM = getObjectForFileFromMap(fileName, SPF_messages);
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
    else
    {
        if (curr_regime == PRIVATE_ANALYSIS_SPF)
        {
            if (PASSES_DONE[LOOP_ANALYZER_DATA_DIST_S1] == 1)
                return true;
            else if (passesIgnoreStateDone.find((passes)curr_regime) == passesIgnoreStateDone.end())
                return true;
        }
        else
        {
            if (passesIgnoreStateDone.find((passes)curr_regime) == passesIgnoreStateDone.end())
                return true;
        }
    }

    return false;
}

static void updateStatsExprs(const int id, const string &file)
{
    for (SgStatement *st = current_file->firstStatement(); st; st = st->lexNext())
        sgStats[st->thebif] = make_pair(file, id);
    for (SgExpression *ex = current_file->firstExpression(); ex; ex = ex->nextInExprTable())
        sgExprs[ex->thellnd] = make_pair(file, id);
}

static inline void unparseProjectIfNeed(SgFile *file, const int curr_regime, const bool need_to_unparse,
                                        const char *newVer, const char *folderName, const char *file_name,
                                        set<string> &allIncludeFiles)
{
    if (curr_regime == CORRECT_CODE_STYLE || need_to_unparse)
    {
        restoreCorrectedModuleProcNames(file);

        if (curr_regime == CORRECT_CODE_STYLE && newVer == NULL)
            newVer = "";

        /*if (curr_regime == CORRECT_CODE_STYLE)
            groupDeclarations(file);*/

        if (newVer == NULL)
        {
            __spf_print(1, "  ERROR: null file addition name\n");
            getObjectForFileFromMap(file_name, SPF_messages).push_back(Messages(ERROR, 1, "Internal error during unparsing process has occurred", 2007));
            throw(-1);
        }

        string fout_name = "";
        if (folderName == NULL)
            fout_name = OnlyName(file_name) + "_" + newVer + "." + OnlyExt(file_name);
        else
        {
            if (strlen(newVer) == 0)
                fout_name = folderName + string("/") + OnlyName(file_name) + "." + OnlyExt(file_name);
            else
                fout_name = folderName + string("/") + OnlyName(file_name) + "_" + newVer + "." + OnlyExt(file_name);
        }

        __spf_print(DEBUG_LVL1, "  Unparsing to <%s> file\n", fout_name.c_str());
        if (curr_regime == INSERT_INCLUDES)
        {
            __spf_print(1, "  try to find file <%s>\n", file_name);
            __spf_print(1, "  in set %d, result %d\n", (int)filesToInclude.size(), filesToInclude.find(file_name) != filesToInclude.end());
        }
        if (curr_regime == INSERT_INCLUDES && filesToInclude.find(file_name) != filesToInclude.end())
        {
            FILE *fOut = fopen(fout_name.c_str(), "w");
            if (fOut)
            {
                file->unparse(fOut);
                fclose(fOut);
            }
            else
            {
                __spf_print(1, "ERROR: can not create file '%s'\n", fout_name.c_str());
                getObjectForFileFromMap(file_name, SPF_messages).push_back(Messages(ERROR, 1, "Internal error during unparsing process has occurred", 2007));
                throw(-1);
            }
        }
        else
        {
            //TODO: add freeForm for each file
            removeIncludeStatsAndUnparse(file, file_name, fout_name.c_str(), allIncludeFiles, out_free_form == 1);

            // copy includes that have not changed
            if (folderName != NULL)
                copyIncludes(allIncludeFiles, commentsToInclude, folderName, curr_regime == REMOVE_DVM_DIRS ? 1 : curr_regime == REMOVE_DVM_DIRS_TO_COMMENTS ? 2 : 0);
        }
    }
}

pair<SgFile*, SgStatement*> currProcessing;
static bool runAnalysis(SgProject &project, const int curr_regime, const bool need_to_unparse, const char *newVer = NULL, const char *folderName = NULL)
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

    auto toSendStrMessage = string(passNames[curr_regime]);
#ifdef _WIN32
    sendMessage_1lvl(wstring(L"выполняется проход '") + wstring(toSendStrMessage.begin(), toSendStrMessage.end()) + L"'");
#endif

    const int n = project.numberOfFiles();
    bool verifyOK = true;
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
    SgStatement::cleanStatsByLine();
    SgStatement::cleanParentStatsForExprs();

    for (int i = n - 1; i >= 0; --i)
    {
        SgFile *file = &(project.file(i));
        current_file_id = i;
        current_file = file;
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

        toSendStrMessage = file->filename();
#ifdef _WIN32
        sendMessage_2lvl(wstring(L"обработка файла '") + wstring(toSendStrMessage.begin(), toSendStrMessage.end()) + L"'");
#endif
        currProcessing.first = file; currProcessing.second = NULL;

        const char *file_name = file->filename();
        __spf_print(DEBUG_LVL1, "  Analyzing: %s\n", file_name);

        if (curr_regime == CONVERT_TO_ENDDO)
            ConverToEndDo(file, getObjectForFileFromMap(file_name, SPF_messages));
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
                /*if (curr_regime == LOOP_ANALYZER_DATA_DIST_S1)
                    states.push_back(new SapforState());*/

                loopAnalyzer(file, parallelRegions, createdArrays, getObjectForFileFromMap(file_name, SPF_messages), DATA_DISTR, 
                             allFuncInfo, declaratedArrays, declaratedArraysSt, arrayLinksByFuncCalls,
                             &(loopGraph.find(file_name)->second));
            }
            catch (...)
            {
                internalExit = 1;
            }
        }
        else if (curr_regime == LOOP_ANALYZER_COMP_DIST)
        {
            auto itFound = loopGraph.find(file_name);
            loopAnalyzer(file, parallelRegions, createdArrays, getObjectForFileFromMap(file_name, SPF_messages), COMP_DISTR, 
                         allFuncInfo, declaratedArrays, declaratedArraysSt, arrayLinksByFuncCalls,
                         &(itFound->second));

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
            checkForRecursion(file, allFuncInfo, getObjectForFileFromMap(file_name, SPF_messages));
        else if (curr_regime == LOOP_GRAPH)        
            loopGraphAnalyzer(file, getObjectForFileFromMap(file_name, loopGraph));
        else if (curr_regime == VERIFY_ENDDO)
        {
            bool res = EndDoLoopChecker(file, getObjectForFileFromMap(file_name, SPF_messages));
            verifyOK &= res;
        }
        else if (curr_regime == VERIFY_INCLUDE)
        {
            bool res = IncludeChecker(file, file_name, getObjectForFileFromMap(file_name, SPF_messages));
            verifyOK &= res;
        }
        else if (curr_regime == VERIFY_DVM_DIRS)
        {
            bool res = DvmDirectiveChecker(file, dvmDirErrors, keepDvmDirectives, ignoreDvmChecker);
            verifyOK &= res;
            if (dvmDirErrors.size() != 0 && ignoreDvmChecker == 0)
                printDvmActiveDirsErrors();
        }
        else if (curr_regime == VERIFY_EQUIVALENCE)
        {
            bool res = EquivalenceChecker(file, file_name, parallelRegions, SPF_messages);
            verifyOK &= res;
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
                vector<pair<DIST::Array*, const DistrVariant*>> currentVar;
                for (int z1 = 0; z1 < currentVariant.size(); ++z1)
                    currentVar.push_back(make_pair(tmp[z1].first, &tmp[z1].second[currentVariant[z1]]));

                selectParallelDirectiveForVariant(file, parallelRegions[z], reducedG, allArrays, itFound->second, currentVar,
                                                  dataDirectives.alignRules, toInsert, parallelRegions[z]->GetId(), arrayLinksByFuncCalls,
                                                  depInfoForLoopGraph, getObjectForFileFromMap(file_name, SPF_messages));

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
            
            insertDirectiveToFile(file, file_name, createdDirectives[file_name], extract, getObjectForFileFromMap(file_name, SPF_messages));
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
                                         allArrays, reducedG, commentsToInclude, templateDeclInIncludes, extract, getObjectForFileFromMap(file_name, SPF_messages),
                                         arrayLinksByFuncCalls, currReg->GetId());
            }

            if (curr_regime == EXTRACT_PARALLEL_DIRS)
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

                insertShadowSpecToFile(file, file_name, distrArrays, reducedG, commentsToInclude, extract, getObjectForFileFromMap(file_name, SPF_messages), declaratedArrays);
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
                    if (isSPF_stat(st)) // except sapfor parallel regions and if attributes dont move
                    {
                        if (st->variant() != SPF_PARALLEL_REG_DIR && st->variant() != SPF_END_PARALLEL_REG_DIR)
                        {
                            if (getAttributes<SgStatement*, SgStatement*>(st->lexNext(), set<int>{ SPF_ANALYSIS_DIR, SPF_PARALLEL_DIR, SPF_TRANSFORM_DIR }).size() > 0)
                                toDel.push_back(st);
                        }
                    }
                }

                for (auto &elem : toDel)
                    elem->deleteStmt();
            }
            else
                __spf_print(1, "   ignore CLEAR_SPF_DIRS\n");
        }
        else if (curr_regime == PREPROC_SPF)
        {
            bool noError = preprocess_spf_dirs(file, commonBlocks, getObjectForFileFromMap(file_name, SPF_messages));
            if (!noError)
                internalExit = 1;
        }
        else if (curr_regime == CHECK_PAR_REG_DIR)
        {
            bool noError = check_par_reg_dirs(file, getObjectForFileFromMap(file_name, SPF_messages));
            if (!noError)
                internalExit = 1;
        }
        else if (curr_regime == PREPROC_ALLOCATES)
            preprocess_allocates(file);
        else if (curr_regime == CORRECT_VAR_DECL)
            VarDeclCorrecter(file);
        else if (curr_regime == CREATE_REMOTES)
            loopAnalyzer(file, parallelRegions, createdArrays, getObjectForFileFromMap(file_name, SPF_messages), REMOTE_ACC, 
                         allFuncInfo, declaratedArrays, declaratedArraysSt, arrayLinksByFuncCalls, 
                         &(loopGraph.find(file_name)->second));
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
            arrayAccessAnalyzer(file, getObjectForFileFromMap(file_name, SPF_messages), declaratedArrays, PRIVATE_STEP4);
        else if (curr_regime == FILL_PAR_REGIONS_LINES)
            fillRegionLines(file, parallelRegions, &(loopGraph[file_name]), &(allFuncInfo[file_name]));
        else if (curr_regime == FILL_COMMON_BLOCKS)
        {
            // fillCommonBlocks(file, commonBlocks);
            vector<pair<SgStatement*, SgStatement*>> lines; // lines for getCommonBlocksRef()

            for (int i = 0; i < file->numberOfFunctions(); ++i)
                lines.push_back(make_pair(file->functions(i), file->functions(i)->lastNodeOfStmt()));

            // try to fill from BLOCK DATA
            SgStatement *st = file->firstStatement();

            while (st)
            {
                if (st->variant() == BLOCK_DATA) //BLOCK_DATA header
                {
                    lines.push_back(make_pair(st, st->lastNodeOfStmt()));
                    st = st->lastNodeOfStmt();
                }
                st = st->lexNext();
            }

            for (auto &startEnd : lines)
            {
                map<string, vector<SgExpression*>> commonBlocksRef;

                getCommonBlocksRef(commonBlocksRef, startEnd.first, startEnd.second);

                // adding found common variables
                for (auto &commonBlockRef : commonBlocksRef)
                {
                    auto it = commonBlocks.find(commonBlockRef.first);
                    if (it == commonBlocks.end())
                    {
                        CommonBlock newCommonBlock(commonBlockRef.first, vector<Variable>());
                        it = commonBlocks.insert(it, make_pair(commonBlockRef.first, newCommonBlock));
                    }

                    int position = 0;
                    for (auto &commonExp : commonBlockRef.second)
                    {
                        vector<pair<SgSymbol*, int>> newVariables;
                        for (SgExpression *currCommon = commonExp->lhs(); currCommon; currCommon = currCommon->rhs())
                            newVariables.push_back(make_pair(currCommon->lhs()->symbol(), position++));

                        it->second.addVariables(file, startEnd.first, newVariables);
                    }
                }
            }
        }
        else if (curr_regime == VERIFY_COMMON)
        {
            bool res = CommonBlockChecker(file, file_name, commonBlocks, getObjectForFileFromMap(file_name, SPF_messages));
            verifyOK &= res;
        }
        else if (curr_regime == LOOP_DATA_DEPENDENCIES)
            doDependenceAnalysisOnTheFullFile(file, 1, 1, 1);
        else if (curr_regime == REMOVE_DVM_DIRS || curr_regime == REMOVE_DVM_DIRS_TO_COMMENTS)
            removeDvmDirectives(file, curr_regime  == REMOVE_DVM_DIRS_TO_COMMENTS);
        else if (curr_regime == SUBST_EXPR)
        {
            expressionAnalyzer(file, defUseByFunctions, commonBlocks, temporaryAllFuncInfo, subs_parallelRegions);
            // analyze again for substituted expressions
            arrayAccessAnalyzer(file, getObjectForFileFromMap(file_name, SPF_messages), declaratedArrays, PRIVATE_STEP4);
        }
        else if (curr_regime == REVERT_SUBST_EXPR)
            revertReplacements(file->filename(), true);
        else if (curr_regime == CREATE_NESTED_LOOPS)
        {
            auto itFound = loopGraph.find(file_name);
            if (itFound != loopGraph.end())
                for (int i = 0; i < itFound->second.size(); ++i)
                    createNestedLoops(itFound->second[i], depInfoForLoopGraph, getObjectForFileFromMap(file_name, SPF_messages));
        }
        else if (curr_regime == GET_ALL_ARRAY_DECL)
            getAllDeclaratedArrays(file, declaratedArrays, declaratedArraysSt, getObjectForFileFromMap(file_name, SPF_messages), subs_parallelRegions);
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
            devourShadowByRemote(file, arrayLinksByFuncCalls);
        else if (curr_regime == TRANSFORM_SHADOW_IF_FULL)
            transformShadowIfFull(file, arrayLinksByFuncCalls);
        else if (curr_regime == MACRO_EXPANSION)
            doMacroExpand(file, getObjectForFileFromMap(file_name, SPF_messages));    
        else if (curr_regime == REVERSE_CREATED_NESTED_LOOPS)
        {
            auto itFound = loopGraph.find(file_name);
            if (itFound != loopGraph.end())
                reverseCreatedNestedLoops(file->filename(), itFound->second);
        }
        else if (curr_regime == CONVERT_ASSIGN_TO_LOOP)
            convertFromAssignToLoop(file, getObjectForFileFromMap(file_name, SPF_messages));
        else if (curr_regime == CONVERT_LOOP_TO_ASSIGN)
            restoreAssignsFromLoop(file);
        else if (curr_regime == PREDICT_SCHEME)
            processFileToPredict(file, getObjectForFileFromMap(file_name, allPredictorStats));
        else if (curr_regime == DEF_USE_STAGE1)
            constructDefUseStep1(file, defUseByFunctions, temporaryAllFuncInfo);
        else if (curr_regime == DEF_USE_STAGE2)
            constructDefUseStep2(file, defUseByFunctions);
        else if (curr_regime == RESTORE_LOOP_FROM_ASSIGN)
            restoreConvertedLoopForParallelLoops(file);
        else if (curr_regime == RESTORE_LOOP_FROM_ASSIGN_BACK)
            restoreConvertedLoopForParallelLoops(file, true);
        else if (curr_regime == SHADOW_GROUPING)
        {
            // TODO: temporary disabled
            /*
            //TODO for all parallel regions
            if (parallelRegions.size() == 1 && parallelRegions[0]->GetName() == "DEFAULT")
            {
                for (int z = 0; z < parallelRegions.size(); ++z)
                    GroupShadowStep1(file, allFuncInfo.find(file_name)->second, parallelRegions[z]->GetAllArraysToModify());
            }*/
        }
        else if (curr_regime == FILL_PARALLEL_REG_FOR_SUBS)
        {
            auto it = subs_allFuncInfo.find(file_name);
            if (it == subs_allFuncInfo.end())
                functionAnalyzer(file, subs_allFuncInfo, true);

            fillRegionLines(file, subs_parallelRegions);
        }
        else if (curr_regime == ADD_TEMPL_TO_USE_ONLY)
            fixUseOnlyStmt(file, parallelRegions);
        else if (curr_regime == GCOV_PARSER)
            parse_gcovfile(file, file_name, getObjectForFileFromMap(file_name, gCovInfo));
        else if(curr_regime == PRIVATE_ARRAYS_BREEDING)
        {
            auto founded = loopGraph.find(file->filename());
            if(founded != loopGraph.end())
                breedArrays(file, loopGraph.find(file->filename())->second);
        }
        else if(curr_regime == LOOPS_SPLITTER)
        {
            auto founded = loopGraph.find(file->filename());
            if (founded != loopGraph.end())
                splitLoops(file, loopGraph.find(file->filename())->second);
        }
        else if (curr_regime == CREATE_INTER_TREE)
        {
            createInterTree(file, getObjectForFileFromMap(file_name, intervals));
            assignCallsToFile(file_name, getObjectForFileFromMap(file_name, intervals));
        }
        else if (curr_regime == INSERT_INTER_TREE)
            insertIntervals(file, getObjectForFileFromMap(file_name, intervals));

        unparseProjectIfNeed(file, curr_regime, need_to_unparse, newVer, folderName, file_name, allIncludeFiles);

    } // end of FOR by files
        
    if (internalExit != 0)
        throw -1;


#ifdef _WIN32
    sendMessage_2lvl(wstring(L""));
#endif
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

                        auto messages = getObjectForFileFromMap(fileName.c_str(), SPF_messages);
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
            G.ChangeQuality(QUALITY, SPEED);

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

                if (parallelRegions[z]->GetId() == 0) // DEFAULT
                {
                    char buf[256];
                    sprintf(buf, "  Can not find arrays or free loops for distribution in this project");

                    for (auto &funcByFile : allFuncInfo)
                    {
                        vector<Messages> &fileM = getObjectForFileFromMap(funcByFile.first.c_str(), SPF_messages);
                        for (auto &func : funcByFile.second)
                        {
                            auto stat = func->funcPointer->GetOriginal();
                            if (stat->variant() == PROG_HEDR)
                                fileM.push_back(Messages(ERROR, stat->lineNumber(), buf, 3010));
                        }
                    }
                }
                else
                {
                    char buf[256];
                    sprintf(buf, "  Can not find arrays or free loops for distribution in this region");

                    for (auto &linesByFile : parallelRegions[z]->GetAllLines())
                    {
                        vector<Messages> &fileM = getObjectForFileFromMap(linesByFile.first.c_str(), SPF_messages);
                        for (auto &lines : linesByFile.second)
                            if (!lines.isImplicit())
                                fileM.push_back(Messages(ERROR, lines.lines.first, buf, 3010));
                    }
                }
                idxToDel.insert(z);
            }
        }

        vector<ParallelRegion*> newParReg;
        for (int z = 0; z < parallelRegions.size(); ++z)
        {
            if (idxToDel.find(z) != idxToDel.end())
            {
                ParallelRegion *regToDel = parallelRegions[z];                
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

        if (parallelRegions.size() == 0)
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
    }
    else if (curr_regime == CALL_GRAPH)
    {    
        if (keepFiles)
        {
            map<string, CallV> V;
            vector<string> E;
            CreateCallGraphViz("_callGraph.txt", allFuncInfo, V, E);
        }
        findDeadFunctionsAndFillCallTo(allFuncInfo, SPF_messages);
        createLinksBetweenFormalAndActualParams(allFuncInfo, arrayLinksByFuncCalls, declaratedArrays);
        updateFuncInfo(allFuncInfo);

        if (keepFiles)
            CreateFuncInfo("_funcInfo.txt", allFuncInfo);
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
             curr_regime == VERIFY_DVM_DIRS ||
             curr_regime == VERIFY_EQUIVALENCE ||
             curr_regime == VERIFY_COMMON)
    {
        if (verifyOK == false)
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
                                    int fileId = SgFile::switchToFile(elem.first);
                                    if (fileId != -1)
                                    {
                                        SgFile *tmpfile = &(CurrentProject->file(fileId));
                                        current_file = tmpfile;
                                        current_file_id = fileId;
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
        fillRegionLinesStep2(parallelRegions, allFuncInfo, &loopGraph);

        if (ignoreDvmChecker == 1)
        {
            if (parallelRegions.size() == 1 && parallelRegions[0]->GetName() == "DEFAULT" && dvmDirErrors.size())
            {
                printDvmActiveDirsErrors();
                throw(-1);
            }
        }

        checkCountOfIter(loopGraph, allFuncInfo, SPF_messages);
        if (keepFiles)
        {
            printLoopGraph("_loopGraph_with_reg.txt", loopGraph, true);
            printParalleRegions("_parallelRegions.txt", parallelRegions);
        }
    }
    else if (curr_regime == FILL_PAR_REGIONS)
    {
        fillRegionFunctions(parallelRegions, allFuncInfo);
        fillRegionArrays(parallelRegions, allFuncInfo, commonBlocks);

        bool noError = checkRegions(parallelRegions, SPF_messages);
        if (!noError)
            internalExit = 1;

        if (keepFiles)
        {
            int err = printCheckRegions("_checkRegions.txt", parallelRegions);
            if (err == -1)
                internalExit = 1;
            err = printCheckRegions(NULL, parallelRegions);
            if (err == -1)
                internalExit = 1;
        }
    }
    else if (curr_regime == RESOLVE_PAR_REGIONS)
    {
        bool error = resolveParRegions(parallelRegions, allFuncInfo, SPF_messages);
        if (error)
            internalExit = 1;
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
    else if (curr_regime == LOOP_ANALYZER_DATA_DIST_S1)
    {
        for (int z = 0; z < parallelRegions.size(); ++z)
        {
            ParallelRegion *currReg = parallelRegions[z];
            auto graph = currReg->GetGraph();
            __spf_print(1, "STAT: par reg %s: requests %d, miss %d, V = %d, E = %d\n", currReg->GetName().c_str(), graph.getCountOfReq(), graph.getCountOfMiss(), graph.GetNumberOfV(), graph.GetNumberOfE());
            printf("STAT: par reg %s: requests %d, miss %d, V = %d, E = %d\n", currReg->GetName().c_str(), graph.getCountOfReq(), graph.getCountOfMiss(), graph.GetNumberOfV(), graph.GetNumberOfE());
        }
    }
    else if (curr_regime == PRINT_PAR_REGIONS_ERRORS)
    {
        if (parallelRegions.size())
        {
            __spf_print(1, "Regions by id:\n");
            for (auto &reg : parallelRegions)
                __spf_print(1, "  %d: %s\n", reg->GetId(), reg->GetName().c_str());

            map<string, FuncInfo*> funcMap;
            createMapOfFunc(allFuncInfo, funcMap);

            string message;
            string conflicts;
            for (auto &nameFunc : funcMap)
            {
                auto func = nameFunc.second;
                if (func->inRegion)
                {
                    message += "  func '";
                    message += nameFunc.first;
                    message += "':";
                    for (auto &regionId : func->callRegions)
                    {
                        message += ' ';
                        message += to_string(regionId);
                    }
                    message += '\n';

                    if (func->callRegions.size() > 1)
                    {
                        conflicts += "  '";
                        conflicts += nameFunc.first;
                        conflicts += "'\n";
                    }
                }
            }

            if (message.size())
                __spf_print(1, "Functions called by regions with ids:\n%s", message.c_str());

            if (conflicts.size())
                __spf_print(1, "Croseed functions (conflicts):\n%s", conflicts.c_str());
        }
        /*
        if (parallelRegions.size() > 1)
        {
            map<string, vector<ParallelRegion*>> crossedByFunction;
            for (auto &reg : parallelRegions)
            {
                auto crossed = reg->GetCrossedFuncs();
                for (auto &crossedF : crossed)
                    crossedByFunction[crossedF->funcName].push_back(reg);
            }

            for (auto &crByF : crossedByFunction)
            {
                if (crByF.second.size() > 1)
                {
                    string regions = "";
                    for (auto &reg : crByF.second)
                        regions += "'" + reg->GetName() + "' ";
                    __spf_print(1, "parallel regions %swere crossed by function '%s'\n", regions.c_str(), crByF.first.c_str());

                    string message;
                    __spf_printToBuf(message, "parallel regions %swere crossed by function '%s'", regions.c_str(), crByF.first.c_str());

                    auto lines = crByF.second[0]->GetAllLines();
                    bool ok = false;
                    for (auto &linePair : lines)
                    {
                        for (auto &line : linePair.second)
                        {
                            if (line.stats.first && line.stats.second)
                            {
                                getObjectForFileFromMap(linePair.first.c_str(), SPF_messages).push_back(Messages(ERROR, line.lines.first, message, 3012));
                                internalExit = 1;
                                ok = true;
                                break;
                            }
                        }
                        if (ok)
                            break;
                    }
                    if (ok == false)
                        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
                }
            }
        }
        */
    }
    else if (curr_regime == FILL_PARALLEL_REG_FOR_SUBS)
    {
        findDeadFunctionsAndFillCallTo(subs_allFuncInfo, SPF_messages, true);
        fillRegionLinesStep2(subs_parallelRegions, subs_allFuncInfo);
        clearRegionStaticData();
    }
    else if (curr_regime == GET_ALL_ARRAY_DECL)
    {
        for (auto array : declaratedArrays)
        {
            if (array.second.first->GetRgionsName().size() == 0)
                array.second.first->SetNonDistributeFlag(DIST::NO_DISTR);
        }
    }

#if _WIN32
    timeForPass = omp_get_wtime() - timeForPass;
    __spf_print(1, "PROFILE: time for this pass = %f sec\n", timeForPass);
#endif

    if (internalExit != 0)
        throw -1;

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
        sprintf(buf, "");  //sprintf(buf, "par");
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
        failed += CheckFunctionsToInline(project, files, "_callGraph_withInc.txt", allFuncInfo, loopGraph, SPF_messages, needToAddErrors, arrayLinksByFuncCalls, parallelRegions);
    else
        failed += CheckFunctionsToInline(project, files, NULL, allFuncInfo, loopGraph, SPF_messages, needToAddErrors, arrayLinksByFuncCalls, parallelRegions);

    if (failed > 0 && needToAddErrors)
        throw -5;
}

static SgProject* createProject(const char *proj_name)
{
    sortFilesBySize(proj_name);
    SgProject *project = new SgProject(proj_name);
    addNumberOfFileToAttribute(project);

    parallelRegions.push_back(new ParallelRegion(0, "DEFAULT"));
    subs_parallelRegions.push_back(new ParallelRegion(0, "DEFAULT"));

    for (int z = 0; z < project->numberOfFiles(); ++z)
        correctModuleProcNames(&(project->file(z)));
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
            runPass(SHADOW_GROUPING, proj_name, folderName);
            runPass(TRANSFORM_SHADOW_IF_FULL, proj_name, folderName);

            runAnalysis(*project, INSERT_SHADOW_DIRS, false, consoleMode ? additionalName.c_str() : NULL, folderName);

            runPass(REVERT_SPF_DIRS, proj_name, folderName);
            runPass(RESTORE_LOOP_FROM_ASSIGN, proj_name, folderName);
            runPass(ADD_TEMPL_TO_USE_ONLY, proj_name, folderName);

            runAnalysis(*project, PREDICT_SCHEME, false);
            
            runAnalysis(*project, UNPARSE_FILE, true, additionalName.c_str(), folderName);

            runPass(EXTRACT_PARALLEL_DIRS, proj_name, folderName);
            runPass(EXTRACT_SHADOW_DIRS, proj_name, folderName);
            runPass(REVERSE_CREATED_NESTED_LOOPS, proj_name, folderName);
            runPass(CLEAR_SPF_DIRS, proj_name, folderName);
            runPass(RESTORE_LOOP_FROM_ASSIGN_BACK, proj_name, folderName);

            //clear shadow grouping
            for (auto &funcbyFile : allFuncInfo)
            {
                for (auto &func : funcbyFile.second)
                {
                    func->shadowTree = NULL;
                    for (auto &sh : func->allShadowNodes)
                        delete sh.second;
                    func->allShadowNodes.clear();
                }
            }
        }
    }
        break;
    case CREATE_NESTED_LOOPS:
    case CONVERT_TO_ENDDO:
    case CORRECT_CODE_STYLE:
    case INSERT_INCLUDES:
    case REMOVE_DVM_DIRS:
    case REMOVE_DVM_DIRS_TO_COMMENTS:
    case PRIVATE_ARRAYS_BREEDING:
    case INSERT_INTER_TREE:
        runAnalysis(*project, curr_regime, true, "", folderName);
        break;
    case INLINE_PROCEDURES:
        runAnalysis(*project, curr_regime, false);
        if (folderName)
            runAnalysis(*project, UNPARSE_FILE, true, "", folderName);
        else
            __spf_print(1, "can not run UNPARSE_FILE - folder name is null\n");
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
    case RESOLVE_PAR_REGIONS:
        runAnalysis(*project, curr_regime, false);
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

int main(int argc, char **argv)
{
#if _WIN32 && _DEBUG
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

    int leakMemDump = 0;
#if _WIN32
    bool withDel = true;
#else
    bool withDel = false;
#endif
    try
    {
        setPassValues();
        consoleMode = 1;
        QUALITY = 100;
        SPEED = 100;
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
                else if (string(curr_arg) == "-q1")
                {
                    i++;
                    QUALITY = atoi(argv[i]);
                    if (QUALITY <= 0 || QUALITY > 100)
                    {
                        __spf_print(1, "QUALITY must be in [0..100] interval, set default value 100");
                        QUALITY = 100;
                    }
                }
                else if (string(curr_arg) == "-q2")
                {
                    i++;
                    SPEED = atoi(argv[i]);
                    if (SPEED <= 0 || SPEED > 100)
                    {
                        __spf_print(1, "SPEED must be in [0..100] interval, set default value 100");
                        SPEED = 100;
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
                else if (string(curr_arg) == "-leak")
                    leakMemDump = 1;
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
                else if (string(curr_arg) == "-delLeak")
                    withDel = true;
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
                else if (string(curr_arg) == "-passTree")
                    InitPassesDependencies(passesDependencies, passesIgnoreStateDone, true);
                else if (string(curr_arg) == "-ver" || string(curr_arg) == "-Ver")
                    exit(0);
                else if (string(curr_arg) == "-freeLoops")
                    parallizeFreeLoops = 1;
                else if (string(curr_arg) == "-autoArray")
                    parallizeFreeLoops = 1;
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
        printStackTrace();
        printf("exception occurred\n");
    }

    deleteAllAllocatedData(withDel);
#if _WIN32 && _DEBUG
    if (leakMemDump)
    {
        _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
        _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
        _CrtDumpMemoryLeaks();
    }
#endif

    return 0;
}
