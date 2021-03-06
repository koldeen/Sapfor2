#include "../Utils/leak_detector.h"

#include "dvm.h"
#include "acc_analyzer.h"
#include "expr_transform.h"
#include <stack>
#include <chrono>

#define PRINT_PROF_INFO 0
using std::string;
using std::vector;
using std::map;
using std::list;
using std::make_pair;
using std::set;
using std::pair;
using std::stack;
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::milliseconds;

void showDefs(set<ExpressionValue*> *defs);
void showDefs(map<SymbolKey, ExpressionValue*> *defs);
void showDefs(map<SymbolKey, set<ExpressionValue*>> *defs);
void showDefs(map<SymbolKey, SgExpression*> *defs);
static void showDefs(map <SymbolKey, set<SgExpression*>> *defs);

static CommonVarsOverseer *overseerPtr = NULL;
//static map<string, ExpressionValue*> allocated;
static map<int, set<ExpressionValue*>> allocated2;

static const char* unknownValueChars = "unknownValue";

static set<ExpressionValue> usedVariablesInStatement(SgStatement *st, set<string> &privates) {
    stack<SgExpression*> toCheck;
    set<ExpressionValue> result;

    for(int i=0;i<3;++i)
        if(st->expr(i))
            toCheck.push(st->expr(i));

    while(!toCheck.empty()) {
        SgExpression* top = toCheck.top();

        toCheck.pop();

        if(top->variant() == VAR_REF)
            result.insert(ExpressionValue(top, top->unparse()));
        if(top->variant() == ARRAY_REF) {
            if(privates.find(top->symbol()->identifier()) != privates.end())
                result.insert(ExpressionValue(top, top->unparse()));
        }

        if (top->rhs())
            toCheck.push(top->rhs());
        if (top->lhs())
            toCheck.push(top->lhs());
    }
    return result;

}

static void addDefinitionReachesStatement(map<SgStatement*, pair<set<SgStatement*>, set<SgStatement*>>>& result, SgStatement* definition, SgStatement* reachesHere)
{
    //this depends on
    auto found_r = result.find(reachesHere);
    if (found_r == result.end())
    {
        pair<set<SgStatement*>, set<SgStatement*>> newPair;
        newPair.first = set<SgStatement*>();
        newPair.second = set<SgStatement*>();
        newPair.first.insert(definition);
        result.insert(found_r, make_pair(reachesHere, newPair));
    }
    else
        found_r->second.first.insert(definition);

    //this used in
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
}

static bool checkSymbolUsedByProcsAndFuncs(SgStatement *st, const ExpressionValue &symbol, map<SymbolKey, set<ExpressionValue>> &arraysAssingments, vector <ControlFlowItem*> &cfis) {
    if(cfis.size() == 0)
        findCFIsForStmt(st, cfis);

    for(ControlFlowItem *cfi : cfis) {

        AnalysedCallsList *callData = cfi->getCall();
        SgFunctionCallExp *funcCall = NULL;
        if (((st = cfi->getStatement()) != NULL) && (st->variant() == PROC_STAT))
        {
            SgCallStmt *callStmt = isSgCallStmt(st);
            for (int i = 0; i < callStmt->numberOfArgs(); ++i)
            {
                SgExpression *arg = callStmt->arg(i);
                if ((arg->variant() == VAR_REF /*|| arg->variant() == ARRAY_REF*/) && argIsUsed(i, callData)) {
                    if(strcmp(symbol.getExp()->symbol()->identifier(), arg->symbol()->identifier())) {
//                        printf("in %d ", st->lineNumber());
//                        printf(" %s is required\n", arg->unparse());
                        return true;
                    }
                }
            }
        }
        else if ((funcCall = cfi->getFunctionCall()) != NULL)
        {
            for (int i = 0; i < funcCall->numberOfArgs(); ++i)
            {
                SgExpression *arg = funcCall->arg(i);
                if ((arg->variant() == VAR_REF /*|| arg->variant() == ARRAY_REF*/) && argIsUsed(i, callData)) {
                    if(strcmp(symbol.getExp()->symbol()->identifier(), arg->symbol()->identifier())) {
//                        printf("in %d ", st->lineNumber());
//                        printf(" %s is required\n", arg->unparse());
                        return true;
                    }
                }
            }
        }
    }

    return false;
}

/**
 * symbol ?????????????????????? ?? st. ?????????? ??????????????????, ?????? ???????????????? symbol ?????????????????????????? ?????????? ?? st.
 * ???????????????? ?????? ?????????????????? x = 7; ???????????????? x ???? ??????????, ?? ?????? x = x + 2 - ??????????
 * symbol - ?????? ExpressionValue ???? SgExpression ?? ???????????????? ???????? symbol()
 */
static bool symbolIsUsed(SgStatement *st, const ExpressionValue &symbol, map<SymbolKey, set<ExpressionValue>> &arraysAssingments, vector <ControlFlowItem*> &cfis) {
    stack<SgExpression*> toCheck;

    if(checkSymbolUsedByProcsAndFuncs(st, symbol, arraysAssingments, cfis)) {
//        if(st->lineNumber() == 345/* || st->lineNumber() == 301*/)
//            printf("from func true\n");
        return true;
    }



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
            if(symbol.getUnparsed() == top->symbol()->identifier()) {
//                if(st->lineNumber() == 345 || st->lineNumber() == 301)
//                    printf("%s == %s is true\n", symbol.getUnparsed().c_str(), top->symbol()->identifier());
                return true;
            }

        //TODO arraysAssignments
        /*
        if(top->variant() == ARRAY_REF) {

            if(symbol.getUnparsed() == top->unparse())
                return true;
        }*/

        //???? ?????????? ?????????????????? ?????????????? ????????????????
        if(top->variant() != ARRAY_REF) {
            SgExpression *rhs = top->rhs();
            SgExpression *lhs = top->lhs();

            if (rhs && rhs->variant() != FUNC_CALL)
                toCheck.push(rhs);
            if (lhs && lhs->variant() != FUNC_CALL)
                toCheck.push(lhs);
        }
    }

    return false;
}

static void updateArraysAssingments(map<SymbolKey, set<ExpressionValue>> &arraysAssingments, map<SymbolKey, set<ExpressionValue*>> &definitions, SgStatement* cur)
{
    for(auto it : definitions)
        for(auto itt : it.second)
            if(itt->getUnparsed() == unknownValueChars)
            {
                auto founded = arraysAssingments.find(it.first);
                if(founded != arraysAssingments.end()) {
//                    for(auto fit : founded->second)
//                       delete fit;
                    arraysAssingments.erase(it.first);
                }
            }

    if(cur->variant() == ASSIGN_STAT)
    {
        SgExpression *var = cur->expr(0);
        if(var->variant() == ARRAY_REF)
        {
            auto founded = arraysAssingments.find(var->symbol());
            string unp = var->unparse();
            ExpressionValue expVal = ExpressionValue(var, unp);
            if(founded == arraysAssingments.end())
                arraysAssingments.insert(founded, make_pair(var->symbol(), set<ExpressionValue>()))->second.insert(expVal  );
            else
                founded->second.insert(expVal);
        }
    }
}

/**
 * ?????????????????? ?????? ?? ??????????????????????????:
 * <???????????????? ???? ?? : ????????<?????? ?????????????????? ???? ?? ???????????????????? : ?????? ?????????????????????????? ?? ?? ????????????????????>>
 * ?? since ????????????????????????, ???? till ???? ????????????????????????
 */
map<SgStatement*, pair<set<SgStatement*>, set<SgStatement*>>> buildRequireReachMapForLoop(SgStatement *since, SgStatement *till, set<string> &privates) {

    int sinceLine = since->lineNumber();
    int tillLine = till->lineNumber();

    map<SgStatement*, pair<set<SgStatement*>, set<SgStatement*>>> result;
    map<SymbolKey, set<ExpressionValue>> arraysAssingments;

    for(SgStatement* cur = since; cur != till; cur = cur->lexNext())
    {
        auto definitions = getReachingDefinitionsExt(cur);
        updateArraysAssingments(arraysAssingments, definitions, cur);
        auto usedVariables = usedVariablesInStatement(cur, privates);
        vector <ControlFlowItem*> cfis;

/*
                printf("after %d:\n", cur->lineNumber());
                for(auto it : arraysAssingments)
                {
                    printf("    %s: ", it.first.getVarName().c_str());
                    for(auto itt : it.second)
                        printf("%s, ", itt.getUnparsed().c_str());
                    printf("\n");
                }

*/
        for(auto& var : usedVariables)
        {
/*            if(cur->lineNumber() == 127) {
                printf("checking %d for %s %s\n",cur->lineNumber(), var.getUnparsed().c_str(), cur->unparse());
           }*/
            if(symbolIsUsed(cur, var, arraysAssingments, cfis))
            {
/*                if(cur->lineNumber() == 127) {
                    printf("%s is used\n", var.getUnparsed().c_str());
               }*/


                auto expressions = definitions.find(var.getExp()->symbol());
                if (expressions != definitions.end())
                {
                    for (ExpressionValue* expValue : expressions->second)
                    {
                        SgStatement *def = expValue->getFrom();
                        if (def->lineNumber() >= sinceLine && def->lineNumber() <= tillLine && def->lineNumber() != cur->lineNumber()) {
                            addDefinitionReachesStatement(result, def, cur);
/*                            if(cur->lineNumber() == 127)
                                printf("connected to %s\n", def->unparse());*/
                        }
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
        printf("\n");
    }*/


    return result;

}

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
    string unp = (newExp == NULL) ? unknownValueChars : string(newExp->unparse());

    int file_id = from == NULL ? current_file_id : from->getFileId();
    auto allocatedMap = allocated2.find(file_id);
    if(allocatedMap == allocated2.end())
        allocatedMap = allocated2.insert(allocatedMap, make_pair(file_id, set<ExpressionValue*>()));

    for(ExpressionValue* expVal : allocatedMap->second)
        if(expVal->getUnparsed() == unp && expVal->getFrom() == from)
            return expVal;

    ExpressionValue* newExpVal = new ExpressionValue(newExp, unp, from);
    allocatedMap->second.insert(newExpVal);
    return newExpVal;

/*    auto alloc = allocatedMap->second.find(unp);
    if (alloc == allocatedMap->second.end())
        newExpVal = allocatedMap->second.insert(alloc, make_pair(unp, new ExpressionValue(newExp, unp, from)))->second;
    else
        newExpVal = alloc->second;
*/
/*    auto alloc = allocated.find(unp);
    if (alloc == allocated.end())
        newExpVal = allocated.insert(alloc, make_pair(unp, new ExpressionValue(newExp, unp, from)))->second;
    else
        newExpVal = alloc->second;
*/
//    return newExpVal;//new ExpressionValue(newExp, unp, from);
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

bool argIsUsed(int i, AnalysedCallsList *callData)
{
    // AnalysedCallsList == -1 or -2 if no user procedure/subroutine found
    if (callData == NULL || (AnalysedCallsList*)(-1) == callData || (AnalysedCallsList*)(-2) == callData)
        return true;

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
    if(((attr & (IN_BIT)) || (attr & (INOUT_BIT))) || isArgIn) //argument used in procedure
        return true;
    else
        return false;
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
    if (symbol == NULL)
        return false;

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
    //TODO: Record_Ref
    if (symbol == NULL)
        return;

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

/*
    for(auto it : defs) {
        printf("%s: ", it.first.getVarName().c_str());
        for(auto itt : it.second)
            printf("%s, ", itt->getUnparsed().c_str());
        printf("\n");
    }
*/
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
    e_in.insert(allEDefs.begin(), allEDefs.end()); //?????????? ?????????? ???????????? ?????????????????? ?????? ??????????????????????
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
    //OUT = e_gen ???????????????????? c (IN - kill)
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
    printf("Defs: %d\n", (int)defs->size());
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
            printf("\n Kill %d\n ", (int)b->getKill()->size());
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
    }
#if PRINT_PROF_INFO
    if (allocated.size())
        __spf_print(1, "   count of elem %lld, in MB %f, info %lld in MB %f, elemCount = %d, elemCount1 = %d\n", 
                    countS, (double)countS / 1024. / 1024., memCount, double(memCount) / 1024./1024., elemCount, elemCount1);
#endif
*/
    //allocated.clear();
}

void deleteAllocatedExpressionValues(int file_id) {
    auto fa = allocated2.find(file_id);
    if(fa != allocated2.end())
        for(auto &elem : fa->second)
            delete elem;
//            delete elem.second;0
    allocated2.clear();
}

//TODO
//TODO
//TODO ?????????????? true ???????? GEN ??????????????????
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

        //???????????????? OUT
        b->getOutDefsP();
    }

    return false;
}

/*
 * ?????????????????? ???????????????????? ?????????????????????? ?????????????????????? ?????? ????????????????????.
 * ?????? ???? ?????????? ???????? ?????????????????? ???????????? ?? ?????????? ??.??. GEN ?????? ???????????????????? ?????????????? ???? IN.
 * ?????? ??????????, ???????????? GEN ?????????????????????? ???? ???????????? ????????????????.
 */
void PreparePointers(ControlFlowGraph *CGraph)
{
    bool setsChanged = true;
    while (setsChanged)
    {
        setsChanged = false;
        //???????????????????? KILL ?? GEN, GEN ?????????? ????????????????????
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
    auto time = high_resolution_clock::now();
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
    __spf_print(PRINT_PROF_INFO, "   block 1 %f\n", 
                duration_cast<milliseconds>(high_resolution_clock::now() - time).count() / 1000.);
    time = high_resolution_clock::now();
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
            auto locT = high_resolution_clock::now();
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
            timeMerge += (duration_cast<milliseconds>(high_resolution_clock::now() - locT).count() / 1000.);
            locT = high_resolution_clock::now();
#endif
            /*Updating OUT, true, if OUT has been changed*/
            setsChanged |= addDefsFilteredByKill(b->getOutDefs(), b->getInDefs(), b->getKill());
#if PRINT_PROF_INFO
            timeAdd += (duration_cast<milliseconds>(high_resolution_clock::now() - locT).count() / 1000.);
#endif
            b = b->getLexNext();
        }
    }
#if PRINT_PROF_INFO
    __spf_print(PRINT_PROF_INFO, "   block 2 %f\n", 
                duration_cast<milliseconds>(high_resolution_clock::now() - time).count() / 1000.);
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

static bool ifExprExist(SgExpression *curr, const int toFind)
{
    if (curr)
    {
        if (curr->id() == toFind)
            return true;
        else
            return ifExprExist(curr->lhs(), toFind) || ifExprExist(curr->rhs(), toFind);
    }
    return false;
}

static SgStatement* getStatmentByExpression(SgStatement* begin, SgExpression* ex)
{
    SgStatement* start = begin ? begin : current_file->firstStatement();
    SgStatement* end = NULL;
    if (begin)
        end = getFuncStat(begin, { MODULE_STMT })->lastNodeOfStmt();

    for (auto st = start; st != end; st = st->lexNext())
    {
        for (int z = 0; z < 3; ++z)
            if (ifExprExist(st->expr(z), ex->id()))
                return st;
    }

    // if NULL found, try to find across full file
    if (begin)
    {
        for (auto st = current_file->firstStatement()->lexNext(); st; st = st->lexNext())
            for (int z = 0; z < 3; ++z)
                if (ifExprExist(st->expr(z), ex->id()))
                    return st;
    }
    return NULL;
}

static void findFuncCall(SgExpression* ex, vector<SgExpression*>& calls)
{
    if (ex)
    {
        if (ex->variant() == FUNC_CALL)
            if (!isIntrinsicFunctionName(ex->symbol()->identifier()))
                calls.push_back(ex);

        findFuncCall(ex->rhs(), calls);
        findFuncCall(ex->lhs(), calls);
    }
}

static bool checkRange(SgStatement *start, SgStatement *end, const DIST::Array* array)
{
    const string arrName = array->GetShortName();
    for (auto st = start; st != end; st = st->lexNext())
    {
        if (st->variant() == ASSIGN_STAT)
        {
            auto ex = st->expr(0);
            if (ex->variant() == ARRAY_REF && ex->symbol()->identifier() == arrName)
                return false;
        }
        else if (st->variant() == READ_STAT || st->variant() == WRITE_STAT)
        {
            for (int z = 0; z < 3; ++z)
            {
                if (st->expr(z))
                {
                    auto listOfS = st->expr(z)->symbRefs();
                    for (auto ex = listOfS; ex; ex = ex->rhs())
                        if (ex->lhs()->variant() == ARRAY_REF && ex->lhs()->symbol()->identifier() == arrName)
                            return false;
                }
            }
        }
        else if (st->variant() == PROC_STAT)
        {
            for (auto args = st->expr(0); args; args = args->rhs())
            {
                if (args->lhs()->variant() == ARRAY_REF)
                    if (args->lhs()->symbol()->identifier() == arrName)
                        return false;
            }
        }
        else
        {
            //TODO: 
        }

        //find func call
        vector<SgExpression*> calls;
        for (int z = 0; z < 3; ++z)
            if (st->expr(z))
                findFuncCall(st->expr(z), calls);
        
        for (auto& elem : calls)
        {
            for (auto args = elem->lhs(); args; args = args->rhs())
            {
                if (args->lhs()->variant() == ARRAY_REF)
                    if (args->lhs()->symbol()->identifier() == arrName)
                        return false;
            }
        }

        if (calls.size())
        {
            if (array->GetLocation().first == DIST::l_MODULE || array->GetLocation().first == DIST::l_COMMON)
            {
                //TODO: need to add IP analysis
            }
        }
    }

    return true;
}

//TODO: improve for MODULE
static bool allowedArrayReference(SgExpression *exp)
{    
    //Must return false if exp is not allowed to be substituted
    SgSymbol* arr = OriginalSymbol(exp->symbol());
    checkNull(arr, convertFileName(__FILE__).c_str(), __LINE__);
    SgStatement* decl = declaratedInStmt(arr);
    checkNull(decl, convertFileName(__FILE__).c_str(), __LINE__);

    DIST::Array* array = getArrayFromDeclarated(decl, arr->identifier());

    checkNull(array, convertFileName(__FILE__).c_str(), __LINE__);
    if (array->GetNonDistributeFlagVal() == DIST::SPF_PRIV)
        return false;
    
    SgStatement* st = getStatmentByExpression(decl, exp);
    checkNull(st, convertFileName(__FILE__).c_str(), __LINE__);

    SgStatement* cp = st->controlParent();
    SgStatement* prev = st;
    while (isSgProgHedrStmt(cp) == NULL)
    {
        prev = cp;
        cp = cp->controlParent();
    }

    auto last = prev->lastNodeOfStmt();
    return checkRange(cp, last, array);
}

bool valueWithArrayReference(SgExpression *exp)
{
    if (!exp)
        return false;

    if (exp->variant() == ARRAY_REF)
        if (exp->symbol() && exp->symbol()->type()->variant() != T_STRING)
            return !allowedArrayReference(exp);

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
