#include "../Utils/leak_detector.h"

#include "dvm.h"
#include "acc_analyzer.h"
#include "expr_transform.h"
#include <stack>

using std::string;
using std::vector;
using std::map;
using std::list;
using std::make_pair;
using std::set;
using std::pair;


void showDefs(map<SymbolKey, map<string, SgExpression*>> *defs);
void showDefs(map<SymbolKey, SgExpression*> *defs);
static void showDefs(map <SymbolKey, set<SgExpression*>> *defs);

static CommonVarsOverseer *overseerPtr = NULL;

bool symbolInExpression(const SymbolKey &symbol, SgExpression *exp)
{
    bool result = false;
    if (exp)
    {
        if (exp->variant() == VAR_REF || exp->variant() == ARRAY_REF)
            return (symbol == exp->symbol());

        bool hasSymbol = false;
        if (exp->rhs())
            hasSymbol |= symbolInExpression(symbol, exp->rhs());
        if (exp->lhs())
            hasSymbol |= symbolInExpression(symbol, exp->lhs());

        result |= hasSymbol;
    }
    return result;
}

void CBasicBlock::addVarToGen(SymbolKey var, SgExpression *value)
{
    addVarToKill(var);
    gen.insert(make_pair(var, value));
}

void CBasicBlock::addVarToKill(const SymbolKey &key)
{
    kill.insert(key);

    for (auto it = gen.begin(); it != gen.end();)
        if (it->first == key)
            it = gen.erase(it);
        else if (symbolInExpression(key, it->second) && !it->first.isPointer())
            it = gen.erase(it);
        else
            ++it;
}

bool argIsReplaceable(int i, AnalysedCallsList *callData)
{
    // AnalysedCallsList == -1 or -2 if no user procedure /subroutine found
    if (callData == NULL || (AnalysedCallsList*)(-1) == callData || (AnalysedCallsList*)(-2) == callData)
        return false;
    SgProcHedrStmt *header = isSgProcHedrStmt(callData->header);
    if (header == NULL)
        return NULL;
    if (header->parameter(i) == NULL)
        return false;
    int attr = header->parameter(i)->attributes();

    if (callData->isArgOut(i, NULL) || (attr & (OUT_BIT)) || (attr & (INOUT_BIT))) //argument modified inside procedure
        return false;
    else if (!(callData->isArgIn(i, NULL) || (attr & (IN_BIT)))) // no information, assume that argument is "inout"
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
                addVarToKill(arg->symbol());
        }
        varsToKill = overseerPtr->killedVars(callStmt->symbol()->identifier());
    }
    else if ((funcCall = cfi->getFunctionCall()) != NULL) 
    {
        for (int i = 0; i < funcCall->numberOfArgs(); ++i) 
        {
            SgExpression *arg = funcCall->arg(i);
            if ((arg->variant() == VAR_REF || arg->variant() == ARRAY_REF) && (!argIsReplaceable(i, callData)))
                addVarToKill(arg->symbol());
        }
        varsToKill = overseerPtr->killedVars(funcCall->symbol()->identifier());
    }

    if (varsToKill)
        for (auto var : *varsToKill)
            addVarToKill(var);

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

void CBasicBlock::processAssignThroughPointer(SgSymbol *symbol, SgExpression *right)
{

    //printf("processAssignThroughPointer REBUILD?!\n");
    auto found = gen.find(symbol);
    if (found != gen.end())
    {
        addVarToGen(found->second->symbol(), right);
        return;
    }

    auto found_inDefs = in_defs.find(symbol);
    if (found_inDefs != in_defs.end())
    {
        for (auto& value : found_inDefs->second)
                addVarToKill(value.second->symbol());
    }
}

void CBasicBlock::processPointerAssignment(SgSymbol *symbol, SgExpression *right)
{
    //right is a single VAR_REF
    SgSymbol *rSymbol = right->symbol();
    parent->getPointers()->insert(SymbolKey(symbol, true));
    if(varIsPointer(rSymbol))
    {
        auto found = gen.find(rSymbol);
        //auto found_inDefsP = in_defs_p.find(rSymbol);
        if(found != gen.end())
            addVarToGen(SymbolKey(symbol, true), found->second);
        //else if(found_inDefsP != in_defs_p.end())
            //addVarToGenP(SymbolKey(symbol, true), found_inDefsP->second);

    }
    else
        addVarToGen(SymbolKey(symbol, true), right);
}

void CBasicBlock::adjustGenAndKillP(ControlFlowItem *cfi)
{
    SgStatement *st = cfi->getStatement();
    if (st != NULL)
    {
        SgExpression *left = st->expr(0);
        SgExpression *right = st->expr(1);

        if (st->variant() == POINTER_ASSIGN_STAT)
            processPointerAssignment(left->symbol(), right);
    }

    //checkFuncAndProcCalls(cfi);
}

void CBasicBlock::processReadStat(SgStatement* readSt)
{
    SgExpression *input = readSt->expr(0);
    std::stack<SgExpression*> toCheck;
    toCheck.push(input);
    while (!toCheck.empty())
    {
        SgExpression *exp = toCheck.top();
        toCheck.pop();
        if (exp->variant() == VAR_REF || exp->variant() == ARRAY_REF)
            addVarToGen(exp->symbol(), NULL);
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
                    processAssignThroughPointer(left->symbol(), right);
                else
                    addVarToGen(left->symbol(), right);
            }
            else if (left->variant() == ARRAY_REF) // a(...) = ...
                addVarToKill(left->symbol());
        }
        else if(st->variant() == READ_STAT)
            processReadStat(st);
        else if (st->variant() == POINTER_ASSIGN_STAT)
            processPointerAssignment(left->symbol(), right);
    }

    checkFuncAndProcCalls(cfi);
}

const map<SymbolKey, set<SgExpression*>> CBasicBlock::getReachedDefinitions(SgStatement *stmt)
{
    ControlFlowItem *cfi = getStart();
    ControlFlowItem *till = getEnd()->getNext();
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

    map<SymbolKey, set<SgExpression*>> defs;
    if (founded)
    {
        for (auto &it : in_defs)
        {
            if (kill.find(it.first) == kill.end())
            {
                auto founded = defs.find(it.first);
                if (founded == defs.end())
                    founded = defs.insert(founded, make_pair(it.first, set<SgExpression*>()));

                for (auto &exp : it.second)
                        founded->second.insert(exp.second);
            }
        }
    }
    return defs;
}

static bool mergeExpressionMaps(map<string, SgExpression*> &main, map<string, SgExpression*> &term)
{
    bool mainChanged = false;
    for (auto it = term.begin(); it != term.end(); ++it)
    {
        auto founded = main.find(it->first);
        if (founded == main.end())
            main.insert(founded, *it);
    }
    return mainChanged;
}

static void mergeDefs(map<SymbolKey, map<string, SgExpression*>> *main, map<SymbolKey, map<string, SgExpression*>> *term, set<SymbolKey> *allowedVars)
{
    for (auto it = term->begin(); it != term->end(); ++it)
    {
        if (!allowedVars || (allowedVars && allowedVars->find(it->first) != allowedVars->end()))
        {
            auto founded = main->find(it->first);
            if (founded == main->end())
                main->insert(founded, *it);
            if (founded != main->end())
                mergeExpressionMaps(founded->second, it->second);
        }
    }
}

void CBasicBlock::initializeOutWithGen()
{
    for (auto it = gen.begin(); it != gen.end(); ++it)
    {
        auto inserted = out_defs.insert(make_pair(it->first, map<string, SgExpression*>()));
        SgExpression *newExp = NULL;
        string newUnparsed = "";
        if (it->second)
        {
            newExp = it->second->copyPtr();
            newUnparsed = newExp->unparse();
        }
        inserted.first->second.insert(make_pair(newUnparsed, newExp));        
    }
}

static bool addDefsFilteredByKill(map<SymbolKey, map<string, SgExpression*>> *main,
                                  map<SymbolKey, map<string, SgExpression*>> *defs, set<SymbolKey> *kill)
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
            if (mergeExpressionMaps(founded->second, it->second))
                mainChanged = true;

    }
    return mainChanged;
}

void showDefs(map<SymbolKey, map<string, SgExpression*>> *defs)
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
            if(iter->second)
                printf("%s", iter->second->unparse());
            else
                printf("empty value");
            if (iter != it->second.end())
                printf(", ");
        }
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
            printf("--- %s => %s", it->first.getVarName().c_str(), it->second->unparse());
        else
            printf("--- %s = %s", it->first.getVarName().c_str(), it->second->unparse());
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

static void showDefsOfGraph(ControlFlowGraph *CGraph)
{
    CBasicBlock *b = CGraph->getFirst();
    while (b != NULL)
    {
        printf("Block %d, prev: ", b->getNum());
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
                cfi->getStatement()->unparsestdout();
            }
            else if(cfi->getOriginalStatement())
            {
                SgStatement *origSt = cfi->getOriginalStatement();
                if(origSt->variant() == IF_NODE)
                {
                    printed = true;
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
            printf("\n Kill %d\n ", b->getKill()->size());
            for (auto it = b->getKill()->begin(); it != b->getKill()->end(); ++it)
                printf("%s ", it->getVarName().c_str());
            printf("\n");
            printf("\n Out ");
            showDefs(b->getOutDefs());
        }
        b = b->getLexNext();
    }
}

void ClearCFGInsAndOutsDefs(ControlFlowGraph *CGraph)
{
    CBasicBlock *b = CGraph->getFirst();
    while (b != NULL)
    {
        b->clearGenKill();
        b->clearDefs();
        b = b->getLexNext();
    }
}

//TODO
//TODO
//TODO
void BuildGenKillAndUpdateOutP(ControlFlowGraph* CGraph)
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
        BuildGenKillAndUpdateOutP(CGraph);

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

void FillCFGInsAndOutsDefs(ControlFlowGraph *CGraph, map<SymbolKey, map<string, SgExpression*>> *inDefs, CommonVarsOverseer *overseer_Ptr)
{
    overseerPtr = overseer_Ptr;
    CBasicBlock *b = CGraph->getFirst();

    PreparePointers(CGraph);

    b = CGraph->getFirst();
    while (b != NULL)
    {
        ControlFlowItem *cfi = b->getStart();
        ControlFlowItem *till = b->getEnd()->getNext();
        while (cfi != till)
        {
            b->adjustGenAndKill(cfi);
            cfi = cfi->getNext();
        }

        /*Initialization of OUT, it equals to GEN	*/
        b->initializeOutWithGen();
        b = b->getLexNext();
    }

    if (inDefs != NULL)
        CGraph->getFirst()->setInDefs(inDefs);

    bool setsChanged = true;
    while (setsChanged)
    {
        setsChanged = false;
        b = CGraph->getFirst();
        while (b != NULL)
        {
            /*Updating IN*/
            for (BasicBlockItem* prev = b->getPrev(); prev != NULL; prev = prev->next)
                mergeDefs(b->getInDefs(), prev->block->getOutDefs(), NULL);

            /*Updating OUT, true, if OUT has been changed*/
            setsChanged |= addDefsFilteredByKill(b->getOutDefs(), b->getInDefs(), b->getKill());

            b = b->getLexNext();
        }
    }

    /*Showtime*/
    //showDefsOfGraph(CGraph);
}

bool valueWithRecursion(const SymbolKey &var, SgExpression *exp)
{
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
    if (exp->variant() == FUNC_CALL)
        return true;

    bool funcFounded = false;
    if (exp->rhs())
        funcFounded = valueWithFunctionCall(exp->rhs());
    if (exp->lhs() && !funcFounded)
        funcFounded = valueWithFunctionCall(exp->lhs());

    return funcFounded;
}

/*
* Can't expand var if:
* 1. it has multiple values
* 2. it is a NULL value
* 3. value has function call
* 4. value has itself within (recursion)
*/
void CBasicBlock::correctInDefsSimple() 
{
    for(auto it = in_defs.begin(); it != in_defs.end();)
    {
        if (it->second.size() != 1) //1
            it = in_defs.erase(it);
        else if(it->second.begin()->second == NULL)
            it = in_defs.erase(it);
        else if (valueWithFunctionCall(it->second.begin()->second)) //3
            it = in_defs.erase(it);
        else if (valueWithRecursion(it->first, it->second.begin()->second)) //4
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
        vector<map<SymbolKey, map<string, SgExpression*>>::const_iterator> toDel;
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

    bool changes = true;
/*    while (changes)
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
