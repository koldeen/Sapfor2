#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>
#include <map>


#include "../Utils/errors.h"
#include "gcov_info.h"

//using namespace std;

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

void isKeyWord(const std::string &lex, key_word &lineType) {
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
            __spf_print(1,"Error: Wrong work of analysis keywords\n");
    }
}

bool isNeverExecuted(const std::string &lex) {
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

void getInfo(std::map<int, Gcov_info> &info, const std::string &str) {
    Gcov_info infoLine;
    Perform infoPerform;
    std::string num, lex;
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
        info.insert(std::make_pair(infoLine.getNumLine(), infoLine));
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
        __spf_print(1,"Error: get unreal type\n");
    }
}

void printPerform(map<int, Perform> info, ostream &myfile) {
    std::map<int, Perform>::iterator cur;
    for (cur = info.begin(); cur != info.end(); cur++) {
        myfile << (*cur).first << ")" << (*cur).second;
    }
}

void printInfo(map<int, Gcov_info> &info, ostream &myfile) {
    map<int, Gcov_info>::iterator cur;
    for (cur = info.begin(); cur != info.end(); cur++) {
        Gcov_info cur_gcov = (*cur).second;
        myfile << "_________________\n";
        myfile << "№" << (*cur).first << endl << cur_gcov;
        if (cur_gcov.getCountCalls() != 0) {
            myfile << "-----Calls----\n";
            printPerform(cur_gcov.getCalls(), myfile);
        }
        if (cur_gcov.getCountBranches() != 0) {
            myfile << "----Branches----\n";
            printPerform(cur_gcov.getBranches(), myfile);
        }
    }
}

std::string modify_name(std::string name) {
    std::string::iterator rit = name.end();
    while ((*rit != '.') && (rit != name.begin()))
        rit--;
    std::string::iterator it;
    std::string new_name;
    for (it = name.begin(); it != rit; it++) {
        new_name += *it;
    }
    return new_name + "_pgcov.txt";
}

void printInfoFiles(map<char*, map<int, Gcov_info>> info, std::string name_f) {
    map<char*, map<int, Gcov_info>>::iterator it;
    name_f = modify_name(name_f);
    ofstream myfile(name_f);
    if (myfile.is_open()) {
        for (it = info.begin(); it != info.end(); it++) {
            myfile << "\nNameFile: " << it->first << std::endl;
            printInfo(it->second, myfile);
        }
    }
}

extern std::map<char*, std::map<int, Gcov_info>> all_info;

void parse_gcovfile(const char *file_gcov) {
   if (file_gcov == NULL)
        __spf_print(1, "Error: incorrectly use function parse_gcovfile\n");
    else {
        int i = 0;
//        char* f = files[i];
//       __spf_print(1, "start parser_gcov\n");
//       while (file_gcov != NULL){
            std::map<int, Gcov_info> info;
            std::ifstream file;
            file.open(file_gcov, std::ios::in);
            if (file.is_open()) {
                __spf_print(1, "open[ %s ]\n", file_gcov);
                std::string str;
                while (!file.eof()) {
                    getline(file, str);
                    getInfo(info, str);
                }
                file.close();
                all_info.insert(make_pair((char *)file_gcov, info));
            }
            else
                __spf_print(1, "Error: unable to open file %s\n", file_gcov);
 //           i++;
 //           f = files[i];
 //       }
            printInfoFiles(all_info, (std::string) args[i]);
    }

}
