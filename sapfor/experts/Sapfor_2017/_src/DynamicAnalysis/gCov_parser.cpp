#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>
#include <map>

#include "gCov_parser_func.h"

using namespace std;

//TODO: 
// надо сделать все функции static,которые локализованы внутри файла
// реализовать заполнение функции, которая в самом низу, формировать нужное имя файла на основе базового

enum key_word
{
    UNKNOWN,
    BRANCH,
    CALL,
};

const char *key_words[] = {
    "",
    "branch",
    "call",
    "taken",
    "returned",
    NULL
};

const char *symbols_neverExecuted[] = {
    "",
    "#####",
    "%%%%%",
    "$$$$$",
    "=====",
    NULL
};

void isKeyWord(const string &lex, key_word &lineType) {
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

bool isNeverExecuted(const string &lex) {
    int i = 1;
    bool find = false;
    while ((!find) && symbols_neverExecuted[i]) {
        if (lex.compare(symbols_neverExecuted[i]) == 0)
            find = true;
        else
            i++;
    }
    return find;
}

void getInfo(map<int, Gcov_info> &info, const string &str) {
    Gcov_info infoLine;
    Perform infoPerform;
    string num, lex;
    key_word lineType = UNKNOWN;
    bool executedCountGot = false;
    int i = 0;
    int len = str.length();
    while (i != len) {
        char c = str[i];
        if ((c >= 48) && (c <= 57)) { //symbols '0'-'9'
            num.push_back(c);
        }
        else {
            switch (c) {
            case ' ':
                if ((!lex.empty()) && (lineType == UNKNOWN))
                    isKeyWord(lex, lineType);
                lex.clear();
                if ((!num.empty()) && ((lineType == BRANCH) || (lineType == CALL)))
                    infoPerform.setNumber(stoi(num, nullptr));
                num.clear();
                break;
            case ':':
                if ((!lex.empty()) && (isNeverExecuted(lex))) {
                    executedCountGot = true;
                }
                if (!num.empty()) {
                    if (!executedCountGot) {
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

    if (infoLine.getNumLine() != -1) {
        info.insert(make_pair(infoLine.getNumLine(), infoLine));
    }
    switch (lineType) {
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

void printPerform(map<int, Perform> info) {
    map<int, Perform>::iterator cur;
    for (cur = info.begin(); cur != info.end(); cur++)
        cout << (*cur).first << ")" << (*cur).second;
}

void printInfo(map<int, Gcov_info> &info) {
    map<int, Gcov_info>::iterator cur;
    for (cur = info.begin(); cur != info.end(); cur++) {
        Gcov_info cur_gcov = (*cur).second;
        cout << "_________________\n";
        cout << "№" << (*cur).first << endl << cur_gcov;
        if (cur_gcov.getCountCalls() != 0) {
            cout << "-----Calls----\n";
            printPerform(cur_gcov.getCalls());
        }
        if (cur_gcov.getCountBranches() != 0) {
            cout << "----Branches----\n";
            printPerform(cur_gcov.getBranches());
        }
    }
}

void printInfoFiles(map<char*, map<int, Gcov_info>> info) {
    map<char*, map<int, Gcov_info>>::iterator it;
    for (it = info.begin(); it != info.end(); it++) {
        cout << "\nNameFile: " << it->first << endl;
        printInfo(it->second);
    }
}

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
            }
            else
                cout << "Error: unable to open file " << args[i] << endl;
        }
        printInfoFiles(all_info);
    }
}

//TODO
void parse_gcovfile(const string basefileName, map<int, Gcov_info> &gCovInfo)
{

}