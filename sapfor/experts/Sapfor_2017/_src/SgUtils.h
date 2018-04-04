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
    int parameterPositionInFunction;

public:
    explicit DefUseList(int type, SgStatement *place, SgFile *file,
        const std::pair<SgSymbol*, std::string> &inFuncParam,
        const std::pair<SgSymbol*, std::string> &varName, 
        const int parameterPosition, const int paramenterPostionInFunction) :
        type(type), place(place), file(file), paramOfFunction(inFuncParam), varName(varName), parameterPosition(parameterPosition), parameterPositionInFunction(paramenterPostionInFunction)
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
    int getParameterPositionInFunction() const { return parameterPositionInFunction; }

    void print(FILE *fileOut = NULL, const bool onlyPositiveLine = false) const
    {
        if (onlyPositiveLine && place->lineNumber() < 0)
            return;
        if (fileOut == NULL)
        {            
            printf("%s: [file: %s, line: %d], '%s' ", (type == 0) ? "DEF" : "USE", file->filename(), place->lineNumber(), varName.second.c_str());
            if (parameterPosition != -1)
                printf(" under call of '%s' function on %d position of args (alt pos %d)", paramOfFunction.second.c_str(), parameterPosition, parameterPositionInFunction);
            printf("\n");
        }
        else
        {
            fprintf(fileOut, "%s: [file: %s, line: %d], '%s' ", (type == 0) ? "DEF" : "USE", file->filename(), place->lineNumber(), varName.second.c_str());
            if (parameterPosition != -1)
                fprintf(fileOut, " under call of '%s' function on %d position of args (alt pos %d)", paramOfFunction.second.c_str(), parameterPosition, parameterPositionInFunction);
            fprintf(fileOut, "\n");
        }

    }
};

enum varType { SCALAR, ARRAY, ANOTHER };

struct Variable
{
private:
    SgFile *file;
    SgStatement *function;
    SgSymbol *symbol; // variable symbol
    std::string fileName;
    std::string functionName;
    std::string name; // variable name
    varType type;     // variable type
public:
    explicit Variable(SgFile *file, SgStatement *function, SgSymbol *symbol, const std::string &name, const varType type) :
        file(file), function(function), symbol(symbol), name(name), type(type),
        fileName(std::string(file->filename())), functionName(std::string(function->symbol()->identifier()))
    {

    }

    SgFile* getFile() const { return file; }
    SgStatement* getFunction() const { return function; }
    SgSymbol* getSymbol() const { return symbol; }
    const std::string& getFileName() const { return fileName; }
    const std::string& getFunctionName() const { return functionName; }
    const std::string& getName() const { return name; }
    const varType getType() const { return type; }
};

struct CommonBlock
{
private:
    std::string name;
    std::vector<Variable> variables;

public:
    explicit CommonBlock(const std::string &name,
        const std::vector<Variable> &variables) :
        name(name), variables(variables)
    {

    }

    const std::string& getName() const { return name; }
    const std::vector<Variable>& getVariables() const { return variables; }

    bool fitFileAndFunction(SgFile *file, SgStatement *function, const Variable &variable) const
    {
        return variable.getFile() == file && variable.getFunction() == function;
    }
    bool fitFileAndFunction(std::string *fileName, std::string *functionName, const Variable &variable) const
    {
        return variable.getFileName() == *fileName && variable.getFunctionName() == *functionName;
    }

    template<typename fileType, typename functionType>
    const std::vector<Variable> getVariables(fileType *file, functionType *function) const
    {
        std::vector<Variable> mappedVariables;

        for (auto &variable : variables)
            if (fitFileAndFunction(file, function, variable))
                mappedVariables.push_back(variable);

        return mappedVariables;
    }

    void addVariables(SgFile *file, SgStatement *function, const std::vector<SgSymbol*> &newVariables)
    {
        for (auto &varSymbol : newVariables)
        {
            varType type = ANOTHER;
            SgStatement *declStatement = declaratedInStmt(varSymbol);
            for (SgExpression *exp = declStatement->expr(0); exp; exp = exp->rhs())
            {
                if (exp->lhs()->symbol() == varSymbol)
                {
                    switch (exp->lhs()->variant())
                    {
                    case VAR_REF:
                        type = SCALAR;
                        break;
                    case ARRAY_REF:
                        type = ARRAY;
                        break;
                    }
                }
            }

            Variable variable(file, function, varSymbol, std::string(varSymbol->identifier()), type);
            variables.push_back(variable);
        }
    }
};

void constructDefUseStep1(SgFile *file, std::map<std::string, std::vector<DefUseList>> &defUseByFunctions);
void constructDefUseStep2(SgFile *file, std::map<std::string, std::vector<DefUseList>> &defUseByFunctions);
std::set<std::string> getAllDefVars(const std::string &funcName);
std::set<std::string> getAllUseVars(const std::string &funcName);
const std::vector<DefUseList>& getAllDefUseVarsList(const std::string &funcName);
const std::vector<DefUseList> getAllDefUseVarsList(const std::string &funcName, const std::string varName);
int printDefUseSets(const char *fileName, const std::map<std::string, std::vector<DefUseList>> &defUseLists);
int printCommonBlocks(const char *fileName, const std::map<std::string, CommonBlock> &commonBlocks);
