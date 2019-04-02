#pragma once

#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <climits>

class Symbol;
class Expression;

#define STRING std::string
#define VECTOR std::vector
#define PAIR std::pair
#define MAP std::map
#define SET std::set
#define TO_STR std::to_string

namespace Distribution
{
    typedef enum distFlag : int { DISTR = 0, NO_DISTR, SPF_PRIV, IO_PRIV } distFlagType;
    typedef enum arrayLocation : int { l_LOCAL = 0, l_COMMON, l_MODULE, l_PARAMETER, l_STRUCT } arrayLocType;

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

        TemplateLink(const TemplateLink &copy)
        {
            linkWithTemplate = copy.linkWithTemplate;
            alignRuleWithTemplate = copy.alignRuleWithTemplate;
            templateArray = copy.templateArray;
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
        int typeSize; // size of one element of array
        // calculated sizes
        VECTOR<PAIR<int, int>> sizes;
        // original sizes + shifts
        VECTOR<PAIR<PAIR<Expression*, PAIR<int, int>>, PAIR<Expression*, PAIR<int, int>>>> sizesExpr;

        // template info by region
        MAP<int, TemplateLink*> templateInfo;
        bool isTemplFlag;
        bool isLoopArrayFlag;
        distFlag isNonDistribute;
        Symbol *declSymbol;
        STRING uniqKey;

        // PAIR<FILE, LINE>
        SET<PAIR<STRING, int>> declPlaces;

        //TYPE: 0 - local, 1 - common, 2 - module, 3 - function parameter
        // PAIR<TYPE, NAME>
        PAIR<arrayLocation, STRING> locationPos;
        VECTOR<VECTOR<PAIR<int, int>>> allShadowSpecs;

        SET<STRING> containsInRegions;

        // file -> lines
        MAP<STRING, SET<int>> usagePlaces;

        VECTOR<bool> mappedDims;
        VECTOR<bool> depracateToDistribute;

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

        void GenUniqKey()
        {
            uniqKey = shortName + locationPos.second + TO_STR(dimSize);
            for (auto &place : declPlaces)
                uniqKey += place.first + TO_STR(place.second);
        }
    public:
        Array()
        {
            isTemplFlag = false;
            isLoopArrayFlag = false;
            isNonDistribute = NO_DISTR;
            typeSize = 0;
            uniqKey = "";
            dimSize = 0;
            id = -1;
            declSymbol = NULL;
        }

        Array(const STRING &name, const STRING &shortName, const int dimSize, const unsigned id,
              const STRING &declFile, const int declLine, const PAIR<arrayLocation, STRING> &locationPos,
              Symbol *declSymbol, const VECTOR<STRING> &regions, const int typeSize) :

            name(name), dimSize(dimSize), id(id), shortName(shortName), 
            isTemplFlag(false), isNonDistribute(DISTR), isLoopArrayFlag(false),
            locationPos(locationPos), declSymbol(declSymbol), typeSize(typeSize)
        {
            declPlaces.insert(std::make_pair(declFile, declLine));
            sizes.resize(dimSize);
            sizesExpr.resize(dimSize);
            mappedDims.resize(dimSize);
            depracateToDistribute.resize(dimSize);

            for (int z = 0; z < dimSize; ++z)
            {
                sizes[z] = std::make_pair((int)INT_MAX, (int)INT_MIN);
                PAIR<int, int> initVal = std::make_pair(0, 0);
                sizesExpr[z] = std::make_pair(std::make_pair((Expression*)NULL, initVal), std::make_pair((Expression*)NULL, initVal));
                mappedDims[z] = false;
                depracateToDistribute[z] = false;
            }
                        
            GenUniqKey();
            for (auto &reg : regions)
                containsInRegions.insert(reg);
        }

        Array(const Array &copy)
        {
            id = copy.id;
            name = copy.name;
            shortName = copy.shortName;
            dimSize = copy.dimSize;
            typeSize = copy.typeSize;

            sizes = copy.sizes;
            sizesExpr = copy.sizesExpr;

            isTemplFlag = copy.isTemplFlag;
            isNonDistribute = copy.isNonDistribute;
            isLoopArrayFlag = copy.isLoopArrayFlag;

            declPlaces = copy.declPlaces;
            locationPos = copy.locationPos;

            allShadowSpecs = copy.allShadowSpecs;

            for (auto &elem : copy.templateInfo)
                templateInfo[elem.first] = new TemplateLink(*elem.second);

            declSymbol = copy.declSymbol;
            uniqKey = copy.uniqKey;
            containsInRegions = copy.containsInRegions;
            mappedDims = copy.mappedDims;
            depracateToDistribute = copy.depracateToDistribute;
        }

        bool RemoveUnpammedDims()
        {
            bool needToRemove = false;
            int countToRem = 0;
            for (int z = 0; z < dimSize; ++z)
            {
                if (!mappedDims[z] || depracateToDistribute[z])
                {
                    needToRemove = true;
                    countToRem++;
                    //break;
                }
            }

            if (needToRemove == false)
                return false;
            if (countToRem == dimSize)
                return true;

            VECTOR<PAIR<int, int>> newSizes;
            VECTOR<PAIR<PAIR<Expression*, PAIR<int, int>>, PAIR<Expression*, PAIR<int, int>>>> newSizesExpr;
            VECTOR<bool> newMappedDims;
            VECTOR<bool> newDepr;

            for (int z = 0; z < dimSize; ++z)
            {
                if (mappedDims[z] && !depracateToDistribute[z])
                {
                    newSizes.push_back(sizes[z]);
                    newSizesExpr.push_back(sizesExpr[z]);
                    newMappedDims.push_back(mappedDims[z]);
                    newDepr.push_back(depracateToDistribute[z]);
                }
            }

            sizes = newSizes;
            sizesExpr = newSizesExpr;
            mappedDims = newMappedDims;
            depracateToDistribute = newDepr;
            dimSize = (int)sizes.size();

            return false;
        }

        int GetDimSize() const { return dimSize; }
        const STRING GetName() const { return name; }
        const STRING GetShortName() const { return shortName; }
        int GetId() const { return id; }
        void SetSizes(VECTOR<PAIR<int, int>> &_sizes, bool notCopyToExpr = false) 
        { 
            sizes = _sizes;
            if (!notCopyToExpr)
            {
                for (int i = 0; i < sizesExpr.size(); ++i)
                {
                    sizesExpr[i].first.second.first = sizes[i].first;
                    sizesExpr[i].second.second.first = sizes[i].second;
                }
            }
        }
        const VECTOR<PAIR<int, int>>& GetSizes() const { return sizes; }
        const VECTOR<PAIR<PAIR<Expression*, PAIR<int, int>>, PAIR<Expression*, PAIR<int, int>>>>& GetSizesExpr() const { return sizesExpr; }
        void SetTemplateFlag(const bool templFlag) { isTemplFlag = templFlag; }
        bool isTemplate() const { return isTemplFlag; }
        bool isLoopArray() const { return isLoopArrayFlag; }
        void setLoopArray(const bool flag) { isLoopArrayFlag = flag; }
        void SetSizesExpr(const VECTOR<PAIR<Expression*, Expression*>> &_sizesExpr)
        {
            for (int i = 0; i < _sizesExpr.size(); ++i)
            {
                sizesExpr[i].first.first = _sizesExpr[i].first;
                sizesExpr[i].second.first = _sizesExpr[i].second;
            }
        }

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
            GenUniqKey();
        }

        void ExtendDimSize(const int dim, const PAIR<int, int> &size) 
        {
            if (size.first == size.second && size.first == -1)
                return;

            sizes[dim].first = std::min(sizes[dim].first, size.first);
            sizes[dim].second = std::max(sizes[dim].second, size.second);

            PAIR<int, int> &left = sizesExpr[dim].first.second;
            PAIR<int, int> &right = sizesExpr[dim].second.second;

            left.second = std::min(left.second, sizes[dim].first - left.first);
            right.second = std::max(right.second, sizes[dim].second - right.first);
        }
        void SetId(const unsigned newId) { id = newId; }

        const SET<PAIR<STRING, int>>& GetDeclInfo() const { return declPlaces; }
        void AddDeclInfo(const PAIR<STRING, int> &declInfo) 
        {
            declPlaces.insert(declInfo); 
            GenUniqKey();
        }

        //save request of shadow spec
        void ExtendShadowSpec(const VECTOR<PAIR<int, int>> &newSpec)
        {
            if (allShadowSpecs.size() == 0)
                allShadowSpecs.resize(dimSize);

            const PAIR<int, int> zeroPair(0, 0);
            for (int i = 0; i < newSpec.size(); ++i)
                if (newSpec[i] != zeroPair)
                    allShadowSpecs[i].push_back(newSpec[i]);
        }
        
        //remove last requst of shadow spec
        void RemoveShadowSpec(const VECTOR<PAIR<int, int>> &delSpec)
        {
            int dimN = 0;
            for (auto &group : allShadowSpecs)
            {
                for (int i = 0; i < group.size(); ++i)
                {
                    if (group[i] == delSpec[dimN])
                    {
                        group.erase(group.begin() + i);
                        break;
                    }
                }
                ++dimN;
            }
        }

        //construct shadow spec from all requests
        const VECTOR<PAIR<int, int>> GetShadowSpec() const
        {
            VECTOR<PAIR<int, int>> shadowSpec;
            shadowSpec.resize(dimSize);
            for (int i = 0; i < dimSize; ++i)
                shadowSpec[i] = std::make_pair(0, 0);

            int dimN = 0;
            for (auto &group : allShadowSpecs)
            {
                for (auto &elem : group)
                {
                    shadowSpec[dimN].first = std::max(shadowSpec[dimN].first, elem.first);
                    shadowSpec[dimN].second = std::max(shadowSpec[dimN].second, elem.second);
                }
                ++dimN;
            }
            return shadowSpec; 
        }

        void ClearShadowSpecs() { allShadowSpecs.clear(); }

        STRING toString()
        {
            STRING retVal = "";
            retVal += TO_STR(id);
            retVal += " " + name;
            retVal += " " + shortName;
            retVal += " " + TO_STR(dimSize);
            retVal += " " + TO_STR(typeSize);
            retVal += " " + TO_STR(isNonDistribute);
            
            retVal += " " + TO_STR(locationPos.first);
            retVal += " " + locationPos.second;

            retVal += " " + TO_STR(sizes.size());
            for (int i = 0; i < sizes.size(); ++i)
                retVal += " " + TO_STR(sizes[i].first) + " " + TO_STR(sizes[i].second);

            retVal += " " + TO_STR(depracateToDistribute.size());
            for (int i = 0; i < depracateToDistribute.size(); ++i)
                retVal += " " + TO_STR((int)depracateToDistribute[i]);

            retVal += " " + TO_STR(mappedDims.size());
            for (int i = 0; i < mappedDims.size(); ++i)
                retVal += " " + TO_STR((int)mappedDims[i]);

            retVal += " " + TO_STR(templateInfo.size());
            for (auto it = templateInfo.begin(); it != templateInfo.end(); ++it)
                retVal += " " + TO_STR(it->first) + it->second->toString();
            
            retVal += " " + TO_STR((int)isTemplFlag);
            retVal += "|" + TO_STR((int)isLoopArrayFlag);
            retVal += "|" + TO_STR(declPlaces.size());

            for (auto &place : declPlaces)
                retVal += "|" + place.first + "|" + TO_STR(place.second);

            retVal += "|" + TO_STR(containsInRegions.size());
            for (auto &reg : containsInRegions)
                retVal += "|" + reg;
            return retVal;
        }

        Array* GetTemplateArray(const int regionId) 
        {
            TemplateLink *currLink = getTemlateInfo(regionId);
            return currLink->templateArray;
        }

        void SetNonDistributeFlag(const distFlag isNonDistribute_) { isNonDistribute = isNonDistribute_; }
        bool GetNonDistributeFlag() const { return (isNonDistribute == DISTR) ? false : true; }
        distFlag GetNonDistributeFlagVal() const { return isNonDistribute; }

        void ChangeLocation(arrayLocation loc, const STRING &name)
        {
            locationPos = std::make_pair(loc, name);
        }

        void SetLocation(arrayLocation loc, const STRING &name)
        {
            ChangeLocation(loc, name);
            GenUniqKey();
        }
        PAIR<arrayLocation, STRING> GetLocation() const { return locationPos; }

        Symbol* GetDeclSymbol() const { return declSymbol; }

        const STRING& GetArrayUniqKey() const { return uniqKey; }

        const SET<STRING>& GetRegionsName() const { return containsInRegions; }
        void SetRegionPlace(const STRING &regName) { if (regName != "") containsInRegions.insert(regName); }
        
        const MAP<STRING, SET<int>>& GetUsagePlaces() const { return usagePlaces; }
        const SET<int> GetUsagePlaces(const STRING &fileName) const
        {
            auto it = usagePlaces.find(fileName);
            if (it == usagePlaces.end())
                return SET<int>();
            return it->second;
        }
        void AddUsagePlace(const STRING &fileName, int lineNumber)
        {
            auto it = usagePlaces.find(fileName);
            if (it == usagePlaces.end())
                it = usagePlaces.insert(it, make_pair(fileName, SET<int>()));
            it->second.insert(lineNumber);
        }

        void SetMappedDim(const int dim)
        {
            if (dim >= dimSize)
                return;
            mappedDims[dim] = true;
        }

        bool IsDimMapped(const int dim) const
        {
            if (dim >= dimSize)
                return false;
            else
                return mappedDims[dim];
        }

        void DeprecateDimension(const int dim, bool value = true)
        {
            if (dim >= dimSize)
                return;
            depracateToDistribute[dim] = value;
        }

        void DeprecateAllDims()
        {
            for (int dim = 0; dim < dimSize; ++dim)
                depracateToDistribute[dim] = true;
        }

        bool IsDimDepracated(const int dim) const
        {
            if (dim >= dimSize)
                return false;
            else
                return depracateToDistribute[dim];
        }
        
        bool isAllDeprecated() const
        {
            bool ret = true;
            for (int z = 0; z < dimSize; ++z)
                ret = ret && depracateToDistribute[z];
            return ret;
        }

        int GetTypeSize() const { return typeSize; }

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