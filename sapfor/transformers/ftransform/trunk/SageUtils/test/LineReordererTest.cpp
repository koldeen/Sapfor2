//
// Created by baa on 11.12.17.
//

#include "LineReorderRecord.hpp"
#include "LineReorderer.hpp"
#include "SignalHandling.hpp"
#include "TestUtils.hpp"
#include "gtest/gtest.h"

using namespace SageTransform;

TEST(LineReordererTest, revertReordering) {
    LineReorderRecord reorderRecord;
    reorderRecord.addMove(1, 2);
    reorderRecord.addMove(2, 4);
    reorderRecord.addMove(3, 5);
    reorderRecord.addMove(4, 3);
    reorderRecord.addMove(5, 6);
    reorderRecord.addMove(6, 1);

    const char *fortranSource = "../../SageUtils/test/LineReordererTest/valid.f90";
    const char *sageProject = "../../SageUtils/test/LineReordererTest/valid.proj";
    const char *midResultSource = "../../SageUtils/test/LineReordererTest/result.mid.f90";
    const char *midExpectSource = "../../SageUtils/test/LineReordererTest/expected.mid.f90";
    const char *finResultSource = "../../SageUtils/test/LineReordererTest/result.fin.f90";
    const char *finExpectSource = "../../SageUtils/test/LineReordererTest/expected.fin.f90";

    SgProject *project = new SgProject(sageProject);
    SgFile *file = &project->file(0);
    SgStatement *stmt = file->firstStatement()->lexNext()->lexNext();

    FILE *outputFile;

    LineReorderer::apply(stmt, reorderRecord);
    file->unparsestdout();
    outputFile = fopen(midResultSource, "w");
    file->unparse(outputFile);
    fclose(outputFile);
    ASSERT_TRUE(TestUtils::compareFortranSources(midResultSource, midExpectSource));

    LineReorderRecord reverseRecord = reorderRecord.buildReverse();
    LineReorderer::apply(stmt, reverseRecord);
    file->unparsestdout();
    outputFile = fopen(finResultSource, "w");
    file->unparse(outputFile);
    fclose(outputFile);
    ASSERT_TRUE(TestUtils::compareFortranSources(finResultSource, finExpectSource));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    SignalHandling signalHandling; //we need to instantiate it to ensure it is linked actually.
    return RUN_ALL_TESTS();
}
