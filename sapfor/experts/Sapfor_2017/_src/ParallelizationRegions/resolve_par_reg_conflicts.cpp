#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include <map>

#include "resolve_par_reg_conflicts.h"
#include "SgUtils.h"

using std::map;
using std::pair;
//using std::tuple;
using std::set;
using std::vector;
using std::string;
using std::make_pair;

set<ParallelRegion*> getRegionByLine2(const vector<ParallelRegion*> &regions, const string &file, const int line)
{
    set<ParallelRegion*> regFound;

    if (regions.size() == 1 && regions[0]->GetName() == "DEFAULT") // only default
    {
        regFound.insert(regions[0]);
        return regFound;
    }
    else if (regions.size() > 0)
    {
        for (int i = 0; i < regions.size(); ++i)
            if (regions[i]->hasThisLine(line, file))
                regFound.insert(regions[i]);

        return regFound;
    }
}

static bool isInCommon(const map<string, CommonBlock> &commonBlocks, const string &arrayName)
{
    for (auto &commonBlockPair : commonBlocks)
        for (auto &variable : commonBlockPair.second.getVariables())
            if (variable.getName() == arrayName)
                return true;

    return false;
}

static void recursiveFill(SgExpression *exp,
                          const string &fileName,
                          const map<string, CommonBlock> &commonBlocks,
                          map<string, set<string>> &localArrayFound,
                          set<string> &commonArrayFound)
{
    if (exp)
    {
        if (exp->variant() == ARRAY_REF)
        {
            string arrayName = string(exp->symbol()->identifier());
            __spf_print(1, "***'%s' is array\n", arrayName.c_str()); // remove this line

            if (isInCommon(commonBlocks, arrayName))
                commonArrayFound.insert(arrayName);
            else
            {
                auto it = localArrayFound.find(fileName);
                if (it == localArrayFound.end())
                    //localArrayFound.insert(it, make_pair(fileName, set<string>()));
                {
                    set<string> newSet;
                    localArrayFound.insert(it, make_pair(fileName, newSet));
                }

                it->second.insert(arrayName);
            }
        }

        recursiveFill(exp->rhs(), fileName, commonBlocks, localArrayFound, commonArrayFound);
        recursiveFill(exp->lhs(), fileName, commonBlocks, localArrayFound, commonArrayFound);
    }
}

void fillRegionArrays(vector<ParallelRegion*> &regions, const map<string, CommonBlock> &commonBlocks)
{
    __spf_print(1, "***RUN fillRegionArrays()\n"); // remove this line
    for (auto &region : regions)
    {
        map<string, set<string>> localArrayFound;
        set<string> commonArrayFound;

        for (auto &fileLines : region->GetAllLines())
        {
            // switch to current file
            if (switchToFile(fileLines.first) != -1)
            {
                __spf_print(1, "***file switched\n"); // remove this line
                for (auto &regionLines : fileLines.second)
                {
                    int iteratorLine = regionLines.lines.first;
                    int endLine = regionLines.lines.second;
                    SgStatement *iterator = regionLines.stats.first;
                    SgStatement *end = regionLines.stats.second;

                    // ÑÅÉ×ÀÑ ÏÐÎÕÎÄ ÏÎ ßÂÍÛÌ ÑÒÐÎÊÀÌ, À ÍÓÆÅÍ ÏÎ ÂÑÅÌ
                    for (; iterator && iterator != end; iterator = iterator->lexNext())
                    {
                        if (isSPF_stat(iterator) || isDVM_stat(iterator))
                            continue;

                        for (int i = 0; i < 3; ++i)
                        {
                            SgExpression *exp = iterator->expr(i);
                            recursiveFill(exp, fileLines.first, commonBlocks, localArrayFound, commonArrayFound);
                            // if (exp) recExpressionPrint(exp); // remove
                        }
                    }
                }
            }
        }

        //region.addUsedLocalArrays(); map<string, set<string>> usedLocalArrays
        //region.addUsedCommonArrays(); set<string> usedCommonArrays;
    }
}

void fillRegionFunctions(vector<ParallelRegion*> &regions, const map<string, vector<FuncInfo*>> allFuncInfo)
{

}

void resolveRegions(const vector<ParallelRegion*> &regions)
{

}