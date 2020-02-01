#include "Array.h"
#include "../Utils/errors.h"
#include "../Utils/utils.h"
#include "../GraphCall/graph_calls.h"

using namespace std;

static vector<pair<int, int>> applyNewOrder(const vector<pair<int, int>>& in, const vector<int>& newOrder)
{
    int countOfDepr = 0;
    for (int z = 0; z < in.size(); ++z)
        countOfDepr += (in[z].first == 0 && in[z].second == 0) ? 1 : 0;

    if (newOrder.size() == 0)
        return in;
    if (newOrder.size() + countOfDepr != in.size())
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

    vector<pair<int, int>> tmp, retTmp(newOrder.size());
    for (int z = 0; z < in.size(); ++z)
        if (!(in[z].first == 0 && in[z].second == 0))
            tmp.push_back(in[z]);

    for (int z = 0; z < newOrder.size(); ++z)
        retTmp[z] = tmp[newOrder[z]];

    vector<pair<int, int>> retVal;
    for (int z = 0, z1 = 0; z < in.size(); ++z)
        if ((in[z].first == 0 && in[z].second == 0))
            retVal.push_back(in[z]);
        else
            retVal.push_back(retTmp[z1++]);

    return retVal;
}

static vector<int> applyNewOrder(const vector<int> &in, const vector<int> &newOrder)
{
    int countOfDepr = 0;
    for (int z = 0; z < in.size(); ++z)
        countOfDepr += (in[z] == -1) ? 1 : 0;
    
    if (newOrder.size() == 0)
        return in;
    if (newOrder.size() + countOfDepr != in.size())
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

    vector<int> tmp, retTmp(newOrder.size());
    for (int z = 0; z < in.size(); ++z)
        if (in[z] != -1)
            tmp.push_back(in[z]);

    for (int z = 0; z < newOrder.size(); ++z)
        retTmp[z] = tmp[newOrder[z]];

    vector<int> retVal;
    for (int z = 0, z1 = 0; z < in.size(); ++z)
        if (in[z] == -1)
            retVal.push_back(in[z]);
        else
            retVal.push_back(retTmp[z1++]);

    return retVal;
}

template<typename T>
static vector<T> applyNewOrderS(const vector<T> &in, const vector<int> &newOrder)
{
    vector<T> retVal(in.size());
    if (newOrder.size() == 0)
        return in;
    if (newOrder.size() != in.size())
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

    for (int z = 0; z < newOrder.size(); ++z)
        retVal[z] = in[newOrder[z]];

    return retVal;
}

namespace Distribution
{
    vector<pair<int, int>> TemplateLink::GetAlignRules() const
    {
        vector<pair<int, int>> retVal = alignRuleWithTemplate;
        if (templateArray == NULL)
            return retVal;

        vector<int> newOrder = templateArray->GetNewTemplateDimsOrder();
        if (newOrder.size() == 0)
            return alignRuleWithTemplate;
        else
            return applyNewOrder(retVal, newOrder);
    }

    vector<int> TemplateLink::GetLinks() const
    {
        vector<int> retVal = linkWithTemplate;
        if (templateArray == NULL)
            return retVal;

        vector<int> newOrder = templateArray->GetNewTemplateDimsOrder();
        if (newOrder.size() == 0)
            return linkWithTemplate;
        else
            return applyNewOrder(retVal, newOrder);
    }

    string TemplateLink::toString() const
    {
        string retVal = "";

        retVal += "#" + to_string(linkWithTemplate.size());
        for (int i = 0; i < linkWithTemplate.size(); ++i)
            retVal += "#" + to_string(linkWithTemplate[i]);

        retVal += "#" + to_string(alignRuleWithTemplate.size());
        for (int i = 0; i < alignRuleWithTemplate.size(); ++i)
            retVal += "#" + to_string(alignRuleWithTemplate[i].first) + "#" + to_string(alignRuleWithTemplate[i].second);

        retVal += "#" + to_string((long long)templateArray);
        return retVal;
    }

    void TemplateLink::AddRule(const int dimNum, int dimTempl, const pair<int, int> &rule, Array *templateArray_)
    {
        linkWithTemplate[dimNum] = dimTempl;
        alignRuleWithTemplate[dimNum] = rule;
        templateArray = templateArray_;
    }

    const vector<pair<int, int>>& Array::GetSizes()
    {
        if (templateDimsOrder.size() == 0)
            return sizes; 
        else
        {
            if (orderedSizes.size() == 0)
                orderedSizes = applyNewOrderS(sizes, templateDimsOrder);
            return orderedSizes;
        }
    }

    const vector<pair<pair<Expression*, pair<int, int>>, pair<Expression*, pair<int, int>>>>& 
        Array::GetSizesExpr()
    {
        if (templateDimsOrder.size() == 0)
            return sizesExpr;
        else
        {
            if (orderedSizesExpr.size() == 0)
                orderedSizesExpr = applyNewOrderS(sizesExpr, templateDimsOrder);
            return orderedSizesExpr;
        }
    }

    void printArrayInfo(const string &file, const map<tuple<int, string, string>, pair<Array*, ArrayAccessInfo*>> &declaratedArrays)
    {
        FILE* out = fopen(file.c_str(), "w");
        if (out == NULL)
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

        for (auto& elem : declaratedArrays)
        {
            Array* currA = elem.second.first;
            ArrayAccessInfo* info = elem.second.second;

            fprintf(out, "Array '%s' (full name '%s'):\n", currA->GetShortName().c_str(), currA->GetName().c_str());
            auto loc = currA->GetLocation();
            string locN = "";
            if (loc.first == l_COMMON)
                locN = "COMMON ";
            else if (loc.first == l_MODULE)
                locN = "MODULE ";
            else if (loc.first == l_PARAMETER)
                locN = "PARAMETER of ";
            else if (loc.first == l_LOCAL)
                locN = "LOCAL of ";
            else if (loc.first == l_LOCAL_SAVE)
                locN = "LOCAL (save) of ";
            else if (loc.first == l_STRUCT)
                locN = "STRUCT ";
            else 
                locN = "UNKN ";
            locN += "'" + loc.second + "'";

            fprintf(out, " type: %s\n", locN.c_str());
            for (auto& byFile : info->GetAllAccessInfo())
            {
                fprintf(out, " FOR FILE '%s':\n", convertFileName(byFile.first.c_str()).c_str());
                for (auto& byLine : byFile.second)
                    for (auto &onLine : byLine.second)
                        fprintf(out, "  %s\n", onLine.PrintInfo().c_str());
            }
            fprintf(out, "=============== \n\n");
        }

        fclose(out);
    }

    void fixTypeOfArrayInfoWithCallGraph(map<tuple<int, string, string>, pair<Array*, ArrayAccessInfo*>> &declaratedArrays,
                                         const map<string, FuncInfo*> &allFuncs)
    {
        for (auto& elem : declaratedArrays)
        {
            ArrayAccessInfo* info = elem.second.second;
            info->checkAndUpdate(allFuncs);
        }
    }

    void ArrayAccessInfo::checkAndUpdate(const map<string, FuncInfo*>& allFuncs)
    {
        for (auto& byFile : accessPatterns)
        {
            for (auto& byLine : byFile.second)
            {
                for (auto& acc : byLine.second)
                {
                    if (acc.underFunctionPar != -1)
                    {
                        auto it = allFuncs.find(acc.fName);
                        if (it != allFuncs.end())
                        {
                            if (it->second->funcParams.isArgIn(acc.underFunctionPar) &&
                                !it->second->funcParams.isArgOut(acc.underFunctionPar))
                            {
                                //switch to READ
                                acc.type = 0;
                            }
                        }
                    }
                }
            }
        }
    }
}
