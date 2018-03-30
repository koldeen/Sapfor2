#pragma once

#include "dvm.h"
#include "utils.h"
#include "Distribution/Distribution.h"

void removeIncludeStatsAndUnparse(SgFile *file, const char *fileName, const char *fout, std::set<std::string> &allIncludeFiles);
SgSymbol* findSymbolOrCreate(SgFile *file, const std::string toFind);
void recExpressionPrint(SgExpression *exp);
void removeSubstrFromStr(std::string &str, const std::string &del);
void getModulesAndFunctions(SgFile *file, std::vector<SgStatement*> &modulesAndFunctions);
void findModulesInFile(SgFile *file, std::vector<SgStatement*> &modules);
void tryToFindPrivateInAttributes(SgStatement *st, std::set<std::string> &privatesVars);

void fillNonDistrArraysAsPrivate(SgStatement *st,
                                 const std::map<std::tuple<int, std::string, std::string>, std::pair<DIST::Array*, DIST::ArrayAccessInfo*>> &declaratedArrays,
                                 const std::map<SgStatement*, std::set<std::tuple<int, std::string, std::string>>> &declaratedArraysSt,
                                 std::set<std::string> &privatesVars);

SgStatement* declaratedInStmt(SgSymbol *toFind);
bool isSPF_comment(SgStatement *st);
void initTags();
bool isDVM_stat(SgStatement *st);
bool isSPF_stat(SgStatement *st);
bool isEqExpressions(SgExpression *left, SgExpression *right, std::map<SgExpression*, std::string> &collection);
void getCommonBlocksRef(std::map<std::string, std::vector<SgExpression*>> &commonBlocks, SgStatement *start, SgStatement *end);

extern std::map<std::pair<std::string, int>, std::tuple<int, std::string, std::string>> tableOfUniqNames;
std::tuple<int, std::string, std::string> getUniqName(const std::map<std::string, std::vector<SgExpression*>> &commonBlocks, SgStatement *decl, SgSymbol *symb);
SgStatement* findMainUnit(SgProject *proj);

template<typename IN_TYPE, typename OUT_TYPE>
const std::vector<OUT_TYPE> getAttributes(IN_TYPE st, const std::set<int> dataType);

struct DefUseList
{
private:
    int type; // def(0) or use(1)
    SgStatement *place;
    SgFile *file;
    std::pair<SgSymbol*, std::string> paramOfFunction;
    int parameterPosition;
    std::pair<SgSymbol*, std::string> varName;

public:
    DefUseList()
    {

    }

    explicit DefUseList(int type, SgStatement *place, SgFile *file,
        std::pair<SgSymbol*, std::string> &inFuncParam,
        std::pair<SgSymbol*, std::string> &varName, 
        const int parameterPosition) :
        type(type), place(place), file(file), paramOfFunction(inFuncParam), varName(varName), parameterPosition(parameterPosition)
    {

    }

    bool isDef() const { return type == 0; }
    bool isUse() const { return type == 1; }
    std::string getVar() const { return varName.second; }
    SgSymbol* getVarS() const { return varName.first; }
    SgFile* getFile() const { return file; }
    SgStatement* getPlace() const { return place; }
    std::string getParamOfFunction() const { return paramOfFunction.second; }
    SgSymbol* getParamOfFunctionS() const { return paramOfFunction.first; }
    int getParameterPosition() const { return parameterPosition; }

    void print() const
    {
        printf("%s: [file: %s line: %d], var '%s' ", (type == 0) ? "DEF" : "USE", file->filename(), place->lineNumber(), varName.second.c_str());
        if (parameterPosition != -1)
            printf(" under call of '%s' function on %d position of args", paramOfFunction.second.c_str(), parameterPosition);
        printf("\n");
    }
};

enum varType
{
    scalar,
    array,
    other
};

struct Variable
{
private:
    SgFile *file;
    SgStatement *function;
    SgSymbol *symbol;
    std::string name;
    varType type;
public:
    explicit Variable(SgFile *file, SgStatement *function, SgSymbol *symbol, std::string &name, varType &type) :
        file(file), function(function), symbol(symbol), name(name), type(type)
    {

    }

    SgFile* getFile() const { return file; }
    SgStatement* getFunction() const { return function; }
    SgSymbol* getSymbol() const { return symbol; }
    const std::string & getName() const { return name; }
    const varType & getType() const { return type; }
};

struct CommonBlock
{
private:
    std::string name;
    std::map<std::pair<SgFile*, SgStatement*>, std::vector<SgSymbol*>> detailVariables; // file, func -> vars
    std::map<std::pair<std::string, std::string>, std::vector<std::pair<std::string, varType>>> variables; // fileName, funcName -> vars

public:
    explicit CommonBlock(std::string &name,
        std::map<std::pair<SgFile*, SgStatement*>, std::vector<SgSymbol*>> &detailVariables,
        std::map<std::pair<std::string, std::string>, std::vector<std::pair<std::string, varType>>> &variables) :
        name(name), detailVariables(detailVariables), variables(variables)
    {

    }

    const std::string & getName() const { return name; }
    const std::map<std::pair<SgFile*, SgStatement*>, std::vector<SgSymbol*>> & getDetailVariables() const { return detailVariables; }
    const std::map<std::pair<std::string, std::string>, std::vector<std::pair<std::string, varType>>> & getVariables() const { return variables; }

    void addVariables(SgFile *file, SgStatement *func, std::vector<SgSymbol*> &newVariables)
    {
        auto pair = std::make_pair(file, func);
        auto pairr = std::make_pair(std::string(file->filename()), std::string(func->symbol()->identifier()));
        auto it = detailVariables.find(pair);
        auto itt = variables.find(pairr);

        if (it == detailVariables.end())
        {
            it = detailVariables.insert(it, std::make_pair(pair, std::vector<SgSymbol*>()));
            itt = variables.insert(itt, std::make_pair(pairr, std::vector<std::pair<std::string, varType>>()));
        }

        for (auto &variable : newVariables)
        {
            varType type = variable->variant() == VAR_REF ? scalar : variable->variant() == ARRAY_REF ? array : other;
            it->second.push_back(variable);
            itt->second.push_back(std::make_pair(variable->identifier(), type));
        }
    }
};

void constructDefUseStep1(SgFile *file, std::map<std::string, std::vector<DefUseList>> &defUseByFunctions);
std::set<std::string> getAllDefVars(const std::string &funcName);
std::set<std::string> getAllUseVars(const std::string &funcName);
const std::vector<DefUseList>& getAllDefUseVarsList(const std::string &funcName);
const std::vector<DefUseList> getAllDefUseVarsList(const std::string &funcName, const std::string varName);