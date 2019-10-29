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
#if __SPF
#include "acc_analyzer.h"
#endif

#ifdef _MSC_VER
#include <io.h>
#define popen _popen 
#define pclose _pclose
#define stat _stat 
#define dup _dup
#define dup2 _dup2
#define fileno _fileno
#define close _close
#define pipe _pipe
#define read _read
#define eof _eof
#else
#include <unistd.h>
#endif

#ifndef STD_OUT_FD 
#define STD_OUT_FD (fileno(stdout)) 
#endif 

#ifndef STD_ERR_FD 
#define STD_ERR_FD (fileno(stderr)) 
#endif

#include <fcntl.h>
#include <stdio.h>
#include <mutex>

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
#ifdef __SPF
    removeFromCollection(basename);
#endif
    delete []basename;

    return retVal;
}

string OnlyExt(const char *filename)
{
    char *extname = new char[16];
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
#ifdef __SPF
    removeFromCollection(extname);
#endif
    delete []extname;
    return retVal;
}

void printHelp(const char **passNames, const int lastPass)
{
    printf("Help info for passes.\n\n");
    printf(" -f90      free form\n");
    //printf(" -sh      turn on static shadow analysis\n");
    printf(" -ver/-Ver version of SAPFOR\n");
    printf(" -priv     turn on static private analysis\n");
    printf(" -keep     keep temporary files\n");
    printf(" -keepSPF  keep SPF directives\n");
    printf(" -keepDVM  keep DVM directives\n");
    printf(" -allVars  get all parallel versions\n");
    printf(" -var N    get specific parallel version, N=1,2,..\n");
    printf(" -parse    run parser with next option\n");
    //printf(" -q1 Q     quality of analysis in percent (1..100, default 100)\n");
    //printf(" -q2 S     speed of analysis in percent   (1..100, default 100)\n");
    printf("\n");    
    printf(" -F    <folderName> output to folder\n");
    printf(" -p    <project name>\n");    
    printf(" -pass <pass_number>\n");
    for (int i = 0; i < lastPass; ++i)
        printf("    pass_num = %d:  %s\n", i, passNames[i]);
    printf("\n");
    printf(" -t    <analysis_num>\n");
    printf("    analysis_num = 1:  loops unroller\n");
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
    printf("    analysis_num = 12: create parallel directives\n");
    printf("    analysis_num = 13: insert directives\n");
    printf("    analysis_num = 14: create array graph\n");
    printf("    analysis_num = 15: check private analysis\n");
    printf("    analysis_num = 16: insert includes\n");
    printf("    analysis_num = 17: remove DVM directives\n");

    throw(-1);
}

void printVersion()
{
    printf("SAPFOR version is %s, build date: %s %s\n", VERSION, __DATE__, __TIME__);
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

void splitString(const string &strIn, const char delim, vector<string> &result)
{
    std::stringstream ss;
    ss.str(strIn);

    std::string item;
    while (std::getline(ss, item, delim))
        result.push_back(item);    
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
    while (tmp[t] != '\\' && t < tmp.size())
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
void convertGlobalBuffer(short *&result, int *&resultSize)
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

void convertGlobalMessagesBuffer(short *&result, int *&resultSize)
{
    auto copySPF_messages = SPF_messages;
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

// pointer -> type of alloc function
static std::unordered_map<void*, std::tuple<int, int, const char*>> pointerCollection;
static bool deleteInProgress = false;
static void* currentPointer = NULL;
static set<void*> deleted;

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
    pointerCollection.insert(std::make_pair(pointer, std::make_tuple(type, line, file)));
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
        if (pointerCollection.size() == 0)
            return;

        auto it = pointerCollection.find(pointer);
        if (it != pointerCollection.end())
            pointerCollection.erase(it);
    }
}

void deletePointerAllocatedData()
{
    int leaks = 0;
    int failed = 0;
    deleteInProgress = true;
    deleted.clear();
    int maxS = -1;
    int z = -1;
    for (auto &elem : pointerCollection)
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

    pointerCollection.clear();
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

vector<int> findLinksBetweenArrays(DIST::Array *from, DIST::Array *to, const int regionId)
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

map<DIST::Array*, DIST::ArrayAccessInfo*> createMapOfArrayAccess(const map<tuple<int, string, string>, pair<DIST::Array*, DIST::ArrayAccessInfo*>> &declaratedArrays)
{
    map<DIST::Array*, DIST::ArrayAccessInfo*> out;

    for (auto& elem : declaratedArrays)
        out[elem.second.first] = elem.second.second;
    return out;
}

class StdCapture
{
public:
    static void Init()
    {
        // make stdout & stderr streams unbuffered
        // so that we don't need to flush the streams
        // before capture and after capture 
        // (fflush can cause a deadlock if the stream is currently being 
        std::lock_guard<std::mutex> lock(m_mutex);
        setvbuf(stdout, NULL, _IONBF, 0);
        setvbuf(stderr, NULL, _IONBF, 0);
    }

    static void BeginCapture()
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        if (m_capturing)
            return;

        secure_pipe(m_pipe);
        m_oldStdOut = secure_dup(STD_OUT_FD);
        m_oldStdErr = secure_dup(STD_ERR_FD);
        secure_dup2(m_pipe[WRITE], STD_OUT_FD);
        secure_dup2(m_pipe[WRITE], STD_ERR_FD);
        m_capturing = true;
#ifndef _MSC_VER
        secure_close(m_pipe[WRITE]);
#endif
    }
    static bool IsCapturing()
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        return m_capturing;
    }
    static void EndCapture()
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        if (!m_capturing)
            return;

        m_captured.clear();
        secure_dup2(m_oldStdOut, STD_OUT_FD);
        secure_dup2(m_oldStdErr, STD_ERR_FD);

        const int bufSize = 1025;
        char buf[bufSize];
        int bytesRead = 0;
        bool fd_blocked(false);
        do
        {
            bytesRead = 0;
            fd_blocked = false;
#ifdef _MSC_VER
            if (!eof(m_pipe[READ]))
                bytesRead = read(m_pipe[READ], buf, bufSize - 1);
#else
            bytesRead = read(m_pipe[READ], buf, bufSize - 1);
#endif
            if (bytesRead > 0)
            {
                buf[bytesRead] = 0;
                m_captured += buf;
            }
            else if (bytesRead < 0)
            {
                fd_blocked = (errno == EAGAIN || errno == EWOULDBLOCK || errno == EINTR);
                if (fd_blocked)
                    std::this_thread::sleep_for(std::chrono::milliseconds(10));
            }
        } while (fd_blocked || bytesRead == (bufSize - 1));

        secure_close(m_oldStdOut);
        secure_close(m_oldStdErr);
        secure_close(m_pipe[READ]);
#ifdef _MSC_VER
        secure_close(m_pipe[WRITE]);
#endif
        m_capturing = false;
    }
    static std::string GetCapture()
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        return m_captured;
    }
private:
    enum PIPES { READ, WRITE };

    static int secure_dup(int src)
    {
        int ret = -1;
        bool fd_blocked = false;
        do
        {
            ret = dup(src);
            fd_blocked = (errno == EINTR || errno == EBUSY);
            if (fd_blocked)
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
        } while (ret < 0);
        return ret;
    }
    static void secure_pipe(int* pipes)
    {
        int ret = -1;
        bool fd_blocked = false;
        do
        {
#ifdef _MSC_VER
            ret = pipe(pipes, 65536, O_BINARY);
#else
            ret = pipe(pipes) == -1;
#endif
            fd_blocked = (errno == EINTR || errno == EBUSY);
            if (fd_blocked)
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
        } while (ret < 0);
    }
    static void secure_dup2(int src, int dest)
    {
        int ret = -1;
        bool fd_blocked = false;
        do
        {
            ret = dup2(src, dest);
            fd_blocked = (errno == EINTR || errno == EBUSY);
            if (fd_blocked)
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
        } while (ret < 0);
    }

    static void secure_close(int& fd)
    {
        int ret = -1;
        bool fd_blocked = false;
        do
        {
            ret = close(fd);
            fd_blocked = (errno == EINTR);
            if (fd_blocked)
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
        } while (ret < 0);

        fd = -1;
    }

    static int m_pipe[2];
    static int m_oldStdOut;
    static int m_oldStdErr;
    static bool m_capturing;
    static std::mutex m_mutex;
    static std::string m_captured;
};

// actually define vars.
int StdCapture::m_pipe[2];
int StdCapture::m_oldStdOut;
int StdCapture::m_oldStdErr;
bool StdCapture::m_capturing;
std::mutex StdCapture::m_mutex;
std::string StdCapture::m_captured;

struct FileInfo
{
    FileInfo() { }
    FileInfo(const string& _fileName, const string& _options, const string& _errPath, const string& _outPath)
    {
        fileName = _fileName;
        options = _options;
        errPath = _errPath;
        outPath = _outPath;
    }

    string fileName;
    string options;
    string errPath;
    string outPath;
};

extern "C" int parse_file(int argc, char* argv[], char* proj_name);
int parseFiles(const char *proj)
{
    FILE* list = fopen(proj, "r");
    if (!list)
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

    vector<FileInfo> listOfProject;
    while (!feof(list))
    {
        char buf[1024];
        if (fgets(buf, 1024, list) == NULL)
            continue;

        string toAdd = buf;
        if (toAdd[toAdd.size() - 1] == '\n')
            toAdd = toAdd.erase(toAdd.size() - 1);

        const string fileNameFixed = (toAdd.substr(0, 2) == "./" ? toAdd.substr(2) : toAdd);
        const string optPath = "./visualiser_data/options/" + fileNameFixed + ".opt";
        const string errPath = "./visualiser_data/options/" + fileNameFixed + ".err";
        const string outPath = "./visualiser_data/options/" + fileNameFixed + ".out";

        FILE* opt = fopen(optPath.c_str(), "r");
        if (!opt)
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
        fgets(buf, 1024, opt);
        string toAddOpt = buf;
        if (toAddOpt[toAddOpt.size() - 1] == '\n')
            toAddOpt = toAddOpt.erase(toAddOpt.size() - 1);

        fclose(opt);
        listOfProject.push_back(FileInfo(fileNameFixed, toAddOpt, errPath, outPath));
    }

    fclose(list);
    int countOfErrors = 0;
    for (auto &elem : listOfProject)
    {
        string file = elem.fileName;
        string options = elem.options;

        vector<string> optSplited;
        splitString(options, ' ', optSplited);

        vector<string> optSplited1;
        for (auto& elem : optSplited)
            if (elem != "")
                optSplited1.push_back(elem);
        optSplited1.insert(optSplited1.begin(), "");

        char** toParse = new char*[optSplited1.size() + 1];
        for (int z = 0; z < optSplited1.size(); ++z)
        {            
            //printf("%s\n", optSplited1[z].c_str());
            if (optSplited1[z][0] == '"' && optSplited1[z][optSplited1[z].size() - 1] == '"')
                optSplited1[z] = optSplited1[z].substr(1, optSplited1[z].size() - 2);
            toParse[z] = (char*)optSplited1[z].c_str();
        }
        toParse[optSplited1.size()] = (char*)file.c_str();

        StdCapture::Init();
        string errorMessage = "";
        try
        {
            StdCapture::BeginCapture();
            int retCode = parse_file(optSplited1.size() + 1, toParse, "dvm.proj");
            if (retCode != 0)
                countOfErrors++;
            StdCapture::EndCapture();
            errorMessage = StdCapture::GetCapture();
        }
        catch (int err)
        {
            countOfErrors++;
            StdCapture::EndCapture();
            errorMessage = StdCapture::GetCapture();
        }
        catch (...)
        {
            countOfErrors++;
            StdCapture::EndCapture();
            errorMessage = StdCapture::GetCapture();
        }

        FILE* ferr = fopen(elem.errPath.c_str(), "w");
        FILE* fout = fopen(elem.outPath.c_str(), "w");
        if (!ferr)
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
        if (!fout)
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
        fclose(fout);

        fprintf(ferr, "%s", errorMessage.c_str());
        fclose(ferr);
        
        delete []toParse;
    }    
    //return (countOfErrors == 0) ? 0 : countOfErrors;
    return 0;
}

extern int pppa_analyzer(int argv, char** argc);
int pppaAnalyzer(const char* options)
{
    string optionsS(options);
    vector<string> splited;

    splited.push_back("");
    splitString(optionsS, ' ', splited);

    char** argv = new char* [splited.size()];
    for (int z = 0; z < splited.size(); ++z)
        argv[z] = (char*)splited[z].c_str();

    StdCapture::Init();
    string errorMessage = "";
    int retCode = pppa_analyzer(splited.size(), argv);
    StdCapture::EndCapture();
    errorMessage = StdCapture::GetCapture();

    delete []argv;
    return retCode;
}