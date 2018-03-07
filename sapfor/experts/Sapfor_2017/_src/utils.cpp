#include "leak_detector.h"

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

#include "utils.h"
#include "errors.h"
#include "version.h"

#include "GraphLoop/graph_loops.h"

using std::map;
using std::pair;
using std::tuple;
using std::set;
using std::vector;
using std::string;

void createMapLoopGraph(map<int, LoopGraph*> &sortedLoopGraph, const vector<LoopGraph*> *loopGraph)
{
    if (loopGraph)
    {
        for (int i = 0; i < (int)loopGraph->size(); ++i)
        {
            sortedLoopGraph[(*loopGraph)[i]->lineNum] = (*loopGraph)[i];
            createMapLoopGraph(sortedLoopGraph, &((*loopGraph)[i]->childs));
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
#ifdef _WIN32
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
#ifdef _WIN32
    removeFromCollection(extname);
#endif
    delete []extname;
    return retVal;
}

void printHelp()
{
    printf("Help info for passes.\n\n");
    printf(" -f90     free form\n");
    //printf(" -sh      turn on static shadow analysis\n");
    printf(" -priv    turn on static private analysis\n");
    printf(" -keep    keep temporary files\n");
    printf(" -keepSPF keep SPF directives\n");
    printf(" -keepDVM keep DVM directives\n");
    printf(" -allVars get all parallel versions\n");
    printf(" -Var N   get specific parallel version, N=1,2,..\n");
    printf(" -q Q     quantity of analysis\n");
    printf("\n");
    printf(" -F    <folderName> output to folder\n");
    printf(" -p    <project name>\n");    
    printf(" -pass <pass_number>\n");
    for (int i = 0; i < EMPTY_PASS; ++i)
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

void convertGlobalBuffer(short *&result, int *&resultSize)
{
    const unsigned len = (unsigned)globalOutputBuffer.size(); 
    result = new short[len + 1];
    result[len] = '\0';
    for (unsigned i = 0; i < len; ++i)
        result[i] = globalOutputBuffer[i];

    resultSize = new int[1];
    resultSize[0] = (int)len;
}

extern map<string, vector<Messages>> SPF_messages; //file ->messages
void clearGlobalMessagesBuffer() { SPF_messages.clear();  }

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

    string val = "";
    val += std::to_string(copySPF_messages.size());
    for (auto it = copySPF_messages.begin(); it != copySPF_messages.end(); ++it)
    {
        val += "|" + it->first + "|" + std::to_string(it->second.size());
        for (int k = 0; k < it->second.size(); ++k)
            val += it->second[k].toString();
    }
    
    const unsigned len = (unsigned)val.size();
    result = new short[len + 1];
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
        bufStr[1] == '$' && bufStr[2] == 's' &&
        bufStr[3] == 'p' && bufStr[4] == 'f';

    return spfStart;
}

void copyIncludes(const set<string> &allIncludeFiles, const map<string, map<int, set<string>>> &commentsToInclude, const char *folderName)
{
    for (auto it = allIncludeFiles.begin(); it != allIncludeFiles.end(); ++it)
    {
        if (commentsToInclude.find(*it) != commentsToInclude.end())
            continue;

        string currFile = *it;
        string newCurrFile = string(folderName) + "\\" + currFile;
        
        FILE *tryToOpen = fopen(newCurrFile.c_str(), "r");
        if (tryToOpen == NULL)
        {
            __spf_print(1, "  try to copy file '%s' to '%s'\n", currFile.c_str(), newCurrFile.c_str());

            FILE *copyFile = fopen(newCurrFile.c_str(), "w");
            FILE *oldFile = fopen(currFile.c_str(), "r");
            if (!copyFile)
            {
                __spf_print(1, "  can not open file '%s' for read\n", currFile.c_str());
                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
            }

            if (!oldFile)
            {
                __spf_print(1, "  can not open file '%s' for write\n", newCurrFile.c_str());
                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
            }
            
            while (!feof(oldFile))
            {
                char buf[16384];
                char *res = fgets(buf, 16384, oldFile);
                if (res == NULL)
                    break;

                string bufStr(buf);
                convertToLower(bufStr);
                if (!keepSpfDirs)
                {
                    bool spfStart = isSPF_comment(bufStr);
                    if (spfStart)
                        bufStr = "\n";
                    fputs(bufStr.c_str(), copyFile);
                    continue;
                }
                fputs(bufStr.c_str(), copyFile);
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

extern "C" void ExitFromOmegaTest(const int c) { throw c; }

static map<string, pair<int, int>> localLinesControl;
static map<string, int> localLastLines;

void startLineControl(const string &file, const int lineStart, const int lineEnd)
{
    localLinesControl.clear();
    localLastLines.clear();

    localLinesControl.insert(std::make_pair(file, std::make_pair(lineStart, lineEnd)));
    localLastLines.insert(std::make_pair(file, lineStart));
}

// this checker is not correct after code transformations
int checkThisLine(const string &file, const int line)
{
    return 0;

    /*if (line == 0)
        return 0;

    auto it1 = localLinesControl.find(file);
    if (it1 != localLinesControl.end())
    {
        auto it2 = localLastLines.find(file);
        if (it2 == localLastLines.end())
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
        else
        {
            if (it2->second > line)
                return -1;
            else if (line < it1->second.first || line > it1->second.second)
                return -1;
            else
                it2->second = line;
        }
    }

    return 0;*/
}

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
            if (fin)
            {
                fseek(fin, 0, SEEK_END);
                size = ftell(fin);
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


// pointer -> type of alloc function
static map<void*, std::tuple<int, int, const char*>> pointerCollection;
// type == 0 -> free, type == 1 -> delete, type == 2 -> delete[]
extern "C" void addToCollection(const int line, const char *file, void *pointer, int type)
{
    auto it = pointerCollection.find(pointer);
    if (it == pointerCollection.end())
        pointerCollection.insert(it, std::make_pair(pointer, std::make_tuple(type, line, file)));
}

extern "C" void removeFromCollection(void *pointer)
{
    auto it = pointerCollection.find(pointer);
    if (it != pointerCollection.end())
        pointerCollection.erase(it);
}

void deletePointerAllocatedData()
{
#ifdef _WIN32
    int leaks = 0;
    int failed = 0;
    for (auto it = pointerCollection.begin(); it != pointerCollection.end(); ++it)
    {
        //printf("%d %s\n", std::get<1>(it->second), std::get<2>(it->second));
        //fflush(NULL);
        if (std::get<0>(it->second) == 0)
        {
            if (it->first)
            {
                free((char*)(it->first));
                leaks++;
            }
            else
                failed++;
        }
        else if (std::get<0>(it->second) == 1)
        {
            if (it->first)
            {
                delete (char*)(it->first);
                leaks++;
            }
            else
                failed++;
        }
        else if (std::get<0>(it->second) == 2)
        {
            if (it->first)
            {
                delete [](char*)(it->first);
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
#endif
}

static unsigned arrayIdCounter = 0;
unsigned getUniqArrayId() { return arrayIdCounter++; }

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
            if (*elem != *rules[0])
                return false;
        return true;
    }
}

bool isAllRulesEqual(const vector<vector<tuple<DIST::Array*, int, pair<int, int>>>> &allRules)
{
    return isAllRulesEqual_l(allRules);
}

bool isAllRulesEqual(const vector<vector<int>> &allRules)
{
    return isAllRulesEqual_l(allRules);
}

bool isAllRulesEqual(const vector<const vector<pair<int, int>>*> &allRules)
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