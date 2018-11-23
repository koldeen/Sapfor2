//
// Created by baa on 16.12.17.
//

#include "LineReorderRecord.hpp"
#include "SignalHandling.hpp"
#include "gtest/gtest.h"

using namespace SageTransform;

TEST(LineReorderRecord, testCombine) {
    LineReorderRecord r1, r2;
    r1.addMove(1, 3);
    r1.addMove(2, 1);
    r1.addMove(3, 2);
    r2 = r2.combine(r1).combine(r1).combine(r1);

    int count = 0;
    for (auto const &x : *r2.getMoves()) {
        EXPECT_EQ(x.first, x.second);
        count++;
    }
    EXPECT_EQ(3, count);
    EXPECT_EQ(3, r2.getMaxLineNumber());
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    SignalHandling signalHandling; //we need to instantiate it to ensure it is linked actually.
    return RUN_ALL_TESTS();
}