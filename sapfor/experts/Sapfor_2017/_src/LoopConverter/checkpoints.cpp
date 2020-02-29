#include "../Utils/leak_detector.h"

#include <vector>
#include <string>
#include <set>

#include "../Utils/SgUtils.h"
#include "../Utils/utils.h"

#include "checkpoints.h"

using namespace std;

enum class typeEvery { TIME, ITER };

static void findDecls(SgExpression* ex, vector<SgExpression*>& local, const map<string, SgStatement*>& localParams, 
                      set<string>& added)
{
    if (ex)
    {
        if (ex->variant() == VAR_REF)
        {
            if (ex->symbol()->variant() == VARIABLE_NAME &&
                localParams.find(ex->symbol()->identifier()) == localParams.end())
            {
                if (added.find(ex->symbol()->identifier()) == added.end())
                {
                    added.insert(ex->symbol()->identifier());
                    local.push_back(ex);
                }
            }
        }

        if (ex->variant() == ARRAY_REF)
        {
            if (ex->symbol()->variant() == VARIABLE_NAME && 
                added.find(ex->symbol()->identifier()) == added.end())
            {
                added.insert(ex->symbol()->identifier());
                local.push_back(new SgArrayRefExp(*ex->symbol()));
            }
        }

        findDecls(ex->lhs(), local, localParams, added);
        findDecls(ex->rhs(), local, localParams, added);
    }
}

static void findLocalData(SgStatement* start, SgStatement* end, vector<SgExpression*>& local, 
                          map<string, SgStatement*>& localParams, set<string>& added)
{
    for (SgStatement* st = start; st != end; st = st->lexNext())
    {
        if (st->variant() == PARAM_DECL)
        {
            auto decl = (SgParameterStmt*)st;
            for (int z = 0; z < decl->numberOfConstants(); ++z)
                localParams[decl->constant(z)->identifier()] = st;
        }

        if (st->variant() == EXTERN_STAT)
            for (SgExpression* ex = st->expr(0); ex; ex = ex->rhs())
                added.insert(ex->lhs()->symbol()->identifier());        
    }

    
    for (SgStatement* st = start; st != end; st = st->lexNext())
    {
        //printf("line %d %s Var %s\n", st->lineNumber(), st->fileName(), tag[st->variant()]);
        if (st->variant() == VAR_DECL || st->variant() == VAR_DECL_90)
            findDecls(st->expr(0), local, localParams, added);
    } 
}

static vector<SgStatement*> findUseOfModules(SgStatement* start, SgStatement* end)
{
    vector<SgStatement*> ret;

    for (SgStatement* st = start; st != end; st = st->lexNext())
    {
        if (st->variant() == USE_STMT)
            ret.push_back(st);
    }

    return ret;
}

static vector<string> findAllModules()
{
    vector<string> ret;

    const string old_file = current_file->filename();

    for (int z = 0; z < CurrentProject->numberOfFiles(); ++z)
    {
        SgFile* file = &CurrentProject->file(z);
        vector<SgStatement*> modules;
        findModulesInFile(file, modules);

        for (auto& elem : modules)
            ret.push_back(elem->symbol()->identifier());
    }

    if (SgFile::switchToFile(old_file) == -1)
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

    return ret;
}

void createCheckpoints(SgFile *file, const map<string, CommonBlock>& commonBlocks)
{
    const string fileCP = "total1_module.for";
    const int line = 8468;
    const int every = 300;
    const int numOfFiles = 3;
    const int unitNum = 789;
    const string additional = string("_") + to_string(current_file_id) + "_" + to_string(line);
    const typeEvery type = typeEvery::TIME;


    SgStatement* lastDecl = NULL;
    if (fileCP == file->filename())
    {
        set<string> commonVars;
        for (auto& common : commonBlocks)
        {
            for (auto& elem : common.second.getVariables())
            {
                if (elem.getType() != CONST)
                    commonVars.insert(elem.getName());
            }
        }
        int numF = file->numberOfFunctions();
        SgStatement* func = NULL;
        SgStatement* point = NULL;
        for (int z = 0; z < numF; ++z)
        {
            func = file->functions(z);
            point = func->lexNext();
            while (point && point->lineNumber() < line && point != func->lastNodeOfStmt() && point->variant() != CONTAINS_STMT)
                point = point->lexNext();

            if (point != func->lastNodeOfStmt())
                break;            
            point = NULL;
            func = NULL;
        }
        checkNull(func, convertFileName(__FILE__).c_str(), __LINE__);
        checkNull(point, convertFileName(__FILE__).c_str(), __LINE__);

        if (func)
        {
            const vector<string> moduleNames = findAllModules();

            lastDecl = func->lexNext();
            while (lastDecl && !isSgExecutableStatement(lastDecl->lexNext()))
                lastDecl = lastDecl->lexNext();

            checkNull(lastDecl, convertFileName(__FILE__).c_str(), __LINE__);

            vector<SgExpression*> local;
            map<string, SgStatement*> localParams;
            set<string> addedToList;
            findLocalData(func->lexNext(), lastDecl, local, localParams, addedToList);
            const vector<SgStatement*> useOfMods = findUseOfModules(func->lexNext(), lastDecl);

            SgStatement* loadBlock = new SgStatement(IF_NODE);
            SgStatement* loadBlockLast = NULL;
            SgStatement* storeBlock = new SgStatement(IF_NODE);

            point->insertStmtBefore(*loadBlock, *point->controlParent());            
            point->insertStmtBefore(*storeBlock, *point->controlParent());

            loadBlock->addComment("! LOAD CHECKPOINT\n");            

            auto arrayFilesType = new SgArrayType(*SgTypeChar());
            arrayFilesType->addDimension(new SgValueExp(numOfFiles + 1));

            auto lenght = new SgValueExp(32);
            arrayFilesType->baseType()->thetype->entry.Template.kind_len = lenght->thellnd;

            SgSymbol* files = new SgSymbol(VARIABLE_NAME, "spf_cp_files", arrayFilesType, func);
            vector<string> filesN;

            SgArrayRefExp* journal = new SgArrayRefExp(*files, *new SgValueExp(numOfFiles + 1));
            filesN.push_back("spf_cp_journal" + additional);
            lastDecl->insertStmtAfter(*new SgAssignStmt(*journal, *new SgValueExp(filesN.back().c_str())), *func);

            int maxFileLen = -1;
            for (int z = numOfFiles; z >= 1; --z)
            {
                filesN.push_back("spf_cp_file_" + to_string(z) + additional);
                maxFileLen = std::max(maxFileLen, (int)(filesN.back().size() + 1));
                lastDecl->insertStmtAfter(*new SgAssignStmt(*new SgArrayRefExp(*files, *new SgValueExp(z)), *new SgValueExp(filesN.back().c_str())), *func);
            }

            vector<SgSymbol*> everyS;
            vector<SgSymbol*> profS;
            vector<SgExpression*> initS;
            
            profS.push_back(new SgSymbol(VARIABLE_NAME, "spf_cp_prof_s", SgTypeFloat(), func));
            profS.push_back(new SgSymbol(VARIABLE_NAME, "spf_cp_prof_e", SgTypeFloat(), func));

            SgCallStmt* profCallS = new SgCallStmt(*new SgSymbol(FUNCTION_NAME, "cpu_time"), *new SgVarRefExp(profS[0]));
            SgCallStmt* profCallE = new SgCallStmt(*new SgSymbol(FUNCTION_NAME, "cpu_time"), *new SgVarRefExp(profS[1]));

            if (type == typeEvery::TIME)
            {
                everyS.push_back(new SgSymbol(VARIABLE_NAME, "spf_cp_start", SgTypeFloat(), func));
                everyS.push_back(new SgSymbol(VARIABLE_NAME, "spf_cp_end", SgTypeFloat(), func));

                initS.push_back(NULL);
                initS.push_back(NULL);

                SgCallStmt* call = new SgCallStmt(*new SgSymbol(FUNCTION_NAME, "cpu_time"), *new SgVarRefExp(everyS[0]));
                lastDecl->insertStmtAfter(*call, *func);
                storeBlock->insertStmtAfter(call->copy(), *storeBlock);

                call = new SgCallStmt(*new SgSymbol(FUNCTION_NAME, "cpu_time"), *new SgVarRefExp(everyS[1]));
                storeBlock->insertStmtBefore(*call, *storeBlock->controlParent());
                call->addComment("! STORE CHECKPOINT\n");

                storeBlock->setExpression(0, *new SgVarRefExp(everyS[1]) - *new SgVarRefExp(everyS[0]) >= *new SgValueExp(every));
            }
            else if (type == typeEvery::ITER)
            {
                everyS.push_back(new SgSymbol(VARIABLE_NAME, "spf_cp_interval", SgTypeInt(), func));
                initS.push_back(new SgValueExp(0));
                SgAssignStmt* init = new SgAssignStmt(*new SgVarRefExp(everyS[0]), *new SgValueExp(0));
                storeBlock->insertStmtAfter(*init, *storeBlock);

                SgAssignStmt* inc = new SgAssignStmt(*new SgVarRefExp(everyS[0]), *new SgVarRefExp(everyS[0]) + *new SgValueExp(1));
                storeBlock->insertStmtBefore(*inc, *storeBlock->controlParent());
                inc->addComment("! STORE CHECKPOINT\n");

                storeBlock->setExpression(0, *new SgVarRefExp(everyS[0]) != *new SgValueExp(every));
            }
            
            vector<SgSymbol*> loadS;
            vector<SgExpression*> initLoadS;
            vector<SgStatement*> insertToLoadS;

            loadS.push_back(new SgSymbol(VARIABLE_NAME, "spf_cp_load", SgTypeInt(), func));
            initLoadS.push_back(new SgValueExp(0));

            loadS.push_back(new SgSymbol(VARIABLE_NAME, "spf_cp_file_n", SgTypeInt(), func));
            initLoadS.push_back(new SgValueExp(1));

            loadS.push_back(new SgSymbol(VARIABLE_NAME, "spf_cp_iostat", SgTypeInt(), func));
            initLoadS.push_back(NULL);

            loadBlock->setExpression(0, *new SgVarRefExp(loadS[0]) == *new SgValueExp(0));
            SgAssignStmt* init = new SgAssignStmt(*new SgVarRefExp(loadS[0]), *new SgValueExp(1));
            insertToLoadS.push_back(init);

            vector<SgExpression*> listSpec;

            SgExpression& unitNull = SgAssignOp(*new SgKeywordValExp("unit"), *new SgKeywordValExp("*"));
            SgExpression& unit = SgAssignOp(*new SgKeywordValExp("unit"), *new SgValueExp(unitNum));
            SgExpression& frmt = SgAssignOp(*new SgKeywordValExp("fmt"), *new SgKeywordValExp("*"));
            SgExpression& frmtProf = SgAssignOp(*new SgKeywordValExp("fmt"), *new SgValueExp(("(A,A" + to_string(maxFileLen) + ",F4.2,A)").c_str()));

            SgExpression* iostat = new SgVarRefExp(loadS[2]);
            SgExpression* fileIdx = new SgVarRefExp(loadS[1]);
            
            listSpec.push_back(&SgAssignOp(*new SgKeywordValExp("iostat"), *iostat));
            listSpec.push_back(&SgAssignOp(*new SgKeywordValExp("status"), *new SgValueExp("old")));
            listSpec.push_back(&SgAssignOp(*new SgKeywordValExp("file"), *journal));
            listSpec.push_back(&unit);

            SgIOControlStmt* openJ_old = new SgIOControlStmt(OPEN_STAT, *makeExprList(listSpec));
            insertToLoadS.push_back(openJ_old);

            vector<SgStatement*> insertToifLoadOk;
            SgIfStmt* ifLoadOk = new SgIfStmt(*iostat == *new SgValueExp(0));
            insertToLoadS.push_back(ifLoadOk);

            SgInputOutputStmt* read = new SgInputOutputStmt(READ_STAT, *makeExprList({ &frmt, &unit }), *fileIdx);
            insertToifLoadOk.push_back(read);
            insertToifLoadOk.push_back(new SgIOControlStmt(CLOSE_STAT, unit));

            listSpec.clear();
            listSpec.push_back(&SgAssignOp(*new SgKeywordValExp("form"), *new SgValueExp("unformatted")));
            listSpec.push_back(&SgAssignOp(*new SgKeywordValExp("iostat"), *iostat));
            listSpec.push_back(&SgAssignOp(*new SgKeywordValExp("status"), *new SgValueExp("old")));
            listSpec.push_back(&SgAssignOp(*new SgKeywordValExp("file"), *new SgArrayRefExp(*files, *fileIdx)));
            listSpec.push_back(&unit);

            SgIOControlStmt* open = new SgIOControlStmt(OPEN_STAT, *makeExprList(listSpec));
            insertToifLoadOk.push_back(open);

            SgIfStmt* ifLoadOk1 = new SgIfStmt(*iostat == *new SgValueExp(0), *new SgIOControlStmt(CLOSE_STAT, unit));
            insertToifLoadOk.push_back(ifLoadOk1);
            ifLoadOk1->insertStmtAfter(*new SgIfStmt(*fileIdx == *new SgValueExp(numOfFiles + 1), *new SgAssignStmt(*fileIdx, *new SgValueExp(1))), *ifLoadOk1);
            ifLoadOk1->insertStmtAfter(*new SgAssignStmt(*fileIdx, *fileIdx + *new SgValueExp(1)), *ifLoadOk1);
            ifLoadOk1->addComment("! LOAD DATA FROM CHECKPOINT\n");
            
            vector<SgExpression*> commentArgs;
            commentArgs.push_back(new SgValueExp(" SECONDS"));
            commentArgs.push_back(&(*new SgVarRefExp(profS[1]) - *new SgVarRefExp(profS[0])));
            commentArgs.push_back(new SgArrayRefExp(*files, *fileIdx));
            commentArgs.push_back(new SgValueExp("SPF CHECKPOINT LOADED FROM "));

            ifLoadOk1->insertStmtAfter(*new SgInputOutputStmt(WRITE_STAT, *makeExprList({ &frmtProf, &unitNull }), *makeExprList(commentArgs)), *ifLoadOk1);
            ifLoadOk1->insertStmtAfter(profCallE->copy(), *ifLoadOk1);

            //READ from modules
            for (auto& mod : moduleNames)
            {
                SgCallStmt* call = new SgCallStmt(*new SgSymbol(FUNCTION_NAME, ("SPF_CP_" + mod).c_str()));
                call->addArg(*new SgValueExp(unitNum));
                call->addArg(*new SgValueExp(0));
                ifLoadOk1->insertStmtAfter(*call, *ifLoadOk1);
            }

            //READ DATA
            if (local.size())
            {
                auto dataRead = new SgInputOutputStmt(READ_STAT, unit, *makeExprList(local));
                ifLoadOk1->insertStmtAfter(*dataRead, *ifLoadOk1);
            }

            ifLoadOk1->insertStmtAfter(profCallS->copy(), *ifLoadOk1);

            listSpec.clear();
            listSpec.push_back(&SgAssignOp(*new SgKeywordValExp("form"), *new SgValueExp("unformatted")));
            listSpec.push_back(&SgAssignOp(*new SgKeywordValExp("iostat"), *iostat));
            listSpec.push_back(&SgAssignOp(*new SgKeywordValExp("file"), *new SgArrayRefExp(*files, *fileIdx)));
            listSpec.push_back(&unit);

            open = new SgIOControlStmt(OPEN_STAT, *makeExprList(listSpec));
            storeBlock->insertStmtAfter(*open, *storeBlock);

            SgIfStmt* ifLoadOk2 = new SgIfStmt(*iostat == *new SgValueExp(0));
            open->insertStmtAfter(*ifLoadOk2, *storeBlock);
            ifLoadOk2->insertStmtAfter(*new SgIfStmt(*fileIdx == *new SgValueExp(numOfFiles + 1), *new SgAssignStmt(*fileIdx, *new SgValueExp(1))), *ifLoadOk2);
            ifLoadOk2->insertStmtAfter(*new SgAssignStmt(*fileIdx, *fileIdx + *new SgValueExp(1)), *ifLoadOk2);
            ifLoadOk2->addComment(("! STORE DATA TO CHECKPOINT " + to_string(local.size()) + " items\n").c_str());

            commentArgs.clear();
            commentArgs.push_back(new SgValueExp(" SECONDS"));
            commentArgs.push_back(&(*new SgVarRefExp(profS[1]) - *new SgVarRefExp(profS[0])));
            commentArgs.push_back(new SgArrayRefExp(*files, *fileIdx));
            commentArgs.push_back(new SgValueExp("SPF CHECKPOINT STORED TO "));

            ifLoadOk2->insertStmtAfter(*new SgInputOutputStmt(WRITE_STAT, *makeExprList({ &frmtProf, &unitNull }), *makeExprList(commentArgs)), *ifLoadOk2);
            ifLoadOk2->insertStmtAfter(profCallE->copy(), *ifLoadOk2);

            SgStatement* assign = ifLoadOk2->lexNext();

            //WRITE from modules
            for (auto& mod : moduleNames)
            {
                SgCallStmt* call = new SgCallStmt(*new SgSymbol(FUNCTION_NAME, ("SPF_CP_" + mod).c_str()));
                call->addArg(*new SgValueExp(unitNum));
                call->addArg(*new SgValueExp(1));
                ifLoadOk2->insertStmtAfter(*call, *ifLoadOk2);
            }

            //WRITE DATA
            if (local.size())
            {
                SgStatement* dataWrite = new SgInputOutputStmt(WRITE_STAT, unit, *makeExprList(local));
                ifLoadOk2->insertStmtAfter(*dataWrite, *ifLoadOk2);
            }

            listSpec.clear();
            listSpec.push_back(&SgAssignOp(*new SgKeywordValExp("iostat"), *iostat));
            listSpec.push_back(&SgAssignOp(*new SgKeywordValExp("file"), *journal));
            listSpec.push_back(&unit);

            SgIOControlStmt* openJ_new = new SgIOControlStmt(OPEN_STAT, *makeExprList(listSpec));

            assign->insertStmtBefore(*new SgIOControlStmt(CLOSE_STAT, unit), *ifLoadOk2);
            assign->insertStmtBefore(*openJ_new, *ifLoadOk2);
            assign->insertStmtBefore(*new SgInputOutputStmt(WRITE_STAT, *makeExprList({ &frmt, &unit }), *fileIdx), *ifLoadOk2);            
            assign->insertStmtBefore(*new SgIOControlStmt(CLOSE_STAT, unit), *ifLoadOk2);

            ifLoadOk2->insertStmtAfter(profCallS->copy(), *ifLoadOk2);

            for (int z = insertToLoadS.size() - 1; z >= 0; --z)
                loadBlock->insertStmtAfter(*insertToLoadS[z], *loadBlock);

            for (int z = insertToifLoadOk.size() - 1; z >= 0; --z)
                ifLoadOk->insertStmtAfter(*insertToifLoadOk[z], *ifLoadOk);

            //TODO:
            /*set<string> elemNotDeclHere;
            for (auto& elem : commonVars)
            {
                if (addedToList.find(elem) == addedToList.end())
                    elemNotDeclHere.insert(elem);
            }
            for (auto& elem : elemNotDeclHere)
                printf("%s\n", elem.c_str());*/

            // make all new declarations
            makeDeclaration(point, everyS, &initS);
            makeDeclaration(point, loadS, &initLoadS);
            makeDeclaration(point, profS);
            makeDeclaration(point, { files });

            //check use
            map<string, bool> modulesDone;
            for (auto& elem : moduleNames)
                modulesDone[elem] = false;

            //check with ONLY
            for (auto& use : useOfMods)
            {
                const string modName = use->symbol()->identifier();
                if (!modulesDone[modName])
                {
                    if (use->expr(0)) // has ONLY
                    {
                        SgExpression* ex = use->expr(0);
                        if (ex && ex->variant() == ONLY_NODE)
                        {
                            modulesDone[modName] = true;
                            auto callName = new SgSymbol(VARIABLE_NAME, ("SPF_CP_" + modName).c_str());
                            ex->setLhs(new SgExpression(EXPR_LIST, new SgVarRefExp(callName), ex->lhs()));
                        }
                    }
                }
            }

            //check other
            for (auto& use : useOfMods)
            {
                const string modName = use->symbol()->identifier();
                if (!modulesDone[modName])
                    modulesDone[modName] = true;
            }

            for (auto& elem : modulesDone)
            {
                if (!elem.second)
                {
                    auto callName = new SgSymbol(VARIABLE_NAME, ("SPF_CP_" + elem.first).c_str());
                    SgSymbol* modS = new SgSymbol(VARIABLE_NAME, elem.first.c_str());
                    SgExpression* only = new SgExpression(ONLY_NODE, new SgExpression(EXPR_LIST, new SgVarRefExp(callName), NULL), NULL);
                    SgStatement* use = new SgStatement(USE_STMT, NULL, modS, only, NULL, NULL);
                    func->insertStmtAfter(*use, *func);
                }
            }
        }
    }
    
    //process modules
    vector<SgStatement*> modules;
    findModulesInFile(file, modules);
    for (auto& mod : modules)
    {
        bool hasContains = false;
        SgStatement* st = mod->lexNext();
        while (st != mod->lastNodeOfStmt() && !hasContains)
        {
            hasContains = st->variant() == CONTAINS_STMT;
            st = st->lexNext();
        }

        vector<SgExpression*> local;
        map<string, SgStatement*> localParams;
        set<string> addedToList;
        findLocalData(mod->lexNext(), hasContains ? st : mod->lastNodeOfStmt(), local, localParams, addedToList);

        SgProcHedrStmt* newF = new SgProcHedrStmt((string("spf_cp_") + mod->symbol()->identifier()).c_str());
        if (!hasContains)
            mod->lastNodeOfStmt()->insertStmtBefore(*new SgStatement(CONTAINS_STMT), *mod);
        mod->lastNodeOfStmt()->insertStmtBefore(*newF, *mod);

        newF->AddArg("unit_f", *SgTypeInt());
        newF->AddArg("type_of_op", *SgTypeInt());
        
        if (local.size())
        {
            SgExpression& unit = SgAssignOp(*new SgKeywordValExp("unit"), *new SgVarRefExp(*newF->parameter(0)));
            auto dataRead = new SgInputOutputStmt(READ_STAT, unit, *makeExprList(local));
            auto dataWrite = new SgInputOutputStmt(WRITE_STAT, unit, *makeExprList(local));

            SgIfStmt* ifBlock = new SgIfStmt(*new SgVarRefExp(*newF->parameter(1)) == *new SgValueExp(0), *dataRead, *dataWrite);
            newF->lastNodeOfStmt()->insertStmtBefore(*ifBlock, *newF);

            ifBlock->addComment(("!STORE OR LOAD " + to_string(local.size()) + " ITEMS\n").c_str());
        }
    }    
}

static string cuttingType(const string& all_decl_with_init)
{
    auto iter = all_decl_with_init.find("::");
    if (iter == string::npos)
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

    return all_decl_with_init.substr(0, iter);
}

static void createModule(SgStatement*& saveModule)
{
    if (saveModule == NULL)
    {
        saveModule = new SgStatement(MODULE_STMT, NULL, new SgSymbol(MODULE_NAME, (string("spf_module_save_") + to_string(current_file_id)).c_str()), NULL, NULL, NULL);
        addControlEndToStmt(saveModule->thebif);

        SgStatement* global = current_file->firstStatement();
        global->insertStmtAfter(*saveModule, *global);
    }

}

static SgExpression* moveSaveAssignToMod(SgExpression* ex, SgStatement*& saveModule, 
                                         map<string, SgStatement*>& declLists, const string& procName, bool withInit)
{
    if (saveModule == NULL)
        createModule(saveModule);

    if (withInit)
    {
        if (ex->variant() != ASSGN_OP)
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
    }
    else
    {
        if (ex->variant() != VAR_REF && ex->variant() != ARRAY_REF)
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
    }
    
    SgSymbol* copy = (withInit) ? &ex->lhs()->symbol()->copy() : &ex->symbol()->copy();
    copy->changeName((string(copy->identifier()) + "_" + procName).c_str());

    SgStatement* decl = NULL;
    if (withInit)
    {
        vector<SgExpression*> inits = { ex->rhs()->copyPtr() };
        decl = makeDeclaration(NULL, { ex->lhs()->symbol() }, &inits);
    }
    else
        decl = makeDeclaration(NULL, { ex->symbol() }, NULL);
    
    const string typeKey = cuttingType(decl->unparse());    
    if (withInit)
    {
        decl->expr(0)->lhs()->setLhs(withInit ? ex->lhs()->copyPtr() : ex->copyPtr());
        decl->expr(0)->lhs()->lhs()->setSymbol(copy);
    }
    else
        decl->expr(0)->lhs()->setSymbol(copy);

    auto it = declLists.find(typeKey);
    if (it == declLists.end())
    {
        declLists.insert(it, make_pair(typeKey, decl));
        saveModule->insertStmtAfter(*decl, *saveModule);
    }
    else
        it->second->setExpression(0, new SgExpression(EXPR_LIST, decl->expr(0)->lhs(), it->second->expr(0)));

    return new SgExpression(RENAME_NODE, new SgVarRefExp((withInit) ? ex->lhs()->symbol() : ex->symbol()), new SgVarRefExp(copy));
}

static string preprocDataString(const string& data)
{
    string ret = "";
    int i = 0; 
    while (i != data.size() && data[i] == ' ')
        ++i;
    while (i != data.size() && data[i] != ' ')
        ret += data[i++];
    while (i != data.size() && data[i] == ' ')
        ret += data[i++];

    while (i != data.size())
    {
        if (data[i] != ' ')
            ret += data[i++];
        else
            i++;
    }

    return ret;
}

void convertSaveToModule(SgFile* file)
{
    int numF = file->numberOfFunctions();
    SgStatement* saveModule = NULL;
    map<string, SgStatement*> declLists;

    for (int ff = 0; ff < numF; ++ff)
    {
        vector<SgExpression*> renames;

        SgStatement* func = file->functions(ff);
        
        string procName = file->functions(ff)->symbol()->identifier();
        set<SgStatement*> toRem;
        vector<SgValueExp*> dataValues;
        map<string, string> dataRenames;

        set<string> symbolsDone;

        vector<int> varsToProcess = { VAR_DECL_90 , DIM_STAT };
        for (int z = 0; z < 2; ++z)
        {
            SgStatement* st = func->lexNext();
            while (st && !isSgExecutableStatement(st))
            {
                if (st->variant() == SAVE_DECL)
                {
                    printf("save in %d %s\n", st->lineNumber(), st->fileName());
                    printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
                }

                if (st->variant() == DATA_DECL && z == 0)
                {
                    if (saveModule == NULL)
                        createModule(saveModule);

                    SgStatement* copyData = st->copyPtr();
                    dataValues.push_back((SgValueExp*)copyData->expr(0));
                    saveModule->lastNodeOfStmt()->insertStmtBefore(*copyData, *saveModule);
                    toRem.insert(st);
                }

                if (st->variant() == varsToProcess[z])
                {
                    SgExpression* list = st->expr(0);
                    vector<SgExpression*> newList;
                    bool changed = false;
                    while (list)
                    {
                        if (list->lhs()->variant() == ASSGN_OP)
                        {
                            changed = true;
                            if (symbolsDone.find(list->lhs()->lhs()->symbol()->identifier()) != symbolsDone.end())
                            {
                                list = list->rhs();
                                continue;
                            }
                            symbolsDone.insert(list->lhs()->lhs()->symbol()->identifier());
                            //printf("here %d %s - %s\n", st->lineNumber(), st->fileName(), list->lhs()->unparse());
                            renames.push_back(moveSaveAssignToMod(list->lhs(), saveModule, declLists, procName, true));
                        }
                        else
                        {
                            if (list->lhs()->symbol())
                            {
                                bool isInData = (list->lhs()->symbol()->attributes() & DATA_BIT) != 0;
                                if (isInData)
                                {
                                    changed = true;
                                    if (symbolsDone.find(list->lhs()->symbol()->identifier()) != symbolsDone.end())
                                    {
                                        list = list->rhs();
                                        continue;
                                    }
                                    symbolsDone.insert(list->lhs()->symbol()->identifier());

                                    renames.push_back(moveSaveAssignToMod(list->lhs(), saveModule, declLists, procName, false));
                                    string left = renames.back()->lhs()->symbol()->identifier();
                                    convertToUpper(left);
                                    string right = renames.back()->rhs()->symbol()->identifier();
                                    convertToUpper(right);
                                    dataRenames[left] = right;
                                }
                                else
                                    newList.push_back(list->lhs());
                            }
                            else
                                newList.push_back(list->lhs());
                        }
                        list = list->rhs();
                    }

                    if (newList.size() && changed)
                    {
                        reverse(newList.begin(), newList.end());
                        st->setExpression(0, makeExprList(newList));
                    }
                    else if (newList.size() == 0 && changed)
                        toRem.insert(st);
                }
                st = st->lexNext();
            }
        }

        for (auto& elem : toRem)
            elem->deleteStmt();

        if (renames.size())
        {
            SgSymbol* modS = new SgSymbol(VARIABLE_NAME, saveModule->symbol()->identifier());
            SgStatement* use = new SgStatement(USE_STMT, NULL, modS, makeExprList(renames), NULL, NULL);
            func->insertStmtAfter(*use, *func);
            
            for (auto& dataV : dataValues)
            {
                char* value = dataV->thellnd->entry.string_val;
                string dataS(value);
                convertToUpper(dataS);
                dataS = preprocDataString(dataS);

                for (auto& elem : dataRenames)
                {
                    auto it = dataS.find(elem.first);
                    if (it != string::npos && 
                        (dataS[it + elem.first.size()] == ' ' || dataS[it + elem.first.size()] == '/') &&
                        (dataS[it - 1] == ',' || dataS[it - 1] == ' ' || dataS[it - 1] == '/'))
                    {
                        dataS = dataS.substr(0, it) + elem.second + dataS.substr(it + elem.first.size());
                    }
                }

                value = (char*)malloc(dataS.size() + 1);
                value[dataS.size()] = '\0';
                memcpy(value, dataS.c_str(), sizeof(char) * dataS.size());
                dataV->thellnd->entry.string_val = value;
            }
        }
    }

    printf("");
}