//
// Created by baa on 15.12.17.
//

#include "TestUtils.hpp"
#include "StringUtils.hpp"

using std::string;
using std::vector;

#include <fstream>
#include <iostream>

using std::ifstream;

#include <iterator>

using std::istream_iterator;

#include <algorithm>

using std::copy;

using namespace SageTransform;
using StringUtils::trim;

string TestUtils::readFile(const char *fileName) {
    std::ifstream ifs(fileName);
    string content((std::istreambuf_iterator<char>(ifs)),
                   (std::istreambuf_iterator<char>()));
    return content;
}

vector<string> TestUtils::readFileLines(const char *fileName) {
    ifstream myfile(fileName);
    std::vector<string> myLines;
    std::copy(std::istream_iterator<string>(myfile),
              std::istream_iterator<string>(),
              std::back_inserter(myLines));
    return myLines;
}

bool TestUtils::compareFortranSources(const char *fileName1, const char *fileName2) {
    vector<string> lines1 = readFileLines(fileName1);
    vector<string> lines2 = readFileLines(fileName2);
    if (lines1.size() > 0 && lines2.size() > 0) {
        size_t maxSize = lines1.size();
        size_t minSize = lines2.size();
        vector<string> *maxLines = &lines1;
        if (lines2.size() > lines1.size()) {
            maxSize = lines2.size();
            minSize = lines1.size();
            maxLines = &lines2;
        }
        for (size_t i = 0; i < minSize; i++) {
            string &s1 = trim(lines1[i]);
            string &s2 = trim(lines2[i]);
            if (s1 != s2) {
                return false;
            }
        }

        string empty("");
        for (size_t i = minSize; i < maxSize; i++) {
            string &s = trim((*maxLines)[i]);
            if (s != empty) {
                return false;
            }
        }
        return true;
    } else {
        return false;
    }
}