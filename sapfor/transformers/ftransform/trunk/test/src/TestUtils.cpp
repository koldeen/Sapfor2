//
// Created by baa on 15.12.17.
//

#include "TestUtils.hpp"
#include <fstream>

std::string SageTransform::TestUtils::readFile(const char *fileName) {
    std::ifstream ifs(fileName);
    std::string content((std::istreambuf_iterator<char>(ifs)),
                        (std::istreambuf_iterator<char>()));
    return content;
}

bool SageTransform::TestUtils::compare(const char *fileName1, const char *fileName2) {
    std::string s1 = readFile(fileName1);
    std::string s2 = readFile(fileName2);
    return !s1.empty() && !s2.empty() && s1 == s2;
}