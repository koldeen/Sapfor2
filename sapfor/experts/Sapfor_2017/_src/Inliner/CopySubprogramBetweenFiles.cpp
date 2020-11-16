#include "../Utils/leak_detector.h"

#include <stdlib.h>
#include <stdio.h>
#include <map>
#include <string>
#include <vector>
#include <algorithm>

#include "dvm.h"
#include "../Utils/errors.h"
#include "../Utils/utils.h"
#include "../Utils/SgUtils.h"
#include "../GraphCall/graph_calls_func.h"
#include "inliner.h"

using std::set;
using std::map;
using std::vector;
using std::pair;
using std::make_pair;
using std::string;
using std::wstring;
using std::to_string;

static map<string, SgExpression*> createMapOfArgs(SgStatement* tempHedr, SgExpression* actualArgs)
{
    __spf_print(1, "------create map of vars------\n"); // DEBUG
    printf("------create map of vars------\n"); // DEBUG
    recExpressionPrint(actualArgs); // DEBUG

    map<string, SgExpression*> vars;

    int i = 0;
    while (actualArgs)
    {
        auto actualArg = actualArgs->lhs();
        auto formalArg = ((SgFunctionSymb*)tempHedr->symbol())->parameter(i++);

        if (actualArg->variant() == INT_VAL)
            printf("%s %d\n", formalArg->identifier(), actualArg->valueInteger()); // DEBUG
        else
            printf("%s %s\n", formalArg->identifier(), actualArg->symbol()->identifier()); // DEBUG

        auto it = vars.find(formalArg->identifier());
        if (it == vars.end())
            vars.insert(it, make_pair(formalArg->identifier(), actualArg));
        else
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

        actualArgs = actualArgs->rhs();
    }

    return vars;
}

static inline SgSymbol* createSymbAndDecl(const string& varName, SgSymbol* newS, SgStatement* lastDecl, SgType* type = NULL)
{    
    static int count = 0; // created variable count

    if (newS)
        newS->changeName(string(varName + "_" + to_string(count++)).c_str());
    else
        newS = findSymbolOrCreate(current_file, string(varName + "_" + to_string(count++)), type);
    makeDeclaration(lastDecl, { newS });

    return newS;
}

static void replaceSymbInExp(SgStatement* st, SgExpression* exp, SgExpression* par, const int i, const bool lhs,
                             const map<string, SgExpression*>& argVars, map<string, SgSymbol*>& locVars, SgStatement* lastDecl,
                             const string& funcName, SgSymbol*& newHedrSymb, const string& suffix = "")
{
    if (exp)
    {
        if (exp->symbol())// && exp->symbol()->variant() == VARIABLE_NAME)
        {
            printf("%p %s\n", exp->symbol(), exp->symbol()->identifier()); // DEBUG
            const string varName = exp->symbol()->identifier();
            auto it = argVars.find(varName);
            if (it != argVars.end())
            {
                if (!par)
                    st->setExpression(i, new SgExpression(*it->second));
                else
                    lhs ? par->setLhs(new SgExpression(*it->second)) : par->setRhs(new SgExpression(*it->second));
            }
            else
            {
                auto it = locVars.find(varName);
                if (it == locVars.end())
                {
                    auto symb = createSymbAndDecl(varName + suffix, &exp->symbol()->copy(), lastDecl);
                    it = locVars.insert(it, make_pair(varName, symb));
                    printf("%s -> %s\n", varName.c_str(), symb->identifier()); // DEBUG
                    if (varName == funcName && !newHedrSymb)
                    {
                        newHedrSymb = symb;
                        printf("new hedrsymb\n"); // DEBUG
                    }
                }
                exp->setSymbol(*it->second);
            }
        }

        replaceSymbInExp(st, exp->lhs(), exp, i, true, argVars, locVars, lastDecl, funcName, newHedrSymb, suffix);
        replaceSymbInExp(st, exp->rhs(), exp, i, false, argVars, locVars, lastDecl, funcName, newHedrSymb, suffix);
    }
}

inline static void replaceSymbInStat(SgStatement* st, SgStatement* tempHedr,
                                     const map<string, SgExpression*>& argVars, map<string, SgSymbol*>& locVars, SgStatement* lastDecl,
                                     const string& funcName, SgSymbol*& newHedrSymb, const string& suffix = "")
{
    if (st->symbol())// && st->variant() != PROC_STAT)// && st->symbol()->variant() == VARIABLE_NAME)
    {
        auto s = st->symbol();
        printf("%p %s\n", s, s->identifier()); // DEBUG

        // TODO: add checking common

        const string varName = st->symbol()->identifier();
        auto it = argVars.find(varName);
        if (it != argVars.end())
            st->setSymbol(*it->second->symbol());
        else
        {
            auto it = locVars.find(st->symbol()->identifier());
            if (it == locVars.end())
            {
                auto symb = createSymbAndDecl(varName + suffix, &st->symbol()->copy(), lastDecl);
                it = locVars.insert(it, make_pair(varName, symb));
                printf("%s -> %s\n", varName.c_str(), symb->identifier()); // DEBUG
                if (varName == funcName && !newHedrSymb)
                {
                    newHedrSymb = symb;
                    printf("new hedrsymb\n"); // DEBUG
                }
            }
            st->setSymbol(*it->second);
        }
    }

    for (int i = 0; i < 3; ++i)
        replaceSymbInExp(st, st->expr(i), NULL, i, false, argVars, locVars, lastDecl, funcName, newHedrSymb, suffix);
}

// equivalent of RemapLocalVariables()
static inline void remapVars(SgStatement* tempHedr,
                             const map<string, SgExpression*>& argVars, map<string, SgSymbol*>& locVars,
                             SgStatement* lastDecl, const int count,
                             const string& funcName, SgSymbol*& newHedrSymb)
{
    printf("%p %s\n", tempHedr->symbol(), tempHedr->symbol()->identifier()); // DEBUG
    for (auto st = tempHedr; st != tempHedr->lastNodeOfStmt(); st = st->lexNext())
    {
        st->unparsestdout(); // DEBUG
        if (isSgExecutableStatement(st)) //st->variant() != FUNC_HEDR)
            replaceSymbInStat(st, tempHedr, argVars, locVars, lastDecl, funcName, newHedrSymb, "_copy_" + to_string(count));
    }
}

static void insert(SgStatement* callSt, SgStatement* tempHedr, SgStatement* begin, SgSymbol* newHedrSymb)
{
    tempHedr->unparsestdout(); // DEBUG

    auto prev = callSt->lexPrev();
    auto last = tempHedr->lastNodeOfStmt();

    auto firstExec = begin->lexNext();
    for (; firstExec && firstExec != tempHedr->lastNodeOfStmt(); firstExec = firstExec->lexNext())
        if (isSgExecutableStatement(firstExec) && firstExec->variant() != FORMAT_STAT)
            break;
    checkNull(firstExec, convertFileName(__FILE__).c_str(), __LINE__);

    tempHedr->extractStmt();
    prev->insertStmtAfter(*firstExec, *callSt->controlParent());

    prev->unparsestdout(); // DEBUG
    firstExec->unparsestdout(); // DEBUG

    last->extractStmt();
    //tempHedr->extractStmt();

    if (callSt->variant() == PROC_STAT)
        callSt->extractStmt();
    else
    {
        callSt->unparsestdout(); // DEBUG
        recExpressionPrint(callSt->expr(1)); // DEBUG
        callSt->setExpression(1, new SgExpression(VAR_REF));
        callSt->expr(1)->setSymbol(newHedrSymb);
        printf("%s\n", newHedrSymb->identifier()); // DEBUG
        callSt->unparsestdout(); // DEBUG
    }
}

static int clean(const string& funcName, SgStatement* funcSt, const map<string, FuncInfo*>& funcMap, vector<SgStatement*>& toDelete)
{
    static int labelId = getLastLabelId();

    funcSt->unparsestdout(); // DEBUG

    // site-independent transformation
    int gotoLabelId = -1;
    SgLabel* contLab = NULL;
    SgStatement* cont = NULL;

    // return goto label if entry function is called
    auto it = funcMap.find(funcName);
    if (it != funcMap.end() && it->second->funcPointer->variant() == ENTRY_STAT)
    {
        auto test = it->second->funcPointer->variant();
        gotoLabelId = ++labelId;
    }

    // TODO: move all ENTRY points to the top of the subprogram
    for (auto st = funcSt; st != funcSt->lastNodeOfStmt()->lexNext(); st = st->lexNext())
    {
        switch (st->variant())
        {
        case ENTRY_STAT:
        {
            SgLabel* gotoLab = new SgLabel(++labelId);
            SgContinueStmt* contSt = new SgContinueStmt();
            contSt->setLabel(*gotoLab);
            st->insertStmtBefore(*contSt, *st->controlParent());

            // return goto label if entry function is called
            auto test = st->symbol();
            if (st->symbol()->identifier() == funcName)
                gotoLabelId = gotoLab->getLabNumber();

            toDelete.push_back(st);
            break;
        }
        case RETURN_STAT:
        {
            if (st->lexNext()->variant() == CONTROL_END && funcSt->lastNodeOfStmt() == st->lexNext())
            {
                toDelete.push_back(st);
                break;
            }

            if (!cont) // create CONT_STAT
            {
                contLab = new SgLabel(++labelId);
                cont = new SgStatement(CONT_STAT);
                //cont = new SgContinueStmt();
                cont->setLabel(*contLab);
                auto test = funcSt->lastNodeOfStmt();
                test->unparsestdout();
                funcSt->lastNodeOfStmt()->insertStmtBefore(*cont, *funcSt);
            }

            SgGotoStmt* gotoSt = new SgGotoStmt(*contLab);
            st->insertStmtBefore(*gotoSt, *st->controlParent());

            toDelete.push_back(st);
            break;
        }
        default:
            break;
        }
    }

    // TODO: move all FORMAT statements into the top level routine

    // TODO: remap all local subprogram variables by creating new unconflicting top level variables

    funcSt->unparsestdout(); // DEBUG

    return gotoLabelId;
}

// true if inserted
static inline bool insert(SgFile* file, SgStatement* callSt, SgSymbol* funcSymb, SgExpression* args, SgStatement* lastDecl, const map<string, FuncInfo*>& funcMap)
{
    static int count = 0; // number of calls for inlining function

    bool isEntry = false;
    SgSymbol* entrySymb = NULL;

    SgStatement* tempHedr = NULL;
    SgSymbol* tempSymb = NULL;

    // TODO: check arguments
    //if (!TestConformability())
    //    return false;

    __spf_print(1, "------creating template------\n"); // DEBUG
    printf("------creating template------\n"); // DEBUG
    // 2.a create function template
    auto funcSt = funcSymb->body();
    if (funcSt->variant() == ENTRY_STAT)
    {
        isEntry = true;
        entrySymb = funcSymb;

        while (funcSt && funcSt->variant() != FUNC_HEDR)
            funcSt = funcSt->lexPrev();
        checkNull(funcSt, convertFileName(__FILE__).c_str(), __LINE__);

        funcSymb = funcSt->symbol();
    }
    // insert template after global statement in current file
    tempSymb = &(funcSymb->copySubprogram(*(file->firstStatement())));
    tempSymb = &tempSymb->copy();
    file->firstStatement()->lexNext()->setSymbol(*tempSymb);
    //tempHedr = file->firstStatement()->lexNext();
    tempHedr = tempSymb->body();
    tempHedr->unparsestdout(); // DEBUG

    // set first inserting statement
    SgStatement* begin = NULL;
    if (isEntry)
    {
        for (auto st = tempHedr; st != tempHedr->lastNodeOfStmt(); st = st->lexNext())
            if (st->variant() == ENTRY_STAT && st->symbol()->identifier() == string(entrySymb->identifier()))
                begin = st;
    }
    else
        begin = tempHedr;
    checkNull(begin, convertFileName(__FILE__).c_str(), __LINE__);
    begin->unparsestdout(); // DEBUG

    // create map of arguments
    SgSymbol* newHedrSymb = NULL; // requires for function with return variable
    map<string, SgExpression*> argVars = createMapOfArgs(tempHedr, args); // local argument variable -> top argument variable
    map<string, SgSymbol*> locVars; // local varname -> new local var
    tempHedr->unparsestdout(); // DEBUG
    remapVars(tempHedr, argVars, locVars, lastDecl, count, begin->symbol()->identifier(), newHedrSymb);
    tempHedr->unparsestdout(); // DEBUG
    //checkNull(newHedrSymb, convertFileName(__FILE__).c_str(), __LINE__);
    if (!newHedrSymb) // if no textual use of return variable, create new anyway
        newHedrSymb = createSymbAndDecl(string(tempSymb->identifier()) + "_copy", &tempSymb->copy(), lastDecl);
    ++count;
    tempHedr->unparsestdout(); // DEBUG

    // clean function
    vector<SgStatement*> toDelete;
    int gotoLabId = clean(funcSymb->identifier(), tempHedr, funcMap, toDelete);
    if (gotoLabId != -1)
    {
        SgLabel* gotoLab = new SgLabel(gotoLabId);
        SgGotoStmt* gotoSt = new SgGotoStmt(*gotoLab);
        callSt->insertStmtBefore(*gotoSt, *callSt->controlParent());
    }

    /*
    // 2.b perform site_specific transformations
    if (st->variant() == ASSIGN_STAT)
        RemapFunctionResultVar(stmt->expr(0), scopy);
    ConformActualAndFormalParameters(scopy, args, stmt);
    */

    // 2.c
    /*
    // 2.d transform all references to subprogram variables to "top level" form
    expanded_stmt = TranslateSubprogramReferences(header_work);

    // 2.e insert template
    */
    insert(callSt, tempHedr, begin, newHedrSymb);

    for (auto& st : toDelete)
        st->extractStmt();

    return true;
}

static inline void replaceCall(SgExpression* exp, SgExpression* par, const int i, const bool lhs,
                               SgStatement* callSt, SgStatement* lastDecl, SgStatement* insertPlace)
{
    // create new call variable for this call and its declaration
    SgSymbol* v = createSymbAndDecl("arg", &exp->symbol()->copy(), lastDecl);

    SgAssignStmt* assign = new SgAssignStmt(*new SgVarRefExp(*v), *exp->copyPtr());
    assign->setlineNumber(getNextNegativeLineNumber());
    insertPlace->insertStmtBefore(*assign, *callSt->controlParent());

    // replace function call to a new variable
    if (!par)
        callSt->setExpression(i, new SgVarRefExp(*v));
    else
        lhs ? par->setLhs(new SgVarRefExp(*v)) : par->setRhs(new SgVarRefExp(*v));
}

static void recFindFuncCall(SgExpression* exp, SgExpression* par, const int i, const bool lhs,
                            const string& funcName, bool& foundCall,
                            SgStatement* callSt, SgStatement* lastDecl, SgStatement* insertPlace)
{
    if (exp)
    {
        recFindFuncCall(exp->rhs(), exp, i, false, funcName, foundCall, callSt, lastDecl, insertPlace);
        recFindFuncCall(exp->lhs(), exp, i, true, funcName, foundCall, callSt, lastDecl, insertPlace);

        if (exp->variant() == FUNC_CALL && exp->symbol() && exp->symbol()->identifier() == funcName)
        {
            foundCall = true;
            if (par) // do not extract external func call
                replaceCall(exp, par, i, lhs, callSt, lastDecl, insertPlace);
        }
    }
}

static inline SgStatement* getFirstInsertedStat(SgStatement* st)
{
    SgStatement* curSt = st;

    while (curSt)
    {
        auto prev = curSt->lexPrev();
        checkNull(prev, convertFileName(__FILE__).c_str(), __LINE__);
        if (prev->lineNumber() > 0)
            break;
        curSt = prev;
    }
    return curSt;
}

static int ParameterType(SgExpression* exp, SgStatement* st)
{
    if (isSgVarRefExp(exp) ||                                    // scalar variable
        isSgArrayRefExp(exp) ||                                  // array variable
        exp->variant() == CONST_REF ||                           // symbol (named) constant
        isSgValueExp(exp))// && exp->type()->variant() != T_STRING) // literal constant
        return 1;
    return 0;
}

static inline void PrecalculateExpression(SgSymbol* sp, SgExpression* e, SgStatement* stmt)
{
    SgStatement* newst;
    newst = new SgAssignStmt(*new SgVarRefExp(sp), *e);
    newst->setlineNumber(getNextNegativeLineNumber());
    stmt->insertStmtBefore(*newst, *stmt->controlParent());
}

static inline void PrecalculateActualParameters(SgStatement* st, SgSymbol* s, SgExpression* e, SgStatement* lastDecl)
{
    // Precalculate actual parameter expressions
    // e - actual parameter list
    int i;
    SgExpression* el;
    SgSymbol* sp;
    if (!e) 
        return;
    //if (is_NoExpansionFunction(s)) return; // expansion may not be made

    i = 1;
    for (el = e; el; el = el->rhs(), i++)
    {
        switch (ParameterType(el->lhs(), st))
        {
        case 1:
            break; // actual parameter can be accessed by reference
        //case 2:  PrecalculateSubscripts(el->lhs(),stmt); break;
        default:            
            sp = createSymbAndDecl("arg", NULL, lastDecl, el->lhs()->type());
            PrecalculateExpression(sp, el->lhs(), st); //to support access by reference 
            el->setLhs(new SgVarRefExp(sp)); //replace actual parameter expression by 'sp' reference
            break;
        }
    }
}

bool inliner(const string& fileName, const string& funcName, const int lineNumber,
             const map<string, vector<FuncInfo*>>& allFuncInfo, map<string, vector<Messages>>& SPF_messages)
{
    map<string, FuncInfo*> funcMap;
    createMapOfFunc(allFuncInfo, funcMap);

    auto func = getFuncInfo(funcMap, funcName);

    if (func)
    {
        if (func->fileName != fileName)
            return true; // not implemented yet

        if (SgFile::switchToFile(func->fileName) == -1)
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

        // now function is expected to be declared in the target file
        SgStatement* callSt = SgStatement::getStatementByFileAndLine(fileName, lineNumber);
        SgStatement* insertPlace = callSt;

        checkNull(callSt, convertFileName(__FILE__).c_str(), __LINE__);

        SgStatement* firstExe = NULL;
        SgStatement* lastDecl = NULL;

        SgStatement* funcStat = func->funcPointer->GetOriginal();
        SgSymbol* funcSymb = funcStat->symbol();

        bool foundCall = false;

        if (!callSt || !isSgExecutableStatement(callSt))
        {
            wstring messageE, messageR;
            __spf_printToLongBuf(messageE, L"It is allowed to inline function only at execution code section.");
#ifdef _WIN32
            __spf_printToLongBuf(messageR, R177);
#endif
            getObjectForFileFromMap(fileName.c_str(), SPF_messages).push_back(Messages(ERROR, lineNumber, messageR, messageE, 2011));
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
        }

        // get last delcaration statement and first execution
        firstExe = getFuncStat(callSt);
        while (firstExe && (!isSgExecutableStatement(firstExe) || isDVM_stat(firstExe)))
            firstExe = firstExe->lexNext();
        lastDecl = firstExe->lexPrev();

        if (!firstExe || !lastDecl)
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

        __spf_print(1, "------start inliner-----\n"); // DEBUG        
        __spf_print(1, "---statement preprocessing---\n"); // DEBUG

        // 1.a: make statement preprocessing
        // if call statement contains several inlining functions, split every such call
        // TODO: check if-clause
        for (int i = 0; i < 3; ++i)
            recFindFuncCall(callSt->expr(i), NULL, i, false, funcName, foundCall, callSt, lastDecl, insertPlace);

        __spf_print(1, "---argument preprocessing---\n"); // DEBUG
        // 1.b: make argument preprocessing
        // get first inserted statement
        SgStatement* begin = getFirstInsertedStat(callSt);
        checkNull(begin, convertFileName(__FILE__).c_str(), __LINE__);

        // if call statement has any expression as its artument, split this expression for separate statement
        // if call statement has any function as its argument, split this call
        for (auto st = begin; st != callSt->lexNext(); st = st->lexNext())
        {
            if (st->variant() == ASSIGN_STAT)
            {
                if (st->expr(1)->symbol() && st->expr(1)->symbol()->identifier() == funcName)
                {                    
                    if (isSgVarRefExp(st->expr(0)) || isSgArrayRefExp(st->expr(0)) && !isSgArrayType(st->expr(0)->type()))
                        PrecalculateActualParameters(st, st->expr(1)->symbol(), st->expr(1)->lhs(), st);
                }
            }
            else if (st->variant() == PROC_STAT)
            {
                if (st->symbol() && st->symbol()->identifier() == funcName)
                {
                    // TODO: ???
                    if (st->expr(0))
                        PrecalculateActualParameters(st, st->symbol(), st->expr(0)->lhs(), st);
                }
            }
        }

        __spf_print(1, "---start inlining---\n"); // DEBUG
        // 2. create function template to modify and insert it
        if (foundCall)
        {
            bool change = true;

            while (change)
            {
                change = false;

                // get first inserted statement
                begin = getFirstInsertedStat(callSt);
                if (!begin)
                    printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
                begin->unparsestdout(); // DEBUG

                for (auto st = begin; st != callSt->lexNext(); st = st->lexNext())
                {
                    //st->unparsestdout(); // DEBUG
                    switch (st->variant())
                    {
                    case ASSIGN_STAT:
                        if (st->expr(1)->variant() == FUNC_CALL && st->expr(1)->symbol() && st->expr(1)->symbol()->identifier() == funcName)
                            change = change || insert(current_file, st, funcSymb, st->expr(1)->lhs(), lastDecl, funcMap);
                        continue;
                    case PROC_STAT:
                        if (st->expr(0)->symbol() && st->expr(0)->symbol()->identifier() == funcName)
                            change = change || insert(current_file, st, funcSymb, st->expr(0), lastDecl, funcMap);
                        continue;
                    default:
                        continue;
                    }
                }
            }
        }
    }
    return false;
}
