// Created by Vladislav Volodkin on 12/20/19.

#pragma once

#include "../GraphLoop/graph_loops_func.h"

#include <string>

class DvmhRegion
{
private:
    std::vector<LoopGraph*> loops;
    std::string fun_name;

public:
    DvmhRegion() { }
    DvmhRegion(LoopGraph *loopNode, const std::string &fun_name);

    SgStatement* getFirstSt() const;
    SgStatement* getLastSt() const;

    void addLoop(LoopGraph* newLoop) { loops.push_back(newLoop); }
    const std::string& getFunName() const { return fun_name; }
    void setFunName(const std::string& newName) { fun_name = newName; }
    const std::vector<LoopGraph*>& getLoops() const { return loops; }
    std::string getFileName() const { return getFirstSt()->fileName(); }
    void append(DvmhRegion& region);
};

