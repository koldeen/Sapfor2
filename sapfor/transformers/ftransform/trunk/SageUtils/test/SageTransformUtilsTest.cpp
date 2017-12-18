//
// Created by baa on 15.12.17.
//

#include <Log.hpp>
#include "SignalHandling.hpp"
#include "TestUtils.hpp"
#include "SageTransformUtils.hpp"
#include "gtest/gtest.h"

using namespace SageTransform;

TEST(SageTransformUtils, swapWithLexPrev) {
    const char *fortranSource = "../../SageUtils/test/SageTransformUtilsTest/swapWithLexPrev.f90";
    const char *sageProject = "../../SageUtils/test/SageTransformUtilsTest/swapWithLexPrev.proj";
    const char *resultSource = "../../SageUtils/test/SageTransformUtilsTest/swapWithLexPrev.result.f90";
    const char *expectSource = "../../SageUtils/test/SageTransformUtilsTest/swapWithLexPrev.expected.f90";

    SgProject *project = new SgProject(sageProject);
    SgFile *file = &project->file(0);
    SgStatement *stmt = file->firstStatement()->lexNext()->lexNext();

    SgStatement *stmtToMove = stmt->lexNext()->lexNext();
    Log::info("Moving up stmt:");

    stmtToMove->unparsestdout();

    SageTransformUtils::swapWithLexPrev(stmtToMove);

    Log::info("Resulting program:");
    file->unparsestdout();
    FILE *outputFile = fopen(resultSource, "w");
    file->unparse(outputFile);
    fclose(outputFile);

    ASSERT_TRUE(TestUtils::compareFortranSources(expectSource, resultSource));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    SignalHandling signalHandling; //we need to instantiate it to ensure it is linked actually.
    return RUN_ALL_TESTS();
}
