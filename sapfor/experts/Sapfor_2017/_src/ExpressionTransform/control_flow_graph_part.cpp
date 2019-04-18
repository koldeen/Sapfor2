#include "../Utils/leak_detector.h"
#include <omp.h>

#include "dvm.h"
#include "acc_analyzer.h"
#include "expr_transform.h"
#include <stack>

#define PRINT_PROF_INFO 0
using std::string;
using std::vector;
using std::map;
using std::list;
using std::make_pair;
using std::set;
using std::pair;
using std::stack;

void showDefs(set<ExpressionValue*> *defs);
void showDefs(map<SymbolKey, ExpressionValue*> *defs);
void showDefs(map<SymbolKey, set<ExpressionValue*>> *defs);
void showDefs(map<SymbolKey, SgExpression*> *defs);
static void showDefs(map <SymbolKey, set<SgExpression*>> *defs);

static CommonVarsOverseer *overseerPtr = NULL;
static map<string, ExpressionValue*> allocated;
//static map<SymbolKey, map<ExpressionValue*, SgStatement*>> symbolAndExpToDefinition;


static set<ExpressionValue> usedVariablesInStatement(SgStatement *st) {
    stack<SgExpression*> toCheck;
    set<ExpressionValue> result;

    for(int i=0;i<3;++i)
        if(st->expr(i))
            toCheck.push(st->expr(i));

    while(!toCheck.empty()) {
        SgExpression* top = toCheck.top();

        toCheck.pop();

        if(top->variant() == VAR_REF || top->variant() == ARRAY_REF)
            result.insert(ExpressionValue(top, top->unparse()));

        if (top->rhs())
            toCheck.push(top->rhs());
        if (top->lhs())
            toCheck.push(top->lhs());
    }
    return result;

}

static void addDefinitionReachesStatement(map<SgStatement*, pair<set<SgStatement*>, set<SgStatement*>>>& result, SgStatement* definition, SgStatement* reachesHere)
{
    auto found_d = result.find(definition);
    if(found_d == result.end())
    {
        pair<set<SgStatement*>, set<SgStatement*>> newPair;
        newPair.first = set<SgStatement*>();
        newPair.second = set<SgStatement*>();
        newPair.second.insert(reachesHere);
        result.insert(found_d, make_pair(definition, newPair));
    }
    else
        found_d->second.second.insert(reachesHere);

    auto found_r = result.find(reachesHere);
        if(found_r == result.end())
        {
            pair<set<SgStatement*>, set<SgStatement*>> newPair;
            newPair.first = set<SgStatement*>();
            newPair.second = set<SgStatement*>();
            newPair.first.insert(definition);
            result.insert(found_r, make_pair(reachesHere, newPair));
        }
    else
        found_r->second.first.insert(definition);
}

/**
 * symbol упоминается в st. Нужно проверить, что значение symbol действительно важно в st.
 * Например для оператора x = 7; значение x не важно, а для x = x + 2 - важно
 * TODO Для функций foo(x); нужно проверить isArgIn() / isArgOut()
 *
 * symbol - это ExpressionValue из SgExpression у которого есть symbol()
 */
static bool symbolIsUsed(SgStatement *st, const ExpressionValue &symbol) {
    stack<SgExpression*> toCheck;

    SgExpression *lval = st->expr(0);
    if(lval)
    {
        if(st->variant() == ASSIGN_STAT)
        {
            if(lval->rhs())
                toCheck.push(lval->rhs());
            if(lval->lhs())
                toCheck.push(lval->lhs());
        }
        else
            toCheck.push(lval);
    }

    for(int i=1;i<3;++i)
        if(st->expr(i))
            toCheck.push(st->expr(i));

    while(!toCheck.empty()) {
        SgExpression* top = toCheck.top();
        toCheck.pop();
        if(top->variant() == VAR_REF)
            if(symbol.getUnparsed() == top->symbol()->identifier())
                return true;

/*        if(top->variant() == ARRAY_REF) {
            //TODO ?
            if(symbol.getUnparsed() == top->unparse())
                return true;
        }*/


        if (top->rhs())
            toCheck.push(top->rhs());
        if (top->lhs())
            toCheck.push(top->lhs());
    }



    return false;
}

/**
 * Построить мап с зависимостями:
 * <Оператор от Х : пара<сет зависящих от Х операторов : сет используюемых в Х операторов>>
 * с since включительно, по till не включительно
 */
map<SgStatement*, pair<set<SgStatement*>, set<SgStatement*>>> buildRequireReachMap(SgStatement *since, SgStatement *till) {

    int sinceLine = since->lineNumber();
    int tillLine = till->lineNumber();

    map<SgStatement*, pair<set<SgStatement*>, set<SgStatement*>>> result;

    for(SgStatement* cur = since; cur != till; cur = cur->lexNext())
    {
        auto definitions = getReachingDefinitionsExt(cur);
        auto usedVariables = usedVariablesInStatement(cur);

        for(auto& var : usedVariables)
        {
            if(symbolIsUsed(cur, var))
            {
                auto expressions = definitions.find(var.getExp()->symbol());
                if (expressions != definitions.end())
                {
                    for (ExpressionValue* expValue : expressions->second)
                    {
                        SgStatement *def = expValue->getFrom();
                        if (def->lineNumber() >= sinceLine && def->lineNumber() <= tillLine && def->lineNumber() != cur->lineNumber())
                            addDefinitionReachesStatement(result, def, cur);
                    }
                }
            }
        }
    }
/*
    for(auto& it : result) {
        printf("st: %d:\n",it.first->lineNumber());
        printf("Depends on:\n");
        for(auto& itt : it.second.first)
            printf("%d ", itt->lineNumber());
        printf("\n");

        printf("Used in:\n");
        for(auto& itt : it.second.second)
            printf("%d ", itt->lineNumber());
        printf("\n");
    }*/

    return result;

}

/*

SgStatement* getDefinitionFor(const SymbolKey& symbol,  ExpressionValue* value)
{
    auto found = symbolAndExpToDefinition.find(symbol);
    if(found == symbolAndExpToDefinition.end())
        return NULL;

    for(auto& it : found->second)
        if(value->unparsedEquals(it.first))
            return it.second;

    return NULL;
}

static void saveDefinitionStatement(SymbolKey &var, ExpressionValue *value, SgStatement *defSt)
{
    auto found = symbolAndExpToDefinition.find(var);
    if(found == symbolAndExpToDefinition.end())
        symbolAndExpToDefinition.insert(found, make_pair(var, map<ExpressionValue*, SgStatement*>()))->second.insert(make_pair(value, defSt));
    else
    {
        auto ffound = found->second.find(value);
        if(ffound == found->second.end())
            ffound->second = defSt;
        else
            found->second.insert(ffound, make_pair(value, defSt));
    }
}
*/

bool symbolInExpression(const SymbolKey &symbol, SgExpression *exp)
{
    bool result = false;
    if (exp)
    {
        if (exp->variant() == VAR_REF)
            return (symbol == exp->symbol());

        if(exp->variant() == ARRAY_REF && symbol == exp->symbol())
            return true;

        bool hasSymbol = false;
        if (exp->rhs())
            hasSymbol |= symbolInExpression(symbol, exp->rhs());
        if (exp->lhs())
            hasSymbol |= symbolInExpression(symbol, exp->lhs());

        result |= hasSymbol;
    }
    return result;
}

ExpressionValue* allocateExpressionValue(SgExpression* newExp, SgStatement* from)
{
    string unp = (newExp == NULL) ? "(unknown value)" : string(newExp->unparse());
    ExpressionValue* newExpVal = NULL;
    /*auto alloc = allocated.find(unp);
    if (alloc == allocated.end())
        newExpVal = allocated.insert(alloc, make_pair(unp, new ExpressionValue(newExp, unp)))->second;
    else
        newExpVal = alloc->second;*/

    return new ExpressionValue(newExp, unp, from);
}

void CBasicBlock::addVarToGen(SymbolKey var, SgExpression *value, SgStatement *defSt)
{
    addVarToKill(var);
    ExpressionValue* expVal = allocateExpressionValue(value, defSt);
    e_gen.insert(expVal);
    gen.insert(make_pair(var, expVal));
//    saveDefinitionStatement(var, expVal, defSt);
}

void CBasicBlock::addVarUnknownToGen(SymbolKey var, SgStatement *defSt) {
    addVarToKill(var);
    ExpressionValue* expVal = allocateExpressionValue(NULL, defSt);

    gen.insert(make_pair(var, expVal));
//    saveDefinitionStatement(var, expVal, defSt);
}

void CBasicBlock::addVarToKill(const SymbolKey &key)
{
    kill.insert(key);

    for (auto it = gen.begin(); it != gen.end();)
        if (it->first == key)
            it = gen.erase(it);
        else
            ++it;

    for (auto it = e_gen.begin(); it != e_gen.end();)
        if (symbolInExpression(key, (*it)->getExp()))
            it = e_gen.erase(it);
        else
            ++it;
}

bool argIsReplaceable(int i, AnalysedCallsList *callData)
{
    // AnalysedCallsList == -1 or -2 if no user procedure/subroutine found
    if (callData == NULL || (AnalysedCallsList*)(-1) == callData || (AnalysedCallsList*)(-2) == callData)
        return false;

    int stored = SwitchFile(callData->file_id);
    SgProcHedrStmt *header = isSgProcHedrStmt(callData->header);
    SgSymbol *currPar = NULL;
    if (header)
        currPar = header->parameter(i);
    SwitchFile(stored);

    if (header == NULL)
        return false;
    if (header->parameter(i) == NULL)
        return false;
    
    int attr = currPar->attributes();
    bool isArgOut = callData->isArgOut(i, NULL);
    bool isArgIn = callData->isArgIn(i, NULL);

    if ((attr & (OUT_BIT)) || (attr & (INOUT_BIT)) || isArgOut) //argument modified inside procedure
        return false;
    else if (!((attr & (IN_BIT)) || isArgIn)) // no information, assume that argument is "inout"
        return false;
    else
        return true;
}

void CBasicBlock::checkFuncAndProcCalls(ControlFlowItem *cfi)
{
    SgStatement *st = NULL;
    AnalysedCallsList *callData = cfi->getCall();
    SgFunctionCallExp *funcCall = NULL;
    set<SgSymbol*> *varsToKill = NULL;
    if (((st = cfi->getStatement()) != NULL) && (st->variant() == PROC_STAT))
    {
        SgCallStmt *callStmt = isSgCallStmt(st);
        for (int i = 0; i < callStmt->numberOfArgs(); ++i)
        {
            SgExpression *arg = callStmt->arg(i);
            if ((arg->variant() == VAR_REF || arg->variant() == ARRAY_REF) && (!argIsReplaceable(i, callData)))
                addVarUnknownToGen(arg->symbol(), st);
        }
        varsToKill = overseerPtr->killedVars(callStmt->symbol()->identifier());
    }
    else if ((funcCall = cfi->getFunctionCall()) != NULL) 
    {
        for (int i = 0; i < funcCall->numberOfArgs(); ++i) 
        {
            SgExpression *arg = funcCall->arg(i);
            if ((arg->variant() == VAR_REF || arg->variant() == ARRAY_REF) && (!argIsReplaceable(i, callData)))
                addVarUnknownToGen(arg->symbol(), cfi->getOriginalStatement());
        }
        varsToKill = overseerPtr->killedVars(funcCall->symbol()->identifier());
    }

    if (varsToKill)
        for (auto var : *varsToKill)
            addVarUnknownToGen(var, cfi->getStatement());
}

set<SymbolKey>* CBasicBlock::getOutVars()
{
    set<SymbolKey> *outVars = new set<SymbolKey>();    
    for (auto elem : out_defs)
        outVars->insert(elem.first);
    return outVars;
}

bool CBasicBlock::varIsPointer(SgSymbol *symbol)
{
    auto found = parent->getPointers()->find(symbol);
    if(found != parent->getPointers()->end())
        return true;

    return false;
}

void CBasicBlock::processAssignThroughPointer(SgSymbol *symbol, SgExpression *right, SgStatement* st)
{
    //printf("processAssignThroughPointer REBUILD?!\n");
    auto found = gen.find(symbol);
    if (found != gen.end())
    {
        addVarToGen(found->second->getExp()->symbol(), right, st);
        return;
    }

    auto found_inDefs = in_defs.find(symbol);
    if (found_inDefs != in_defs.end())
    {
        for (auto& value : found_inDefs->second)
            addVarUnknownToGen(value->getExp()->symbol(), st);
    }
}

void CBasicBlock::processPointerAssignment(SgSymbol *symbol, SgExpression *right, SgStatement* st)
{
    //right is a single VAR_REF
    SgSymbol *rSymbol = right->symbol();
    parent->getPointers()->insert(SymbolKey(symbol, true));
    if(varIsPointer(rSymbol))
    {
        auto found = gen.find(rSymbol);
        //auto found_inDefsP = in_defs_p.find(rSymbol);
        if(found != gen.end())
            addVarToGen(SymbolKey(symbol, true), found->second->getExp(), st);
        //else if(found_inDefsP != in_defs_p.end())
            //addVarToGenP(SymbolKey(symbol, true), found_inDefsP->second);
    }
    else
        addVarToGen(SymbolKey(symbol, true), right, st);
}

void CBasicBlock::adjustGenAndKillP(ControlFlowItem *cfi)
{
    SgStatement *st = cfi->getStatement();
    if (st != NULL)
    {
        SgExpression *left = st->expr(0);
        SgExpression *right = st->expr(1);

        if (st->variant() == POINTER_ASSIGN_STAT)
            processPointerAssignment(left->symbol(), right, st);
    }

    //checkFuncAndProcCalls(cfi);
}

void CBasicBlock::processReadStat(SgStatement *readSt)
{
    SgExpression *input = readSt->expr(0);
    std::stack<SgExpression*> toCheck;

    if (input)
        toCheck.push(input);

    while (!toCheck.empty())
    {
        SgExpression *exp = toCheck.top();
        toCheck.pop();
        if (exp->variant() == VAR_REF || exp->variant() == ARRAY_REF)
            addVarToGen(exp->symbol(), NULL, readSt);
            //addVarToKill(exp->symbol());
        else
        {
            if (exp->rhs())
                toCheck.push(exp->rhs());
            if (exp->lhs())
                toCheck.push(exp->lhs());
        }
    }
}

void CBasicBlock::adjustGenAndKill(ControlFlowItem *cfi)
{
    SgStatement *st = cfi->getStatement();
    if (st != NULL)
    {
        SgExpression *left = st->expr(0);
        SgExpression *right = st->expr(1);

        if (st->variant() == ASSIGN_STAT)
        {
            if (left->variant() == VAR_REF) // x = ...
            {
                if (varIsPointer(left->symbol()))
                    processAssignThroughPointer(left->symbol(), right, st);
                else
                    addVarToGen(left->symbol(), right, st);
            }
            else if (left->variant() == ARRAY_REF) // a(...) = ...
                addVarToGen(left->symbol(), right, st);
        }
        else if(st->variant() == READ_STAT)
            processReadStat(st);
        else if (st->variant() == POINTER_ASSIGN_STAT)
            processPointerAssignment(left->symbol(), right, st);
    }

    checkFuncAndProcCalls(cfi);
}

bool CBasicBlock::expressionIsAvailable(ExpressionValue* expValue) {

    for(auto it = e_gen.begin(); it != e_gen.end(); ++it)
        if(**it == *expValue)
            return true;

    for(auto it = e_in.begin(); it != e_in.end(); ++it)
        if(**it == *expValue)
        {
            bool killed = false;
            for(auto killIt = kill.begin(); killIt != kill.end(); ++killIt)
                if(symbolInExpression(*killIt, expValue->getExp()))
                {
                    killed = true;
                    break;
                }
            if(!killed)
                return true;
        }
    return false;
}

const map<SymbolKey, set<ExpressionValue*>> CBasicBlock::getReachedDefinitionsExt(SgStatement *stmt)
{
    ControlFlowItem *cfi = getStart();
    ControlFlowItem *till = getEnd()->getNext();
    clearGenKill();
    bool founded = false;
    while (cfi != till)
    {
        if (cfi->getStatement() == stmt || cfi->getOriginalStatement() == stmt)
        {
            founded = true;
            break;
        }
        adjustGenAndKill(cfi);
        cfi = cfi->getNext();
    }


    map<SymbolKey, set<ExpressionValue*>> defs;
    if (founded)
    {
        for (auto &it : in_defs)
        {
            if (kill.find(it.first) == kill.end())
            {
                auto founded = defs.find(it.first);
                if (founded == defs.end())
                    founded = defs.insert(founded, make_pair(it.first, set<ExpressionValue*>()));

                for (auto &exp : it.second)
                    founded->second.insert(exp);
            }
        }

        for(auto &it : gen)
            defs.insert(make_pair(it.first, set<ExpressionValue*>())).first->second.insert(it.second);
    }

    return defs;
}

size_t max1 = 0;
size_t min1 = 0;
size_t max2 = 0;
size_t min2 = 0;
size_t countMerge = 0;

static bool mergeExpressionMaps(set<ExpressionValue*> &main, set<ExpressionValue*> &term)
{
#if PRINT_PROF_INFO
    ++countMerge;
    max1 = std::max(max1, main.size());
    max2 = std::max(max2, term.size());
    min1 = std::min(min1, main.size());
    min2 = std::min(min2, term.size());
#endif
    size_t mainSize = main.size();
    main.insert(term.begin(), term.end());
    if(main.size() != mainSize)
        return true;
    return false;
}

static void mergeDefs(map<SymbolKey, set<ExpressionValue*>> *main, map<SymbolKey, set<ExpressionValue*>> *term, set<SymbolKey> *allowedVars)
{
    for (auto &toCheck : *term)
    {
        if (!allowedVars || (allowedVars && allowedVars->find(toCheck.first) != allowedVars->end()))
        {
            auto founded = main->find(toCheck.first);
            if (founded == main->end())
                main->insert(founded, toCheck);
            else if (founded != main->end())
                mergeExpressionMaps(founded->second, toCheck.second);
        }
    }
}

void CBasicBlock::initializeOut()
{
    for (auto &elem : gen)
    {
        SgExpression *newExp = NULL;
        if (elem.second)
        {
            auto inserted = out_defs.find(elem.first);
            if (inserted == out_defs.end())
                inserted = out_defs.insert(inserted, make_pair(elem.first, set<ExpressionValue*>()));
            inserted->second.insert(elem.second);
        }
    }
}

void CBasicBlock::initializeEOut(set<ExpressionValue*>& allEDefs)
{
    e_in.insert(allEDefs.begin(), allEDefs.end()); //чтобы потом только уменьшать при пересечении
    if(getPrev() != NULL) //OUT[first] = empty
        e_out.insert(allEDefs.begin(), allEDefs.end());
}


bool CBasicBlock::updateEDefs()
{
    //IN == intersection of all prev OUT
    for (BasicBlockItem *prev = getPrev(); prev != NULL; prev = prev->next)
    {
        CBasicBlock *b = prev->block;
        for(auto it = e_in.begin(); it != e_in.end();)
            if(b->e_out.find(*it) == b->e_out.end())
                it = e_in.erase(it);
            else
                ++it;
    }
    int out_size = e_out.size();
    //OUT = e_gen обеъденить c (IN - kill)
    e_out.clear();
    e_out.insert(e_gen.begin(), e_gen.end());
    for(auto it = e_in.begin(); it != e_in.end(); ++it)
    {
        bool killed = false;
        for(auto killIt = kill.begin(); killIt != kill.end(); ++killIt)
            if(symbolInExpression(*killIt, (*it)->getExp()))
            {
                killed = true;
                break;
            }
        if(!killed)
            e_out.insert(*it);
    }

    if(out_size != e_out.size())
        return true;
    return false;
}

static bool addDefsFilteredByKill(map<SymbolKey, set<ExpressionValue*>> *main,
                                  map<SymbolKey, set<ExpressionValue*>> *defs, set<SymbolKey> *kill)
{
    bool mainChanged = false;
    for (auto it = defs->begin(); it != defs->end(); ++it)
    {
        SymbolKey key = it->first;
        if (kill->find(key) != kill->end())
            continue;

        auto founded = main->find(key);
        if (founded == main->end())
        {
            main->insert(make_pair(key, it->second));
            mainChanged = true;
        }
        else
            mainChanged |= mergeExpressionMaps(founded->second, it->second);
    }
    return mainChanged;
}

void showDefs(map<SymbolKey, set<ExpressionValue*>> *defs)
{
    printf("Defs: %d\n", (int)defs->size());
    for (auto it = defs->begin(); it != defs->end(); ++it)
    {
        if (it->first.isPointer())
            printf("--- %s => ", it->first.getVarName().c_str());
        else
            printf("--- %s = ", it->first.getVarName().c_str());
        for (auto iter = it->second.begin(); iter != it->second.end(); ++iter)
        {
            printf("%s", (*iter)->getUnparsed().c_str());
            if (iter != it->second.end())
                printf(", ");
        }
        printf("\n");
    }
    printf("\n");
}

void showDefs(set<ExpressionValue*> *defs)
{
    printf("Defs: %d\n", (int)defs->size());
    printf(" ");
    for (auto it = defs->begin(); it != defs->end(); ++it)
    {
        printf("%s, ", (*it)->getUnparsed().c_str());
    }
    printf("\n");
}

void showDefs(map<SymbolKey, ExpressionValue*> *defs)
{
    printf("Defs: %d\n", (int)defs->size());
    for (auto it = defs->begin(); it != defs->end(); ++it)
    {
        if(it->first.isPointer())
            printf("--- %s => %s", it->first.getVarName().c_str(), it->second->getUnparsed().c_str());
        else
            printf("--- %s = %s", it->first.getVarName().c_str(), it->second->getUnparsed().c_str());
        printf("\n");
    }
    printf("\n");
}

void showDefs(map<SymbolKey, SgExpression*> *defs)
{
    printf("Defs: %d\n", (int)defs->size());
    for (auto it = defs->begin(); it != defs->end(); ++it)
    {
        if(it->first.isPointer())
            printf("--- %s => %s", it->first.getVarName().c_str(), it->second == NULL ? "value is undefined" : it->second->unparse());
        else
            printf("--- %s = %s", it->first.getVarName().c_str(), it->second == NULL ? "value is undefined" : it->second->unparse());
        printf("\n");
    }
    printf("\n");
}

static void showDefs(map <SymbolKey, set<SgExpression*>> *defs)
{
    printf("Defs: %d\n", defs->size());
    for(auto it = defs->begin(); it != defs->end(); ++it)
    {
        printf("--- %s = ", it->first.getVarName().c_str());
        for(auto itt = it->second.begin(); itt != it->second.end(); ++itt)
            printf("%s, ", (*itt)->unparse());
        printf("\n");
    }

    printf("\n");
}

void debugStructure(ControlFlowGraph *CGraph, const string &filename)
{
    CBasicBlock *b = CGraph->getFirst();
    printf("strict digraph {\n");
    while (b != NULL)
    {
        printf("\"%s_%d\" [shape = box, label = \"%s_%d\n", b->getProc()->funName, b->getNum(), b->getProc()->funName, b->getNum());

        bool printed = false;
        ControlFlowItem *cfi = b->getStart();
        ControlFlowItem *till = b->getEnd()->getNext();
        while (cfi != till)
        {
            if (cfi->getStatement())
            {
                printed = true;
                printf("%d ", cfi->getStatement()->lineNumber());
                printf("%s\n", cfi->getStatement()->unparse());
            }
            else if(cfi->getOriginalStatement())
            {
                SgStatement *origSt = cfi->getOriginalStatement();
                if(origSt->variant() == IF_NODE)
                {
                    printed = true;
                    printf("%d ", origSt->lineNumber());
                    printf("If:   (%s)\n", ((SgIfStmt*) origSt)->conditional()->unparse());
                }

            }
            cfi = cfi->getNext();
        }
        if (!printed)
        {
            SgStatement* origStmt = NULL;
            cfi = b->getStart();
            while (cfi != till)
            {
                if ((origStmt = cfi->getOriginalStatement()) != NULL)
                {
                    printed = true;
                    printf("Original: %s\n", origStmt->unparse());
                }
                cfi = cfi->getNext();
            }
        }

        printf("\"];\n");

        for (BasicBlockItem *prev = b->getPrev(); prev != NULL; prev = prev->next)
            printf("\"%s_%d\" -> \"%s_%d\";\n", prev->block->getProc()->funName, prev->block->getNum(), b->getProc()->funName, b->getNum());
        printf("\n");

        b = b->getLexNext();
    }
    printf("}\n");
}


void showDefsOfGraph(ControlFlowGraph *CGraph)
{
    CBasicBlock *b = CGraph->getFirst();
    while (b != NULL)
    {

        printf("\n\nBlock %d, prev: ", b->getNum());
        for (BasicBlockItem *prev = b->getPrev(); prev != NULL; prev = prev->next)
            printf("%d, ", prev->block->getNum());
        printf("\n");

        bool printed = false;
        ControlFlowItem *cfi = b->getStart();
        ControlFlowItem *till = b->getEnd()->getNext();
        while (cfi != till)
        {
            if (cfi->getStatement())
            {
                printed = true;
                printf("%d ", cfi->getStatement()->lineNumber());
                cfi->getStatement()->unparsestdout();
            }
            else if(cfi->getOriginalStatement())
            {
                SgStatement *origSt = cfi->getOriginalStatement();
                if(origSt->variant() == IF_NODE)
                {
                    printed = true;
                    printf("%d ", origSt->lineNumber());
                    printf("If:   (%s)\n", ((SgIfStmt*) origSt)->conditional()->unparse());
                }

            }
            cfi = cfi->getNext();
        }
        if (!printed)
        {
            SgStatement* origStmt = NULL;
            cfi = b->getStart();
            while (cfi != till)
            {
                if ((origStmt = cfi->getOriginalStatement()) != NULL)
                {
                    printed = true;
                    printf("Original: ");
                    origStmt->unparsestdout();
                }
                cfi = cfi->getNext();
            }
        }

        if (printed)
        {
            printf("\n In ");
            showDefs(b->getInDefs());
            printf("\n Gen");
            showDefs(b->getGen());
            printf("\n E Gen");
            showDefs(b->getEGen());
            printf("\n Kill %d\n ", b->getKill()->size());
            for (auto it = b->getKill()->begin(); it != b->getKill()->end(); ++it)
                printf("%s ", it->getVarName().c_str());
            printf("\n");
            printf("\n Out ");
            showDefs(b->getOutDefs());
            printf("\n E In ");
            showDefs(b->getEIn());
            printf("\n E Out ");
            showDefs(b->getEOut());
        }
        b = b->getLexNext();
    }
}

void ClearCFGInsAndOutsDefs(ControlFlowGraph *CGraph)
{
    int64_t memCount = 0;
    int64_t elemCount = 0;
    int64_t elemCount1 = 0;
    CBasicBlock *b = CGraph->getFirst();
    while (b != NULL)
    {
#if PRINT_PROF_INFO
        auto gen = b->getGen();
        for (auto &elem : *gen)
        {
            memCount += elem.first.getVarName().size() + sizeof(SgExpression*);
            ++elemCount;
            elemCount1 += 2;
        }

        auto in_def = b->getInDefs();
        for (auto &elem : *in_def)
        {
            memCount += elem.first.getVarName().size() + elem.second.size() * sizeof(ExpressionValue*);
            ++elemCount;
            elemCount1 = elemCount1 + 1 + elem.second.size();
        }
        auto out_def = b->getOutDefs();
        for (auto &elem : *out_def)
        {
            memCount += elem.first.getVarName().size() + elem.second.size() * sizeof(ExpressionValue*);
            ++elemCount;
            elemCount1 = elemCount1 + 1 + elem.second.size();
        }
#endif
        b->clearGenKill();
        b->clearDefs();
        b = b->getLexNext();
    }

    /*int64_t countS = 0;
    for (auto &elem : allocated)
    {
#if PRINT_PROF_INFO
        countS += elem.second->getUnparsed().size();
#endif
        if (elem.second->getUnparsed() != "")
            delete elem.second;        
    }*/
#if PRINT_PROF_INFO
    if (allocated.size())
        __spf_print(1, "   count of elem %lld, in MB %f, info %lld in MB %f, elemCount = %d, elemCount1 = %d\n", 
                    countS, (double)countS / 1024. / 1024., memCount, double(memCount) / 1024./1024., elemCount, elemCount1);
#endif
    //allocated.clear();
}

//TODO
//TODO
//TODO вернуть true если GEN изменился
bool BuildGenKillAndUpdateOutP(ControlFlowGraph* CGraph)
{
    CBasicBlock* b = CGraph->getFirst();
    while (b != NULL)
    {
        ControlFlowItem *cfi = b->getStart();
        ControlFlowItem *till = b->getEnd()->getNext();
        while (cfi != till)
        {
            b->adjustGenAndKillP(cfi);
            cfi = cfi->getNext();
        }
        b = b->getLexNext();

        //Обновить OUT
        b->getOutDefsP();
    }

    return false;
}

/*
 * Отдельная подготовка достигающих определений для указателей.
 * Она не может быть проведена вместе с быной т.к. GEN для указателей зависит от IN.
 * Всё также, только GEN обновляется на каждой итерации.
 */
void PreparePointers(ControlFlowGraph *CGraph)
{
    bool setsChanged = true;
    while (setsChanged)
    {
        setsChanged = false;
        //Вычисление KILL и GEN, GEN могло измениться
        setsChanged |= BuildGenKillAndUpdateOutP(CGraph);

        CBasicBlock* b = CGraph->getFirst();
        while (b != NULL)
        {
            /*Updating IN for pointers*/
            for (BasicBlockItem* prev = b->getPrev(); prev != NULL; prev = prev->next)
                mergeDefs(b->getInDefsP(), prev->block->getOutDefsP(), NULL);

            /*Updating OUT for pointers, true, if OUT has been changed*/
            setsChanged |= addDefsFilteredByKill(b->getOutDefsP(), b->getInDefsP(), b->getKillP());
            b = b->getLexNext();
        }
    }
}

void FillCFGInsAndOutsDefs(ControlFlowGraph *CGraph, map<SymbolKey, set<ExpressionValue*>> *inDefs, CommonVarsOverseer *overseer_Ptr)
{
    overseerPtr = overseer_Ptr;
    CBasicBlock *b = CGraph->getFirst();

    PreparePointers(CGraph);

    b = CGraph->getFirst();
#if PRINT_PROF_INFO
    double time = omp_get_wtime();
#endif
    set<ExpressionValue*> availableExpressions;
    while (b != NULL)
    {
        ControlFlowItem *cfi = b->getStart();
        ControlFlowItem *till = b->getEnd()->getNext();
        while (cfi != till)
        {
            b->adjustGenAndKill(cfi);
            cfi = cfi->getNext();
        }

        availableExpressions.insert(b->getEGen()->begin(), b->getEGen()->end());
        /*Initialization of OUT, it equals to GEN	*/
        b->initializeOut();
        b = b->getLexNext();
    }
    b = CGraph->getFirst();
    while(b != NULL)
    {
        b->initializeEOut(availableExpressions);
        b = b->getLexNext();
    }
#if PRINT_PROF_INFO
    __spf_print(PRINT_PROF_INFO, "   block 1 %f\n", omp_get_wtime() - time);
    time = omp_get_wtime();
#endif
    if (inDefs != NULL)
        CGraph->getFirst()->setInDefs(inDefs);

    double timeMerge = 0;
    double timeAdd = 0;
    bool setsChanged = true;

    size_t countIn1 = 0;
    countMerge = 0;
    size_t countSet1 = 0;
    size_t countSet2 = 0;
    while (setsChanged)
    {
        setsChanged = false;
        b = CGraph->getFirst();
        while (b != NULL)
        {
#if PRINT_PROF_INFO
            double locT = omp_get_wtime();
#endif
            /*Updating IN*/
            for (BasicBlockItem *prev = b->getPrev(); prev != NULL; prev = prev->next)
            {
#if PRINT_PROF_INFO
                countSet1 = std::max(countSet1, b->getInDefs()->size());
                countSet2 = std::max(countSet2, prev->block->getOutDefs()->size());
                countIn1++;
#endif
                mergeDefs(b->getInDefs(), prev->block->getOutDefs(), NULL);

            }
#if PRINT_PROF_INFO
            timeMerge += (omp_get_wtime() - locT);
            locT = omp_get_wtime();
#endif
            /*Updating OUT, true, if OUT has been changed*/
            setsChanged |= addDefsFilteredByKill(b->getOutDefs(), b->getInDefs(), b->getKill());
#if PRINT_PROF_INFO
            timeAdd += (omp_get_wtime() - locT);
#endif
            b = b->getLexNext();
        }
    }
#if PRINT_PROF_INFO
    __spf_print(PRINT_PROF_INFO, "   block 2 %f\n", omp_get_wtime() - time);
    __spf_print(PRINT_PROF_INFO, "     merge %f, count %d, MM [%lld, %lld] [%lld, %lld], merge call %lld, %lld %lld\n",
                timeMerge, countIn1, min1, max1, min2, max2, countMerge, countSet1, countSet2);
    __spf_print(PRINT_PROF_INFO, "     add %f\n", timeAdd);
#endif
    setsChanged = true;
    while (setsChanged)
    {
        setsChanged = false;
        b = CGraph->getFirst();
        while (b != NULL)
        {
            setsChanged |= b->updateEDefs();
            b = b->getLexNext();
        }
    }
    //printf("[%s]: %s\n", tag[newDeclaration->variant()], newDeclaration->unparse());

    /*Showtime*/
    //showDefsOfGraph(CGraph);
}

bool valueWithRecursion(const SymbolKey &var, SgExpression *exp)
{
    if (!exp)
        return false;

    if (exp->variant() == VAR_REF)
        return var == exp->symbol();

    bool recursionFounded = false;
    if (exp->rhs())
        recursionFounded = valueWithRecursion(var, exp->rhs());
    if (exp->lhs() && !recursionFounded)
        recursionFounded = valueWithRecursion(var, exp->lhs());

    return recursionFounded;
}

bool valueWithFunctionCall(SgExpression *exp) 
{
    if (!exp)
        return false;

    if (exp->variant() == FUNC_CALL)
        return true;

    bool funcFounded = false;
    if (exp->rhs())
        funcFounded = valueWithFunctionCall(exp->rhs());
    if (exp->lhs() && !funcFounded)
        funcFounded = valueWithFunctionCall(exp->lhs());

    return funcFounded;
}

bool valueWithArrayReference(SgExpression *exp)
{
    if (!exp)
        return false;

    if (exp->variant() == ARRAY_REF)
        return true;

    bool arrayFounded = false;
    if (exp->rhs())
        arrayFounded = valueWithArrayReference(exp->rhs());
    if (exp->lhs() && !arrayFounded)
        arrayFounded = valueWithArrayReference(exp->lhs());

    return arrayFounded;
}

/*
* Can't expand var if:
* 1. it has multiple values
* 2. it is a NULL value
* 3. value has function call
* 4. value has itself within (recursion)
* 5. value has array reference
*/
void CBasicBlock::correctInDefsSimple()
{
    for(auto it = in_defs.begin(); it != in_defs.end();)
    {
        if (it->second.size() != 1) //1
            it = in_defs.erase(it);
        else if((*(it->second.begin()))->getExp() == NULL)
            it = in_defs.erase(it);
        else if (valueWithFunctionCall((*(it->second.begin()))->getExp())) //3
            it = in_defs.erase(it);
        else if (valueWithRecursion(it->first, (*(it->second.begin()))->getExp())) //4
            it = in_defs.erase(it);
        else if(valueWithArrayReference((*(it->second.begin()))->getExp()))
            it = in_defs.erase(it);
        else
            it++;
    }
}


/*
* Can't expand var if
* value is not present in one of previous block
*/
bool CBasicBlock::correctInDefsIterative() 
{
    bool changed = false;
    BasicBlockItem *bi = getPrev();

    if (bi)
    {
        set<SymbolKey> *allowedVars = bi->block->getOutVars();

        for (bi = bi->next; bi != NULL; bi = bi->next)
        {
            set<SymbolKey> *nextAllowedVars = bi->block->getOutVars();
            for (auto it = allowedVars->begin(); it != allowedVars->end();)
            {
                if (nextAllowedVars->find(*it) == nextAllowedVars->end())
                    it = allowedVars->erase(it);
                else
                    ++it;
            }
            delete nextAllowedVars;
        }

        //Clean inDefs
        for (auto it = in_defs.begin(); it != in_defs.end();)
            if (allowedVars->find(it->first) == allowedVars->end())
                it = in_defs.erase(it);
            else
                it++;

        //Clean outDefs
        vector<map<SymbolKey, set<ExpressionValue*>>::const_iterator> toDel;
        for (auto it = out_defs.begin(); it != out_defs.end(); ++it)
            if (allowedVars->find(it->first) == allowedVars->end()
                && gen.find(it->first) == gen.end())
                toDel.push_back(it);

        for (int i = 0; i < toDel.size(); ++i)
            out_defs.erase(toDel[i]);

        if (toDel.size() != 0)
            changed = true;

        delete allowedVars;
    }

    return changed;
}

void CorrectInDefs(ControlFlowGraph *CGraph)
{
    CBasicBlock *b = CGraph->getFirst();
    while (b != NULL)
    {
        b->correctInDefsSimple();
        b = b->getLexNext();
    }
/*    bool changes = true;
    while (changes)
    {
        changes = false;
        b = CGraph->getFirst();
        while (b != NULL)
        {
            changes |= b->correctInDefsIterative();
            b = b->getLexNext();
        }
    }*/
}
