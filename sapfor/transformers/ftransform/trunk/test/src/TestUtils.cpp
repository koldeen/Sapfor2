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

using namespace SageTransform;
using StringUtils::trim;

vector<string> TestUtils::readFileLines(const char *fileName) {
    std::ifstream inputFileStream(fileName);
    string line;
    vector<string> lines;
    while (std::getline(inputFileStream, line)) {
        lines.push_back(line);
    }
    return lines;
}

bool TestUtils::compareStrict(const char *fileName1, const char *fileName2) {
    vector<string> lines1 = readFileLines(fileName1);
    vector<string> lines2 = readFileLines(fileName2);
    bool result = true;
    if (lines1.size() != lines2.size()) {
        std::cerr << "Mismatch: different number of lines " << lines1.size() << " and " << lines2.size() << std::endl;
        result = false;
    } else if (lines1.size() > 0) {
        for (size_t i = 0; i < lines1.size(); i++) {
            string &s1 = lines1[i];
            string &s2 = lines2[i];
            if (s1 != s2) {
                std::cerr << "Mismatch at line " << i + 1 << ": " << std::endl;
                std::cerr << lines1[i] << " | " << fileName1 << std::endl;
                std::cerr << lines2[i] << " | " << fileName2 << std::endl;
                result = false;
            }
        }
    }
    return result;
}

bool TestUtils::compareFortranSources(const char *fileName1, const char *fileName2) {
    vector<string> lines1 = readFileLines(fileName1);
    vector<string> lines2 = readFileLines(fileName2);
    if (lines1.size() > 0 && lines2.size() > 0) {
        bool result = true;
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
                std::cerr << "Mismatch at line " << i + 1 << ": " << std::endl;
                std::cerr << lines1[i] << " | " << fileName1 << std::endl;
                std::cerr << lines2[i] << " | " << fileName2 << std::endl;
                result = false;
            }
        }

        string empty("");
        for (size_t i = minSize; i < maxSize; i++) {
            string &s = trim((*maxLines)[i]);
            if (s != empty) {
                std::cerr << "Mismatch at line " << i << ": " << std::endl;
                std::cerr << "Files have different number of lines" << std::endl;
                result = false;
            }
        }
        return result;
    } else {
        return false;
    }
}

bool TestUtils::compileAndCompareOutputs(const char *fileName1, const char *fileName2) {
    return compileAndCompareOutputs("", fileName1, fileName2);
}

bool TestUtils::compileAndCompareOutputs(const char *workFolder, const char *fileName1, const char *fileName2) {
    std::cout << "Compile and compare " << fileName1 << " and " << fileName2 << std::endl;
    string workFolderStr(workFolder);
    string exe1 = workFolderStr + "t1.exe";
    string exe2 = workFolderStr + "t2.exe";
    string txt1 = workFolderStr + "t1.txt";
    string txt2 = workFolderStr + "t2.txt";
    if (compileAndRun(fileName1, exe1.c_str(), txt1.c_str())
        && compileAndRun(fileName2, exe2.c_str(), txt2.c_str())) {
        return compareStrict(txt1.c_str(), txt2.c_str());
    } else {
        return false;
    }
}

bool TestUtils::compileAndRun(const char *fileName, const char *exeName, const char *outputName) {
    std::string command;
    command = command + "gfortran " + fileName + " -o " + exeName;
    command = command + " && ./" + exeName + " > " + outputName;
    std::cout << "Running " << command << std::endl;
    int result = system(command.c_str());
    return WEXITSTATUS(result) == 0;
}