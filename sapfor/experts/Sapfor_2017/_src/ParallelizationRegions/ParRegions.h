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

    void AddLocalArray(const std::string &functionName, const std::string &arrayName)
    {
        auto it = usedLocalArrays.find(functionName);
        if (it == usedLocalArrays.end())
            it = usedLocalArrays.insert(it, make_pair(functionName, std::set<std::string>()));

        it->second.insert(arrayName);
    }

    void AddCommonArray(const std::string &arrayName) { usedCommonArrays.insert(arrayName); }

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
    std::map<std::string, std::set<std::string>> usedLocalArrays; // func -> arrays
    std::set<std::string> crossedFunctions;

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
};
