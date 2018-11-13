#pragma once

enum varType { SCALAR, ARRAY, CONST, ANOTHER };

struct CommonVariableUse
{
private:
    std::string fileName;
    std::string functionName;
    SgSymbol *useS;

    SgFile *file;
    SgStatement *function;
    bool isBlockData;
public:
    explicit CommonVariableUse(SgFile *file, SgStatement *function, SgSymbol *useS) :
        file(file), function(function), useS(useS),
        fileName(std::string(file->filename())), functionName(std::string(function->symbol()->identifier()))
    {
        if (function->variant() == BLOCK_DATA)
            isBlockData = true;
        else
            isBlockData = false;
    }

    const std::string& getFileName() const { return fileName; }
    const std::string& getFunctionName() const { return functionName; }
    bool isBlockDataUse() const { return isBlockData; }
    SgFile* getFile() const { return file; }
    SgStatement* getFunction() const { return function; }
    SgStatement* getDeclaratedPlace() const 
    {
        if (current_file->filename() != fileName)
            SgFile::switchToFile(fileName);
        return useS->declaredInStmt(); 
    }
};

struct Variable
{
private:
    std::vector<CommonVariableUse> allUse;
    SgSymbol *symbol; // variable symbol
    SgStatement *declPace;

    std::string name; // variable name
    varType type;     // variable type
    int position;
public:
    explicit Variable(SgFile *file, SgStatement *function, SgSymbol *symbol, const std::string &name, const varType type, const int position) :
        symbol(symbol), name(name), type(type), position(position)
    {
        declPace = declaratedInStmt(symbol);
        allUse.push_back(CommonVariableUse(file, function, symbol));
    }

    SgSymbol* getSymbol() const { return symbol; }
    const std::vector<CommonVariableUse>& getAllUse() const { return allUse; }
    const std::string& getName() const { return name; }
    varType getType() const { return type; }
    int getPosition() const { return position; }
    SgStatement *getDeclarated() const { return declPace; }

    void addUse(SgFile *file, SgStatement *function, SgSymbol *useS)
    {
        for (auto &use : allUse)
            if (use.getFile() == file && use.getFunction() == function)
                return;

        allUse.push_back(CommonVariableUse(file, function, useS));
    }

    bool hasUse(const std::string &file, const std::string &function) const
    {
        for (auto &use : allUse)
            if (use.getFileName() == file && use.getFunctionName() == function)
                return true;

        return false;
    }

    void print(FILE *fileOut) const
    {
        fprintf(fileOut, "  %3d, '%s', %s\n", position, name.c_str(), type == SCALAR ? "SCALAR" : type == ARRAY ? "ARRAY" : "ANOTHER");
    }
};

struct CommonBlock
{
private:
    std::string name;
    std::vector<Variable> variables;

    // position -> variables
    std::map<int, std::vector<Variable>> groupedVars;

    Variable* hasVariable(const std::string &name, const varType type, const int position);
    Variable* hasVariable(SgSymbol *symbol, const varType type, const int position);
public:
    explicit CommonBlock(const std::string &name, const std::vector<Variable> &variables) :
        name(name), variables(variables)
    {
        for (auto &var : variables)
        {
            auto it = groupedVars.find(var.getPosition());
            if (it == groupedVars.end())
                it = groupedVars.insert(it, make_pair(var.getPosition(), std::vector<Variable>()));

            it->second.push_back(var);
        }
    }

    const std::string& getName() const { return name; }
    const std::vector<Variable>& getVariables() const { return variables; }
    const std::map<int, std::vector<Variable>>& getGroupedVars() const { return groupedVars; };

    const std::vector<const Variable*> getVariables(SgFile *file, SgStatement *function) const;
    const std::vector<const Variable*> getVariables(const std::string &file, const std::string &function) const;
    const std::vector<const Variable*> getVariables(int position) const;

    void addVariables(SgFile *file, SgStatement *function, const std::vector<std::pair<SgSymbol*, int>> &newVariables);
    void print(FILE *fileOut) const;
};
