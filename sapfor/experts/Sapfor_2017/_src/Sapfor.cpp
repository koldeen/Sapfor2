﻿#include "Utils/leak_detector.h"

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
#include <chrono>
#if _WIN32 && _DEBUG
#include <crtdbg.h>
#endif

#define DEBUG_LVL1 true
#define RELEASE_CANDIDATE 0

#include "ParallelizationRegions/ParRegions_func.h"
#include "ParallelizationRegions/resolve_par_reg_conflicts.h"
#include "ParallelizationRegions/expand_extract_reg.h"

#include "Distribution/Distribution.h"
#include "Distribution/GraphCSR.h"
#include "Distribution/Arrays.h"
#include "Distribution/DvmhDirective.h"

#include "CreateInterTree/CreateInterTree.h"

#include "Utils/errors.h"
#include "Utils/SgUtils.h"
#include "LoopAnalyzer/loop_analyzer.h"

#include "GraphCall/graph_calls_func.h"
#include "GraphLoop/graph_loops_func.h"
#include "DynamicAnalysis/gCov_parser_func.h"
#include "DynamicAnalysis/createParallelRegions.h"

#include "DirectiveAnalyzer/DirectiveAnalyzer.h"
#include "VerificationCode/verifications.h"
#include "Distribution/CreateDistributionDirs.h"
#include "PrivateAnalyzer/private_analyzer.h"
#include "ExpressionTransform/expr_transform.h"

#include "Predictor/PredictScheme.h"
#include "Predictor/PredictorModel.h"
#include "ExpressionTransform/expr_transform.h"
#include "SageAnalysisTool/depInterfaceExt.h"
#include "DvmhRegions/DvmhRegionInserter.h"
#include "DvmhRegions/LoopChecker.h"
#include "DvmhRegions/ReadWriteAnalyzer.h"
#include "Utils/utils.h"
#include "LoopAnalyzer/directive_creator.h"
#include "Distribution/Array.h"
#include "VisualizerCalls/get_information.h"
#include "VisualizerCalls/SendMessage.h"

#include "Transformations/enddo_loop_converter.h"
#include "Transformations/loop_transform.h"
#include "Transformations/array_assign_to_loop.h"
#include "Transformations/private_arrays_breeder.h"
#include "Transformations/loops_splitter.h"
#include "Transformations/loops_combiner.h"
#include "Transformations/uniq_call_chain_dup.h"
#include "Transformations/checkpoints.h"
#include "Transformations/swap_array_dims.h"
#include "Transformations/function_purifying.h"

#include "Inliner/inliner.h"

#include "dvm.h"
#include "Sapfor.h"
#include "Utils/PassManager.h"

using namespace std;
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::milliseconds;

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
        for (auto& toDel : declaredArrays)
        {
            if (!toDel.second.first->IsTemplate())
            {
                delete toDel.second.first;
                delete toDel.second.second;
            }
        }
        declaredArrays.clear();

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

        commentsToInclude.clear();
        SPF_messages.clear();

        for (int i = 0; i < EMPTY_ALGO; ++i)
            delete[]ALGORITHMS_DONE[i];
        delete project;

        GraphsKeeper::deleteGraphsKeeper();
        deletePointerAllocatedData();
    }
}

static inline void printDvmActiveDirsErrors()
{
    for (auto &err : dvmDirErrors)
    {
        vector<Messages> &currMessages = getObjectForFileFromMap(err.first.c_str(), SPF_messages);
        for (auto &code : err.second)
        {
            __spf_print(1, "  ERROR: at line %d: Active DVM directives are not supported yet\n", code);
            currMessages.push_back(Messages(ERROR, code, R53, L"Active DVM directives are not supported (turn on DVM-directive support option)", 1020));
        }
    }
}

extern "C" void printLowLevelWarnings(const char *fileName, const int line, const wchar_t* messageR, const char* messageE, const int group)
{
    vector<Messages> &currM = getObjectForFileFromMap(fileName, SPF_messages);
    __spf_print(1, "WARR: line %d: %s\n", line, messageE);
	if (!messageE)
		printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

	if (messageR)
		currM.push_back(Messages(WARR, line, messageR, to_wstring(messageE), group));
	else
		currM.push_back(Messages(WARR, line, to_wstring(messageE), to_wstring(messageE), group));
}

extern "C" void printLowLevelNote(const char *fileName, const int line, const wchar_t *messageR, const char *messageE, const int group)
{
    vector<Messages> &currM = getObjectForFileFromMap(fileName, SPF_messages);
    __spf_print(1, "NOTE: line %d: %s\n", line, messageE);
    currM.push_back(Messages(NOTE, line, messageR, to_wstring(messageE), group));
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
    auto node1 = current_file->firstStatement();

    for (; node1; node1 = node1->lexNext())
        sgStats[node1->thebif] = make_pair(file, id);
    
    auto node = current_file->firstStatement()->thebif;
    for (; node; node = node->thread)
        if (sgStats.find(node) == sgStats.end())
            sgStats[node] = make_pair(file, id);

    for (SgExpression *ex = current_file->firstExpression(); ex; ex = ex->nextInExprTable())
        sgExprs[ex->thellnd] = make_pair(file, id);
}

static map<string, int> filesNameWithoutExt;
static string unparseProjectIfNeed(SgFile* file, const int curr_regime, const bool need_to_unparse,
                                   const char* newVer, const char* folderName, set<string>& allIncludeFiles, bool toString = false)
{
    string unparseToBuf = "";
    const char* file_name = file->filename();
    if (curr_regime == CORRECT_CODE_STYLE || need_to_unparse)
    {
        restoreCorrectedModuleProcNames(file);

        if (keepSpfDirs)
            revertion_spf_dirs(file, declaredArrays, declaratedArraysSt);
        else
        {
            vector<SgStatement*> toDel;
            for (SgStatement* st = file->firstStatement(); st; st = st->lexNext())
                if (isSPF_stat(st)) // except sapfor parallel regions and if attributes dont move
                    if (st->variant() != SPF_PARALLEL_REG_DIR && st->variant() != SPF_END_PARALLEL_REG_DIR)
                        toDel.push_back(st);

            for (auto& elem : toDel)
                elem->deleteStmt();
        }

        if (curr_regime == CORRECT_CODE_STYLE && newVer == NULL)
            newVer = "";

        /*if (curr_regime == CORRECT_CODE_STYLE)
            groupDeclarations(file);*/

        if (newVer == NULL)
        {
            __spf_print(1, "  ERROR: null file addition name\n");
            getObjectForFileFromMap(file_name, SPF_messages).push_back(Messages(ERROR, 1, R102, L"Internal error during unparsing process has occurred", 2007));
            throw(-1);
        }

        string fout_name = "";
        const string outExt = (out_free_form == 1) ? "f90" : "for";

        string fPartOfName = OnlyName(file_name);
        if (!toString)
            if (filesNameWithoutExt.find(fPartOfName)->second != 1)
                fPartOfName = FullNameWithExt(file_name);

        if (folderName == NULL)
            fout_name = fPartOfName + "_" + newVer + "." + outExt;
        else
        {
            if (strlen(newVer) == 0)
                fout_name = folderName + string("/") + fPartOfName + "." + outExt;
            else
                fout_name = folderName + string("/") + fPartOfName + "_" + newVer + "." + outExt;
        }

        if (toString)
            __spf_print(1, "  Unparsing to string\n");
        else
            __spf_print(1, "  Unparsing to <%s> file\n", fout_name.c_str());
        if (curr_regime == INSERT_INCLUDES)
        {
            __spf_print(1, "  try to find file <%s>\n", file_name);
            __spf_print(1, "  in set %d, result %d\n", (int)filesToInclude.size(), filesToInclude.find(file_name) != filesToInclude.end());
        }

        //TODO: add freeForm for each file
        if (curr_regime == INSERT_INCLUDES && filesToInclude.find(file_name) != filesToInclude.end())            
            unparseToBuf = removeIncludeStatsAndUnparse(file, file_name, fout_name.c_str(), allIncludeFiles, out_free_form == 1, moduleUsesByFile, moduleDecls, toString, true);
        else
        {
            unparseToBuf = removeIncludeStatsAndUnparse(file, file_name, fout_name.c_str(), allIncludeFiles, out_free_form == 1, moduleUsesByFile, moduleDecls, toString);

            // copy includes that have not changed
            if (folderName != NULL)
            {
                int removeDvmDirs = 0;
                if (curr_regime == REMOVE_DVM_DIRS)
                    removeDvmDirs = 1;
                else if (curr_regime == REMOVE_DVM_DIRS_TO_COMMENTS)
                    removeDvmDirs = 2;


                set<string> allIncludeFilesFiltr;
                set<string> modFiles;
                for (auto& elem : moduleDecls)
                    modFiles.insert(elem.second);

                for (auto& elem : allIncludeFiles)
                {
                    if (modFiles.find(elem) == modFiles.end())
                        allIncludeFilesFiltr.insert(elem);
                }
                allIncludeFiles = allIncludeFilesFiltr;

                copyIncludes(allIncludeFiles, commentsToInclude, folderName, keepSpfDirs, removeDvmDirs);
            }
        }

        //restore of restore
        restoreCorrectedModuleProcNames(file);
    }

    return unparseToBuf;
}

string unparseProjectToString(SgFile *file, const int curr_regime)
{
    set<string> allIncludeFiles;
    return unparseProjectIfNeed(file, curr_regime, true, "", NULL, allIncludeFiles, true);
}

static bool isNotNullIntersection(const set<DIST::Array*> &first, const set<DIST::Array*> &second)
{
    for (auto &elem1 : first)
        if (second.find(elem1) != second.end())
            return true;
    
    return false;
}

static set<DIST::Array*> fillDistributedArraysD(const DataDirective& dataDirectives, bool onlyCommon = false)
{
    set<DIST::Array*> distrArrays;
    set<DIST::Array*> distrArraysD;
    set<DIST::Array*> distrArraysAdded;

    for (int z = 0; z < dataDirectives.distrRules.size(); ++z)
        distrArraysD.insert(dataDirectives.distrRules[z].first);
    for (int z = 0; z < dataDirectives.alignRules.size(); ++z)
        distrArraysD.insert(dataDirectives.alignRules[z].alignArray);

    for (auto& elem : tableOfUniqNamesByArray)
    {
        set<DIST::Array*> realRefs;
        getRealArrayRefs(elem.first, elem.first, realRefs, arrayLinksByFuncCalls);
        if (isNotNullIntersection(realRefs, distrArraysD))
            distrArraysAdded.insert(elem.first);
    }
        
    for (auto& elem : distrArraysD)
    {
        if (onlyCommon)
        {
            if (elem->GetLocation().first == DIST::l_COMMON)
                distrArrays.insert(elem);
        }
        else
            distrArrays.insert(elem);
    }

    for (auto& elem : distrArraysAdded)
    {
        if (onlyCommon)
        {
            if (elem->GetLocation().first == DIST::l_COMMON)
                distrArrays.insert(elem);
        }
        else
            distrArrays.insert(elem);
    }
    return distrArrays;
}

static set<string> fillDistributedArrays(const DataDirective &dataDirectives, bool onlyCommon = false, bool shortName = false)
{
    set<string> distrArrays;
    set<DIST::Array*> ret = fillDistributedArraysD(dataDirectives, onlyCommon);

    for (auto& elem : ret)
        distrArrays.insert(shortName ? elem->GetShortName() : elem->GetName());
    return distrArrays;
}

static bool comparSort(pair<int, int> left, pair<int, int> right)
{
    return (left.second > right.second);
}

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
#else
    sendMessage_1lvl(wstring(L"running pass '") + wstring(toSendStrMessage.begin(), toSendStrMessage.end()) + L"'");
#endif

    const int n = project.numberOfFiles();
    bool verifyOK = true;
    int internalExit = 0;

    //for process include files
    set<string> allIncludeFiles;

    //for insert and extract dirs
    map<string, string> templateDeclInIncludes;

    //for function checker
    map<string, pair<string, int>> functionNames;

    // **********************************  ///
    /// FIRST STEP - RUN ANALYSIS BY FILES ///
    // **********************************  ///
    auto timeForPass = high_resolution_clock::now();
    
    sgStats.clear();
    sgExprs.clear();
    SgStatement::cleanStatsByLine();
    SgStatement::cleanParentStatsForExprs();

    SgStatement::setCurrProcessFile("");
    SgStatement::setCurrProcessLine(-1);

    set<string> allFileNames;
    for (int i = n - 1; i >= 0; --i)
    {
        SgFile *file = &(project.file(i));
        allFileNames.insert(file->filename());
        updateStatsExprs(current_file_id, file->filename());
    }

    auto rw_analyzer = ReadWriteAnalyzer(allFuncInfo);  // doesn't analyze anything until first query

    for (int i = n - 1; i >= 0; --i)
    {
        createNeededException();
        SgFile *file = &(project.file(i));

        toSendStrMessage = file->filename();
#ifdef _WIN32
        sendMessage_2lvl(wstring(L"обработка файла '") + wstring(toSendStrMessage.begin(), toSendStrMessage.end()) + L"'");
#else 
        sendMessage_2lvl(wstring(L"processing file '") + wstring(toSendStrMessage.begin(), toSendStrMessage.end()) + L"'");
#endif
        sendMessage_progress(std::to_wstring((int)(((double)(n - i) / n) * 100)));

        const char *file_name = file->filename();
        __spf_print(DEBUG_LVL1, "  Analyzing: %s\n", file_name);

        if (curr_regime == CONVERT_TO_ENDDO)
            ConverToEndDo(file, getObjectForFileFromMap(file_name, SPF_messages));
        else if (curr_regime == UNROLL_LOOPS)
        {
            __spf_print(DEBUG_LVL1, "  it is not implemented yet\n");
            throw(-1);
        }
        else if (curr_regime == LOOP_ANALYZER_DATA_DIST_S0)
        {
            vector<Messages> tmp;
            loopAnalyzer(file, parallelRegions, createdArrays, tmp, DATA_DISTR,
                         allFuncInfo, declaredArrays, declaratedArraysSt, arrayLinksByFuncCalls, createDefUseMapByPlace(), true, &(loopGraph.find(file_name)->second));
        }
        else if (curr_regime == LOOP_ANALYZER_DATA_DIST_S1 || curr_regime == ONLY_ARRAY_GRAPH)
        {
            try
            {
                //save current state
                /*if (curr_regime == LOOP_ANALYZER_DATA_DIST_S1)
                    states.push_back(new SapforState());*/

                loopAnalyzer(file, parallelRegions, createdArrays, getObjectForFileFromMap(file_name, SPF_messages), DATA_DISTR, 
                             allFuncInfo, declaredArrays, declaratedArraysSt, arrayLinksByFuncCalls, createDefUseMapByPlace(),
                             false, &(loopGraph.find(file_name)->second));
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
                         allFuncInfo, declaredArrays, declaratedArraysSt, arrayLinksByFuncCalls, createDefUseMapByPlace(),
                         false, &(itFound->second));
            
            UniteNestedDirectives(itFound->second);
        }
        else if (curr_regime == CALL_GRAPH)
        {
            auto it = allFuncInfo.find(file_name);
            if (it == allFuncInfo.end())
                functionAnalyzer(file, allFuncInfo, getObjectForFileFromMap(file_name, loopGraph), getObjectForFileFromMap(file_name, SPF_messages));
        }
        else if (curr_regime == CALL_GRAPH2)
        {
            checkForRecursion(file, allFuncInfo, getObjectForFileFromMap(file_name, SPF_messages));
            intentInsert(getObjectForFileFromMap(file_name, allFuncInfo));
        }
        else if (curr_regime == LOOP_GRAPH)
            loopGraphAnalyzer(file, getObjectForFileFromMap(file_name, loopGraph), getObjectForFileFromMap(file_name, intervals), getObjectForFileFromMap(file_name, SPF_messages), mpiProgram);
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
            auto &loopsInFile = getObjectForFileFromMap(file_name, loopGraph);

            map<int, LoopGraph*> mapLoopsInFile;
            createMapLoopGraph(loopsInFile, mapLoopsInFile);

            map<string, FuncInfo*> mapFuncInfo;
            createMapOfFunc(allFuncInfo, mapFuncInfo);

            for (int z = 0; z < parallelRegions.size(); ++z)
            {
                vector<pair<int, pair<string, vector<Expression*>>>> toInsert;

                const DataDirective &dataDirectives = parallelRegions[z]->GetDataDir();
                const vector<int> &currentVariant = parallelRegions[z]->GetCurrentVariant();
                DIST::GraphCSR<int, double, attrType> &reducedG = parallelRegions[z]->GetReducedGraphToModify();
                DIST::Arrays<int> &allArrays = parallelRegions[z]->GetAllArraysToModify();

                auto& tmp = dataDirectives.distrRules;
                vector<pair<DIST::Array*, const DistrVariant*>> currentVar;

                if (mpiProgram == 0)
                {
                    for (int z1 = 0; z1 < currentVariant.size(); ++z1)
                        currentVar.push_back(make_pair(tmp[z1].first, &tmp[z1].second[currentVariant[z1]]));
                }
                else
                {                    
                    for (auto& loop : mapLoopsInFile)
                    {
                        auto& rules = loop.second->getDataDir().distrRules;
                        for (auto& rule : rules)
                            currentVar.push_back(make_pair(rule.first, &rule.second[0]));
                    }
                }

                map<LoopGraph*, void*> depInfoForLoopGraphV;
                for (auto& elem : depInfoForLoopGraph)
                    depInfoForLoopGraphV[elem.first] = elem.second;

                selectParallelDirectiveForVariant(new File(file), parallelRegions[z], reducedG, allArrays, loopsInFile, mapLoopsInFile, mapFuncInfo, currentVar,
                                                  dataDirectives.alignRules, toInsert, parallelRegions[z]->GetId(), arrayLinksByFuncCalls,
                                                  depInfoForLoopGraphV, getObjectForFileFromMap(file_name, SPF_messages));

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

            if (mpiProgram == 0)
            {
                auto callGraph = getObjectForFileFromMap(file_name, allFuncInfo);
                map<string, FuncInfo*> mapFuncInfo;
                createMapOfFunc(callGraph, mapFuncInfo);

                for (int z = 0; z < parallelRegions.size(); ++z)
                {
                    ParallelRegion* currReg = parallelRegions[z];

                    const DataDirective& dataDirectives = currReg->GetDataDir();
                    const vector<int>& currentVariant = currReg->GetCurrentVariant();
                    const DIST::Arrays<int>& allArrays = currReg->GetAllArrays();
                    DIST::GraphCSR<int, double, attrType>& reducedG = currReg->GetReducedGraphToModify();

                    const set<string> distrArrays = fillDistributedArrays(dataDirectives);
                    const vector<string> distrRules = dataDirectives.GenRule(currentVariant);
                    const vector<vector<dist>> distrRulesSt = dataDirectives.GenRule(currentVariant, 0);
                    const vector<string> alignRules = dataDirectives.GenAlignsRules();


                    insertDistributionToFile(file, file_name, dataDirectives, distrArrays, distrRules, distrRulesSt, alignRules, loopGraph,
                        allArrays, reducedG, commentsToInclude, templateDeclInIncludes, extract, getObjectForFileFromMap(file_name, SPF_messages),
                        arrayLinksByFuncCalls, mapFuncInfo, currReg->GetId());
                }
            }

            if (extract)
            {
                createdDirectives[file_name].clear();

                //clear shadow specs
                for (auto& array : declaredArrays)
                    array.second.first->ClearShadowSpecs();
            }
            else if (mpiProgram == 0)
            {
                set<uint64_t> regNum;
                for (int z = 0; z < parallelRegions.size(); ++z)
                    regNum.insert(parallelRegions[z]->GetId());
                insertTemplateModuleUse(file, regNum, arrayLinksByFuncCalls);
            }
        }
        else if (curr_regime == INSERT_SHADOW_DIRS || curr_regime == EXTRACT_SHADOW_DIRS)
        {
            const bool extract = (curr_regime == EXTRACT_SHADOW_DIRS);

            set<string> distrArraysDone;
            for (int z = 0; z < parallelRegions.size(); ++z)
            {
                ParallelRegion *currReg = parallelRegions[z];
                DataDirective &dataDirectives = currReg->GetDataDirToModify();
                DIST::GraphCSR<int, double, attrType> &reducedG = parallelRegions[z]->GetReducedGraphToModify();

                set<string> distrArraysF = fillDistributedArrays(dataDirectives);

                set<string> distrArrays;
                for (auto& elem : distrArraysF)
                    if (distrArraysDone.find(elem) == distrArraysDone.end())
                        distrArrays.insert(elem);
                insertShadowSpecToFile(file, file_name, distrArrays, reducedG, commentsToInclude, extract, getObjectForFileFromMap(file_name, SPF_messages), declaredArrays);

                distrArraysDone.insert(distrArrays.begin(), distrArrays.end());
            }

            if (!extract)
            {
                for (int z = 0; z < parallelRegions.size(); ++z)
                {
                    ParallelRegion* currReg = parallelRegions[z];
                    DataDirective& dataDirectives = currReg->GetDataDirToModify();
                    const set<DIST::Array*> distrCommonArrays = fillDistributedArraysD(dataDirectives, true);
                    insertRealignsBeforeFragments(currReg, file, distrCommonArrays, arrayLinksByFuncCalls);
                }
            }
        }
        else if (curr_regime == REVERT_SPF_DIRS)
        {
            if (keepSpfDirs)
                revertion_spf_dirs(file, declaredArrays, declaratedArraysSt);
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
            bool noError = preprocess_spf_dirs(file, commonBlocks, getObjectForFileFromMap(file_name, SPF_messages), allFileNames);
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
                         allFuncInfo, declaredArrays, declaratedArraysSt, arrayLinksByFuncCalls, createDefUseMapByPlace(),
                         false, &(loopGraph.find(file_name)->second));
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
            arrayAccessAnalyzer(file, getObjectForFileFromMap(file_name, SPF_messages), declaredArrays, PRIVATE_STEP4);
        else if (curr_regime == FILL_PAR_REGIONS_LINES)
            fillRegionLines(file, parallelRegions, getObjectForFileFromMap(file_name, SPF_messages), &(loopGraph[file_name]), &(allFuncInfo[file_name]));
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
        else if (curr_regime == REMOVE_DVM_INTERVALS)
        {
            vector<SgStatement*> toDel;
            for (SgStatement *st = file->firstStatement(); st; st = st->lexNext())
            {
                if (st->variant() == DVM_INTERVAL_DIR)
                    toDel.push_back(st);
                else if (st->variant() == DVM_ENDINTERVAL_DIR)
                    toDel.push_back(st);
                else if (st->variant() == DVM_EXIT_INTERVAL_DIR)
                    toDel.push_back(st);
            }
            //TODO: move comments
            for (auto &elem : toDel)
                elem->deleteStmt();
        }
        else if (curr_regime == SUBST_EXPR)
        {
            expressionAnalyzer(file, defUseByFunctions, commonBlocks, temporaryAllFuncInfo, subs_parallelRegions);
            // analyze again for substituted expressions
            arrayAccessAnalyzer(file, getObjectForFileFromMap(file_name, SPF_messages), declaredArrays, PRIVATE_STEP4);
        }
        else if (curr_regime == REVERT_SUBST_EXPR)
            revertReplacements(file->filename(), true);
        else if (curr_regime == CREATE_NESTED_LOOPS)
        {
            map<string, FuncInfo*> mapFuncInfo;
            createMapOfFunc(allFuncInfo, mapFuncInfo);

            map<LoopGraph*, void*> depInfoForLoopGraphV;
            for (auto& elem : depInfoForLoopGraph)
                depInfoForLoopGraphV[elem.first] = elem.second;

            auto itFound = loopGraph.find(file_name);
            if (itFound != loopGraph.end())
                for (int i = 0; i < itFound->second.size(); ++i)
                    createNestedLoops(itFound->second[i], depInfoForLoopGraphV, mapFuncInfo, getObjectForFileFromMap(file_name, SPF_messages));
        }
        else if (curr_regime == GET_ALL_ARRAY_DECL)
            getAllDeclaredArrays(file, declaredArrays, declaratedArraysSt, getObjectForFileFromMap(file_name, SPF_messages), subs_parallelRegions, keyValueFromGUI);
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

                if (isSPF_stat(st))
                {
                    auto itD = dirsInfo.find(fName);
                    if (itD == dirsInfo.end())
                        itD = dirsInfo.insert(itD, make_pair(fName, make_pair(set<int>(), set<int>())));
                    itD->second.first.insert(line);
                }
                if (isDVM_stat(st))
                {
                    auto itD = dirsInfo.find(fName);
                    if (itD == dirsInfo.end())
                        itD = dirsInfo.insert(itD, make_pair(fName, make_pair(set<int>(), set<int>())));
                    itD->second.second.insert(line);
                }
                st = st->lexNext();
            }
        }
        else if (curr_regime == BUILD_INCLUDE_DEPENDENCIES)
        {
            auto fileIt = includeDependencies.find(file_name);
            if (fileIt == includeDependencies.end())
                fileIt = includeDependencies.insert(fileIt, make_pair(file_name, set<string>()));

            set<string> modFiles;
            for (auto& elem : moduleDecls)
                modFiles.insert(elem.second);

            for (SgStatement *first = file->firstStatement(); first; first = first->lexNext())
            {
                if (strcmp(file_name, first->fileName()))
                {
                    if (first->variant() == MODULE_STMT && modFiles.find(first->fileName()) != modFiles.end())
                        first = first->lastNodeOfStmt();
                    else
                        fileIt->second.insert(first->fileName());
                }
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
        else if (curr_regime == CONVERT_ASSIGN_TO_LOOP) // And MOVE COMPLITE DECLARATION as ASSIGN OPERATORS
            convertFromAssignToLoop(file, getObjectForFileFromMap(file_name, SPF_messages));
        else if (curr_regime == CONVERT_LOOP_TO_ASSIGN)
        {
            if (PASSES_DONE[CONVERT_ASSIGN_TO_LOOP])
                restoreAssignsFromLoop(file);
            else
                __spf_print(1, "skip CONVERT_LOOP_TO_ASSIGN");
        }
        else if (curr_regime == CALCULATE_STATS_SCHEME)
            processFileToPredict(file, getObjectForFileFromMap(file_name, allPredictorStats));
        else if (curr_regime == DEF_USE_STAGE1)
            constructDefUseStep1(file, defUseByFunctions, temporaryAllFuncInfo, getObjectForFileFromMap(file_name, SPF_messages));
        else if (curr_regime == DEF_USE_STAGE2)
            constructDefUseStep2(file, defUseByFunctions);
        else if (curr_regime == RESTORE_LOOP_FROM_ASSIGN)
            restoreConvertedLoopForParallelLoops(file);
        else if (curr_regime == RESTORE_LOOP_FROM_ASSIGN_BACK)
            restoreConvertedLoopForParallelLoops(file, true);
        else if (curr_regime == FILL_PARALLEL_REG_FOR_SUBS)
        {
            auto it = subs_allFuncInfo.find(file_name);
            if (it == subs_allFuncInfo.end())
            {
                vector<LoopGraph*> tmp;
                functionAnalyzer(file, subs_allFuncInfo, tmp, getObjectForFileFromMap(file_name, SPF_messages), true);
            }

            fillRegionLines(file, subs_parallelRegions, getObjectForFileFromMap(file_name, SPF_messages));
        }
        else if (curr_regime == ADD_TEMPL_TO_USE_ONLY)
            fixUseOnlyStmt(file, parallelRegions);
        else if (curr_regime == GCOV_PARSER)
            parse_gcovfile(file, consoleMode == 1 ? file_name : "./visualiser_data/gcov/" + string(file_name), getObjectForFileFromMap(file_name, gCovInfo), keepFiles);        
        else if(curr_regime == PRIVATE_ARRAYS_BREEDING)
        {
            set<SgSymbol*> tmp;
            auto founded = loopGraph.find(file->filename());
            if (founded != loopGraph.end())
            {
                int err = breedArrays(file, founded->second, tmp, getObjectForFileFromMap(file_name, SPF_messages));
                if (err != 0)
                    internalExit = -1;
            }
        }
        else if (curr_regime == PRIVATE_ARRAYS_SHRINKING)
        {
            set<SgSymbol*> tmp;
            auto founded = loopGraph.find(file->filename());
            if (founded != loopGraph.end())
            {
                int err = breedArrays(file, founded->second, tmp, getObjectForFileFromMap(file_name, SPF_messages));
                if (err != 0)
                    internalExit = -1;
            }
        }
        else if(curr_regime == LOOPS_SPLITTER)
        {
            auto founded = loopGraph.find(file->filename());
            if (founded != loopGraph.end())
            {
                int err = splitLoops(file, founded->second, getObjectForFileFromMap(file_name, SPF_messages));
                if (err != 0)
                    internalExit = -1;
            }
        }
        else if(curr_regime == LOOPS_COMBINER)
        {
            auto founded = loopGraph.find(file->filename());
            if (founded != loopGraph.end())
            {
                int err = combineLoops(file, founded->second, getObjectForFileFromMap(file_name, SPF_messages), inOnlyForloopOnPlace);
                if (err != 0)
                    internalExit = -1;
            }
        }
        else if (curr_regime == CREATE_INTER_TREE)
        {
            vector<string> include_functions;
            
            createInterTree(file, getObjectForFileFromMap(file_name, intervals), removeNestedIntervals, getObjectForFileFromMap(file_name, SPF_messages));
            assignCallsToFile(consoleMode == 1 ? file_name : "./visualiser_data/gcov/" + string(file_name), getObjectForFileFromMap(file_name, intervals));
            removeNodes(intervals_threshold, getObjectForFileFromMap(file_name, intervals), include_functions);
        }
        else if (curr_regime == INSERT_INTER_TREE)
            insertIntervals(file, getObjectForFileFromMap(file_name, intervals));
        else if (curr_regime == INSERT_REGIONS)
        {
            map<string, FuncInfo*> mapOfFuncs;
            createMapOfFunc(allFuncInfo, mapOfFuncs);

            auto loopForFile = getObjectForFileFromMap(file_name, loopGraph);
            DvmhRegionInserter regionInserter(file, loopForFile, rw_analyzer, arrayLinksByFuncCalls, mapOfFuncs);

            //collect info about <parallel> functions
            regionInserter.updateParallelFunctions(loopGraph);
            
            if ((parallelRegions.size() == 0 && parallelRegions[0]->GetName() == "DEFAULT") || mpiProgram == 1)
                regionInserter.insertDirectives(NULL);
            else
                regionInserter.insertDirectives(&parallelRegions);

            //remove privates from loops out of DVMH region 
            //remove parallel directives from loops out of DVMH region 
            map<int, LoopGraph*> mapLoopGraph;
            createMapLoopGraph(loopForFile, mapLoopGraph);
            for (auto& loopPair : mapLoopGraph)
            {
                auto loop = loopPair.second;
                if (loop->directive && loop->inDvmhRegion <= 0)
                {
                    SgStatement* lexPrev = loop->loop->GetOriginal()->lexPrev();

                    if (lexPrev->variant() == DVM_PARALLEL_ON_DIR)
                    {
                        if (mpiProgram == 1)
                            lexPrev->deleteStmt();
                        else
                        {
                            SgExprListExp* list = isSgExprListExp(lexPrev->expr(1));
                            if (list)
                            {
                                vector<SgExpression*> newList;
                                for (SgExpression* ex = list; ex; ex = ex->rhs())
                                    if (ex->lhs()->variant() != ACC_PRIVATE_OP)
                                        newList.push_back(ex->lhs());

                                lexPrev->setExpression(1, makeExprList(newList));
                            }
                        }
                    }
                }
            }

            //create interface for 'parallel' functions
            regionInserter.createInterfaceBlock();
        }
        else if (curr_regime == VERIFY_FUNC_DECL)
        {
            bool res = FunctionsChecker(file, functionNames, SPF_messages);
            verifyOK &= res;
        }
        else if (curr_regime == RESTORE_COPIES)
            restoreCopies(file);
        else if (curr_regime == SET_TO_ALL_DECL_INIT_ZERO)
            setAllDeclsWithInitZero(file);
        else if (curr_regime == DUMP_DECLS_WITH_INIT)
            dumpAllDeclsWithInit(file, (i == n - 1));
        else if (curr_regime == CREATE_CHECKPOINTS)
            createCheckpoints(file, commonBlocks, filesInfo);
        else if (curr_regime == CONVERT_SAVE_TO_MODULE)
            convertSaveToModule(file);
        else if (curr_regime == PROCESS_IO)
            preprocessOpenOperators(file, filesInfo);
        else if (curr_regime == CONVERT_STRUCTURES_TO_SIMPLE)
            replaceStructuresToSimpleTypes(file);
        else if (curr_regime == PURE_INTENT_INSERT)
            intentInsert(getObjectForFileFromMap(file_name, allFuncInfo));
        else if (curr_regime == TEST_PASS)
        {
        //test pass
        }
        unparseProjectIfNeed(file, curr_regime, need_to_unparse, newVer, folderName, allIncludeFiles);
    } // end of FOR by files

    if (internalExit != 0)
        throw -1;

    sendMessage_2lvl(wstring(L""));
    // **********************************  ///
    /// SECOND AGGREGATION STEP            ///
    // **********************************  ///
    SgStatement::setCurrProcessFile("");
    SgStatement::setCurrProcessLine(-1);
    
    if (curr_regime == LOOP_ANALYZER_DATA_DIST_S2 || curr_regime == ONLY_ARRAY_GRAPH)
    {
        if (curr_regime == ONLY_ARRAY_GRAPH)
            keepFiles = 1;

        if (mpiProgram)
        {
            for (auto& byFile : loopGraph)
                for (auto& loop : byFile.second)
                    loop->reduceAccessGraph();
        }
        else
        {
            set<DIST::Array*> usedArrays;
            for (int i = 0; i < parallelRegions.size(); ++i)
            {
                ParallelRegion* currReg = parallelRegions[i];
                DIST::GraphCSR<int, double, attrType>& G = currReg->GetGraphToModify();
                DIST::GraphCSR<int, double, attrType>& reducedG = currReg->GetReducedGraphToModify();
                DIST::Arrays<int>& allArrays = currReg->GetAllArraysToModify();

                usedArrays.insert(allArrays.GetArrays().begin(), allArrays.GetArrays().end());

                if (currReg->HasUserDvmDirs())
                {
                    set<DIST::Array*> alignedArrays;
                    set<DIST::Array*> addedArrays;

                    bool error = false;
                    if (currReg->GetUsersDirecites(DVM_REALIGN_DIR)->size())
                    {
                        bool ret = buildGraphFromUserDirectives(*(currReg->GetUsersDirecites(DVM_REALIGN_DIR)), G, allArrays, arrayLinksByFuncCalls, alignedArrays, addedArrays);
                        error = error || ret;
                        alignedArrays.insert(addedArrays.begin(), addedArrays.end());
                    }

                    if (currReg->GetUsersDirecites(DVM_ALIGN_DIR)->size())
                    {
                        bool ret = buildGraphFromUserDirectives(*(currReg->GetUsersDirecites(DVM_ALIGN_DIR)), G, allArrays, arrayLinksByFuncCalls, alignedArrays, addedArrays);
                        error = error || ret;
                        alignedArrays.insert(addedArrays.begin(), addedArrays.end());
                    }

                    if (currReg->GetUsersDirecites(DVM_DISTRIBUTE_DIR)->size())
                        error = false;

                    if (error == false)
                        error = (currReg->GetUsersDirecites(DVM_REALIGN_DIR)->size() == 0) &&
                        (currReg->GetUsersDirecites(DVM_ALIGN_DIR)->size() == 0) &&
                        (currReg->GetUsersDirecites(DVM_DISTRIBUTE_DIR)->size() == 0);

                    if (error)
                    {
                        wstring messageR, messageE;
                        __spf_printToLongBuf(messageE, L"Can not build align graph from user's DVM directives in this region");
                        __spf_printToLongBuf(messageR, R67);

                        for (auto& lines : currReg->GetAllLines())
                        {
                            const auto& vecLines = lines.second;
                            const string& fileName = lines.first;

                            auto& messages = getObjectForFileFromMap(fileName.c_str(), SPF_messages);
                            for (auto& line : vecLines)
                            {
                                if ((line.stats.first && line.stats.second) || currReg->GetId() == 0)
                                {
                                    messages.push_back(Messages(ERROR, line.lines.first, messageR, messageE, 1036));

                                    __spf_print(1, "Can not build align graph from user's DVM directives in this region in '%s': %d\n",
                                        fileName.c_str(), line.lines.first);
                                }
                            }
                        }
                        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
                    }
                    else
                    {
                        currReg->ClearUserDirs();

                        set<int> varsToClear = { DVM_DYNAMIC_DIR, DVM_INHERIT_DIR };
                        removeStatementsFromAllproject(varsToClear);

                        //TODO: need to add template clones, so remove all dirs!
                        // clear user directives from all loops
                        for (auto& byFile : loopGraph)
                        {
                            if (SgFile::switchToFile(byFile.first) == -1)
                                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

                            for (auto& loop : byFile.second)
                                loop->clearUserDirectives();
                        }
                        // clear other dirs
                        set<int> varsToClear1 = { ACC_REGION_DIR, ACC_END_REGION_DIR, ACC_ACTUAL_DIR, ACC_GET_ACTUAL_DIR,
                                                  DVM_SHADOW_DIR, DVM_REALIGN_DIR, DVM_REDISTRIBUTE_DIR, DVM_VAR_DECL, HPF_TEMPLATE_STAT, DVM_REMOTE_ACCESS_DIR };
                        removeStatementsFromAllproject(varsToClear1);
                    }
                }

                G.SetMaxAvailMemory(currentAvailMemory);
                G.ChangeQuality(QUALITY, SPEED);

                reducedG.SetMaxAvailMemory(currentAvailMemory);
                DIST::createOptimalDistribution<int, double, attrType>(G, reducedG, allArrays, currReg->GetId(), (curr_regime == ONLY_ARRAY_GRAPH));

                set<DIST::Array*> usedArraysLocal;
                usedArraysLocal.insert(allArrays.GetArrays().begin(), allArrays.GetArrays().end());

                //add array that linked with used
                for (auto& used : usedArraysLocal)
                {
                    set<DIST::Array*> allArrayRefs;
                    getAllArrayRefs(used, used, allArrayRefs, arrayLinksByFuncCalls);

                    for (auto& array : allArrayRefs)
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

                    for (auto& array : realArrayRefs)
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
                        wstring bufE, bufR;
                        __spf_printToLongBuf(bufE, L"Can not find arrays or free loops for distribution in this project");
                        __spf_printToLongBuf(bufR, R130);

                        for (auto& funcByFile : allFuncInfo)
                        {
                            vector<Messages>& fileM = getObjectForFileFromMap(funcByFile.first.c_str(), SPF_messages);
                            for (auto& func : funcByFile.second)
                            {
                                auto stat = func->funcPointer->GetOriginal();
                                if (stat->variant() == PROG_HEDR)
                                    fileM.push_back(Messages(ERROR, stat->lineNumber(), bufR, bufE, 3010));
                            }
                        }
                    }
                    else
                    {
                        wstring bufE, bufR;
                        __spf_printToLongBuf(bufE, L"Can not find arrays or free loops for distribution in this region");
                        __spf_printToLongBuf(bufR, R131);

                        for (auto& linesByFile : parallelRegions[z]->GetAllLines())
                        {
                            vector<Messages>& fileM = getObjectForFileFromMap(linesByFile.first.c_str(), SPF_messages);
                            for (auto& lines : linesByFile.second)
                                if (!lines.isImplicit())
                                    fileM.push_back(Messages(ERROR, lines.lines.first, bufR, bufE, 3010));
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
                    ParallelRegion* regToDel = parallelRegions[z];
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
    }
    else if (curr_regime == CALL_GRAPH)
    {    
        if (keepFiles)
        {
            map<string, CallV> V;
            vector<string> E;
            CreateCallGraphViz("_callGraph.txt", allFuncInfo, V, E);
        }
        findDeadFunctionsAndFillCalls(allFuncInfo, SPF_messages);

        createLinksBetweenFormalAndActualParams(allFuncInfo, arrayLinksByFuncCalls, declaredArrays, SPF_messages, keepFiles);
        propagateWritesToArrays(allFuncInfo);
        updateFuncInfo(allFuncInfo);

        uniteIntervalsBetweenProcCalls(intervals, allFuncInfo);
        if (keepFiles)
        {
            CreateFuncInfo("_funcInfo.txt", allFuncInfo);
            saveIntervals("_intervals_united.txt", intervals);
        }
        updateLoopIoAndStopsByFuncCalls(loopGraph, allFuncInfo);

        moveAllocatesInterproc(arrayLinksByFuncCalls);

        removeDistrStateFromDeadFunctions(allFuncInfo, declaredArrays);
        propagateArrayFlags(arrayLinksByFuncCalls, declaredArrays, SPF_messages);
    }
    else if (curr_regime == CALL_GRAPH2)
    {
        map<string, FuncInfo*> allFuncs;
        createMapOfFunc(allFuncInfo, allFuncs);
        completeFillOfArrayUsageBetweenProc(loopGraph, allFuncInfo);

        fixTypeOfArrayInfoWithCallGraph(declaredArrays, allFuncs);

        //for each file of graphLoop
        for (auto &loopGraphInFile : loopGraph)
        {
            LoopChecker checker(loopGraphInFile.second);
            checker.updateLoopGraph(allFuncs);
        }

        detectCopies(allFuncInfo);
        fillInterfaceBlock(allFuncInfo);

        //this call is only for testing
        //setPureStatus(allFuncInfo);

        //add conflict messages for all loops
        for (auto byFile : loopGraph)
        {
            map<int, LoopGraph*> allLoops;
            createMapLoopGraph(byFile.second, allLoops);
            for (auto& loop : allLoops)
            {
                if (loop.second->hasLimitsToParallel())
                {
                    loop.second->addConflictMessages(&SPF_messages[loop.second->fileName]);
                    __spf_print(1, "added conflict messages to loop on line %d\n", loop.second->lineNum);
                }
            }
        }

        if (keepFiles)
            printArrayInfo("_arrayInfo.txt", declaredArrays);
    }
    else if (curr_regime == INSERT_SHADOW_DIRS)
    {
        for (auto &comment : commentsToInclude)
        {
            if (consoleMode)
            {
                __spf_print(1, "  write to <%s_%s> file\n", comment.first.c_str(), newVer);
                insertDistributionToFile(comment.first.c_str(), (comment.first + "_" + string(newVer)).c_str(), comment.second);
            }
            else
            {
                if (folderName)
                {
                    __spf_print(1, "  write to <%s> file\n", (string(folderName) + "/" + string(comment.first)).c_str());
                    insertDistributionToFile(comment.first.c_str(), (string(folderName) + "/" + string(comment.first)).c_str(), comment.second);
                }
                /*else
                {
                    __spf_print(1, "  write to <%s> file\n", (string(comment.first)).c_str());
                    insertDistributionToFile(it->first.c_str(), (string(comment.first)).c_str(), comment.second);
                }*/
            }
        }

        // copy includes that have not changed
        if (folderName != NULL)
            copyIncludes(allIncludeFiles, commentsToInclude, folderName, keepSpfDirs);
    }
    else if (curr_regime == EXTRACT_SHADOW_DIRS)
        commentsToInclude.clear();
    else if (curr_regime == VERIFY_ENDDO ||
             curr_regime == VERIFY_INCLUDE ||
             curr_regime == VERIFY_DVM_DIRS ||
             curr_regime == VERIFY_EQUIVALENCE ||
             curr_regime == VERIFY_COMMON ||
             curr_regime == VERIFY_FUNC_DECL)
    {
        if (verifyOK == false)
            throw(-1);
    }
    else if (curr_regime == PRIVATE_ANALYSIS_SPF)
    {
        SgStatement *mainUnit = findMainUnit(&project, SPF_messages);
        if (mainUnit)
        {
            //PrivateAnalyzerForMain(mainUnit);
            Private_Vars_Analyzer(mainUnit);
        }
        else
        {
            for (int i = n - 1; i >= 0; --i)
            {
                createNeededException();
                SgFile *file = &(project.file(i));

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
        
        if (mpiProgram)
        {
            bool wasDone = false;
            for (int z = 0; z < parallelRegions.size(); ++z)
            {
                DIST::Arrays<int>& allArrays = parallelRegions[z]->GetAllArraysToModify();

                if (ALGORITHMS_DONE[CREATE_DISTIBUTION][z] == 0)
                    recalculateArraySizes(arraysDone, allArrays.GetArrays(), arrayLinksByFuncCalls, allFuncInfo);

                if (ALGORITHMS_DONE[CREATE_DISTIBUTION][z] != 0)
                    wasDone = true;

                ALGORITHMS_DONE[CREATE_DISTIBUTION][z] = 1;
                ALGORITHMS_DONE[CREATE_ALIGNS][z] = 1;
            }

            if (parallelRegions.size() == 0)
                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

            if (!wasDone)
            {
                for (auto& byFile : loopGraph)
                    for (auto& loop : byFile.second)
                        loop->createVirtualTemplateLinks(arrayLinksByFuncCalls, SPF_messages);

                //add dummy array
                DataDirective& dataDirectives = parallelRegions[0]->GetDataDirToModify();
                DIST::Arrays<int>& allArrays = parallelRegions[0]->GetAllArraysToModify();
                for (auto& byFile : loopGraph)
                {
                    map<int, LoopGraph*> allLoops;
                    createMapLoopGraph(byFile.second, allLoops);
                    bool found = false;
                    for (auto& loop : allLoops)
                    {
                        auto& tmp = loop.second->getDataDir();
                        if (tmp.distrRules.size() != 0)
                        {
                            dataDirectives.distrRules.push_back(tmp.distrRules[0]);
                            DIST::Array* firstTempl = dataDirectives.distrRules.back().first;

                            firstTempl->DeprecateAllDims();
                            allArrays.AddArrayToGraph(firstTempl);
                            firstTempl->ChangeName("dvmh_additional_parallel");
                            found = true;
                            break;
                        }
                    }
                    if (found)
                        break;
                }
            }
        }
        else
        {

            for (int z = 0; z < parallelRegions.size(); ++z)
            {
                DIST::GraphCSR<int, double, attrType>& reducedG = parallelRegions[z]->GetReducedGraphToModify();
                DIST::Arrays<int>& allArrays = parallelRegions[z]->GetAllArraysToModify();
                DataDirective& dataDirectives = parallelRegions[z]->GetDataDirToModify();

                if (ALGORITHMS_DONE[CREATE_DISTIBUTION][z] == 0)
                {
                    //recalculate array sizes after expression substitution
                    recalculateArraySizes(arraysDone, allArrays.GetArrays(), arrayLinksByFuncCalls, allFuncInfo);

                    createDistributionDirs(reducedG, allArrays, dataDirectives, SPF_messages, arrayLinksByFuncCalls);
                    ALGORITHMS_DONE[CREATE_DISTIBUTION][z] = 1;
                }

                if (ALGORITHMS_DONE[CREATE_ALIGNS][z] == 0)
                {
                    if (keepFiles)
                    {
                        char fName[256];
                        sprintf(fName, "_graph_reduced_with_templ_reg%d.txt", parallelRegions[z]->GetId());
                        reducedG.CreateGraphWiz(fName, vector<tuple<int, int, attrType>>(), allArrays, true);
                    }
                    createAlignDirs(reducedG, allArrays, dataDirectives, parallelRegions[z]->GetId(), arrayLinksByFuncCalls, SPF_messages);
                    ALGORITHMS_DONE[CREATE_ALIGNS][z] = 1;
                }
                
                SgStatement* mainUnit = findMainUnit(&project, SPF_messages);

                map<string, vector<SgExpression*>> commonBlocks;
                checkNull(mainUnit, convertFileName(__FILE__).c_str(), __LINE__);
                getCommonBlocksRef(commonBlocks, mainUnit, mainUnit->lastNodeOfStmt());

                // check array declaration
                for (auto& arrayP : dataDirectives.GenAlignsRules(NULL))
                {
                    auto array = arrayP.alignArray;
                    if (array->IsLoopArray() || array->IsTemplate())
                        continue;
                    if (array->GetLocation().first == DIST::l_COMMON)
                    {
                        auto nameOfCommon = array->GetLocation().second;
                        if (commonBlocks.find(nameOfCommon) == commonBlocks.end())
                        {
                            auto declPlaces = array->GetDeclInfo();
                            for (auto& place : declPlaces)
                            {
                                vector<Messages>& currMessages = getObjectForFileFromMap(place.first.c_str(), SPF_messages);
                                __spf_print(1, "  ERROR: distributed array '%s' in common block '%s' must have declaration in main unit\n", array->GetShortName().c_str(), nameOfCommon.c_str());

                                wstring messageE, messageR;
                                __spf_printToLongBuf(messageE, L"distributed array '%s' in common block '%s' must have declaration in main unit",
                                    to_wstring(array->GetShortName()).c_str(), to_wstring(nameOfCommon).c_str());
                                __spf_printToLongBuf(messageR, R75,
                                    to_wstring(array->GetShortName()).c_str(), to_wstring(nameOfCommon).c_str());
                                currMessages.push_back(Messages(ERROR, place.second, messageR, messageE, 1042));
                            }
                            internalExit = 1;
                        }
                    }
                }

                __spf_print(1, "*** FOR PARALLEL REGION '%s':\n", parallelRegions[z]->GetName().c_str());
                result = dataDirectives.GenAlignsRules();
                for (int i = 0; i < result.size(); ++i)
                    __spf_print(1, "  %s\n", result[i].c_str());
            }
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

        if (ignoreDvmChecker == 1 && parallelRegions.size() == 1 && parallelRegions[0]->GetName() == "DEFAULT" && dvmDirErrors.size())
        {
            printDvmActiveDirsErrors();
            throw(-1);
        }

        checkCountOfIter(loopGraph, allFuncInfo, SPF_messages);
        calculateLinesOfCode(parallelRegions);
        if (keepFiles)
        {
            printLoopGraph("_loopGraph_with_reg.txt", loopGraph, true);
            printParalleRegions("_parallelRegions.txt", parallelRegions);
        }
    }
    else if (curr_regime == FILL_PAR_REGIONS)
    {
        fillRegionIntervals(parallelRegions);
        fillRegionFunctions(parallelRegions, allFuncInfo);
        fillRegionArrays(parallelRegions, allFuncInfo, commonBlocks);

        bool noError = checkRegions(parallelRegions, allFuncInfo, SPF_messages);
        if (!noError)
            internalExit = 1;

        if (keepFiles)
        {
            int err = printCheckRegions("_checkRegions.txt", parallelRegions, allFuncInfo);
            if (err == -1)
                internalExit = 1;
            err = printCheckRegions(NULL, parallelRegions, allFuncInfo);
            if (err == -1)
                internalExit = 1;
        }
    }
    else if (curr_regime == CHECK_ARGS_DECL)
    {
        bool error = checkArgumentsDeclaration(&project, allFuncInfo, parallelRegions, SPF_messages);;
        if (error)
            internalExit = 1;
    }
    else if (curr_regime == RESOLVE_PAR_REGIONS)
    {
        bool error = resolveParRegions(parallelRegions, allFuncInfo, SPF_messages, mpiProgram);
        if (error)
            internalExit = 1;
    }
    else if (curr_regime == EXPAND_EXTRACT_PAR_REGION)
    {
        bool error = expandExtractReg(std::get<0>(inData),
                                      std::get<1>(inData),
                                      std::get<2>(inData),
                                      parallelRegions,
                                      getObjectForFileFromMap(std::get<0>(inData).c_str(), SPF_messages),
                                      !std::get<3>(inData));

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
        bool cond = (folderName != NULL) || (consoleMode) || (!consoleMode && curr_regime == EXTRACT_PARALLEL_DIRS);
        if (cond && mpiProgram == 0)
        {
            //insert template declaration to main program
            const bool extract = (curr_regime == EXTRACT_PARALLEL_DIRS);
            for (int i = n - 1; i >= 0; --i)
            {
                createNeededException();

                SgFile *file = &(project.file(i));
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
                        const vector<vector<dist>> distrRulesSt = dataDirectives.GenRule(currentVariant, 0);

                        insertTempalteDeclarationToMainFile(file, dataDirectives, templateDeclInIncludes, distrRules, distrRulesSt, allArrays, extract, currReg->GetId(), includedToThisFile);
                    }
                    break;
                }
            }
        }
    }
    else if (curr_regime == DEF_USE_STAGE1)
    {
        if (keepFiles)
            printDefUseSets("_defUseList.txt", defUseByFunctions);
    }
    else if (curr_regime == LOOP_ANALYZER_DATA_DIST_S0)
    {
        checkArraysMapping(loopGraph, SPF_messages, arrayLinksByFuncCalls);
        propagateArrayFlags(arrayLinksByFuncCalls, declaredArrays, SPF_messages);

        if (mpiProgram == 0)
        {
            for (int z = 0; z < parallelRegions.size(); ++z)
                filterArrayInCSRGraph(loopGraph, allFuncInfo, parallelRegions[z], arrayLinksByFuncCalls, SPF_messages);
            propagateArrayFlags(arrayLinksByFuncCalls, declaredArrays, SPF_messages);
        }

        for (auto& loopByFile : loopGraph)
        {
            for (auto& loop : loopByFile.second)
            {
                loop->removeNonDistrArrays();
                loop->removeGraphData();
            }
        }

        for (auto &funcByFile : allFuncInfo)
            for (auto &func : funcByFile.second)
                func->removeNonDistrArrays();

        //restore
        for (int z = 0; z < parallelRegions.size(); ++z)
        {
            parallelRegions[z]->GetAllArraysToModify().cleanData();
            parallelRegions[z]->GetGraphToModify().ClearGraphCSR();
            parallelRegions[z]->GetReducedGraphToModify().ClearGraphCSR();
        }
        createdArrays.clear();
    }
    else if (curr_regime == LOOP_ANALYZER_DATA_DIST_S1)
    {
        for (int z = 0; z < parallelRegions.size(); ++z)
        {
            ParallelRegion *currReg = parallelRegions[z];
            auto graph = currReg->GetGraph();
            __spf_print(1, "STAT: par reg %s: requests %d, miss %d, V = %d, E = %d\n", currReg->GetName().c_str(), graph.getCountOfReq(), graph.getCountOfMiss(), graph.GetNumberOfV(), graph.GetNumberOfE());
        }
    }
    else if (curr_regime == PRINT_PAR_REGIONS_ERRORS)
    {
        bool error = checkRegionsResolving(parallelRegions, allFuncInfo, commonBlocks, SPF_messages, mpiProgram);
        if (error)
            internalExit = 1;
    }
    else if (curr_regime == FILL_PARALLEL_REG_FOR_SUBS)
    {
        findDeadFunctionsAndFillCalls(subs_allFuncInfo, SPF_messages, true);
        fillRegionLinesStep2(subs_parallelRegions, subs_allFuncInfo);
        clearRegionStaticData();
    }
    else if (curr_regime == GET_ALL_ARRAY_DECL)
    {
        bool hasNonDefaultReg = false;
        for (auto &elem : subs_parallelRegions)
            if (elem->GetName() != "DEFAULT")
                hasNonDefaultReg = true;

        if (hasNonDefaultReg)
        {
            for (auto array : declaredArrays)
            {
                if (array.second.first->GetRegionsName().size() == 0)
                    array.second.first->SetNonDistributeFlag(DIST::NO_DISTR);
                else if (array.second.first->GetRegionsName().size() == 1)
                {
                    string test = *array.second.first->GetRegionsName().begin();
                    convertToLower(test);
                    if (test == "default")
                        array.second.first->SetNonDistributeFlag(DIST::NO_DISTR);
                }
            }
        }
    }
    else if (curr_regime == GCOV_PARSER)
    {
        parseTimesDvmStatisticFile((consoleMode == 1) ? string("statistic.txt") : "./visualiser_data/statistic/" + string("statistic.txt"), intervals);

        //fixed count, devide by value from PROG_HEDR
        SgStatement* mainUnit = findMainUnit(&project, SPF_messages);
        if (mainUnit->variant() != PROG_HEDR)
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
        const int line = mainUnit->lineNumber();
        auto itF = gCovInfo.find(mainUnit->fileName());
        if (itF != gCovInfo.end())
        {
            auto itL = itF->second.find(line);
            if (itL != itF->second.end())
            {
                auto totalExec = itL->second.getExecutedCount();
                if (totalExec != 1)
                {
                    for (auto& byFile : gCovInfo)
                        for (auto& byLine : byFile.second)
                            byLine.second.setExecutedCount(byLine.second.getExecutedCount() / totalExec);
                }
            }
        }
    }
    else if (curr_regime == PREDICT_SCHEME)
    {
        int maxSizeDist = 0;
        for (int z = 0; z < parallelRegions.size(); ++z)
        {
            const DataDirective &dataDirectives = parallelRegions[z]->GetDataDir();
            const vector<int> &currentVariant = parallelRegions[z]->GetCurrentVariant();

            auto &tmp = dataDirectives.distrRules;
            vector<pair<DIST::Array*, const DistrVariant*>> currentVar;
            for (int z1 = 0; z1 < currentVariant.size(); ++z1)
                currentVar.push_back(make_pair(tmp[z1].first, &tmp[z1].second[currentVariant[z1]]));

            for (auto &elem : currentVar)
            {
                DIST::Array *array = elem.first;
                const DistrVariant *var = elem.second;

                int countBlock = 0;
                for (int z = 0; z < var->distRule.size(); ++z)
                    if (var->distRule[z] == dist::BLOCK)
                        ++countBlock;
                maxSizeDist = std::max(maxSizeDist, countBlock);
            }
        }
                        
        SpfInterval *mainIterval = getMainInterval(&project, intervals, SPF_messages);
        topologies.clear();
        if (maxSizeDist)
        {
            const int procNum = 8;
            //TODO:
            //topologies = getTopologies(procNum, maxSizeDist);
            throw -10;

            const int countOfTop = topologies.size();
            if (countOfTop < 0)
                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

            for (auto &inter : intervals)
                initTimeForIntervalTree(countOfTop, inter.second);

            for (int z = 0; z < parallelRegions.size(); ++z)
            {
                const DataDirective &dataDirectives = parallelRegions[z]->GetDataDir();
                const vector<int> &currentVariant = parallelRegions[z]->GetCurrentVariant();
                DIST::Arrays<int> &allArrays = parallelRegions[z]->GetAllArraysToModify();

                auto &tmp = dataDirectives.distrRules;
                vector<pair<DIST::Array*, const DistrVariant*>> currentVar;
                for (int z1 = 0; z1 < currentVariant.size(); ++z1)
                    currentVar.push_back(make_pair(tmp[z1].first, &tmp[z1].second[currentVariant[z1]]));

                map<LoopGraph*, ParallelDirective*> parallelDirs;
                vector<std::tuple<DIST::Array*, vector<long>, pair<string, int>>> allSingleRemotes;
                for (int i = n - 1; i >= 0; --i)
                {
                    SgFile *file = &(project.file(i));
                    auto fountInfo = findAllDirectives(file, getObjectForFileFromMap(file->filename(), loopGraph), parallelRegions[z]->GetId());
                    parallelDirs.insert(fountInfo.begin(), fountInfo.end());

                    auto fountRem = findAllSingleRemotes(file, parallelRegions[z]->GetId(), parallelRegions);
                    allSingleRemotes.insert(allSingleRemotes.end(), fountRem.begin(), fountRem.end());
                }
                //TODO!
                //int err = predictScheme(parallelRegions[z], currentVar, allArrays.GetArrays(), parallelDirs, intervals, SPF_messages, allSingleRemotes, maxSizeDist, procNum);                
                /*if (err != 0)
                    internalExit = err;*/
            }

            vector<SpfInterval*> tmp = { mainIterval };
            aggregatePredictedTimes(tmp);

            int idx = 0;
            int best = -1;
            double bestSpeedUp = 0;
            for (auto &top : topologies)
            {
                string outStr = "";
                for (auto &elem : top)
                    outStr += std::to_string(elem) + " ";
                double currS = mainIterval->exec_time / mainIterval->predictedTimes[idx];
                __spf_print(1, "%d: speed up %f for top. %s\n", idx, currS, outStr.c_str());
                
                if (best == -1 || bestSpeedUp < currS)
                {
                    bestSpeedUp = currS;
                    best = idx;
                }
                ++idx;
            }
            __spf_print(1, "best topology %d with speed up %f\n", best, bestSpeedUp);
        }
        else
            for (auto &inter : intervals)
                initTimeForIntervalTree(0, inter.second);

    }
    else if (curr_regime == CREATE_INTER_TREE)
    {
        if (keepFiles)
            saveIntervals("_intervals.txt", intervals);
    }
    else if (curr_regime == CREATE_PARALLEL_REGIONS)
    {
        SpfInterval* mainInterval = getMainInterval(&project, intervals, SPF_messages);
        createParallelRegions(&project, mainInterval, gCovInfo, allFuncInfo);
    }
    else if (curr_regime == SUBST_EXPR)
    {
        /*SgStatement *mainUnit = findMainUnit(&project);
        if (mainUnit)
            runPrivateAnalysis(mainUnit);
        else
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);*/
    }
    else if (curr_regime == DUPLICATE_FUNCTIONS)
    {
        if (!duplicateFunctions(allFuncInfo, arrayLinksByFuncCalls, SPF_messages))
            internalExit = 1;
    }
    else if (curr_regime == REMOVE_COPIES)
        removeCopies(allFuncInfo);
    else if (curr_regime == ADD_TEMPL_TO_USE_ONLY)
        correctTemplateModuleDeclaration((folderName == NULL) ? "" : folderName);
    else if (curr_regime == PURE_COMMON_TO_PARAMS)
        commonTransfer(allFuncInfo, commonBlocks);
    else if (curr_regime == PURE_SAVE_TO_PARAMS)
        saveTransfer(allFuncInfo);
    else if (curr_regime == PURE_MODULE_TO_PARAMS)
        moduleTransfer(allFuncInfo);
    else if (curr_regime == PURE_INTENT_INSERT)
        setPureStatus(allFuncInfo);
    else if (curr_regime == SHADOW_GROUPING)
    {
        if (staticShadowAnalysis)
        {
            //TODO for all parallel regions
            if (parallelRegions.size() == 1 && parallelRegions[0]->GetName() == "DEFAULT")
            {
                for (int z = 0; z < parallelRegions.size(); ++z)
                    GroupShadow(allFuncInfo, loopGraph, parallelRegions[z]->GetAllArraysToModify(), arrayLinksByFuncCalls);
            }
        }
        else
            __spf_print(1, "skip\n");
    }
    else if (curr_regime == SWAP_LOOPS)
        swapLoopsForParallel(loopGraph, SPF_messages, 1);
    else if (curr_regime == RESTORE_SWAP_LOOPS)
        swapLoopsForParallel(loopGraph, SPF_messages, -1);
    else if (curr_regime == CREATE_PARALLEL_DIRS)
        filterParallelDirectives(loopGraph, createdDirectives);
    else if (curr_regime == INLINE_PROCEDURES)
    {
        map<SgStatement*, set<SgSymbol*>> newSymbsToDeclare;
        map<string, FuncInfo*> tmpM;
        createMapOfFunc(allFuncInfo, tmpM);
        FuncInfo* mainF = NULL;
        for (auto& elem : tmpM)
            if (elem.second->isMain)
                mainF = elem.second;
        checkNull(mainF, convertFileName(__FILE__).c_str(), __LINE__);
        
        //inliner(mainF->funcName, allFuncInfo, SPF_messages, newSymbsToDeclare);
        //inDataProc.push_back(make_tuple("zran3", "mg.f", 197));
        //inDataProc.push_back(make_tuple("randlc", "ep_ddp.for", 121));
        
#if 1
        if (inDataProc.size())
        {
            map<int, vector<int>> sortByLvl;

            int maxLvlCall = 0;
            for (int z = 0; z < inDataProc.size(); ++z)
            {
                if (std::get<2>(inDataProc[z]) != -1)
                {
                    int lvl = getLvlCall(mainF, 0, std::get<0>(inDataProc[z]), std::get<1>(inDataProc[z]), std::get<2>(inDataProc[z]));
                    if (lvl == -1)
                        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
                    maxLvlCall = std::max(maxLvlCall, lvl);
                    sortByLvl[lvl].push_back(z);
                }
            }

            for (int z = 0; z < inDataProc.size(); ++z)
                if (std::get<2>(inDataProc[z]) == -1)
                    sortByLvl[maxLvlCall + 1].push_back(z);

            for (auto& byLvl : sortByLvl)
            {
                for (auto& idx : byLvl.second)
                {
                    auto& tup = inDataProc[idx];

                    if (std::get<2>(tup) != -1)
                    {
                        __spf_print(1, "call inliner with [%s %s %d]\n", std::get<1>(tup).c_str(), std::get<0>(tup).c_str(), std::get<2>(tup));
                        inliner(std::get<1>(tup), std::get<0>(tup), std::get<2>(tup), allFuncInfo, SPF_messages, newSymbsToDeclare);
                    }
                }
            }
        }
        else if (inDataChains.size())
        {
            //TODO: need to add attribute to all shadow copies
            for (auto& elem : tmpM)
            {
                auto itNeed = inDataChains.find(elem.first);
                if (itNeed != inDataChains.end() && itNeed->second.size())
                {
                    const FuncInfo* curr = elem.second;
                    const set<pair<string, int>>& needToInline = itNeed->second;

                    for (int k = 0; k < curr->detailCallsFrom.size(); ++k)
                    {
                        if (needToInline.find(curr->detailCallsFrom[k]) == needToInline.end() && 
                            !isIntrinsicFunctionName(curr->detailCallsFrom[k].first.c_str()))
                        {
                            pair<void*, int> detail = curr->pointerDetailCallsFrom[k];
                            
                            if (SgFile::switchToFile(curr->fileName) == -1)
                                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

                            if (detail.second == PROC_STAT)
                                ((SgStatement*)detail.first)->addAttribute(BOOL_VAL);
                            else if (detail.second == FUNC_CALL)
                            {
                                //TODO: many functions in same statement
                                SgStatement* callSt = SgStatement::getStatementByFileAndLine(curr->fileName, curr->detailCallsFrom[k].second);
                                if (!callSt)
                                    printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
                                //((SgExpression*)detail.first)->addAttribute(BOOL_VAL);
                                callSt->addAttribute(BOOL_VAL);
                            }
                            else
                                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

                            __spf_print(1, " added attribute to %s %d\n", curr->detailCallsFrom[k].first.c_str(), curr->detailCallsFrom[k].second);
                        }
                    }
                }
            }

            __spf_print(1, "call inliner from main\n");
            inliner(mainF->funcName, allFuncInfo, SPF_messages, newSymbsToDeclare);
        }
#endif
        createDeclarations(newSymbsToDeclare);
    }


#if _WIN32
    const float elapsed = duration_cast<milliseconds>(high_resolution_clock::now() - timeForPass).count() / 1000.;
    __spf_print(1, "PROFILE: time for this pass = %f sec\n", elapsed);
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
        if (mpiProgram != 0)
            sprintf(buf, "__mpi");
        else
        {
            sprintf(buf, "v%d", i + 1);
            currentVariants[maxDimsIdxReg][maxDimsIdx] = i;
            if (i != 0)
            {
                for (int p = 0; p < parallelRegions.size(); ++p)
                {
                    DataDirective& dataDirectives = parallelRegions[p]->GetDataDirToModify();

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
    /*else if (failed < 0)
        throw -6;*/
}

static void fillAllSymbs(SgExpression *ex, set<SgSymbol*> &refs)
{
    if (ex)
    {
        if (ex->variant() == VAR_REF || ex->variant() == ARRAY_REF)
            refs.insert(ex->symbol());

        fillAllSymbs(ex->lhs(), refs);
        fillAllSymbs(ex->rhs(), refs);
    }
}

static SgProject* createProject(const char *proj_name)
{
    Statement::deactiveConsistentchecker();
    sortFilesBySize(proj_name);
    SgProject *project = new SgProject(proj_name);
    addNumberOfFileToAttribute(project);

    parallelRegions.push_back(new ParallelRegion(0, "DEFAULT"));
    subs_parallelRegions.push_back(new ParallelRegion(0, "DEFAULT"));

    Statement::activeConsistentchecker();

    //hide duplicated functions
    for (int z = 0; z < project->numberOfFiles(); ++z)
    {
        SgFile* file = &(project->file(z));

        const string fileN = file->filename();
        auto first = file->firstStatement();
        SgStatement* lastValid = NULL;
        for (SgStatement* st = first->lexNext(), *stPrev = first; 
             st; 
             st = st->lexNext(), stPrev = stPrev->lexNext())
        {
            if (st->comments())
            {
                string comm(st->comments());
                if (comm.find("!SPF SHADOW FILES") != string::npos)
                {
                    if (st->variant() == CONTROL_END)
                        lastValid = st;
                    else
                        lastValid = stPrev;
                    break;
                }
            }
        }

        if (lastValid)
        {
            vector<SgStatement*> toExtract;
            auto st = lastValid->lexNext();
            while (st)
            {
                toExtract.push_back(st);
                st = st->lastNodeOfStmt();
                st = st->lexNext();
            }

            /*for (auto st = lastValid->lexNext(); st; st = st->lexNext())
                ;*/

            set<int> validVars = { PROG_HEDR, FUNC_HEDR, PROC_HEDR, BLOCK_DATA, MODULE_STMT };
            for (auto& elem : toExtract)
            {
                int var = elem->variant();
                if (validVars.find(var) == validVars.end())
                    printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
                hiddenData[fileN].push_back(elem->extractStmt());
            }
            lastValid->setLexNext((SgStatement*)NULL);
        }
    }

    //dump symbol table and symbol use
    /*printSymbolTable(current_file);
    for (auto st = current_file->firstStatement()->lexNext(); st; st = st->lexNext())
    {
        if (st->variant() != MODULE_STMT && isSgProgHedrStmt(st) == NULL)
        {
            set<SgSymbol*> refs;
            for (int z = 0; z < 3; ++z)
                if (st->expr(z))
                    fillAllSymbs(st->expr(z), refs);

            if (refs.size())
            {
                printf("FOR STATEMENT ON LINE %d:\n", st->lineNumber());
                st->unparsestdout();
                printf("refs ids:");
                for (auto& elem : refs)
                    printf(" %d (%s)", elem->id(), elem->identifier());
                printf(";\n\n");
            }
        }
    }*/

    set<string> filesInProj;
    //preprocess module includes
    for (int z = 0; z < project->numberOfFiles(); ++z)
        filesInProj.insert((project->file(z)).filename());

    //check main unit
    findMainUnit(project, SPF_messages);

    set<string> globalFunctions;
    for (int z = 0; z < project->numberOfFiles(); ++z)
    {
        SgFile* file = &(project->file(z));

        string name = OnlyName(file->filename());
        if (filesNameWithoutExt.find(name) == filesNameWithoutExt.end())
            filesNameWithoutExt[name] = 1;
        else
            filesNameWithoutExt[name]++;

        fillModuleUse(file, moduleUsesByFile, moduleDecls);

        int funcCount = file->numberOfFunctions();
        for (int k = 0; k < funcCount; ++k)
        {
            auto func = file->functions(k);
            if (func->controlParent()->variant() == GLOBAL)
                globalFunctions.insert(func->symbol()->identifier());
        }
    }
    filterModuleUse(moduleUsesByFile, moduleDecls);

    map<string, int> shifts;
    //shiftLines if modules included
    for (int z = 0; z < project->numberOfFiles(); ++z)
    {
        SgFile* file = &(project->file(z));
        const string fileN = file->filename();
        auto it = moduleUsesByFile.find(fileN);
        if (it == moduleUsesByFile.end())
            continue;
        const int shiftN = it->second.size();
        shifts[fileN] = shiftN;
        __spf_print(1, "  shift by %d for %s\n", shiftN, fileN.c_str());
    }

    for (int z = 0; z < project->numberOfFiles(); ++z)
    {
        SgFile* file = &(project->file(z));

        for (SgStatement* st = file->firstStatement()->lexNext(); st; st = st->lexNext())
        {
            string currF = st->fileName();
            auto it = shifts.find(currF);
            if (it != shifts.end() && file->filename() == currF)
                st->setlineNumber(st->lineNumber() - it->second);
        }
    }

    for (int z = 0; z < project->numberOfFiles(); ++z)
        correctModuleProcNames(&(project->file(z)), globalFunctions);

    for (int z = 0; z < project->numberOfFiles(); ++z)
        removeExecutableFromModuleDeclaration(&(project->file(z)), filesInProj);

    for (int z = 0; z < project->numberOfFiles(); ++z)
    {
        SgFile* file = &(project->file(z));
        correctModuleSymbols(file);
        //file->unparsestdout();
    }
    
    if (detectMpiCalls(project, SPF_messages))
    {
        mpiProgram = 1;
        keepDvmDirectives = 0;
        ignoreIO = 1;
        parallizeFreeLoops = 0;
    }

    return project;
}

void runPass(const int curr_regime, const char *proj_name, const char *folderName)
{
    // init math functions of FORTRAN
    initIntrinsicFunctionNames();
    initTags();
    InitPassesDependencies(passesDependencies, passesIgnoreStateDone);
    setPassValues();

    if (project == NULL && curr_regime != PARSE_FILES)
    {
        project = createProject(proj_name);
        //first check correctness
        runPass(VERIFY_FUNC_DECL, proj_name, folderName);
    }
        
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

        int lastI = 1;
        if (mpiProgram == 0)
            lastI = countMaxValuesForParallelVariants(maxDims, maxDimsIdx, maxDimsIdxReg, currentVariants);
        if (genAllVars == 0)
            lastI = 1;

        for (int i = 0; i < lastI; ++i)
        {
            //if specific variant number is requested, skip all others
            if (genSpecificVar >= 0 && i != genSpecificVar && mpiProgram == 0)
                continue;

            string additionalName = selectAddNameOfVariant(i, maxDimsIdx, maxDimsIdxReg, currentVariants);

            runPass(CREATE_PARALLEL_DIRS, proj_name, folderName);

            runPass(CONVERT_LOOP_TO_ASSIGN, proj_name, folderName);

            runAnalysis(*project, INSERT_PARALLEL_DIRS, false, consoleMode ? additionalName.c_str() : NULL, folderName);

            runPass(REVERT_SUBST_EXPR, proj_name, folderName);

            if (mpiProgram == 0)
                runPass(CREATE_REMOTES, proj_name, folderName);

            if (mpiProgram == 0)
            {
                runPass(REMOVE_AND_CALC_SHADOW, proj_name, folderName);
                runPass(SHADOW_GROUPING, proj_name, folderName);
                runPass(TRANSFORM_SHADOW_IF_FULL, proj_name, folderName);
                runAnalysis(*project, INSERT_SHADOW_DIRS, false, consoleMode ? additionalName.c_str() : NULL, folderName);
            }

            runPass(RESTORE_LOOP_FROM_ASSIGN, proj_name, folderName);

            if (mpiProgram == 0)
                runPass(ADD_TEMPL_TO_USE_ONLY, proj_name, folderName);

            runAnalysis(*project, INSERT_REGIONS, false);

            runAnalysis(*project, CALCULATE_STATS_SCHEME, false);
            for (auto& elem : allPredictorStats)
                __spf_print(1, "  stat for file %s: %s\n", elem.first.c_str(), elem.second.to_string().c_str());
            //TODO: need to rewrite this to new algo 
            /*if (!folderName && !consoleMode || predictOn)
                runAnalysis(*project, PREDICT_SCHEME, false); */

            runAnalysis(*project, REMOVE_COPIES, false);
            runAnalysis(*project, SWAP_LOOPS, false);

            if (folderName || consoleMode)
                runAnalysis(*project, UNPARSE_FILE, true, additionalName.c_str(), folderName);
            
            runAnalysis(*project, RESTORE_SWAP_LOOPS, false); // restore
            runAnalysis(*project, RESTORE_COPIES, false);

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
                    func->shadowTreeStart = NULL;
                    func->shadowTreeEnd = NULL;
                    for (auto &sh : func->allShadowNodes)
                        delete sh.second;
                    func->allShadowNodes.clear();
                }
            }

            //clear template clones && region status
            for (auto& loopByFile : loopGraph)
            {
                for (auto& loop : loopByFile.second)
                {
                    loop->clearForSwap();
                    if (loop->directive)
                        loop->directive->cloneOfTemplate = "";
                    loop->inDvmhRegion = 0;
                    loop->propagateDvmhRegion(0);
                }
            }

            for (int z = 0; z < parallelRegions.size(); ++z)
            {
                const DataDirective &dataDirectives = parallelRegions[z]->GetDataDir();
                const vector<int> &currentVariant = parallelRegions[z]->GetCurrentVariant();
               
                auto &tmp = dataDirectives.distrRules;
                for (int z1 = 0; z1 < currentVariant.size(); ++z1)
                {
                    if (tmp[z1].first->IsTemplate())
                        tmp[z1].first->ClearTemplateClones();
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
    case PRIVATE_ARRAYS_SHRINKING:
    case LOOPS_SPLITTER:
    case INSERT_INTER_TREE:
    case REMOVE_DVM_INTERVALS:
    case SET_TO_ALL_DECL_INIT_ZERO:
    case CREATE_CHECKPOINTS:
    case PURE_INTENT_INSERT:
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
        // all these cases run UNPARSE_FILE after 
    case RESOLVE_PAR_REGIONS:
    case CREATE_PARALLEL_REGIONS:
    case DUPLICATE_FUNCTIONS:
    case LOOPS_COMBINER:
    case CONVERT_STRUCTURES_TO_SIMPLE:
    case PURE_COMMON_TO_PARAMS:
    case PURE_SAVE_TO_PARAMS:
    case PURE_MODULE_TO_PARAMS:
    case TEST_PASS:
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
    case PARSE_FILES:
        {
            int err = parseFiles(proj_name, filesCompilationOrder, parseForInlining);
            if (err != 0)
                throw err;
        }
        break;
    default:
        runAnalysis(*project, curr_regime, false);
        break;
    }
}

extern "C" int parse_file(int argc, char* argv[], char* proj_name);
extern int pppa_analyzer(int argv, char** argc);

bool runAsClient = false;

int main(int argc, char **argv)
{
    int leakMemDump = 0;
    bool withDel = false;

    try
    {
        setPassValues();
        consoleMode = 1;
        QUALITY = 100;
        SPEED = 100;

        bool printed = false;
        for (int i = 0; i < argc; ++i)
        {
            const char* curr_arg = argv[i];
            if (string(curr_arg) == "-client")
            {
                printVersion("[SAPFOR]: ");
                printed = true;
                break;
            }
        }
        if (!printed)
            printVersion();
        
        const char *proj_name = "dvm.proj";
        const char *folderName = NULL;

        int curr_regime = EMPTY_PASS;
        int numVar = 0;

        out_free_form = 0; // F90 style out
        out_upper_case = 1;
        out_line_unlimit = 0;

        bool printText = false;

        int serverPort = -1;

        for (int i = 0; i < argc; ++i)
        {
            const char *curr_arg = argv[i];
            switch (curr_arg[0])
            {
            case '-':
                if (string(curr_arg) == "-threshold")
                {
                    i++;
                    intervals_threshold = atoi(argv[i]);
                }
                else if (string(curr_arg) == "-removeNestedIntervals")
                    removeNestedIntervals = true;
                else if (string(curr_arg) == "-p")
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
                    printHelp(passNames, EMPTY_PASS);
                else if (string(curr_arg) == "-leak")
                {
                    leakMemDump = 1;
#if _WIN32 && _DEBUG
                    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
                }
                else if (string(curr_arg) == "-f90")
                {
                    out_free_form = 1;
                    out_line_unlimit = 1;
                }
                else if (string(curr_arg) == "-sh")
                    staticShadowAnalysis = 1;
                else if (string(curr_arg) == "-priv")
                    staticPrivateAnalysis = 1;
                else if (string(curr_arg) == "-keep")
                    keepFiles = 1;
                else if (string(curr_arg) == "-pred")
                    predictOn = 1;
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
                else if (string(curr_arg) == "-parse")
                {
                    auto result = splitCommandLineForParse(argv + i + 1, argc - i - 1);
                    if (result.second.size() == 0)
                    {
                        printf("Nothing to parse\n");
                        exit(0);
                    }

                    int code = -1;
                    char** nextArgv = new char* [32];
                    nextArgv[0] = "parse from spf";
                    int z = 0;
                    for (auto& file : result.second)
                    {
                        int countOfArgs = 1;
                        for (auto& opt : result.first)
                            nextArgv[countOfArgs++] = (char*)opt.c_str();
                        
                        if (z != 0)
                        {
                            nextArgv[countOfArgs++] = "-a";
                            nextArgv[countOfArgs++] = "dvm.proj";
                        }
                        nextArgv[countOfArgs++] = (char*)file.c_str();
                        //code = parse_file(argc - i, argv + i, "dvm.proj");
                        code = parse_file(countOfArgs, nextArgv, "dvm.proj");
                        if (code != 0)
                        {
                            printf("Parsing was completed with error code %d\n", code);
                            break;
                        }
                        ++z;
                    }

                    delete[] nextArgv;
                    if (code == 0)
                        printf("Parsing was completed successfully\n");
                    exit(0);
                }
                else if (string(curr_arg) == "-mpi")
                    mpiProgram = 1;
                else if (string(curr_arg) == "-pppa")
                {
                    int code = pppa_analyzer(argc - i, argv + i);
                    if (code == 0)
                        printf("PPPA was completed successfully\n");
                    else
                        printf("PPPA was completed with error code %d\n", code);
                    exit(0);
                }
                else if (string(curr_arg) == "-client")
                {
                    runAsClient = true;
                    withDel = false;
                    consoleMode = false;

                    i++;
                    if (i < argc)
                        serverPort = atoi(argv[i]);
                    break;
                }
                break;
            default:
                break;
            }
        }

        if (mpiProgram == 1)
        {
            keepDvmDirectives = 0;
            ignoreIO = 1;
            parallizeFreeLoops = 0;
        }

        if (runAsClient)
        {
            printf("[SAPFOR]: Started as client with server port %d\n", serverPort);
            RunSapforAsClient(serverPort);
        }
        else
        {
            if (curr_regime == EMPTY_PASS)
                printHelp(passNames, EMPTY_PASS);

            runPass(curr_regime, proj_name, folderName);
            if (printText)
                runPass(UNPARSE_FILE, proj_name, folderName);
        }
    }
    catch (...)
    {
        printStackTrace();
        printf("exception occurred\n");
        for (auto& byFile : SPF_messages)
        {
            for (auto& message : byFile.second)
            {
                string toPrint = "";
                for (int z = 0; z < message.engMessage.size(); ++z)
                    toPrint += message.engMessage[z];
                string type;
                if (message.type == WARR)
                    type = "WARR";
                else if (message.type == ERROR)
                    type = "ERROR";
                else if (message.type == NOTE)
                    type = "NOTE";
                else 
                    type = "UNKN";

                printf("%s - [#%d: %s: line %d]: %s\n", type.c_str(), message.group, byFile.first.c_str(), message.line, toPrint.c_str());
            }
        }
    }

    deleteAllAllocatedData(withDel);


#if _WIN32 && _DEBUG
    if (leakMemDump)
    {
        printf("START PRINT\n");
        _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
        _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
        _CrtDumpMemoryLeaks();
    }
#endif

    return 0;
}
