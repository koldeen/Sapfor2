//
// Created by baa on 13.09.17.
//

#include "SageUtils.hpp"
#include "SignalHandling.hpp"
#include "../include/SageTransformLib.hpp"
#include "gtest/gtest.h"

using namespace SageTransform;

TEST(LoopTransformTighten, tightenValid) {
    LoopTransformTighten tighten;
    const char *fileName = "../../SageTransformLib/test/LoopTransformTightenTest/valid.proj";
    SgProject *project = new SgProject(fileName);
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
    file->unparsestdout();
    FILE *outputFile = fopen("../../SageTransformLib/test/LoopTransformTightenTest/valid.result.f90", "w");
    file->unparse(outputFile);
    fclose(outputFile);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    SignalHandling signalHandling; //we need to instantiate it to ensure it is linked actually.
    return RUN_ALL_TESTS();
}