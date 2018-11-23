//
// Created by baa on 29.08.2017.
//

#include <SignalHandling.hpp>
#include "../include/StringUtils.hpp"
#include "gtest/gtest.h"

using namespace SageTransform;

TEST(StringUtils, inplaceCutElement) {
    char * line = (char *) malloc(sizeof(char)*100);
    {
        strcpy(line, "!PRG combine 2\n");
        line[2] = 'a';
        StringUtils::inplaceCutElement(line,
                                       '\n', 0);
        const char *expectedResult = "";
        ASSERT_STREQ(expectedResult, line);
    }  
    {
        strcpy(line, "!PRG combine 1\n!PRG combine 2\n");
        StringUtils::inplaceCutElement(line,
                                       '\n', 1);
        const char *expectedResult = "!PRG combine 1\n";
        ASSERT_STREQ(expectedResult, line);
    }
    {
        strcpy(line, "!PRG combine 1\n!PRG combine 2\n");
        StringUtils::inplaceCutElement(line,
                                       '\n', 0);
        const char *expectedResult = "!PRG combine 2\n";
        ASSERT_STREQ(expectedResult, line);
    }
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    SignalHandling signalHandling; //we need to instantiate it to ensure it is linked actually.
    return RUN_ALL_TESTS();
}