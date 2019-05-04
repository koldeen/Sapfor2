#include "Array.h"

using namespace std;

namespace Distribution
{
    vector<pair<int, int>> TemplateLink::GetAlignRules() const
    {
        vector<pair<int, int>> retVal = alignRuleWithTemplate;
        vector<int> newOrder = templateArray->GetNewTemplateDimsOrder();
        if (newOrder.size() == 0)
            return alignRuleWithTemplate;
        else //TODO
            return retVal;
    }

    vector<int> TemplateLink::GetLinks() const
    {
        vector<int> retVal = linkWithTemplate;
        vector<int> newOrder = templateArray->GetNewTemplateDimsOrder();
        if (newOrder.size() == 0)
            return linkWithTemplate;
        else //TODO
            return retVal;
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

    void TemplateLink::AddRule(const int dimNum, int value, const pair<int, int> &rule, Array *templateArray_)
    {
        linkWithTemplate[dimNum] = value;
        alignRuleWithTemplate[dimNum] = rule;
        templateArray = templateArray_;
    }
}
