#include "../Utils/leak_detector.h"

#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>
#include <map>

#include "dvm.h"
#include "gCov_parser_func.h"
#include "../Utils/SgUtils.h"

using namespace std;

enum key_word
{
    UNKNOWN,
    BRANCH,
    CALL,
};

static const char *key_words[] = 
{
    "",
    "branch",
    "call",
    "taken",
    "returned",
    NULL
};

static const char *symbols_neverExecuted[] = 
{
    "",
    "#####",
    "%%%%%",
    "$$$$$",
    "=====",
    NULL
};

static void isKeyWord(const string &lex, key_word &lineType) 
{
    int i = 1;
    bool find = false;
    while ((!find) && key_words[i]) {
        if (lex.compare(key_words[i]) == 0)
            find = true;
        else
            i++;
    }
    switch (i) {
    case 1:
        lineType = BRANCH;
        break;
    case 2:
        lineType = CALL;
        break;
    default:
        if (lineType != UNKNOWN)
        {
            __spf_print(1, "Error: Wrong work of analysis keywords\n");
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
        }
    }
}

static bool isNeverExecuted(const string &lex) 
{
    int i = 1;
    bool find = false;
    while ((!find) && symbols_neverExecuted[i]) 
    {
        if (lex.compare(symbols_neverExecuted[i]) == 0)
            find = true;
        else
            i++;
    }
    return find;
}

static void getInfo(map<int, Gcov_info> &info, const string &str) 
{
    Gcov_info infoLine;
    Perform infoPerform;
    string num, lex;
    key_word lineType = UNKNOWN;
    bool executedCountGot = false;
    int i = 0;
    int len = str.length();
    int minus = 0;
    int ddot = 0;
    while (i != len) 
    {
        char c = str[i];
        if ((c >= 48) && (c <= 57))  //symbols '0'-'9'
            num.push_back(c);
        else
        {
            switch (c) 
            {
            case ' ':
                if ((!lex.empty()) && (lineType == UNKNOWN))
                    isKeyWord(lex, lineType);
                lex.clear();
                if ((!num.empty()) && ((lineType == BRANCH) || (lineType == CALL)))
                    infoPerform.setNumber(stoi(num, nullptr));
                num.clear();
                break;
            case ':':
                ddot++;
                if ((!lex.empty()) && (isNeverExecuted(lex))) 
                {
                    executedCountGot = true;
                    infoLine.setExecutedCount(0);
                }
                if (!num.empty())
                {
                    if (!executedCountGot)
                    {
                        const int64_t value = stoll(num);
                        if (minus == 1 && ddot == 1 && value == 0)
                            infoLine.setExecutedCount(-1);
                        else
                            infoLine.setExecutedCount(value);
                        executedCountGot = true;
                    }
                    else
                        infoLine.setNumLine(stoi(num, nullptr));
                }
                num.clear();
                break;
            case '%':
                if (!num.empty())
                    infoPerform.setPercent(stoi(num, nullptr));
                num.clear();
                break;
            case '-':
                minus++;
                num.push_back('0');
                break;
            default:
                //Try find 'branch' or 'call'
                lex.push_back(c);
            }
        }
        i++;
    }

    if (infoLine.getNumLine() != -1)    
        info.insert(make_pair(infoLine.getNumLine(), infoLine));
    
    switch (lineType) 
    {
    case BRANCH:
        ((*(info.rbegin())).second).setBranch(infoPerform);
        break;
    case CALL:
        ((*(info.rbegin())).second).setCall(infoPerform);
        break;
    case UNKNOWN:
        break;
    default:
        __spf_print(1, "Error: get unreal type\n");
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
        break;
    }
}

static void printPerform(map<int, Perform> info, ostream &myfile) 
{
    map<int, Perform>::iterator cur;
    for (cur = info.begin(); cur != info.end(); cur++)
        myfile << (*cur).first << ")" << (*cur).second;
}

static void printInfo2file(map<int, Gcov_info> &info, ostream &myfile) 
{
    map<int, Gcov_info>::iterator cur;
    for (cur = info.begin(); cur != info.end(); cur++) 
    {
        Gcov_info cur_gcov = (*cur).second;
        myfile << "_________________\n";
        myfile << "№" << (*cur).first << endl << cur_gcov;
        if (cur_gcov.getCountCalls() != 0) 
        {
            myfile << "-----Calls----\n";
            printPerform(cur_gcov.getCalls(), myfile);
        }

        if (cur_gcov.getCountBranches() != 0) 
        {
            myfile << "----Branches----\n";
            printPerform(cur_gcov.getBranches(), myfile);
        }
    }
}

static inline string modify_name(const string &name) 
{    
    return name + "_pgcov.txt";
}

/*
-добавить флаги при компиляции : gfortran -O2 -g -fprofile-arcs -ftest-coverage
- запустить программу
- отдать исходник профилировщику с флагом : LANG=en_US.utf8 gcov -b file.f
*/

static void fixGcovInfo(SgFile *fileSg, map<int, Gcov_info> &gCovInfo)
{
    for (SgStatement *st = fileSg->firstStatement(); st; st = st->lexNext())
    {
        if (isSgExecutableStatement(st) && !isDVM_stat(st) && !isSPF_stat(st) &&
            (st->variant() != DVM_INTERVAL_DIR && st->variant() != DVM_ENDINTERVAL_DIR))
        {
            auto next = st->lexNext();
            const int currLine = st->lineNumber();
            const int nextLine = next ? next->lineNumber() : -1;
            if (next)
            {
                if (nextLine == currLine)
                    continue;

                auto it = gCovInfo.find(currLine);

                if (it != gCovInfo.end())
                {
                    if (it->second.getExecutedCount() <= 0)
                    {
                        int nextL = currLine + 1;
                        while (nextL != nextLine)
                        {
                            auto itNext = gCovInfo.find(nextL);
                            if (itNext != gCovInfo.end())
                            {
                                if (itNext->second.getExecutedCount() >= 0)
                                {
                                    it->second.clear();
                                    it->second.setExecutedCount(itNext->second.getExecutedCount());
                                    for (auto &call : itNext->second.getCalls())
                                        it->second.setCall(call.second);
                                    for (auto &branch : itNext->second.getBranches())
                                        it->second.setBranch(branch.second);

                                    // copy to between 
                                    for (int z = currLine + 1; z != nextL; ++z)
                                    {
                                        auto itZ = gCovInfo.find(z);
                                        if (itZ != gCovInfo.end())
                                        {
                                            itZ->second.clear();
                                            itZ->second.setExecutedCount(itNext->second.getExecutedCount());
                                            for (auto &call : itNext->second.getCalls())
                                                itZ->second.setCall(call.second);
                                            for (auto &branch : itNext->second.getBranches())
                                                itZ->second.setBranch(branch.second);
                                        }
                                    }
                                    break;
                                }
                            }
                            nextL++;
                        }
                    }
                }
            }
        }
    }

    for (SgStatement *st = fileSg->firstStatement(); st; st = st->lexNext())
    {
        if (isSgExecutableStatement(st) && !isDVM_stat(st) && !isSPF_stat(st) &&
            (st->variant() != DVM_INTERVAL_DIR && st->variant() != DVM_ENDINTERVAL_DIR))
        {
            if (st->variant() == CONTROL_END)
            {
                auto cp = st->controlParent();
                auto it = gCovInfo.find(cp->lineNumber());
                if (it != gCovInfo.end() && cp->variant() != PROG_HEDR &&
                    cp->variant() != PROC_HEDR && cp->variant() != FUNC_HEDR &&
                    isSgExecutableStatement(cp))
                {
                    auto it = gCovInfo.find(st->lineNumber());
                    auto itCp = gCovInfo.find(cp->lineNumber());
                    if (it != gCovInfo.end())
                    {
                        it->second.clear();
                        it->second.setExecutedCount(itCp->second.getExecutedCount());
                        for (auto &call : itCp->second.getCalls())
                            it->second.setCall(call.second);
                        for (auto &branch : itCp->second.getBranches())
                            it->second.setBranch(branch.second);
                    }
                }
                continue;
            }
        }
    }
}

static map<string, map<int, Gcov_info>> allGCovInfo;
void parse_gcovfile(SgFile *fileSg, const string &basefileNameIn, map<int, Gcov_info> &gCovInfo, bool keep)
{
    if (basefileNameIn == "")
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
    else 
    {
        const string basefileName = basefileNameIn + ".gcov";
        ifstream file;
        file.open(basefileName, ios::in);
        if (file.is_open()) 
        {
            string str;
            while (!file.eof()) 
            {
                getline(file, str);
                getInfo(gCovInfo, str);
            }
            file.close();
            fixGcovInfo(fileSg, gCovInfo);

            if (keep)
            {
                // FOR DEBUG ONLY
                string name_f = modify_name(basefileName);
                ofstream myfile(name_f);
                if (myfile.is_open())
                    printInfo2file(gCovInfo, myfile);
                else
                    __spf_print(1, "   Error: unable to create file %s\n", name_f.c_str());
            }
        }
        else
            __spf_print(1, "   Error: unable to open file %s\n", basefileName.c_str());
    }
    allGCovInfo[fileSg->filename()] = gCovInfo;
}

bool __gcov_doesThisLineExecuted(const string &file, const int line)
{
    bool ret = true;
    auto itF = allGCovInfo.find(file);
    if (itF != allGCovInfo.end())
    {
        auto itL = itF->second.find(line);
        if (itL != itF->second.end())
            ret = itL->second.getExecutedCount() != 0;
    }
    return ret;
}

pair<int, int64_t> __gcov_GetExecuted(const string &file, const int line)
{
    pair<int, int64_t> ret = make_pair(0, 0);
    auto itF = allGCovInfo.find(file);
    if (itF != allGCovInfo.end())
    {
        auto itL = itF->second.find(line);
        if (itL != itF->second.end())
            ret.second = itL->second.getExecutedCount();
        else
            ret.first = -1;
    }
    else
        ret.first = -1;
    return ret;
}

void parseTimesDvmStatisticFile(const string &file, map<string, vector<SpfInterval*>> &intervals)
{
    map<string, map<int, SpfInterval*>> mapOfIntervals;
    for (auto &intByfile : intervals)
        createMapOfinterval(mapOfIntervals[intByfile.first], intByfile.second);

    FILE *stat = fopen(file.c_str(), "r");
    if (stat)
    {
        char buf[8192];
        int execDone = 1;
        int line = -1;
        string fileN = "";
        SpfInterval *curr = NULL;

        while (!feof(stat))
        {
            char *read = fgets(buf, 8192, stat);
            if (read)
            {
                const string origLine(read);
                auto itF = origLine.find("INTERVAL");
                auto itTypeU = origLine.find("USER");
                auto itExpr = origLine.find("EXPR=");
                if (itF != string::npos && itTypeU != string::npos && itExpr != string::npos)
                {
                    execDone = 0;
                    line = -1;
                    fileN = "";        
                    int expr = 0;
                    curr = NULL;

                    auto itL = origLine.find("NLINE=");
                    if (itL != string::npos)
                    {
                        string lineS = "";
                        for (size_t z = itL + 6; origLine[z] != ' '; ++z)
                            lineS += origLine[z];
                        line = atoi(lineS.c_str());
                    }

                    auto itS = origLine.find("SOURCE=");
                    if (itS != string::npos)
                    {
                        string source = "";
                        for (size_t z = itS + 7; origLine[z] != ' '; ++z)
                            source += origLine[z];
                        fileN = source;
                        convertToLower(fileN);
                    }

                    string exprS = "";
                    for (size_t z = itExpr + 5; origLine[z] != '\n'; ++z)
                        exprS += origLine[z];
                    expr = atoi(exprS.c_str());

                    if (line != -1 && fileN != "")
                    {
                        auto itIntF = mapOfIntervals.find(fileN);
                        if (itIntF == mapOfIntervals.end())
                        {
                            //TODO: error
                        }
                        else
                        {
                            for (auto &inter : itIntF->second)
                            {
                                if (inter.second->tag == expr)
                                {
                                    curr = inter.second;
                                    string execCountS = "";
                                    auto itExec = origLine.find("EXE_COUNT=");
                                    string execS = "";
                                    for (size_t z = itExec + 10; origLine[z] != ' '; ++z)
                                        execS += origLine[z];
                                    inter.second->exec_count = atoi(execS.c_str());
                                    break;
                                }
                            }
                        }
                    }
                }

                auto itE = origLine.find("Execution time");
                if (itE != string::npos && execDone == 0)
                {
                    execDone = 1;
                    size_t idx = 16;
                    while (origLine[idx++] == ' ');
                    string execC = "";
                    for (size_t z = idx - 1; z < origLine.size(); ++z)
                        execC += origLine[z];
                    double execTime = atof(execC.c_str());

                    if (line != -1 && fileN != "" && curr)
                        curr->exec_time += execTime;
                }
            }
        }
        fclose(stat);
    }
    else
        __spf_print(1, "   Error: unable to open file %s\n", file.c_str());
}
