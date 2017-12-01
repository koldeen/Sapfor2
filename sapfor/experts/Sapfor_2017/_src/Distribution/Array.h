#pragma once

#include <string>
#include <vector>
#include <map>
#include <algorithm>

#define STRING std::string
#define VECTOR std::vector
#define PAIR std::pair
#define MAP std::map
#define SET std::set
#define TO_STR std::to_string

namespace Distribution
{
    class Array;

    struct TemplateLink
    {
        TemplateLink(const int dimSize)
        {
            linkWithTemplate.resize(dimSize);
            alignRuleWithTemplate.resize(dimSize);
            for (int i = 0; i < dimSize; ++i)
                linkWithTemplate[i] = -1;
            templateArray = NULL;
        }

        VECTOR<int> linkWithTemplate;
        VECTOR<PAIR<int, int>> alignRuleWithTemplate;
        Array *templateArray;

        STRING toString()
        {
            STRING retVal = "";

            retVal += " " + TO_STR(linkWithTemplate.size());
            for (int i = 0; i < linkWithTemplate.size(); ++i)
                retVal += " " + TO_STR(linkWithTemplate[i]);

            retVal += " " + TO_STR(alignRuleWithTemplate.size());
            for (int i = 0; i < alignRuleWithTemplate.size(); ++i)
                retVal += " " + TO_STR(alignRuleWithTemplate[i].first) + " " + TO_STR(alignRuleWithTemplate[i].second);

            retVal += " " + TO_STR((long long)templateArray);
            return retVal;
        }
    };

    class Array
    {
    private:
        unsigned id;
        STRING name;
        STRING shortName;
        int dimSize;
        VECTOR<PAIR<int, int>> sizes;
        // template info by region
        MAP<int, TemplateLink*> templateInfo;
        bool isTemplFlag;
        bool isNonDistribute;

        SET<PAIR<STRING, int>> declPlaces;

        //0 - local, 1 - common, 2 - module
        int location;
        STRING locName;

        TemplateLink* getTemlateInfo(const int regionId)
        {
            auto it = templateInfo.find(regionId);
            TemplateLink *currLink = NULL;
            if (it == templateInfo.end())
            {
                currLink = new TemplateLink(dimSize);
                templateInfo[regionId] = currLink;
            }
            else
                currLink = it->second;
            return currLink;
        }

        VECTOR<PAIR<int, int>> shadowSpec;
    public:
        Array()
        {

        }

        Array(const STRING &name, const STRING &shortName, const int dimSize, const unsigned id
            , const STRING &declFile, const int declLine, const PAIR<int, STRING> &locationPos) :
            name(name), dimSize(dimSize), id(id), shortName(shortName), isTemplFlag(false), isNonDistribute(false),
            location(locationPos.first), locName(locationPos.second)
        {
            declPlaces.insert(std::make_pair(declFile, declLine));
            sizes.resize(dimSize);
            shadowSpec.resize(dimSize);
            for (int i = 0; i < dimSize; ++i)
                shadowSpec[i] = std::make_pair(0, 0);
        }

        int GetDimSize() const { return dimSize; }
        const STRING GetName() const { return name; }
        const STRING GetShortName() const { return shortName; }
        int GetId() const { return id; }
        void SetSizes(VECTOR<PAIR<int, int>> &_sizes) { sizes = _sizes; }
        const VECTOR<PAIR<int, int>>& GetSizes() const { return sizes; }
        void SetTemplateFlag(const bool templFlag) { isTemplFlag = templFlag; }
        bool isTemplate() const { return isTemplFlag; }
        int AddLinkWithTemplate(const int dimNum, const int value, Array *templateArray_, const PAIR<int, int> &rule, const int regionId)
        {
            int err = 0;
            if (dimNum >= dimSize)
                err = -1;
            else
            {
                TemplateLink *currLink = getTemlateInfo(regionId);
                                
                currLink->linkWithTemplate[dimNum] = value;
                currLink->alignRuleWithTemplate[dimNum] = rule;
                currLink->templateArray = templateArray_;
            }
            return err;
        }
        const VECTOR<int>& GetLinksWithTemplate(const int regionId) 
        {
            TemplateLink *currLink = getTemlateInfo(regionId);
            return currLink->linkWithTemplate;
        }

        const VECTOR<PAIR<int, int>>& GetAlignRulesWithTemplate(const int regionId)
        {
            TemplateLink *currLink = getTemlateInfo(regionId);
            return currLink->alignRuleWithTemplate;
        }

        void ChangeName(const STRING &newName)
        {
            auto pos = name.find(shortName);
            if (pos != STRING::npos)
            {
                name.erase(pos, shortName.size());
                shortName = newName;
                name += newName;
            }
        }

        void ExtendDimSize(const int dim, const PAIR<int, int> &size) 
        {
            if (size.first == size.second && size.first == -1)
                return;

            sizes[dim].first = std::min(sizes[dim].first, size.first);
            sizes[dim].second = std::max(sizes[dim].second, size.second);
        }
        void SetId(const unsigned newId) { id = newId; }

        const SET<PAIR<STRING, int>>& GetDeclInfo() { return declPlaces; }

        void ExtendShadowSpec(const VECTOR<PAIR<int, int>> &newSpec)
        {
            for (int i = 0; i < dimSize; ++i)
            {
                shadowSpec[i].first = std::max(shadowSpec[i].first, newSpec[i].first);
                shadowSpec[i].second = std::max(shadowSpec[i].first, newSpec[i].second);
            }
        }

        const VECTOR<PAIR<int, int>> &GetShadowSpec() { return shadowSpec; }

        STRING toString()
        {
            STRING retVal = "";
            retVal += " " + TO_STR(id);
            retVal += " " + name;
            retVal += " " + shortName;
            retVal += " " + TO_STR(dimSize);

            if (isNonDistribute)
                retVal += " 1";
            else
                retVal += " 0";

            retVal += " " + TO_STR(location);
            retVal += " " + locName;

            retVal += " " + TO_STR(sizes.size());
            for (int i = 0; i < sizes.size(); ++i)
                retVal += " " + TO_STR(sizes[i].first) + " " + TO_STR(sizes[i].second);

            retVal += " " + TO_STR(templateInfo.size());
            for (auto it = templateInfo.begin(); it != templateInfo.end(); ++it)
                retVal += " " + TO_STR(it->first) + it->second->toString();
            
            retVal += " " + TO_STR((int)isTemplFlag);
            retVal += "|" + TO_STR(declPlaces.size());

            for (auto &place : declPlaces)
                retVal += "|" + place.first + "|" + TO_STR(place.second);            
            return retVal;
        }

        Array* GetTemplateArray(const int regionId) 
        {
            TemplateLink *currLink = getTemlateInfo(regionId);
            return currLink->templateArray;
        }

        void SetNonDistributeFlag(bool isNonDistribute_) { isNonDistribute = isNonDistribute_; }
        bool GetNonDistributeFlag() const { return isNonDistribute; }

        void SetLocation(int loc, const STRING &name) { location = loc; locName = name; }
        PAIR<int, STRING> GetLocation() const { return std::make_pair(location, locName); }

        ~Array() 
        {
            for (auto &templ : templateInfo)
                delete templ.second;
        }
    };

    
    class ArrayAccessInfo
    {
    private:
        MAP<STRING, std::set<PAIR<int, char>>> accessPattern; // file -> PAIRS<LINE, R/W -> 0, 1>
    public:
        void AddAccessInfo(const PAIR<int, char> &info, const STRING &file)
        {
            auto it = accessPattern.find(file);
            if (it == accessPattern.end())
                it = accessPattern.insert(it, make_pair(file, std::set<PAIR<int, char>>()));
            it->second.insert(info);
        }
        const MAP<STRING, std::set<PAIR<int, char>>>& GetAllAccessInfo() const { return accessPattern; }
    };
}
#undef VECTOR
#undef STRING
#undef PAIR
#undef MAP
#undef SET
#undef TO_STR