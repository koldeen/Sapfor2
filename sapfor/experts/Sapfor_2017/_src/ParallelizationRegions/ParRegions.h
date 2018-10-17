#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include <map>

#include "../Distribution/DvmhDirective.h"
#include "../Distribution/GraphCSR.h"
#include "../Distribution/Distribution.h"
#include "../Utils/AstWrapper.h"

#if __SPF
#include "../Utils/SgUtils.h"
#endif

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
    bool operator<(const ParallelRegionLines &otherLines) const { return lines.first < otherLines.lines.first; }

    void print(FILE *fileOut)
    {
        fprintf(fileOut, " [%d -- %d]", lines.first, lines.second);
        if (stats.first && stats.second)
            fprintf(fileOut, " explicit\n");
        else
            fprintf(fileOut, "\n");
    }

    bool isImplicit() const { return stats.first == NULL || stats.second == NULL; }

    // <start, end> lines
    std::pair<int, int> lines;
    // <start, end> stats
    std::pair<Statement*, Statement*> stats;
};

#if __SPF
struct ParallelRegionArray
{
private:
    std::string name;
    std::string fileName;
    SgSymbol *origSymbol;
    SgSymbol *copySymbol;
    std::vector<SgStatement*> declStatements;
    std::vector<ParallelRegionLines> allLines;
public:
    explicit ParallelRegionArray(const std::string &name, const std::string &fileName, SgSymbol *origSymbol, SgSymbol *copySymbol,
                                 const ParallelRegionLines &lines, std::vector<SgStatement*> &declStatements) :
                                 name(name), fileName(fileName), origSymbol(origSymbol), copySymbol(copySymbol), declStatements(declStatements)
    {
        allLines.push_back(lines);
    }

    const std::string& getName() const { return name; }
    const std::string& getFileName() const { return fileName; }
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
#endif

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

    void AddFuncCalls(const std::string &func) { functionsCall.insert(func); }

#if __SPF
    void AddAllFuncCalls(FuncInfo *func) { allFunctionsCall.insert(func); }
    void AddCrossedFunc(FuncInfo *func) { crossedFunctions.insert(func); }
#endif

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

#if __SPF
    const std::set<FuncInfo*>& GetAllFuncCalls() const { return allFunctionsCall; }
    const std::set<FuncInfo*>& GetCrossedFuncs() const { return crossedFunctions; }
    const std::map<FuncInfo*, std::map<DIST::Array*, std::vector<ParallelRegionLines>>>& GetUsedLocalArrays() const { return usedLocalArrays; }
    const std::map<FuncInfo*, std::map<DIST::Array*, std::vector<ParallelRegionLines>>>& GetUsedCommonArrays() const { return usedCommonArrays; }
    const std::map<std::string, std::map<SgSymbol*, SgSymbol*>>& GetFuncSymbols() const { return funcSymbols; }

    void AddUsedLocalArray(FuncInfo *func, DIST::Array *array, const ParallelRegionLines &lines)
    {
        auto it = usedLocalArrays.find(func);
        if (it == usedLocalArrays.end())
            it = usedLocalArrays.insert(it, std::make_pair(func, std::map<DIST::Array*, std::vector<ParallelRegionLines>>()));

        auto itt = it->second.find(array);
        if (itt == it->second.end())
            itt = it->second.insert(itt, std::make_pair(array, std::vector<ParallelRegionLines>()));

        for (auto &curLines : itt->second)
            if (curLines == lines)
                return;

        itt->second.push_back(lines);
    }

    void AddUsedCommonArray(FuncInfo *func, DIST::Array *array, const ParallelRegionLines &lines)
    {
        auto it = usedCommonArrays.find(func);
        if (it == usedCommonArrays.end())
            it = usedCommonArrays.insert(it, std::make_pair(func, std::map<DIST::Array*, std::vector<ParallelRegionLines>>()));

        auto itt = it->second.find(array);
        if (itt == it->second.end())
            itt = it->second.insert(itt, std::make_pair(array, std::vector<ParallelRegionLines>()));

        for (auto &curLines : itt->second)
            if (curLines == lines)
                return;

        itt->second.push_back(lines);
    }

    void AddFuncSymbols(const std::string &fileName, SgSymbol *origin, SgSymbol *copy)
    {
        auto it = funcSymbols.find(fileName);
        if (it == funcSymbols.end())
            it = funcSymbols.insert(it, std::make_pair(fileName, std::map<SgSymbol*, SgSymbol*>()));

        auto itt = it->second.find(origin);
        if (itt == it->second.end())
            it->second.insert(std::make_pair(origin, copy));
    }

    void AddFileForFuncSymbols(const std::string &fileName)
    {
        auto it = funcSymbols.find(fileName);
        if (it == funcSymbols.end())
            it = funcSymbols.insert(it, std::make_pair(fileName, std::map<SgSymbol*, SgSymbol*>()));
    }
#endif

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

        if (type == DVM_DISTRIBUTE_DIR || type == DVM_VAR_DECL)
            userDvmDistrDirs.insert(userDvmDistrDirs.end(), dirs.begin(), dirs.end());
        else if (type == DVM_ALIGN_DIR)
            userDvmAlignDirs.insert(userDvmAlignDirs.end(), dirs.begin(), dirs.end());
        else if (type == DVM_SHADOW_DIR)
            userDvmShadowDirs.insert(userDvmShadowDirs.end(), dirs.begin(), dirs.end());
        else if (type == DVM_REALIGN_DIR)
            userDvmRealignDirs.insert(userDvmRealignDirs.end(), dirs.begin(), dirs.end());
        else if (type == DVM_REDISTRIBUTE_DIR)
            userDvmRedistrDirs.insert(userDvmRedistrDirs.end(), dirs.begin(), dirs.end());

        if (type == DVM_DISTRIBUTE_DIR ||
            type == DVM_ALIGN_DIR ||
            type == DVM_SHADOW_DIR ||
            type == DVM_REALIGN_DIR ||
            type == DVM_REDISTRIBUTE_DIR ||
            type == DVM_VAR_DECL)
        {
            for (auto &dir : dirs)
                dir->extractStmt();
        }
    }

    const std::vector<Statement*>* GetUsersDirecites(const int type) const
    {
        if (type == DVM_DISTRIBUTE_DIR || type == DVM_VAR_DECL)
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

#if __SPF
    // for RESOLVE_PAR_REGIONS
    std::set<FuncInfo*> allFunctionsCall;
    std::set<FuncInfo*> crossedFunctions;
    std::map<FuncInfo*, std::map<DIST::Array*, std::vector<ParallelRegionLines>>> usedLocalArrays;  // func -> array -> lines
    std::map<FuncInfo*, std::map<DIST::Array*, std::vector<ParallelRegionLines>>> usedCommonArrays; // func -> array -> lines
    std::map<std::string, std::map<SgSymbol*, SgSymbol*>> funcSymbols;                              // file name -> (origin symbol, new symbol)
    //
#endif

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
