#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>
#include <map>

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

static std::string modify_name(std::string name) 
{
    std::string::iterator rit = name.end();
    while ((*rit != '.') && (rit != name.begin()))
        rit--;
    std::string::iterator it;
    std::string new_name;
    for (it = name.begin(); it != rit; it++)
        new_name += *it;
    
    return new_name + "_pgcov.txt";
}

static void printInfoFiles(map<char*, map<int, Gcov_info>> info, string name_f) 
{
    map<char*, map<int, Gcov_info>>::iterator it;
    name_f = modify_name(name_f);
    ofstream myfile(name_f);

    if (myfile.is_open()) 
    {
        for (it = info.begin(); it != info.end(); it++)
        {
            myfile << "\nNameFile: " << it->first << endl;
            printInfo2file(it->second, myfile);
        }
    }
}

/*
void parse_gcovfile(int nfl, char* args[]) {
    map<char*, map<int, Gcov_info>> all_info;
    if (nfl == 0)
        printf("Error: incorrectly use function parse_gcovfile\n");
    else {
        for (int i = 0; i<nfl; i++) {
            map<int, Gcov_info> info;
            ifstream file;
            file.open(args[i], ios::in);
            if (file.is_open()) {
                string str;
                while (!file.eof()) {
                    getline(file, str);
                    getInfo(info, str);
                }
                file.close();
                all_info.insert(make_pair(args[i], info));
                printInfoFiles(all_info, (std::string) args[i]);
            }
            else
                cout << "Error: unable to open file " << args[i] << endl;
        }
    }

}
*/

/*
-добавить флаги при компиляции : -fprofile-arcs -ftest-coverage
- запустить программу
- отдать исходник профилировщику с флагом : gcov -b [file.F]
*/

//TODO
void parse_gcovfile(const string basefileName, map<int, Gcov_info> &gCovInfo)
{
    // map<char*, map<int, Gcov_info>> all_info;
    if (basefileName.empty())
        printf("Error: incorrectly use function parse_gcovfile\n");
    else {
        //  for (int i = 0; i<nfl; i++) {
        //      map<int, Gcov_info> info;
        ifstream file;
        file.open(basefileName, ios::in);
        if (file.is_open()) {
            string str;
            while (!file.eof()) {
                getline(file, str);
                getInfo(gCovInfo, str);
            }
            file.close();
            //          all_info.insert(make_pair(args[i], info));
            string name_f = modify_name(basefileName);
            ofstream myfile(name_f);
            if (myfile.is_open()) {
                printInfo2file(gCovInfo, myfile);
            }
            else
                __spf_print(1, "Error: unable to create file %s\n", name_f);
        }
        else
            __spf_print(1, "Error: unable to open file %s\n", basefileName);
        //         cout << "Error: unable to open file " << args[i] << endl;
        //     }
    }
}