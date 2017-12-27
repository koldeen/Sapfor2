//
// Created by baa on 26.12.17.
//

//
// Created by baa on 13.09.17.
//

#include "LoopWrapTransform.hpp"
#include "SignalHandling.hpp"
#include "TestUtils.hpp"
#include "gtest/gtest.h"

using namespace SageTransform;

TEST(LoopWrapTransform, t1_simple_cases) {
    const char *sourceFile = "valid.f90";
    const char *projectFile = "../../SageTransformLib/test/LoopWrapTransformTest/t1-simple/valid.proj";
    const char *finResultSource = "../../SageTransformLib/test/LoopWrapTransformTest/t1-simple/result.fin.f90";
    const char *finExpectSource = "../../SageTransformLib/test/LoopWrapTransformTest/t1-simple/expected.fin.f90";

    SgForStmt *loop1, *loop2, *loop4, *loop6, *loop8, *loop9;
    SgIfStmt *if1;
    SgStatement *inv1;
    SgSymbol *iSymbol, *jSymbol, *kSymbol;

    SgProject *project = new SgProject(projectFile);
    SgFile *file = &project->file(0);
    SgStatement *stmt = file->firstStatement();
    while(!isSgAssignStmt(stmt)) stmt = stmt->lexNext();
    kSymbol = ((SgAssignStmt *)stmt)->lhs()->symbol();
    //skip to first loop, the init loop
    while (!isSgForStmt(stmt)) stmt = stmt->lexNext();
    loop1 = isSgForStmt(stmt);
    while (!isSgForStmt(stmt)) stmt = stmt->lexNext();
    loop2 = isSgForStmt(stmt);
    while (!isSgIfStmt(stmt)) stmt = stmt->lexNext();
    if1 = isSgIfStmt(stmt);
    while (!isSgForStmt(stmt)) stmt = stmt->lexNext();
    loop4 = isSgForStmt(stmt);
    while (!isSgForStmt(stmt)) stmt = stmt->lexNext();
    while (!isSgForStmt(stmt)) stmt = stmt->lexNext();
    loop6 = isSgForStmt(stmt);
    inv1 = stmt->lexNext();
    while (!isSgForStmt(stmt)) stmt = stmt->lexNext();
    while (!isSgForStmt(stmt)) stmt = stmt->lexNext();
    loop8 = isSgForStmt(stmt);
    while (!isSgForStmt(stmt)) stmt = stmt->lexNext();
    loop9 = isSgForStmt(stmt);

    iSymbol = loop2->symbol();
    jSymbol = loop1->symbol();
    //tests
    LoopWrapTransform loopWrap;
    loopWrap.wrapWithOneIteration(iSymbol, loop1);

    SgForStmt *iLoopAroundIf = loopWrap.wrapWithOneIteration(iSymbol, if1, loop4->lexPrev());
    loopWrap.wrapWithOneIteration(jSymbol, iLoopAroundIf);

    loopWrap.wrapWithOneIteration(kSymbol, loop4);
    loopWrap.wrapWithOneIteration(kSymbol, loop6->lexNext(), loop8->lexPrev()->lexPrev());
    loopWrap.wrapWithOneIteration(kSymbol, loop9);

    FILE *outputFile;
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