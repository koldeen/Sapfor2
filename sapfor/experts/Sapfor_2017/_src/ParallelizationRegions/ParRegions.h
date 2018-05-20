#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include <map>

#include "../Distribution/DvmhDirective.h"
#include "../Distribution/GraphCSR.h"
#include "../Distribution/Distribution.h"
#include "../AstWrapper.h"

#include "../SgUtils.h"

struct ParallelRegionLines
{
    ParallelRegionLines() 
    {
        lines = std::make_pair(-1, -1);
        stats = std::make_pair<Statement*, Statement*>(NULL, NULL);
    }

    ParallelRegionLines(const std::pair<int, int> &lines) : lines(lines) 
    {
        stats = std::make_pair<Statement*, Statement*>(NULL, NULL);
    }

    ParallelRegionLines(const std::pair<int, int> &lines, const std::pair<Statement*, Statement*> stats) : lines(lines), stats(stats) { }

    bool operator==(const ParallelRegionLines &regionLines) const { return lines == regionLines.lines && stats == regionLines.stats; }

    void print(FILE *fileOut)
    {
        fprintf(fileOut, " [%d -- %d]", lines.first, lines.second);
        if (stats.first && stats.second)
            fprintf(fileOut, " explicit\n");
        else
            fprintf(fileOut, "\n");
    }

    // <start, end> lines
    std::pair<int, int> lines;
    // <start, end> stats
    std::pair<Statement*, Statement*> stats;
};

struct ParallelRegionArray
{
private:
    std::string name;
    SgSymbol *origSymbol;
    SgSymbol *copySymbol;
    std::vector<SgStatement*> declStatements;
    std::vector<ParallelRegionLines> allLines;
public:
    explicit ParallelRegionArray(const std::string &name, SgSymbol *origSymbol, SgSymbol *copySymbol, std::vector<SgStatement*> &declStatements,
                                 const ParallelRegionLines &lines) :
        name(name), origSymbol(origSymbol), copySymbol(copySymbol), declStatements(declStatements)
    {
        allLines.push_back(lines);
    }

    const std::string& getName() const { return name; }
    SgSymbol* getOrigSymbol() const { return origSymbol; }
    SgSymbol* getCopySymbol() const { return copySymbol; }
    const std::vector<SgStatement*>& getDeclStatements() const { return declStatements; }
    const std::vector<ParallelRegionLines>& getAllLines() const { return allLines; }

    void addLines(const ParallelRegionLines &newLines)
    {
        for (auto &lines : allLines)
            if (lines == newLines)
                return;

        allLines.push_back(newLines);
    }

    void setCopySymbol(SgSymbol *copySymbol) { this->copySymbol = copySymbol; }
};

struct ParallelRegion
{
public:
    ParallelRegion(const int regionId, const std::string &originalName) : regionId(regionId), originalName(originalName) { }

    ParallelRegion(const ParallelRegion &copy) : allArrays(copy.allArrays), G(copy.G), reducedG(copy.reducedG), dataDirectives(copy.dataDirectives)
    {
        regionId = copy.regionId;
        originalName = copy.originalName;
        lines = copy.lines;
        functionsCall = copy.functionsCall;
        currentVariant = copy.currentVariant;
    }

    int AddLines(const std::pair<int, int> &linesToAdd, const std::string &file, const std::pair<Statement*, Statement*> *startEnd = NULL)
    {
        if (linesToAdd.first > linesToAdd.second)
            return -1;

        auto it = lines.find(file);
        if (it == lines.end())
            it = lines.insert(it, make_pair(file, std::vector<ParallelRegionLines>()));

        if (startEnd)
            it->second.push_back(ParallelRegionLines(linesToAdd, *startEnd));
        else
            it->second.push_back(ParallelRegionLines(linesToAdd));

        return 0;
    }

    void AddFuncCalls(const std::string &func)
    {
        functionsCall.insert(func);
        allFunctionsCall.insert(func);
    }

    void AddAllFuncCalls(const std::string &func) { allFunctionsCall.insert(func); }

    void AddCrossedFunc(const std::string &func) { crossedFunctions.insert(func); }

    int GetId() const { return regionId; }
    const std::string& GetName() const { return originalName; }
    const std::map<std::string, std::vector<ParallelRegionLines>>& GetAllLines() const { return lines; }
    const std::vector<ParallelRegionLines>* GetLines(const std::string &file) const 
    {
        auto it = lines.find(file);
        if (it == lines.end())
            return NULL;
        else
            return &(it->second);
    }

    const DIST::GraphCSR<int, double, attrType>& GetGraph() { return G; }
    DIST::GraphCSR<int, double, attrType>& GetGraphToModify() { return G; }

    const DIST::GraphCSR<int, double, attrType>& GetReducedGraph() { return reducedG; }
    DIST::GraphCSR<int, double, attrType>& GetReducedGraphToModify() { return reducedG; }

    const DIST::Arrays<int>& GetAllArrays() { return allArrays; }
    DIST::Arrays<int>& GetAllArraysToModify() { return allArrays; }

    void SetCurrentVariant(const std::vector<int> &newVariant) { currentVariant = newVariant; }
    const std::vector<int>& GetCurrentVariant() const { return currentVariant; }

    const DataDirective& GetDataDir() const { return dataDirectives; }
    DataDirective& GetDataDirToModify() { return dataDirectives; }

    const std::set<std::string>& GetFuncCalls() const { return functionsCall; }

    const std::set<std::string>& GetAllFuncCalls() const { return allFunctionsCall; }

    const std::set<std::string>& GetCrossedFuncs() const { return crossedFunctions; }

    const std::map<std::string, std::set<std::string>>& GetUsedLocalArrays() const { return usedLocalArrays; }

    const std::map<std::string, std::map<std::string, ParallelRegionArray>>& GetLocalArrays() const { return localArrays; }

    const std::set<std::string>& GetUsedCommonArrays() const { return usedCommonArrays; }

    const std::map<std::string, ParallelRegionArray>& GetCommonArrays() const { return commonArrays; }

    const std::map<std::string, std::vector<std::pair<SgSymbol*, SgSymbol*>>>& GetReplacedSymbols() const { return replacedSymbols; }

    void AddUsedLocalArray(const std::string &functionName, const std::string &arrayName)
    {
        auto it = usedLocalArrays.find(functionName);
        if (it == usedLocalArrays.end())
            it = usedLocalArrays.insert(it, make_pair(functionName, std::set<std::string>()));

        it->second.insert(arrayName);
    }

    void AddLocalArray(const std::string &functionName,
                       const std::string &arrayName, SgSymbol *origSymbol, SgSymbol *copySymbol, const ParallelRegionLines &lines)
    {
        auto it = localArrays.find(functionName);
        if (it == localArrays.end())
            it = localArrays.insert(it, std::make_pair(functionName, std::map<std::string, ParallelRegionArray>()));

        auto itt = it->second.find(arrayName);
        if (itt == it->second.end())
        {
            std::vector<SgStatement*> declStatemets;
            declaratedInStmt(origSymbol, &declStatemets);
            itt = it->second.insert(itt, std::make_pair(arrayName, ParallelRegionArray(arrayName, origSymbol, copySymbol, declStatemets, lines)));
            return;
        }

        itt->second.addLines(lines);
    }

    void AddUsedCommonArray(const std::string &arrayName) { usedCommonArrays.insert(arrayName); }

    void AddCommonArray(const std::string &arrayName, SgSymbol *origSymbol, SgSymbol *copySymbol, const ParallelRegionLines &lines)
    {
        auto it = commonArrays.find(arrayName);
        if (it != commonArrays.end())
        {
            it->second.addLines(lines);
            return;
        }

        std::vector<SgStatement*> declStatemets;
        declaratedInStmt(origSymbol, &declStatemets);
        commonArrays.insert(it, std::make_pair(arrayName, ParallelRegionArray(arrayName, origSymbol, copySymbol, declStatemets, lines)));
    }

    void AddReplacedSymbols(const std::string &functionName, SgSymbol *origin, SgSymbol *copy)
    {
        auto it = replacedSymbols.find(functionName);
        if (it == replacedSymbols.end())
            it = replacedSymbols.insert(it, std::make_pair(functionName, std::vector<std::pair<SgSymbol*, SgSymbol*>>()));

        it->second.push_back(std::make_pair(origin, copy));
    }

    bool HasThisLine(const int line, const std::string &file) const
    {
        bool retVal = false;
        auto it = lines.find(file);
        if (it != lines.end())
        {
            for (int i = 0; i < it->second.size(); ++i)
            {
                if (it->second[i].lines.first <= line && it->second[i].lines.second >= line)
                {
                    retVal = true;
                    break;
                }
            }
        }

        return retVal;
    }

    std::string toString()
    {
        std::string retVal = "";

        retVal += " " + std::to_string(regionId);
        retVal += " " + originalName;
        retVal += " " + std::to_string(lines.size());

        for (auto it = lines.begin(); it != lines.end(); ++it)
        {
            retVal += "|" + it->first + "|";
            retVal += std::to_string(it->second.size());
            for (int i = 0; i < it->second.size(); ++i)
                retVal += " " + std::to_string(it->second[i].lines.first) + " " + std::to_string(it->second[i].lines.second);
        }

        const std::set<DIST::Array*> &arrays = allArrays.GetArrays();
        retVal += " " + std::to_string(arrays.size());

        //create map<array_address, DIST::Array_toString()> 
        for (auto it = arrays.begin(); it != arrays.end(); ++it)
        {
            retVal += " " + std::to_string((long long)(*it));
            retVal += " " + (*it)->toString();
        }

        retVal += " " + std::to_string(dataDirectives.alignRules.size());
        for (int i = 0; i < dataDirectives.alignRules.size(); ++i)
            retVal += dataDirectives.alignRules[i].toString();

        return retVal;
    }

    void CleanData()
    {
        reducedG.cleanData();
        currentVariant.clear();

        dataDirectives.distrRules.clear();
        dataDirectives.alignRules.clear();
    }

    void print(FILE *fileOut)
    {
        fprintf(fileOut, "  regionId %d\n", regionId);
        fprintf(fileOut, "  originalName '%s'\n", originalName.c_str());
        fprintf(fileOut, "  functions call from %d:\n", (int)functionsCall.size());
        for (auto &func : functionsCall)
            fprintf(fileOut, "    '%s'\n", func.c_str());
        fprintf(fileOut, "  total lines %d:\n", (int)lines.size());
        for (auto &line : lines)
        {
            fprintf(fileOut, "    in file '%s':\n", line.first.c_str());
            for (auto &elem : line.second)
            {
                fprintf(fileOut, "     ");
                elem.print(fileOut);
            }
        }
    }

    void AddUserDirectives(const std::vector<Statement*> &dirs, const int type)
    {
        if (dirs.size() == 0)
            return;

        if (type == DVM_DISTRIBUTE_DIR)
            userDvmDistrDirs.insert(userDvmDistrDirs.end(), dirs.begin(), dirs.end());
        else if (type == DVM_ALIGN_DIR)
            userDvmAlignDirs.insert(userDvmAlignDirs.end(), dirs.begin(), dirs.end());
        else if (type == DVM_SHADOW_DIR)
            userDvmShadowDirs.insert(userDvmShadowDirs.end(), dirs.begin(), dirs.end());
        else if (type == DVM_REALIGN_DIR)
            userDvmRealignDirs.insert(userDvmRealignDirs.end(), dirs.begin(), dirs.end());
        else if (type == DVM_REDISTRIBUTE_DIR)
            userDvmRedistrDirs.insert(userDvmRedistrDirs.end(), dirs.begin(), dirs.end());
    }

    const std::vector<Statement*>* GetUsersDirecites(const int type) const
    {
        if (type == DVM_DISTRIBUTE_DIR)
            return &userDvmDistrDirs;
        else if (type == DVM_ALIGN_DIR)
            return &userDvmAlignDirs;
        else if (type == DVM_SHADOW_DIR)
            return &userDvmShadowDirs;
        else if (type == DVM_REALIGN_DIR)
            return &userDvmRealignDirs;
        else if (type == DVM_REDISTRIBUTE_DIR)
            return &userDvmRedistrDirs;
        else
            return NULL;
    }

    bool HasUserDvmDirs() const 
    {
        return userDvmDistrDirs.size()   != 0 ||
               userDvmAlignDirs.size()   != 0 ||
               userDvmShadowDirs.size()  != 0 ||
               userDvmRealignDirs.size() != 0 ||
               userDvmRedistrDirs.size() != 0;
    }

private:
    int regionId;
    //name in program
    std::string originalName;
    // file -> lines info
    std::map<std::string, std::vector<ParallelRegionLines>> lines;
    std::set<std::string> functionsCall;

    // for RESOLVE_PAR_REGIONS
    std::set<std::string> allFunctionsCall;
    std::set<std::string> usedCommonArrays;
    std::map<std::string, std::set<std::string>> usedLocalArrays; // func name -> array names
    std::set<std::string> crossedFunctions;
    std::map<std::string, std::vector<std::pair<SgSymbol*, SgSymbol*>>> replacedSymbols; // func name -> (origin symbol, new symbol)

    std::map<std::string, ParallelRegionArray> commonArrays; // array name -> array
    std::map<std::string, std::map<std::string, ParallelRegionArray>> localArrays; // func -> array name -> array
    //

    // for LOOP_ANALYZER_DATA_DIST
    DIST::GraphCSR<int, double, attrType> G;
    DIST::Arrays<int> allArrays;

    DIST::GraphCSR<int, double, attrType> reducedG;
    //

    //for directive creating
    DataDirective dataDirectives;
    std::vector<int> currentVariant;
    //

    std::vector<Statement*> userDvmDistrDirs;
    std::vector<Statement*> userDvmAlignDirs;
    std::vector<Statement*> userDvmShadowDirs;
    std::vector<Statement*> userDvmRealignDirs;
    std::vector<Statement*> userDvmRedistrDirs;
};
