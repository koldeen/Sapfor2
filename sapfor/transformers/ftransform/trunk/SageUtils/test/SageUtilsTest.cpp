//
// Created by baa on 20.12.17.
//

#include <Log.hpp>
#include "SignalHandling.hpp"
#include "TestUtils.hpp"
#include "SageUtils.hpp"
#include "gtest/gtest.h"

using namespace SageTransform;

TEST(SageUtils, getFilename) {
    //use neighbour test
    const char *fortranSource = "../../SageUtils/test/SageTransformUtilsTest/swapWithLexPrev.f90";
    const char *sageProject = "../../SageUtils/test/SageTransformUtilsTest/swapWithLexPrev.proj";

    SgProject *project = new SgProject(sageProject);
    SgFile *file = &project->file(0);
    SgStatement *stmt = file->firstStatement()->lexNext()->lexNext();

    string filename = SageUtils::getFilename(stmt);
    string expected = "swapWithLexPrev.f90";

    ASSERT_EQ(expected, filename);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    SignalHandling signalHandling; //we need to instantiate it to ensure it is linked actually.
    return RUN_ALL_TESTS();
}
