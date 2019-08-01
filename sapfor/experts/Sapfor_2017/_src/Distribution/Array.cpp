#include "Array.h"
#include "../Utils/errors.h"
#include "../Utils/utils.h"

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

        retVal += " " + to_string(linkWithTemplate.size());
        for (int i = 0; i < linkWithTemplate.size(); ++i)
            retVal += " " + to_string(linkWithTemplate[i]);

        retVal += " " + to_string(alignRuleWithTemplate.size());
        for (int i = 0; i < alignRuleWithTemplate.size(); ++i)
            retVal += " " + to_string(alignRuleWithTemplate[i].first) + " " + to_string(alignRuleWithTemplate[i].second);

        retVal += " " + to_string((long long)templateArray);
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
}
