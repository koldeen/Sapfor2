#include "StringUtils.hpp"
#include <sstream>
#include <algorithm>
#include <cstring>
#include <iostream>

using namespace SageTransform;

bool StringUtils::startsWith(string const &str, string const &prefix) {
    if (str.length() >= prefix.length()) {
        return (0 == str.compare(0, prefix.length(), prefix));
    } else {
        return false;
    }
}

bool StringUtils::endsWith(string const &str, std::string const &ending) {
    if (str.length() >= ending.length()) {
        return (0 == str.compare(str.length() - ending.length(), ending.length(), ending));
    } else {
        return false;
    }
}

/* from stackoverflow */
std::vector<std::string> &StringUtils::split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

/* from stackoverflow */
//this method DOES NOT remove empty results, which appear in between two delim symbols in a row
std::vector<std::string> StringUtils::split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

std::string StringUtils::unsplit(const std::vector<std::string> &v, char delim) {
    std::string result;
    result.append(v[0]);
    for (size_t i = 1; i < v.size(); ++i) {
        result += delim;
        result += v[i];
    }
    return result;
}

//this method removes empty results, which appear in split between two delim symbols in a row
std::vector<std::string> StringUtils::tokenize(const std::string &s, char delim) {
    std::vector<std::string> result;
    std::vector<std::string> splitTokens = split(s, delim);
    for (unsigned int i = 0; i < splitTokens.size(); i++) {
        if (splitTokens.at(i).length() > 0) {
            result.push_back(splitTokens[i]);
        }
    }
    return result;
}

int getCharCount(const std::string &str, const char c) {
    return (int) std::count(str.begin(), str.end(), c);
}

std::vector<std::string> StringUtils::tokenizeRespectParenthesis(const std::string &s, char delim) {
    std::vector<std::string> result;
    std::vector<std::string> splitTokens = split(s, delim);
    int openBrackets = 0;
    std::string token;
    for (unsigned int i = 0; i < splitTokens.size(); i++) {
        if (splitTokens.at(i).length() > 0) {
            openBrackets += getCharCount(splitTokens.at(i), '(');
            openBrackets -= getCharCount(splitTokens.at(i), ')');
            token += splitTokens.at(i);
            if (openBrackets == 0) {
                result.push_back(token);
                token = "";
            } else if (openBrackets > 0) {
                token += delim;
            } else if (openBrackets < 0) {
                throw "Illegal brackets";
            }
        }
    }
    return result;
}

void StringUtils::inplaceCutElement(char *cstring, char splitDelim, int removedIndex) {
    //validate inputs
    if (cstring == NULL) return;
    if (splitDelim == '\0') return;
    if (removedIndex < 0) return;
    //find removed part start
    int count = 0;
    int charInd = 0;
    int prevInd = 0;
    int nextInd = 0;
    while (count <= removedIndex) {
//        std::cout << "at char " << cstring[charInd] << std::endl;
        if (cstring[charInd] == '\0') {
            prevInd = nextInd;
            nextInd = charInd;
//            std::cout << "next start " << nextInd << " prev start " << prevInd << std::endl;
            break;
        }
        if (cstring[charInd] == splitDelim) {
            count++;
//            std::cout << "count " << count << " target " << removedIndex << std::endl;
            prevInd = nextInd;
            nextInd = charInd + 1;
//            std::cout << "next start " << nextInd << " prev start " << prevInd << std::endl;
        }
        charInd++;
    }
    if (cstring[nextInd] == '\0') {
        cstring[prevInd] = '\0';
    } else {
        strcpy(cstring + prevInd, cstring + nextInd);
    }
}

void StringUtils::removeLineStartingWith(char *pCharComments, const string &prefix) {
    vector<string> comments = StringUtils::split(pCharComments, '\n');
    int lineToRemove = 0;
    for (vector<string>::iterator pComment = comments.begin(); pComment != comments.end(); ++pComment) {
        if (StringUtils::startsWith(*pComment, prefix)) {
            break;
        } else {
            lineToRemove++;
        }
    }
    StringUtils::inplaceCutElement(pCharComments, '\n', lineToRemove);
}
