#include "leak_detector.h"
/*
 * DvmhDvmhRegionIsertor.cpp
 *
 *  Created on: May 14, 2018
 *      Author: vladislav
 */

#include "DvmhRegionInserter.h"

using namespace std;

void DvmhRegionInsertor::printFuncName(SgStatement* st)
{
    if (st->variant() == PROG_HEDR)
    {
        SgProgHedrStmt *progH = (SgProgHedrStmt*)st;
        cout << "Program: " << progH->symbol()->identifier() << endl;
    }
    else if (st->variant() == PROC_HEDR)
    {
        SgProcHedrStmt *procH = (SgProcHedrStmt*)st;
        cout << "Procedure: " << procH->symbol()->identifier() << endl;
    }
    else if (st->variant() == FUNC_HEDR)
    {
        SgFuncHedrStmt *funcH = (SgFuncHedrStmt*)st;
        cout << "Function: " << funcH->symbol()->identifier() << endl;
    }
}

// TODO: init first and last statements
void DvmhRegionInsertor::findEdgesForRegions(const vector<LoopGraph*> &loops) // here as link
{
    for (auto &loopNode : loops)
    {
        if (!hasLimitsToDvmhParallel(loopNode))
        {
            SgStatement* func_st = getFuncStat(loopNode->loop);
            string fun_name = func_st->symbol()->identifier();
            DvmhRegion *dvmhRegion = new DvmhRegion(loopNode, fun_name);
            regions.push_back(dvmhRegion);
        }
        else if (loopNode->children.size() > 0)
            findEdgesForRegions(loopNode->children);
    }
}

bool DvmhRegionInsertor::hasLimitsToDvmhParallel(const LoopGraph *loop) const
{
    bool hasDirective = false;
    if (loop->lineNum > 0 || (loop->lineNum < 0 && loop->altLineNum > 0))
        hasDirective = (loop->loop->GetOriginal()->lexPrev()->variant() == DVM_PARALLEL_ON_DIR);

    return loop->hasGoto || loop->hasPrints || loop->hasImpureCalls || !loop->directive || !hasDirective;
}

void DvmhRegionInsertor::insertRegionDirectives()
{
    for (auto &region : regions)
    {
        if (region->loops.size() == 0)
            continue;

        SgStatement *regionStartSt = new SgStatement(ACC_REGION_DIR);

        SgStatement *statementBefore = region->getFirstSt()->lexPrev();
        if (!statementBefore || statementBefore->variant() != DVM_PARALLEL_ON_DIR) 
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

        //move comments before
        if (statementBefore->comments())
        {
            regionStartSt->setComments(statementBefore->comments());
            statementBefore->delComments();
        }
        statementBefore->insertStmtBefore(*regionStartSt, *statementBefore->controlParent());

        SgStatement *regionEndSt = new SgStatement(ACC_END_REGION_DIR);
        SgStatement *lastStOfTheLoop = region->getLastSt();
        lastStOfTheLoop->insertStmtAfter(*regionEndSt, *region->getFirstSt()->controlParent());
    }
}

// checks loop node itself, doesn't check its children
LoopCheckResults DvmhRegionInsertor::checkLoopForPurenessAndIO(LoopGraph *loopNode, const map<string, FuncInfo*> &allFuncs)
{
    LoopCheckResults loopCheckResults;

    for (auto &nameAndLineOfFuncCalled : loopNode->calls)
    {
        FuncInfo *calledFuncInfo = NULL;

        auto it = allFuncs.find(nameAndLineOfFuncCalled.first);
        if (it != allFuncs.end())
            calledFuncInfo = it->second;

        if (!calledFuncInfo)
        {
            if (isIntrinsicFunctionName(nameAndLineOfFuncCalled.first.c_str()))
                continue;
            else
            { // if funcInfo was not found assume func to be impure
                loopCheckResults.hasImpureCalls = true;
                loopCheckResults.usesIO = true;
                break;
            }
        }

        if (!calledFuncInfo->isPure) 
            loopCheckResults.hasImpureCalls = true;

        if (calledFuncInfo->usesIO())
            loopCheckResults.usesIO = true;

        if (loopCheckResults.usesIO && loopCheckResults.hasImpureCalls)
            break;
    }

    return loopCheckResults;
}

DvmhRegionInsertor::DvmhRegionInsertor(SgFile *curFile, const vector<LoopGraph*> &curLoopGraph)
    : file(curFile), loopGraph(curLoopGraph)
{ }

LoopCheckResults DvmhRegionInsertor::updateLoopNode(LoopGraph *loop, const map<string, FuncInfo*> &allFuncs)
{
    LoopCheckResults loopChecks = checkLoopForPurenessAndIO(loop, allFuncs);
    bool hasImpureCalls = loopChecks.hasImpureCalls;
    bool usesIO = loopChecks.usesIO;

    for (auto &nestedLoop : loop->children) 
    {
        loopChecks = updateLoopNode(nestedLoop, allFuncs);
        hasImpureCalls |= loopChecks.hasImpureCalls;
        usesIO |= loopChecks.usesIO;
    }

    loop->hasImpureCalls = hasImpureCalls;
    loop->hasPrints |= usesIO;

    return LoopCheckResults(loop->hasPrints, loop->hasImpureCalls);
}

void DvmhRegionInsertor::updateLoopGraph(const map<string, FuncInfo*> &allFuncs)
{
    for (auto &loopNode : loopGraph)
        updateLoopNode(loopNode, allFuncs);
}


/*
    1. ���������� ������ ������ ������ �������
    2. ������ ���������� � ����� ������� ���������
    3. ���� ����� ��������� ���-�� ����:
        �) ��� ��������� �����-����
        �) ���� ����������� ���������� -- ��������� ������ (����� ���������, ���� ������ �� ������������ � ����. �������)
        �) ���� ����� ������� -- ������������ �� ������ �� ����������������� � ���� �������*
*/

static bool SymbDefinedIn(SgSymbol* var, SgStatement* st)
{
    return st->variant() == ASSIGN_STAT && st->expr(0)->variant() == ARRAY_REF && st->expr(0)->symbol()->identifier() == var->identifier();
}

// Finds the closest variable's defenition (test only)
// static std::map<SymbolKey, std::set<SgExpression*> > dummyDefenitions(SgStatement* st)
// {
//  std::map<SymbolKey, std::set<SgExpression*> > result;

//  set<SgSymbol*> usedSymbols = getUsedSymbols(st);

//  for (auto& var : usedSymbols)
//  {
//      SgStatement* prev = st->lexPrev();

//      std::set<SgExpression*> defs;
//      while (prev)
//      {
//          if (SymbDefinedIn(var, prev)) {
//              defs.insert(prev->expr(1));
//              break;
//          }

//          prev = prev->lexPrev();
//      }

//      result[SymbolKey(var, false)] = defs;
//  }

//  return result;
// }

void DvmhRegionInsertor::insertActualDirectives() 
{
    int funcNum = file->numberOfFunctions();
    RDKeeper rd = RDKeeper(file);

    for (auto const& defsByStatement : rd.defsByStatement)
    {
        SgStatement* st = defsByStatement.first;
        StDefs st_defs = defsByStatement.second;

        DvmhRegion* region = getContainingRegion(st);

        vector<SgSymbol*> toActualise;
        for (auto const& elem : st_defs) 
        {
            SgSymbol* symbol = elem.first;
            set<SgStatement*> defs = elem.second;
            /*
            // DEBUG
            cout << "~~~~~~~~~~~~~~~~~~~~~" << endl;
            st->unparsestdout();
            cout << symbol.getVarName() + ": " << endl;
            for (auto &def : defs) {
                if (def) {
                    def->unparsestdout();
                }
            }
            cout << "********************" << endl;
            // END OF DEBUG
            */
            if (region) 
            {
                // Searching for defenition not in region
                bool symbolDeclaredInSequentPart = false;
                for (auto& def : defs) 
                {
                    auto saveName = current_file->filename();

                    if (!def->switchToFile())
                        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

                    DvmhRegion* containingRegion = getContainingRegion(def);
                    if (!containingRegion) 
                    {
                        symbolDeclaredInSequentPart = true;
                        break;
                    }

                    if (SgFile::switchToFile(saveName) == -1)
                        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
                }
                if (symbolDeclaredInSequentPart)
                    region->addToActualisation(symbol);
            }
            else 
            {
                // Searching for defenition in region
                bool symbolDeclaredInRegion = false;
                for (auto& def : defs) 
                {
                    auto saveName = current_file->filename();

                    if (!def->switchToFile())
                        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

                    const DvmhRegion* containingRegion = getContainingRegion(def);
                    if (containingRegion) 
                    {
                        symbolDeclaredInRegion = true;
                        break;
                    }

                    if (SgFile::switchToFile(saveName) == -1)
                        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
                }
                if (symbolDeclaredInRegion)
                    toActualise.push_back(symbol);
            }
        }
        insertActualDirectiveBefore(st, toActualise, ACC_GET_ACTUAL_DIR);
    }

    for (auto& region : regions)
    {
        if (region->loops.size() > 0) 
            insertActualDirectiveBefore(region->getFirstSt()->lexPrev()->lexPrev(), region->needActualisation, ACC_ACTUAL_DIR);
    }
}

static bool compareByStart(const DvmhRegion *a, const DvmhRegion *b)
{
    if (a->loops.size() < 1 || b->loops.size() < 1)
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

    return a->loops[0]->loop->lineNumber() < b->loops[0]->loop->lineNumber();
}

static bool areNeighbours(const DvmhRegion *first, const DvmhRegion *second)
{
    set<int> toSkip = { DVM_PARALLEL_ON_DIR };
    SgStatement* mediumSt = first->getLastSt()->lexNext();
    while (toSkip.count(mediumSt->variant())) // skip statements which don't prevent from merging
        mediumSt = mediumSt->lexNext();

    SgStatement* firstSt = second->getFirstSt();
    return mediumSt->fileName() == firstSt->fileName() && mediumSt->lineNumber() == firstSt->lineNumber();
}

void DvmhRegionInsertor::mergeRegions()
{
    if (regions.size() < 2)
        return;

    sort(regions.begin(), regions.end(), compareByStart);

    vector<DvmhRegion*> newRegions;
    DvmhRegion *newRegion = new DvmhRegion();
    DvmhRegion *regionPrev = regions[0];

    bool isFirst = true;
    for (auto& loop : regions[0]->loops)
        newRegion->loops.push_back(loop);

    for (auto& region : regions)
    {
        if (newRegion->fun_name == "" && region->loops.size() > 0) 
        {
            SgStatement* func_st = getFuncStat(region->loops[0]->loop);
            string fun_name = func_st->symbol()->identifier();
            newRegion->fun_name = fun_name;
        }
        //printf("Merge number %d\n", i++);
        if (isFirst) // skip first region
        {
            isFirst = false;
            continue;
        }

        // logic of intermediate derectives here, in perspective they can be accumulated and moved
        if (!areNeighbours(regionPrev, region))
        {
            newRegions.push_back(newRegion);
            newRegion = new DvmhRegion();
        }

        regionPrev = region;
        for (auto& loop : region->loops)
            newRegion->loops.push_back(loop);
        for (auto& s : region->needActualisation)
            newRegion->addToActualisation(s);
    }
    newRegions.push_back(newRegion);

    for (auto& old : regions)
        delete old;
    regions.clear();

    regions = newRegions;
}

void DvmhRegionInsertor::insertDirectives()
{
    __spf_print(1, "Find edges for regions\n");
    findEdgesForRegions(loopGraph);
    __spf_print(1, "Merging regions\n");
    mergeRegions();
    __spf_print(1, "Insert regions\n");
    insertRegionDirectives();
     __spf_print(1, "Insert actuals\n");

     //TODO
    // insertActualDirectives();
    //vector<DvmhRegion*> l_regions;
    //for (auto &region : regions)
    //  l_regions.push_back(&region);

    //__spf_print(1, "Constructing Abstract Graph\n");
    //AFlowGraph graph = AFlowGraph(file, l_regions);
}

/*********** DvmhRegion *************/
DvmhRegion::DvmhRegion(LoopGraph *loopNode, const string &fun_name) : fun_name(fun_name)
{
    loops.push_back(loopNode);
}

bool DvmhRegion::isInRegion(SgStatement *st) 
{
    if (!st)
        return false;

    int line = st->lineNumber();
    bool inLoop = false;
    for (auto& loop : loops)
        inLoop |= (st->fileName() == loop->fileName && line >= loop->lineNum && line < loop->lineNumAfterLoop);
    return inLoop;
}

DvmhRegion* DvmhRegionInsertor::getContainingRegion(SgStatement *st) 
{
    for (auto& region : regions) 
        if (region->isInRegion(st)) 
            return region;
    return NULL;
}

void DvmhRegionInsertor::insertActualDirectiveBefore(SgStatement *st, std::vector<SgSymbol*> symbols, int directive) 
{
    if (symbols.size() < 1 || !st)
        return;

    SgStatement *actualizingSt = new SgStatement(directive);

    SgExprListExp t;
    for (auto symbol : symbols) {
        SgExpression *expr = new SgVarRefExp(symbol);
        t.append(*expr);
    }

    actualizingSt->setExpression(0, *t.rhs());
    st->insertStmtBefore(*actualizingSt, *st->controlParent());
    /*
    printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
    getActualSt->unparsestdout();
    printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^");
    */
}

SgStatement* DvmhRegion::getFirstSt() const 
{
    if (loops.size() < 1) 
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
    return loops.front()->loop;
}

SgStatement* DvmhRegion::getLastSt() const
{
    if (loops.size() < 1) 
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
    return loops.back()->loop->lastNodeOfStmt();
}

// /* AFlowGraph*/
// DFGNode::DFGNode(CBasicBlock* bblock) {
//  initial.push_back(bblock);
//  type = block;
//  id = bblock->getNum();
//  // Fill containing statements
//  ControlFlowItem* cfi = bblock->getStart();
//  while (cfi && cfi->getBBno() == bblock->getNum()) 
//  {
//      SgStatement *st = cfi->getStatement();
//      if (st) {
//          content.push_back(st);

//          // Fill used distributed arrays
//          set<SgSymbol*> symbols = getUsedSymbols(st); 
//          // TODO: append used symbols in func call
//          for (auto symbol: symbols) {
//              try {
//                  DIST::Array* arr = getArrayFromDeclarated(declaratedInStmt(symbol), symbol->identifier());
//                  if (arr && !arr->GetNonDistributeFlag())
//                      d_arrays.push_back(symbol);
//              }
//              catch (...) {
//                  cout << "Disribute array assertion having some fun." << endl;
//              }
//          }
//      }

//      cfi = cfi->getNext();
//  }
// }

// DFGNode::DFGNode(vector<DFGNode*> elements) {
//  if (elements.size() == 0)
//      return;

//  // Add all initial bblocks of all element-nodes to the new one
//  for (auto node : elements) {
//      initial.insert(initial.end(), node->initial.begin(), node->initial.end()); // TODO: control duplicates
//      content.insert(content.end(), node->content.begin(), node->content.end());
//      d_arrays.insert(d_arrays.end(), node->d_arrays.begin(), node->d_arrays.end());      
//  }

//  // Add predecessors of first element-node to the new one
//  for (auto pred : elements.front()->prev)
//      prev.push_back(pred);
//  // Successors
//  for (auto succ_b : elements.back()->succ)
//      succ.push_back(succ_b);
    
//  type = par_loop;
//  id = elements.front()->id;
// }

// set<SgSymbol *> DFGNode::getSymbolsFromExpression(SgExpression *exp) 
// {
//  set<SgSymbol *> result;

//  if (exp)
//  {
//      if (exp->variant() == ARRAY_REF) 
//          result.insert(exp->symbol());

//      set<SgSymbol *> lhsSymbols = getSymbolsFromExpression(exp->lhs());
//      set<SgSymbol *> rhsSymbols = getSymbolsFromExpression(exp->rhs());

//      result.insert(lhsSymbols.begin(), lhsSymbols.end());
//      result.insert(rhsSymbols.begin(), rhsSymbols.end());
//  }

//  return result;
// }

// set<SgSymbol *> DFGNode::getUsedSymbols(SgStatement* st) 
// {
//  set<SgSymbol *> result;

//  // ignore not executable statements
//  if (!isSgExecutableStatement(st)) {
//      return result;
//  }

//  for (int i = 0; i < 3; ++i) {
//      if (st->expr(i)) {
//          set<SgSymbol *> symbolsUsedInExpression = getSymbolsFromExpression(st->expr(i));
//          result.insert(symbolsUsedInExpression.begin(), symbolsUsedInExpression.end());
//      }
//  }

//  return result;
// }

// string DFGNode::getInfo() const
// {
//  string s_content = "";
//  for (auto st: content)
//      s_content = s_content + st->unparse() + "\n";

//  string s_d_arrays = "";
//  for (auto arr: d_arrays)
//      s_d_arrays = s_d_arrays + string(arr->identifier()) + " , ";

//  string s_prev = "";
//  for (auto node: prev)
//      s_prev = s_prev + to_string(node->id) + " , ";

//  string s_succ = "";
//  for (auto node: succ)
//      s_succ = s_succ + to_string(node->id) + " , ";

//  string info = "id ["        + to_string(id)         + "]\n" +\
//              + "type ["      + to_string(type)       + "]\n" +\
//              + "content["    + s_content             + "]\n" +\
//              + "prev["       + s_prev                + "]\n" +\
//              + "succ["       + s_succ                + "]\n" +\
//              + "d_arrays["   + s_d_arrays            + "]\n";
//  return info;
// }

// bool DFGNode::addSucc(DFGNode* new_succ) 
// {
//  for (auto old_succ : succ)
//      if (old_succ == new_succ || old_succ->id == new_succ->id)
//          return false;
//  succ.push_back(new_succ);
//  return true;
// }

// bool DFGNode::addPrev(DFGNode* new_prev) 
// {
//  for (auto old_prev : prev)
//      if (old_prev == new_prev || old_prev->id == new_prev->id)
//          return false;
    
//  prev.push_back(new_prev);
//  return true;
// }

// DFGNode* AFlowGraph::getNode(string fun_name, int id)
// {
//  auto check = fun_graphs.find(fun_name);
//  if (check == fun_graphs.end())
//      return NULL;
    
//  vector<DFGNode*> graph = fun_graphs[fun_name];
//  for (auto node: graph) 
//  {
//      if (node->id == id)
//          return node;
//  }

//  return NULL;
// }

// AFlowGraph::AFlowGraph(SgFile file, vector<DvmhRegion*> regions) 
// {
//  // Build initial full CFG
//  SgStatement *st = file.functions(0);
//  GraphsKeeper* graphsKeeper = GraphsKeeper::getGraphsKeeper();
//  ControlFlowGraph* CGraph = graphsKeeper->buildGraph(st)->CGraph;

//  // Build initial abstract CFG
//  int funcNum = file.numberOfFunctions();
//  // Convert all bblocks to nodes
//  for (int i = 0; i < funcNum; ++i)
//  {
//      vector<DFGNode*> fun_graph;
//      string func_name = file.functions(i)->symbol()->identifier();
//      ControlFlowGraph* CGraph = graphsKeeper->getGraph(func_name)->CGraph;
//      if (!CGraph) 
//      {
//          cout << "Failed to find graph for function " << func_name << endl;
//          continue;
//      }

//      CBasicBlock* bb = CGraph->getFirst();
//      while (bb) 
//      {
//          fun_graph.push_back(new DFGNode(bb));
//          bb = bb->getLexNext();
//      }
//      fun_graphs[func_name] = fun_graph;
//  }
//  // Link nodes
//  for (int i = 0; i < funcNum; ++i)
//  {
//      string func_name = file.functions(i)->symbol()->identifier();
//      ControlFlowGraph* CGraph = graphsKeeper->getGraph(func_name)->CGraph;
//      if (!CGraph) 
//      {
//          cout << "Failed to find graph for function " << func_name << endl;
//          continue;
//      }

//      CBasicBlock* bb = CGraph->getFirst();
//      while (bb) 
//      {
//          DFGNode* node = getNode(func_name, bb->getNum());
//          if (!node) {
//              cout << "Node not found" << endl;
//              bb = bb->getLexNext();
//              continue;
//          }

//          BasicBlockItem* succ = bb->getSucc();
//          while (succ) {
//              DFGNode* succ_node = getNode(func_name, succ->block->getNum());
//              if (!succ_node) {
//                  cout << "Succ node not found" << endl;
//                  succ = succ->next;
//                  continue;
//              }

//              node->succ.push_back(succ_node);
//              succ = succ->next;
//          }
//          BasicBlockItem* prev = bb->getPrev();
//          while (prev) {
//              DFGNode* prev_node = getNode(func_name, prev->block->getNum());
//              if (!prev_node) {
//                  cout << "Prev node not found" << endl;
//                  prev = prev->next;
//                  continue;
//              }

//              node->prev.push_back(prev_node);
//              prev = prev->next;
//          }

//          // cout << node->getInfo(); // debug
//          // cout << "___________" << endl;
//          bb = bb->getLexNext();
//      }
//  }
//  /*
//  // Join nodes, composing regions
//  vector<DFGNode*> region_nodes;
//  for (auto region : regions)
//  {
//      auto fun_graph = fun_graphs[region->fun_name];
//      // Accumulate all nodes composing region
//      vector<DFGNode*> elements;
//      bool firstPassed = false;
//      auto firstNodeIt = fun_graph.end(); // initialisation
//      DFGNode* firstBlock;
//      for (auto loop : region->loops)
//      {
//          SgStatement* st = loop->loop;
//          SgStatement* end = loop->loop->lastNodeOfStmt();
//          while (st && st != end)
//          {
//              CBasicBlock* bb = graphsKeeper->findBlock(st);
//              if (bb)
//              {
//                  DFGNode* node = getNode(region->fun_name, bb->getNum());
//                  elements.push_back(node);
//                  auto it = find(fun_graph.begin(), fun_graph.end(), node);

//                  if (!firstPassed) // Save first block, to insert region node on it's place
//                  {
//                      firstNodeIt = it;
//                      firstBlock = node;
//                      firstPassed = true;
//                  }
//                  else
//                      fun_graph.erase(it);
//              } else
//              {
//                  cout << "Failed to find bblock for statement:" << endl;
//                  st->unparsestdout();
//              }

//              st = st->lexNext();
//          }
//      }
//      DFGNode* region_node = new DFGNode(elements);

//      // Set links to the new node
//      DFGNode* lastBlock = elements.back();
//      for (auto node : fun_graph)
//      {
//          // Found region's last basic block in some node's predecessors => replace this bond 
//          auto it = find(node->prev.begin(), node->prev.end(), lastBlock);
//          if (it != node->prev.end())
//          {
//              int idx = it - node->prev.begin();
//              node->prev[idx] = region_node;
//          }
//          // Found region's first block in some node's successors => replace this bond
//          it = find(node->succ.begin(), node->succ.end(), firstBlock);
//          if (it != node->succ.end())
//          {
//              int idx = it - node->succ.begin();
//              node->succ[idx] = region_node;
//          }
//      }

//      // Push new node
//      auto it = fun_graph.insert(firstNodeIt, region_node);
//      fun_graph.erase(it+1);
//      fun_graphs[region->fun_name] = fun_graph;
//  }
    
//  // Remove verticies which doesn't reference destributed arrays
//  for (auto graph: fun_graphs) {
//      vector<DFGNode*> shrinked_graph;
//      for (auto node: graph.second) {
//          if (node->d_arrays.size() > 0 || node->type == par_loop) {
//              shrinked_graph.push_back(node);
//              continue;
//          }
            
//          // link successors with predecessors directly
//          for (auto prev_node: node->prev) {
//              for (auto succ_node: node->succ) {
//                  prev_node->addSucc(succ_node);
//                  succ_node->addPrev(prev_node);
//              }
//          }
//          for (auto prev_node: node->prev) {
//              // delete node itself from succ of its predecessor  
//              auto node_in_succ = find(prev_node->succ.begin(), prev_node->succ.end(), node);
//              if (node_in_succ == prev_node->succ.end()) {
//                  cout << "cannot find node in succ of its predecessor" << endl;
//                  continue;
//              }
//              prev_node->succ.erase(node_in_succ);
//          }
//          for (auto succ_node: node->succ) {
//              // delete node itself from prev of its successor    
//              auto node_in_prev = find(succ_node->prev.begin(), succ_node->prev.end(), node);
//              if (node_in_prev == succ_node->prev.end()) {
//                  cout << "cannot find node in prev of its successor" << endl;
//                  continue;
//              }
//              succ_node->prev.erase(node_in_prev);
//          }

//          delete(node);
//      }
//      fun_graphs[graph.first] = shrinked_graph;
//  }
//  */
//  //Debug print
//  for (auto graph: fun_graphs) {
//      cout << "Graph for function: " << graph.first << endl;
//      for (auto node: graph.second) {
//          cout << node->getInfo(); // debug
//          cout << "___________" << endl;
//      }
//  }
//  cout << "Graph printed" << endl;
// }

RDKeeper::RDKeeper(SgFile *file) 
{
    // Build CFG
    SgStatement *st = file->functions(0);
    GraphsKeeper* graphsKeeper = GraphsKeeper::getGraphsKeeper();
    ControlFlowGraph* CGraph = graphsKeeper->buildGraph(st)->CGraph;

    // Find gen for every bb

    // Find defs for every statement
}

set<SgSymbol *> RDKeeper::getSymbolsFromExpression(SgExpression *exp) 
{
    set<SgSymbol *> result;

    if (exp)
    {
        if (exp->variant() == ARRAY_REF) {
            SgSymbol* symbol = exp->symbol();
            DIST::Array*arr = getArrayFromDeclarated(declaratedInStmt(symbol), symbol->identifier());

            if (!arr->GetNonDistributeFlag()) // if array's distributed add it
                result.insert(exp->symbol());
        }

        set<SgSymbol *> lhsSymbols = getSymbolsFromExpression(exp->lhs());
        set<SgSymbol *> rhsSymbols = getSymbolsFromExpression(exp->rhs());

        result.insert(lhsSymbols.begin(), lhsSymbols.end());
        result.insert(rhsSymbols.begin(), rhsSymbols.end());
    }

    return result;
}

set<SgSymbol *> RDKeeper::getUsedSymbols(SgStatement* st) 
{
    set<SgSymbol *> result;

    // ignore not executable statements
    if (!isSgExecutableStatement(st) || st->variant() == CONTAINS_STMT || isSgControlEndStmt(st) || isDVM_stat(st) || st->variant() == FOR_NODE)
        return result;

    for (int i = 0; i < 3; ++i) {
        if (st->expr(i)) {
            set<SgSymbol *> symbolsUsedInExpression = getSymbolsFromExpression(st->expr(i));
            result.insert(symbolsUsedInExpression.begin(), symbolsUsedInExpression.end());
        }
    }

    return result;
}