//
// Created by Vladislav Volodkin on 12/20/19.
//

#ifndef SAPFOR_DVMHREGION_H
#define SAPFOR_DVMHREGION_H
#include "../GraphLoop/graph_loops_func.h"

#include <string>
#include <unordered_set>


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
    std::string getFileName() const { return this->getFirstSt()->fileName(); }
    std::unordered_set<SgSymbol*> get_modified();  // may raise NotImplemented
    std::unordered_set<SgSymbol*> get_read();  // may raise NotImplemented
    void append(DvmhRegion& region);
};


#endif //SAPFOR_DVMHREGION_H
