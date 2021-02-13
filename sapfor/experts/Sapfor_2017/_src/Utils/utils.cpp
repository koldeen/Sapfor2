#include "../Utils/leak_detector.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdint>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <vector>
#include <map>
#include <set>
#include <utility>
#include <string>
#include <assert.h>
#include <locale>
#include <algorithm>
#include <thread>

#include "utils.h"
#include "errors.h"
#include "version.h"

#include "../GraphLoop/graph_loops.h"
#include "../Distribution/Array.h"
#include "../Distribution/Arrays.h"
#include "../DynamicAnalysis/gcov_info.h"
#include "../ParallelizationRegions/ParRegions.h"

#if __SPF
#include "acc_analyzer.h"
#endif

using std::map;
using std::pair;
using std::tuple;
using std::set;
using std::vector;
using std::string;
using std::wstring;

void createMapLoopGraph(map<int, LoopGraph*> &sortedLoopGraph, const vector<LoopGraph*> *loopGraph)
{
    if (loopGraph)
    {
        for (int i = 0; i < (int)loopGraph->size(); ++i)
        {
            auto it = sortedLoopGraph.find((*loopGraph)[i]->lineNum);
            if (it != sortedLoopGraph.end())
                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

            sortedLoopGraph[(*loopGraph)[i]->lineNum] = (*loopGraph)[i];
            createMapLoopGraph(sortedLoopGraph, &((*loopGraph)[i]->children));
        }
    }
}

string FullNameWithExt(const char* filename)
{
    char* basename = new char[strlen(filename) + 1];
    int i;

    strcpy(basename, filename);
    for (i = (int)strlen(filename) - 1; i >= 0; --i)
    {
        if (basename[i] == '.')
        {
            basename[i] = '_';
            break;
        }
    }

    string retVal(basename);
    delete[] basename;

    return retVal;
}

string OnlyName(const char *filename)
{
    char *basename = new char[strlen(filename) + 1];
    int i;

    strcpy(basename, filename);
    for (i = (int)strlen(filename) - 1; i >= 0; --i)
    {
        if (basename[i] == '.')
        {
            basename[i] = '\0';
            break;
        }
    }

    string retVal(basename);
    delete[] basename;

    return retVal;
}

string OnlyExt(const char *filename)
{
    char *extname = new char[1024];
    int i;

    int len = (int)strlen(filename);
    for (i = len - 1; i >= 0; --i)
    {
        if (filename[i] == '.')
        {
            i++;
            int k;
            int bound = len - i;
            for (k = 0; k < bound; ++k, ++i)
                extname[k] = filename[i];
            extname[k] = '\0';
            break;
        }
    }

    string retVal(extname);
    delete[] extname;
    return retVal;
}

void printHelp(const char **passNames, const int lastPass)
{
    printf("Help info for passes.\n\n");
    printf(" -f90                free form\n");
    printf(" -sh                 turn on static shadow analysis\n");
    printf(" -ver/-Ver           version of SAPFOR\n");
    printf(" -priv               turn on static private analysis\n");
    printf(" -keep               keep temporary files\n");
    printf(" -keepSPF            keep SPF directives\n");
    printf(" -keepDVM            keep DVM directives\n");
    printf(" -allVars            get all parallel versions\n");
    printf(" -var N              get specific parallel version, N=1,2,..\n");
    printf(" -parse              run parser with next option\n");
    printf(" -inlineH <funcName> run hierarchical inlining for all functions called from 'funcName'\n");
    printf(" -inlineI <funcName> <lineNum> <fileName> run incremental inlining for function 'funcName' on 'lineNum' of 'fileName'\n");
    printf(" -passInfo           print passes information\n");
    printf("\n");

    printf(" -F    <folderName> output to folder\n");
    printf(" -p    <project name>\n");    
    printf(" -pass <pass_number>\n");
    for (int i = 0; i < lastPass; ++i)
        printf("    pass_num = %d:  %s\n", i, passNames[i]);
    printf("\n");
    printf(" -t    <analysis_num>\n");
    /*printf("    analysis_num = 1:  loops unroller\n");
    printf("    analysis_num = 2:  end do loop converter\n");
    printf("    analysis_num = 3:  code style correcter\n");
    printf("    analysis_num = 4:  optimal distribution\n");
    printf("    analysis_num = 5:  call graph\n");
    printf("    analysis_num = 6:  loop graph\n");
    printf("    analysis_num = 7:  compute directives\n");
    printf("    analysis_num = 8:  verification: end do\n");
    printf("    analysis_num = 9:  verification: exec in include\n");
    printf("    analysis_num = 10: find functions for including\n");
    printf("    analysis_num = 11: create distribution directives\n");
    printf("    analysis_num = 12: create parallel directives\n");*/
    printf("    analysis_num = 13: insert parallel directives\n");
    /*printf("    analysis_num = 14: create array graph\n");
    printf("    analysis_num = 15: check private analysis\n");
    printf("    analysis_num = 16: insert includes\n");
    printf("    analysis_num = 17: remove DVM directives\n");*/

    throw(-1);
}

void printVersion(const string pref)
{
    printf("%sSAPFOR version is %s, build date: %s %s\n", pref.c_str(), VERSION, __DATE__, __TIME__);
}

const string printVersionAsFortranComm()
{
    char buf[512];
    sprintf(buf, "! *** generated by SAPFOR with version %s and build date: %s %s\n", VERSION, __DATE__, __TIME__);
    return string(buf);
}

void convertToLower(string &str)
{
    std::locale loc;

    for (int i = 0; i < str.length(); ++i)
        str[i] = std::tolower(str[i], loc);
}

void convertToUpper(string &str)
{
    std::locale loc;

    for (int i = 0; i < str.length(); ++i)
        str[i] = std::toupper(str[i], loc);
}

void splitString(const string &strIn, const char delim, vector<string> &result, bool withQuotes)
{
    std::stringstream ss;
    ss.str(strIn);

    vector<string> tmp_result;
    string item;    
    while (std::getline(ss, item, delim))
        tmp_result.push_back(item);
    
    if (withQuotes)
    {
        bool quStarted = false;
        item = "";
        for (auto& elem : tmp_result)
        {
            if (elem.size())
            {
                if (quStarted)
                {
                    item += " " + elem;
                    if (elem[elem.size() - 1] == '"')
                    {
                        quStarted = false;
                        result.push_back(item.erase(item.size() - 1, 1));
                    }
                }
                else
                {
                    if (elem[0] == '"')
                    {
                        quStarted = true;
                        item = elem.erase(0, 1);

                        if (item[item.size() - 1] == '"')
                        {
                            quStarted = false;
                            result.push_back(item.erase(item.size() - 1, 1));
                        }
                    }
                    else
                        result.push_back(elem);

                }
            }
            else if (quStarted)
                item += " ";
        }
    }
    else
        result = tmp_result;
}

void splitString(const wstring& strIn, const char delim, vector<wstring>& result, bool withQuotes)
{
    std::wstringstream ss;
    ss.str(strIn);

    vector<wstring> tmp_result;
    wstring item;
    wchar_t buf[1024];
    while (ss.good())
    {        
        ss.getline(buf, 1024, delim);
        tmp_result.push_back(buf);
    }

    if (withQuotes)
    {
        bool quStarted = false;
        item = L"";
        for (auto& elem : tmp_result)
        {
            if (elem.size())
            {
                if (quStarted)
                {
                    item += elem;
                    if (elem[elem.size() - 1] == L'"')
                    {
                        quStarted = false;
                        result.push_back(item.erase(item.size() - 1, 1));
                    }
                }
                else
                {
                    if (elem[0] == '"')
                    {
                        quStarted = true;
                        item = elem.erase(0, 1);

                        if (item[item.size() - 1] == L'"')
                        {
                            quStarted = false;
                            result.push_back(item.erase(item.size() - 1, 1));
                        }
                    }
                    else
                        result.push_back(elem);

                }
            }
            else if (quStarted)
                item += L" ";
        }
    }
    else
        result = tmp_result;
}

void removeSubstrFromStr(string &str, const string &del)
{
    string::size_type pos = str.find(del);
    while (pos != string::npos)
    {
        str.erase(pos, del.size());
        pos = str.find(del, pos + 1);
    }
}

string convertFileName(const char *file)
{
    string tmp(file);
    std::reverse(tmp.begin(), tmp.end());
    int t = 0;
    while (tmp[t] != '\\' && tmp[t] != '/' && t < tmp.size())
        t++;
    tmp.erase(tmp.begin() + t, tmp.end());       
    std::reverse(tmp.begin(), tmp.end());
    return tmp;
}

void printBlanks(const int sizeOfBlank, const int countOfBlanks)
{
    for (int k = 0; k < countOfBlanks; ++k)
        for (int m = 0; m < sizeOfBlank; ++m)
        {
            char buf[256];
            sprintf(buf, " ");
            addToGlobalBufferAndPrint(buf);
        }
}

string globalOutputBuffer = "";
int consoleMode = 0;
void addToGlobalBufferAndPrint(const string &toPrint)
{
    globalOutputBuffer += toPrint;
    if (consoleMode)
    {
        printf("%s", toPrint.c_str());
        fflush(NULL);
    }
}

void clearGlobalBuffer() { globalOutputBuffer = ""; }
const string& getGlobalBuffer() { return globalOutputBuffer; }

set<short*> allocated;
set<int*> allocatedInt;
static void convertGlobalBuffer(short *&result, int *&resultSize)
{
    const unsigned len = (unsigned)globalOutputBuffer.size(); 
    result = new short[len + 1];
    allocated.insert(result);

    result[len] = '\0';
    for (unsigned i = 0; i < len; ++i)
        result[i] = globalOutputBuffer[i];

    resultSize = new int[1];
    resultSize[0] = (int)len;
}

extern map<string, vector<Messages>> SPF_messages; //file ->messages
void clearGlobalMessagesBuffer() 
{
    //clear allocated memory
    for (auto& elem : allocated)
        delete[]elem;
    for (auto& elem : allocatedInt)
        delete[]elem;
    allocated.clear();
    allocatedInt.clear();

    SPF_messages.clear();  
}

static map<string, vector<Messages>> removeCopies(map<string, vector<Messages>> in)
{
    map<string, vector<Messages>> out;
    for (auto& byFile : in)
    {
        map<tuple<typeMessage, int, int, wstring>, const Messages*> uniq;
        for (auto& message : byFile.second)
        {
            auto key = make_tuple(message.type, message.group, message.line, message.value);
            /*string tmp = "";
            for (auto& s : message.toString())
                tmp += (char)s;
            __spf_print(1, "%s\n", tmp.c_str());*/
            uniq[key] = &message;
        }
        __spf_print(1, "messages filtering for file '%s': count before %d, count after %d\n", byFile.first.c_str(), byFile.second.size(), uniq.size());
        vector<Messages> uniqV;
        for (auto& elem : uniq)
        {
            /*string tmp = "";
            for (auto& s : elem.second->toString())
                tmp += (char)s;
            __spf_print(1, "%s\n", tmp.c_str());*/
            uniqV.push_back(*elem.second);
        }

        out[byFile.first] = uniqV;
    }

    return out;
}

static void convertGlobalMessagesBuffer(short *&result, int *&resultSize)
{
    auto copySPF_messages = removeCopies(SPF_messages);
    for (auto &byFile : copySPF_messages)
    {
        vector<Messages> newVal;
        bool waschanged = false;
        for (auto &message : byFile.second)
        {
            if (message.line > 0)
                newVal.push_back(message);
            else
                waschanged = true;
        }

        if (waschanged)
            byFile.second = newVal;
    }

    wstring val = L"";
    val += std::to_wstring(copySPF_messages.size());
    for (auto it = copySPF_messages.begin(); it != copySPF_messages.end(); ++it)
    {
        val += L"|" + to_wstring(it->first.c_str()) + L"|" + std::to_wstring(it->second.size());
        for (int k = 0; k < it->second.size(); ++k)
            val += it->second[k].toString();
    }
    
    const unsigned len = (unsigned)val.size();
    result = new short[len + 1];
    allocated.insert(result);

    result[len] = '\0';
    for (unsigned i = 0; i < len; ++i)
        result[i] = val[i];

    resultSize = new int[1];
    resultSize[0] = (int)len;
}


void convertBuffers(short*& resultM, int*& resultSizeM, short*& result, int*& resultSize)
{
    convertGlobalMessagesBuffer(resultM, resultSizeM);
    convertGlobalBuffer(result, resultSize);
}

bool isSPF_comment(const string &bufStr)
{
    bool spfStart = false;
    if (bufStr.size() > 6)
        spfStart = (bufStr[0] == '!' || bufStr[0] == 'c') &&
                    bufStr[1] == '$' && bufStr[2] == 's'  &&
                    bufStr[3] == 'p' && bufStr[4] == 'f';

    return spfStart;
}

bool isDVM_comment(const string& bufStr)
{
    bool dvmStart = false;
    if (bufStr.size() > 6)
    {
        dvmStart = (bufStr[0] == '!' || bufStr[0] == 'c') &&
                    bufStr[1] == 'd' && bufStr[2] == 'v'  &&
                    bufStr[3] == 'm' && bufStr[4] == '$';
    }
    return dvmStart;
}

void copyIncludes(const set<string> &allIncludeFiles, const map<string, map<int, set<string>>> &commentsToInclude, 
                  const char *folderName, bool keepSpfDirs, int removeDvmDirs)
{
    for (auto &include : allIncludeFiles)
    {
        if (commentsToInclude.find(include) != commentsToInclude.end())
            continue;

        string newCurrFile = string(folderName) + "/" + include;
        
        FILE *tryToOpen = fopen(newCurrFile.c_str(), "r");
        if (tryToOpen == NULL)
        {
            __spf_print(1, "  try to copy file '%s' to '%s'\n", include.c_str(), newCurrFile.c_str());

            FILE *copyFile = fopen(newCurrFile.c_str(), "w");
            FILE *oldFile = fopen(include.c_str(), "r");
            if (!copyFile)
            {
                __spf_print(1, "  can not open file '%s' for read\n", include.c_str());
                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
            }

            if (!oldFile)
            {
                __spf_print(1, "  can not open file '%s' for write\n", newCurrFile.c_str());
                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
            }
            
            while (!feof(oldFile))
            {
                char buf[8192];
                char *res = fgets(buf, 16384, oldFile);
                if (res == NULL)
                    break;

                const string orig(buf);
                string bufStr(buf);
                convertToLower(bufStr);
                if (!keepSpfDirs)
                {
                    bool spfStart = isSPF_comment(bufStr);
                    if (spfStart)
                        bufStr = "\n";                    
                }
                //remove DVM dirs or save DVM dirs as comment
                if (removeDvmDirs == 1 || removeDvmDirs == 2)
                {
                    if (bufStr[0] == '!' || bufStr[0] == 'c')
                    {
                        if (bufStr[1] == 'd' && bufStr[2] == 'v' && bufStr[3] == 'm' && bufStr[4] == '$')
                        {
                            if (removeDvmDirs == 1)
                                bufStr = "";
                            else if (removeDvmDirs == 2)
                                bufStr.insert(1, " ");
                        }
                    }
                }

                // save original include name
                if (bufStr.find("include") != string::npos)
                    fputs(orig.c_str(), copyFile);
                else
                {
                    if (bufStr != "")
                        fputs(bufStr.c_str(), copyFile);
                }
            }
            fclose(oldFile);
            fclose(copyFile);
            fflush(NULL);
        }
        else
            fclose(tryToOpen);
    }
}

string splitDirective(const string &in_)
{
    if (in_ == "")
        return "";

    string in(in_);
    string lastEnd = "";
    if (in[in.size() - 1] == '\n')
    {
        in.erase(in.begin() + in_.size() - 1);
        lastEnd = "\n";
    }

    string out = "";
    if (in.size() < 71)
        out = in;
    else
    {
        char buf[72];

        int len = in.size() - 71;
        int idx = 71;

        buf[in.copy(buf, 71, 0)] = '\0';
        out += buf;
        if (len > 0)
            out += "\n!DVM$&";

        while (len > 65)
        {
            buf[in.copy(buf, 65, idx)] = '\0';
            out += buf;
            len -= 65;
            idx += 65;

            if (len > 0)
                out += "\n!DVM$&";
        }

        if (len > 0)
        {
            buf[in.copy(buf, 65, idx)] = '\0';
            out += buf;
        }
    }

    return out + lastEnd;
}

string splitDirectiveFull(const string &in_)
{
    if (in_ == "")
        return "";

    string in(in_);
    string lastEnd = "";
    if (in[in.size() - 1] == '\n')
    {
        in.erase(in.begin() + in_.size() - 1);
        lastEnd = "\n";
    }

    string out = "";
    vector<string> splited;
    splitString(in_, '\n', splited);
    for (int z = 0; z < splited.size(); ++z)
    {
        if (z != 0)
            out += "\n";
        out += splitDirective(splited[z]);
    }
    return out + lastEnd;
}

void ExitFromOmegaTest(const int c) { throw c; }
extern "C" void ExitFromParser(const int c) { ExitFromOmegaTest(c); }

void sortFilesBySize(const char *proj_name)
{
    FILE *proj = fopen(proj_name, "r");
    if (proj)
    {
        map<pair<long, string>, string> files;

        while (!feof(proj))
        {
            char buf[512];
            fgets(buf, 512, proj);

            string filename(buf);
            long size;
            FILE *fin = fopen(filename.c_str(), "rb");
            FILE *p_fin = fin;
            if (fin)
            {
                fseek(p_fin, 0, SEEK_END);
                size = ftell(p_fin);
                fclose(fin);
            }
            else
                size = 0;

            files[make_pair(size, filename)] = filename;            
        }

        fclose(proj);
        proj = fopen(proj_name, "w");
        for (auto it = files.rbegin(); it != files.rend(); ++it)
            fwrite(it->second.c_str(), sizeof(char), it->second.size(), proj);
        fclose(proj);
    }
    else
    {
        __spf_print(1, "project file '%s' does not exist\n", proj_name);
        throw(-1);
    }
}

void uniteVectors(const vector<pair<pair<string, string>, vector<pair<int, int>>>> &first,
                  const vector<pair<pair<string, string>, vector<pair<int, int>>>> &second,
                  vector<pair<pair<string, string>, vector<pair<int, int>>>> &result)
{
    int *uniteF = new int[first.size()];
    int *uniteS = new int[second.size()];
    memset(uniteF, 0, sizeof(int) * first.size());
    memset(uniteS, 0, sizeof(int) * second.size());

    for (int i = 0; i < (int)first.size(); ++i)
    {
        const string &arrayName = first[i].first.second;
        int k;
        for (k = 0; k < (int)second.size(); ++k)
        {
            if (uniteS[k] == 0)
            {
                if (arrayName == second[k].first.second)
                {
                    uniteS[k] = 1;
                    break;
                }
            }
        }

        if (k != (int)second.size())
        {
            uniteF[i] = 1;
            assert(first[i].second.size() == second[k].second.size());
            result.push_back(make_pair(first[i].first, vector<pair<int, int>>(first[i].second.size())));

            const vector<pair<int, int>> &boundsF = first[i].second;
            const vector<pair<int, int>> &boundsS = second[k].second;
            for (int z = 0; z < (int)boundsF.size(); ++z)
            {
                pair<int, int> newBounds = std::make_pair(std::max(boundsF[z].first, boundsS[z].first), std::max(boundsF[z].second, boundsS[z].second));
                result.back().second[z] = newBounds;
            }
        }
    }

    for (int i = 0; i < (int)first.size(); ++i)
    {
        if (uniteF[i] == 0)
            result.push_back(first[i]);
    }

    for (int i = 0; i < (int)second.size(); ++i)
    {
        if (uniteS[i] == 0)
            result.push_back(second[i]);
    }

    delete[]uniteF;
    delete[]uniteS;
}

#include <unordered_map>

#define FULL_ERROR_DUMP 1

// pointer -> type of alloc function
#if FULL_ERROR_DUMP
static std::unordered_map<void*, std::tuple<int, int, const char*>> pointerCollection;
static std::unordered_map<void*, std::tuple<int, int, const char*>> pointerCollectionLocal;
#else
static std::unordered_map<void*, std::tuple<int>> pointerCollection;
static std::unordered_map<void*, std::tuple<int>> pointerCollectionLocal;
#endif

static bool deleteInProgress = false;
static void* currentPointer = NULL;
static set<void*> deleted;

static bool storeInLocal = false;

// type == 0 -> free, type == 1 -> delete, type == 2 -> delete[]
// acc_analyzer.h: ControlFlowItem = 3, doLoopItem = 4, doLoops = 5, LabelCFI = 6, CLAStatementItem = 7
//   VarItem = 8, VarSet = 9, DoLoopDataItem = 10, DoLoopDataList = 11
//   CVarEntryInfo = 12, CScalarVarEntryInfo = 13, CRecordVarEntryInfo = 14
//   ArraySubscriptData = 15, CArrayVarEntryInfo = 16, BasicBlockItem = 17,  
//   CallAnalysisLog = 18, CExprList = 19, SymbolKey = 20, CBasicBlock = 21
//   CommonVarSet = 22, AnalysedCallsList = 23, CallData = 24, CommonVarInfo = 25
//   CommonDataItem = 26, CommonData = 27, PrivateDelayedItem = 28, ActualDelayedData = 29
//   ControlFlowGraph = 30
extern "C" void addToCollection(const int line, const char *file, void *pointer, int type)
{
#if FULL_ERROR_DUMP
    if (storeInLocal)
        pointerCollectionLocal.insert(std::make_pair(pointer, std::make_tuple(type, line, file)));
    pointerCollection.insert(std::make_pair(pointer, std::make_tuple(type, line, file)));
#else
    if (storeInLocal)
        pointerCollectionLocal.insert(std::make_pair(pointer, std::make_tuple(type)));
    pointerCollection.insert(std::make_pair(pointer, std::make_tuple(type)));
#endif
}

extern "C" void removeFromCollection(void *pointer)
{
    if (deleteInProgress)
    {
        if (pointer != currentPointer)
            deleted.insert(pointer);
    }
    else
    {        
        auto it = pointerCollection.find(pointer);
        if (it != pointerCollection.end())
            pointerCollection.erase(it);

        if (storeInLocal)
        {
            auto it = pointerCollectionLocal.find(pointer);
            if (it != pointerCollectionLocal.end())
                pointerCollectionLocal.erase(it);
        }
    }
}

void startLocalColletion() { storeInLocal = true; }
void finishLocalColletion() { storeInLocal = false; }

void deleteLeaks()
{
    map<string, int> places;
    auto copy = pointerCollection;
    for (auto& elem : copy)
    {
        string place = std::get<2>(elem.second);
        places[place]++;
        if (place.find("make_nodes.c") != string::npos)
        {
            free((char*)(elem.first));

            auto it = pointerCollection.find(elem.first);
            if (it != pointerCollection.end())
                pointerCollection.erase(it);
        }
    }
}

void deletePointerAllocatedData(bool delLocal)
{
    int leaks = 0;
    int failed = 0;
    deleteInProgress = true;
    deleted.clear();
    int maxS = -1;
    int z = -1;

#if FULL_ERROR_DUMP
    std::unordered_map<void*, std::tuple<int, int, const char*>>* toDelCollection = delLocal ? &pointerCollectionLocal : &pointerCollection;
#else
    std::unordered_map<void*, std::tuple<int>>* toDelCollection = delLocal ? &pointerCollectionLocal : &pointerCollection;
#endif
    for (auto &elem : *toDelCollection)
    {
        ++z;
        maxS = std::max(maxS, (int)deleted.size());

        auto itD = deleted.find(elem.first);
        if (deleted.find(elem.first) != deleted.end())
        {            
            deleted.erase(itD);
            continue;
        }

        const pair<void*, int> pointer = std::make_pair(elem.first, std::get<0>(elem.second));
        currentPointer = pointer.first;
        //printf("[%d]: %d %s\n", z, std::get<1>(elem.second), std::get<2>(elem.second));
        //fflush(NULL);
        if (pointer.second == 0)
        {
            if (pointer.first)
            {
                free((char*)(pointer.first));
                leaks++;
            }
            else
                failed++;
        }
        else if (pointer.second == 1)
        {
            if (pointer.first)
            {
                delete (char*)(pointer.first);
                leaks++;
            }
            else
                failed++;
        }
        else if (pointer.second == 2)
        {
            if (pointer.first)
            {
                delete [](char*)(pointer.first);
                leaks++;
            }
            else
                failed++;
        }
        else if (pointer.second >= 3 && pointer.second <= 30)
        {
            if (pointer.first)
            {
                switch (pointer.second)
                {
#if __SPF
                case 3: delete (ControlFlowItem*)pointer.first; break;
                case 4: delete (doLoopItem*)pointer.first; break;
                case 5: delete (doLoops*)pointer.first; break;
                case 6: delete (LabelCFI*)pointer.first; break;
                case 7: delete (CLAStatementItem*)pointer.first; break;
                case 8: delete (VarItem*)pointer.first; break;
                case 9: delete (VarSet*)pointer.first; break;
                case 10: delete (DoLoopDataItem*)pointer.first; break;
                case 11: delete (DoLoopDataList*)pointer.first; break;
                case 12: delete (CVarEntryInfo*)pointer.first; break;
                case 13: delete (CScalarVarEntryInfo*)pointer.first; break;
                case 14: delete (CRecordVarEntryInfo*)pointer.first; break;
                case 15: delete (ArraySubscriptData*)pointer.first; break;
                case 16: delete (CArrayVarEntryInfo*)pointer.first; break;
                case 17: delete (BasicBlockItem*)pointer.first; break;
                case 18: delete (CallAnalysisLog*)pointer.first; break;
                case 19: delete (CExprList*)pointer.first; break;
                case 20: delete (SymbolKey*)pointer.first; break;
                case 21: delete (CBasicBlock*)pointer.first; break;
                case 22: delete (CommonVarSet*)pointer.first; break;
                case 23: delete (AnalysedCallsList*)pointer.first; break;
                case 24: delete (CallData*)pointer.first; break;
                case 25: delete (CommonVarInfo*)pointer.first; break;
                case 26: delete (CommonDataItem*)pointer.first; break;
                case 27: delete (CommonData*)pointer.first; break;
                case 28: delete (PrivateDelayedItem*)pointer.first; break;
                case 29: delete (ActualDelayedData*)pointer.first; break;
                case 30: delete (ControlFlowGraph*)pointer.first; break;
#endif
                default:
                    break;
                }

                leaks++;
            }
            else
                failed++;
        }
    }

    if (leaks > 0)
        printf("SAPFOR: detected %d leaks of memory\n", leaks);
    if (failed > 0)
        printf("SAPFOR: detected failed %d leaks of memory\n", failed);
    printf("SAPFOR: deleted set size %d, maxS = %d\n", (int)deleted.size(), maxS);

    toDelCollection->clear();
    deleted.clear();
    deleteInProgress = false;
    currentPointer = NULL;
}

static unsigned arrayIdCounter = 0;
unsigned getUniqArrayId() { return arrayIdCounter++; }

static bool isAllRulesEqualWA_l(const vector<vector<tuple<DIST::Array*, int, pair<int, int>>>> &rules)
{
    if (rules.size() <= 1)
        return true;
    else
    {
        vector<tuple<DIST::Array*, int, pair<int, int>>> first = rules[0];
        for (auto &elem : rules)
        {
            int z = 0;
            if (elem.size() != first.size())
                return false;
            for (auto &item : elem)
                if (std::get<2>(item) != std::get<2>(first[z++]))
                    return false;
        }
        return true;
    }
}

template<typename T>
static bool isAllRulesEqual_l(T rules)
{
    if (rules.size() <= 1)
        return true;
    else
    {
        for (auto &elem : rules)
            if (elem != rules[0])
                return false;
        return true;
    }
}

template<typename T>
static bool isAllRulesEqual_p(T rules)
{
    if (rules.size() <= 1)
        return true;
    else
    {
        for (auto &elem : rules)
            if (elem != rules[0])
                return false;
        return true;
    }
}

bool isAllRulesEqualWithoutArray(const vector<vector<tuple<DIST::Array*, int, pair<int, int>>>> &allRules)
{
    return isAllRulesEqualWA_l(allRules);
}

bool isAllRulesEqual(const vector<vector<tuple<DIST::Array*, int, pair<int, int>>>> &allRules)
{
    return isAllRulesEqual_l(allRules);
}

bool isAllRulesEqual(const vector<vector<int>> &allRules)
{
    return isAllRulesEqual_l(allRules);
}

bool isAllRulesEqual(const vector<vector<pair<int, int>>> &allRules)
{
    return isAllRulesEqual_p(allRules);
}

static int newLineNumber = -2; // -1 is used for OMP
int getNextNegativeLineNumber()
{
    int ret = newLineNumber;
    newLineNumber--;
    return ret;
}

void findAndReplaceDimentions(vector<tuple<DIST::Array*, int, pair<int, int>>> &rule, const DIST::Arrays<int> &allArrays)
{
    for (int i = 0; i < rule.size(); ++i)
    {
        if (std::get<0>(rule[i]) == NULL)
            continue;
        int alignTo = -1;
        int ok = allArrays.GetDimNumber(std::get<0>(rule[i]), (std::get<1>(rule[i])), alignTo);
        if (ok != 0)
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

        (std::get<1>(rule[i])) = alignTo;
    }
}

vector<int> findLinksBetweenArrays(DIST::Array *from, DIST::Array *to, const uint64_t regionId)
{
    vector<int> retVal(from->GetDimSize());
    std::fill(retVal.begin(), retVal.end(), -1);

    if (to->IsTemplate())
    {
        if (to != from->GetTemplateArray(regionId))
            return retVal;
        else
            return from->GetLinksWithTemplate(regionId);
    }
    else
    {
        if (to->GetTemplateArray(regionId) != from->GetTemplateArray(regionId))
        {
            string leftT = to->GetTemplateArray(regionId) ? to->GetTemplateArray(regionId)->GetShortName() : "nul";
            string rightT = from->GetTemplateArray(regionId) ? from->GetTemplateArray(regionId)->GetShortName() : "nul";
            __spf_print(1, "regionId = %d: templates for array %s and %s not eq: %s != %s\n", 
                        regionId, from->GetName().c_str(), to->GetName().c_str(), leftT.c_str(), rightT.c_str());
        }
        else
        {
            auto ruleL = from->GetLinksWithTemplate(regionId);
            auto ruleR = to->GetLinksWithTemplate(regionId);

            int currD = 0;
            for (auto &elem1 : ruleL)
            {                
                int idx = 0;
                for (auto &elem2 : ruleR)
                {
                    if (elem2 == elem1)
                    {
                        retVal[currD] = idx;
                        break;
                    }
                    ++idx;
                }
                ++currD;
            }
        }

        return retVal;
    }
}

std::wstring to_wstring(const std::string str) { return std::wstring(str.begin(), str.end()); }

template<typename objT>
objT& getObjectForFileFromMap(const char *fileName, map<string, objT> &mapObject)
{
    auto it = mapObject.find(fileName);
    if (it == mapObject.end())
        it = mapObject.insert(it, std::make_pair(fileName, objT()));
    return it->second;
}

template vector<Messages>& getObjectForFileFromMap(const char *fileName, map<string, vector<Messages>>&);
template vector<LoopGraph*>& getObjectForFileFromMap(const char *fileName, map<string, vector<LoopGraph*>>&);
template vector<FuncInfo*>& getObjectForFileFromMap(const char *fileName, map<string, vector<FuncInfo*>>&);
template map<int, Gcov_info>& getObjectForFileFromMap(const char *fileName, map<string, std::map<int, Gcov_info>>&);
template map<int, double>& getObjectForFileFromMap(const char *fileName, map<string, std::map<int, double>>&);

static set<string> mpiFunctions;
bool isMpiFunction(const string& func)
{
    if (mpiFunctions.size() == 0)
    {
        mpiFunctions.insert("mpi_address");
        mpiFunctions.insert("mpi_allgather");
        mpiFunctions.insert("mpi_allgatherv");
        mpiFunctions.insert("mpi_allreduce");
        mpiFunctions.insert("mpi_alltoall");
        mpiFunctions.insert("mpi_alltoallv");
        mpiFunctions.insert("mpi_barrier");
        mpiFunctions.insert("mpi_bcast");
        mpiFunctions.insert("mpi_bsend");
        mpiFunctions.insert("mpi_bsend_init");
        mpiFunctions.insert("mpi_buffer_attach");
        mpiFunctions.insert("mpi_buffer_detach");
        mpiFunctions.insert("mpi_cart_coords");
        mpiFunctions.insert("mpi_cart_create");
        mpiFunctions.insert("mpi_cart_get");
        mpiFunctions.insert("mpi_cart_rank");
        mpiFunctions.insert("mpi_cart_shift");
        mpiFunctions.insert("mpi_cart_sub");
        mpiFunctions.insert("mpi_cartdim_get");
        mpiFunctions.insert("mpi_comm_create");
        mpiFunctions.insert("mpi_comm_dup");
        mpiFunctions.insert("mpi_comm_free");
        mpiFunctions.insert("mpi_comm_group");
        mpiFunctions.insert("mpi_comm_rank");
        mpiFunctions.insert("mpi_comm_size");
        mpiFunctions.insert("mpi_comm_split");
        mpiFunctions.insert("mpi_dims_create");
        mpiFunctions.insert("mpi_finalize");
        mpiFunctions.insert("mpi_gather");
        mpiFunctions.insert("mpi_gatherv");
        mpiFunctions.insert("mpi_get_count");
        mpiFunctions.insert("mpi_get_processor_name");
        mpiFunctions.insert("mpi_graph_create");
        mpiFunctions.insert("mpi_graph_get");
        mpiFunctions.insert("mpi_graph_neighbors");
        mpiFunctions.insert("mpi_graph_neighbors_count");
        mpiFunctions.insert("mpi_graphdims_get");
        mpiFunctions.insert("mpi_group_compare");
        mpiFunctions.insert("mpi_group_difference");
        mpiFunctions.insert("mpi_group_excl");
        mpiFunctions.insert("mpi_group_free");
        mpiFunctions.insert("mpi_group_incl");
        mpiFunctions.insert("mpi_group_intersection");
        mpiFunctions.insert("mpi_group_rank");
        mpiFunctions.insert("mpi_group_size");
        mpiFunctions.insert("mpi_group_translate_ranks");
        mpiFunctions.insert("mpi_group_union");
        mpiFunctions.insert("mpi_ibsend");
        mpiFunctions.insert("mpi_init");
        mpiFunctions.insert("mpi_initialized");
        mpiFunctions.insert("mpi_iprobe");
        mpiFunctions.insert("mpi_irecv");
        mpiFunctions.insert("mpi_irsend");
        mpiFunctions.insert("mpi_isend");
        mpiFunctions.insert("mpi_issend");
        mpiFunctions.insert("mpi_op_create");
        mpiFunctions.insert("mpi_op_free");
        mpiFunctions.insert("mpi_pack");
        mpiFunctions.insert("mpi_pack_size");
        mpiFunctions.insert("mpi_probe");
        mpiFunctions.insert("mpi_recv");
        mpiFunctions.insert("mpi_recv_init");
        mpiFunctions.insert("mpi_reduce");
        mpiFunctions.insert("mpi_reduce_scatter");
        mpiFunctions.insert("mpi_request_free");
        mpiFunctions.insert("mpi_rsend");
        mpiFunctions.insert("mpi_rsend_init");
        mpiFunctions.insert("mpi_scan");
        mpiFunctions.insert("mpi_scatter");
        mpiFunctions.insert("mpi_scatterv");
        mpiFunctions.insert("mpi_send");
        mpiFunctions.insert("mpi_send_init");
        mpiFunctions.insert("mpi_sendrecv");
        mpiFunctions.insert("mpi_sendrecv_replace");
        mpiFunctions.insert("mpi_ssend");
        mpiFunctions.insert("mpi_ssend_init");
        mpiFunctions.insert("mpi_start");
        mpiFunctions.insert("mpi_startall");
        mpiFunctions.insert("mpi_test");
        mpiFunctions.insert("mpi_testall");
        mpiFunctions.insert("mpi_testany");
        mpiFunctions.insert("mpi_testsome");
        mpiFunctions.insert("mpi_topo_test");
        mpiFunctions.insert("mpi_type_commit");
        mpiFunctions.insert("mpi_type_contiguous");
        mpiFunctions.insert("mpi_type_extent");
        mpiFunctions.insert("mpi_type_free");
        mpiFunctions.insert("mpi_type_hindexed");
        mpiFunctions.insert("mpi_type_hvector");
        mpiFunctions.insert("mpi_type_indexed");
        mpiFunctions.insert("mpi_type_lb");
        mpiFunctions.insert("mpi_type_size");
        mpiFunctions.insert("mpi_type_struct");
        mpiFunctions.insert("mpi_type_ub");
        mpiFunctions.insert("mpi_type_vector");
        mpiFunctions.insert("mpi_unpack");
        mpiFunctions.insert("mpi_wait");
        mpiFunctions.insert("mpi_waitall");
        mpiFunctions.insert("mpi_waitany");
        mpiFunctions.insert("mpi_waitsome");
        mpiFunctions.insert("mpi_wtick");
        mpiFunctions.insert("mpi_wtime");
    }

    return mpiFunctions.find(func) != mpiFunctions.end();
}

map<DIST::Array*, DIST::ArrayAccessInfo*> createMapOfArrayAccess(const map<tuple<int, string, string>, pair<DIST::Array*, DIST::ArrayAccessInfo*>> &declaredArrays)
{
    map<DIST::Array*, DIST::ArrayAccessInfo*> out;

    for (auto& elem : declaredArrays)
        out[elem.second.first] = elem.second.second;
    return out;
}

string readFileToStr(const string& name)
{
    string sf;
    std::ifstream inf;

    inf.open(name);
    if (!inf)
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

    getline(inf, sf, '\0');
    inf.close();
    return sf;
}

void writeFileFromStr(const string& name, const string &data)
{
    string sf;
    std::ofstream outf;

    outf.open(name);
    if (!outf)
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
    outf << data;    
    outf.close();
}

ParallelRegion* getRegionById(const vector<ParallelRegion*>& regions, const uint64_t regionId)
{
    for (auto& region : regions)
        if (region->GetId() == regionId)
            return region;

    return NULL;
}

ParallelRegion* getRegionByName(const vector<ParallelRegion*>& regions, const string& regionName)
{
    string test = regionName;
    convertToLower(test);

    for (auto& region : regions)
        if (region->GetName() == test)
            return region;

    return NULL;
}


ParallelRegion* getRegionByLine(const vector<ParallelRegion*>& regions, const string& file, const int line)
{
    if (regions.size() == 1 && regions[0]->GetName() == "DEFAULT") // only default
        return regions[0];
    else if (regions.size() > 0)
    {
        set<ParallelRegion*> regFound;

        for (int i = 0; i < regions.size(); ++i)
            if (regions[i]->HasThisLine(line, file))
                regFound.insert(regions[i]);

        if (regFound.size() == 0)
            return NULL;
        else if (regFound.size() == 1)
            return *regFound.begin();
        else
        {
            __spf_print(1, "WARN: this lines included in more than one region!!\n");
            return NULL;
        }
    }
    else
        return NULL;

    return NULL;
}

set<ParallelRegion*> getAllRegionsByLine(const vector<ParallelRegion*>& regions, const string& file, const int line)
{
    set<ParallelRegion*> regFound;

    if (regions.size() == 1 && regions[0]->GetName() == "DEFAULT") // only default
        regFound.insert(regions[0]);
    else if (regions.size() > 0)
    {
        for (int i = 0; i < regions.size(); ++i)
            if (regions[i]->HasThisLine(line, file))
                regFound.insert(regions[i]);
    }

    return regFound;
}

pair<vector<string>, vector<string>> splitCommandLineForParse(char** argv, int argc)
{
    vector<string> options;
    vector<string> files;

    //fdv|f|ftn|for|f90|f95|f03
    for (int z = 0; z < argc; ++z)
    {
        string isFile = argv[z];
        if (isFile.find(".for") != string::npos ||
            isFile.find(".f90") != string::npos ||
            isFile.find(".fdv") != string::npos ||
            isFile.find(".ftn") != string::npos ||
            isFile.find(".f95") != string::npos ||
            isFile.find(".f03") != string::npos ||
            isFile.find(".f") != string::npos)
        {
            files.push_back(isFile);
        }
        else
            options.push_back(isFile);
    }

    return make_pair(options, files);
}
