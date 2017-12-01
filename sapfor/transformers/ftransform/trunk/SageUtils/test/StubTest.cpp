//
// Created by aielemental on 23.04.2017.
//

#include <algorithm>

#include "../include/SageUtils.hpp"
#include "gtest/gtest.h"

TEST(StubTest, CheckTestLibraryIntegration) {
    const char * result = SageTransform::SageUtils::decodeStmtVariant(100);
    const char * expect = "GLOBAL";
    int sz = 6;
    for (int i = 0; i < sz; i++) {
        EXPECT_EQ(result[i], expect[i]);
    }
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}