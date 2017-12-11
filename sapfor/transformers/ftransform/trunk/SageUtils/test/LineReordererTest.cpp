//
// Created by baa on 11.12.17.
//

#include <LineReorderRecord.hpp>
#include <LineReorderer.hpp>
#include "SignalHandling.hpp"
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

    LineReorderRecord reverseRecord = reorderRecord.buildReverse();

    const char *fortranSource = "../../SageUtils/test/LineReordererTest/valid.f90";
    //todo parse in test itself
    const char *sageProject = "../../SageUtils/test/LineReordererTest/valid.proj";
    SgProject *project = new SgProject(sageProject);
    SgFile *file = &project->file(0);
    SgStatement *stmt = file->firstStatement();

    LineReorderer::apply(stmt, reverseRecord);

    file->unparsestdout();
    FILE *outputFile = fopen("../../SageUtils/test/LineReordererTest/valid.result.f90", "w");
    file->unparse(outputFile);
    fclose(outputFile);

    //todo compare with expected
    ASSERT_TRUE(true);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    SignalHandling signalHandling; //we need to instantiate it to ensure it is linked actually.
    return RUN_ALL_TESTS();
}
