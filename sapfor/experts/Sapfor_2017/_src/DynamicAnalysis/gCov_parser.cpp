#include "../Utils/leak_detector.h"

#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>
#include <map>

#include "dvm.h"
#include "gCov_parser_func.h"

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
            cout << "Error: Wrong work of analysis keywords\n";
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
                if ((!lex.empty()) && (isNeverExecuted(lex))) 
                {
                    executedCountGot = true;
                }
                if (!num.empty()) 
                {
                    if (!executedCountGot)
                    {
                        infoLine.setExecutedCount(stoi(num, nullptr));
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
        cout << "Error: get unreal type\n";
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
        if (isSgExecutableStatement(st))
        {
            auto next = st->lexNext();
            const int currLine = st->lineNumber();
            const int nextLine = next ? next->lineNumber() : -1;
            if (next)
            {
                auto it = gCovInfo.find(currLine);
                if (it == gCovInfo.end())
                    printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

                if (it->second.getExecutedCount() == 0)
                {
                    int nextL = currLine + 1;
                    while (nextL != nextLine)
                    {
                        auto itNext = gCovInfo.find(nextL);
                        if (itNext != gCovInfo.end())
                        {
                            if (itNext->second.getExecutedCount() != 0)
                            {
                                it->second.setExecutedCount(itNext->second.getExecutedCount());
                                for (auto &call : itNext->second.getCalls())
                                    it->second.setCall(call.second);
                                for (auto &branch : itNext->second.getBranches())
                                    it->second.setBranch(branch.second);
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

void parse_gcovfile(SgFile *fileSg, const string &basefileNameIn, map<int, Gcov_info> &gCovInfo)
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

#if _WIN32 && _DEBUG
            // FOR DEBUG ONLY
            string name_f = modify_name(basefileName);
            ofstream myfile(name_f);
            if (myfile.is_open()) 
                printInfo2file(gCovInfo, myfile);            
            else
                __spf_print(1, "   Error: unable to create file %s\n", name_f.c_str());
#endif
        }
        else
            __spf_print(1, "   Error: unable to open file %s\n", basefileName.c_str());
    }
}