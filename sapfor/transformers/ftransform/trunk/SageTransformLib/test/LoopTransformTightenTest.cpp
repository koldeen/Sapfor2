//
// Created by baa on 13.09.17.
//

#include <LineReorderer.hpp>
#include <TestUtils.hpp>
#include "SageUtils.hpp"
#include "SignalHandling.hpp"
#include "../include/SageTransformLib.hpp"
#include "gtest/gtest.h"

using namespace SageTransform;

TEST(LoopTransformTighten, tightenValid) {
    LoopTransformTighten tighten;
    const char *projectFile = "../../SageTransformLib/test/LoopTransformTightenTest/valid.proj";
    const char *midResultSource = "../../SageTransformLib/test/LoopTransformTightenTest/result.mid.f90";
    const char *finResultSource = "../../SageTransformLib/test/LoopTransformTightenTest/result.fin.f90";
    const char *midExpectSource = "../../SageTransformLib/test/LoopTransformTightenTest/expected.mid.f90";
    const char *finExpectSource = "../../SageTransformLib/test/LoopTransformTightenTest/expected.fin.f90";
    SgProject *project = new SgProject(projectFile);
    SgFile *file = &project->file(0);
    SgStatement *stmt = file->firstStatement();
    //skip to first loop, the init loop
    while (!isSgForStmt(stmt)) stmt = stmt->lexNext();
    //skip whole init loop
    stmt = SageUtils::getLastLoopStatement(isSgForStmt(stmt));
    //skip to second loop with invariant
    while (!isSgForStmt(stmt)) stmt = stmt->lexNext();
    SgForStmt *forLoop = isSgForStmt(stmt);
    std::map<SgSymbol *, DependencyType> dependencies;
    SgSymbol *symbol = isSgAssignStmt(forLoop->lexNext())->lhs()->symbol();
    dependencies.insert({symbol, DependencyType::FLOW_DEP});
    ASSERT_TRUE(tighten.canTighten(forLoop, dependencies));

    tighten.tighten(forLoop, 2);
    FILE *outputFile;
    outputFile = fopen(midResultSource, "w");
    file->unparse(outputFile);
    fclose(outputFile);
    ASSERT_TRUE(TestUtils::compareFortranSources(midResultSource, midExpectSource));

    auto &pair = LoopTransformTighten::getLaunches()->at(0);
    SgStatement * loopStmt = pair.first;
    LineReorderRecord record = pair.second.buildReverse();
    LineReorderer().apply(loopStmt, record);
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