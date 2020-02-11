#pragma once

#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <climits>
#include "DvmhDirectiveBase.h"

class Symbol;
class Expression;
struct FuncInfo;

#define STRING std::string
#define VECTOR std::vector
#define PAIR std::pair
#define MAP std::map
#define SET std::set
#define TO_STR std::to_string

namespace Distribution
{
    typedef enum distFlag : int { DISTR = 0, NO_DISTR, SPF_PRIV, IO_PRIV } distFlagType;
    typedef enum arrayLocation : int { l_LOCAL = 0, l_COMMON, l_MODULE, l_PARAMETER, l_STRUCT, l_LOCAL_SAVE } arrayLocType;

    class Array;

    class TemplateLink
    {
    private:
        VECTOR<int> linkWithTemplate;
        VECTOR<PAIR<int, int>> alignRuleWithTemplate;
        Array *templateArray;

    public:
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

        Array* GetTemplateArray() const { return templateArray; }
        VECTOR<PAIR<int, int>> GetAlignRules() const;
        VECTOR<int> GetLinks() const;
        void AddRule(const int dimNum, int value, const PAIR<int, int> &rule, Array *templateArray_);
        STRING toString() const;
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

        VECTOR<PAIR<int, int>> orderedSizes;
        VECTOR<PAIR<PAIR<Expression*, PAIR<int, int>>, PAIR<Expression*, PAIR<int, int>>>> orderedSizesExpr;

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

        bool ompThreadPrivate;

    private:
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

        //clones of template for realignes
        MAP<VECTOR<dist>, STRING> templateClones;
        VECTOR<int> templateDimsOrder;

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
            ompThreadPrivate = false;
        }

        Array(const STRING &name, const STRING &shortName, const int dimSize, const unsigned id,
              const STRING &declFile, const int declLine, const PAIR<arrayLocation, STRING> &locationPos,
              Symbol *declSymbol, bool inOmpThreadPriv, const VECTOR<STRING> &regions, const int typeSize) :

            name(name), dimSize(dimSize), id(id), shortName(shortName), 
            isTemplFlag(false), isNonDistribute(DISTR), isLoopArrayFlag(false),
            locationPos(locationPos), declSymbol(declSymbol), typeSize(typeSize), ompThreadPrivate(inOmpThreadPriv)
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
            ompThreadPrivate = copy.ompThreadPrivate;
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
        const VECTOR<PAIR<int, int>>& GetSizes();
        const VECTOR<PAIR<PAIR<Expression*, PAIR<int, int>>, PAIR<Expression*, PAIR<int, int>>>>& GetSizesExpr();
        void SetTemplateFlag(const bool templFlag) { isTemplFlag = templFlag; }
        bool IsTemplate() const { return isTemplFlag; }
        bool IsLoopArray() const { return isLoopArrayFlag; }
        bool IsArray() const { return !isTemplFlag && !isLoopArrayFlag; }
        void SetLoopArray(const bool flag) { isLoopArrayFlag = flag; }
        void SetSizesExpr(const VECTOR<PAIR<Expression*, Expression*>> &_sizesExpr)
        {
            for (int i = 0; i < _sizesExpr.size(); ++i)
            {
                sizesExpr[i].first.first = _sizesExpr[i].first;
                sizesExpr[i].second.first = _sizesExpr[i].second;
            }
        }

        int AddLinkWithTemplate(const int dimNum, const int dimTempl, Array *templateArray_, const PAIR<int, int> &rule, const int regionId)
        {
            int err = 0;
            if (dimNum >= dimSize)
                err = -1;
            else
            {
                TemplateLink *currLink = getTemlateInfo(regionId);
                currLink->AddRule(dimNum, dimTempl, rule, templateArray_);
            }
            return err;
        }

        VECTOR<int> GetLinksWithTemplate(const int regionId)
        {
            TemplateLink *currLink = getTemlateInfo(regionId);
            return currLink->GetLinks();
        }

        VECTOR<PAIR<int, int>> GetAlignRulesWithTemplate(const int regionId)
        {
            TemplateLink *currLink = getTemlateInfo(regionId);
            return currLink->GetAlignRules();
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
            /*if (size.first == size.second)
                return;*/

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
            retVal += "#" + name;
            retVal += "#" + shortName;
            retVal += "#" + TO_STR(dimSize);
            retVal += "#" + TO_STR(typeSize);
            retVal += "#" + TO_STR(isNonDistribute);
            
            retVal += "#" + TO_STR(locationPos.first);
            retVal += "#" + locationPos.second;

            retVal += "#" + TO_STR(sizes.size());
            for (int i = 0; i < sizes.size(); ++i)
                retVal += "#" + TO_STR(sizes[i].first) + "#" + TO_STR(sizes[i].second);

            retVal += "#" + TO_STR(depracateToDistribute.size());
            for (int i = 0; i < depracateToDistribute.size(); ++i)
                retVal += "#" + TO_STR((int)depracateToDistribute[i]);

            retVal += "#" + TO_STR(mappedDims.size());
            for (int i = 0; i < mappedDims.size(); ++i)
                retVal += "#" + TO_STR((int)mappedDims[i]);

            retVal += "#" + TO_STR(templateInfo.size());
            for (auto it = templateInfo.begin(); it != templateInfo.end(); ++it)
                retVal += "#" + TO_STR(it->first) + it->second->toString();
            
            retVal += "#" + TO_STR((int)isTemplFlag);
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
            return currLink->GetTemplateArray();
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

        STRING GetIndepUniqName() const { return shortName + locationPos.second + TO_STR(dimSize); }

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
            {
                if (templateDimsOrder.size() == 0)
                   return mappedDims[dim];
                else
                   return mappedDims[templateDimsOrder[dim]];
            }
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
            {
                if (templateDimsOrder.size() == 0)
                    return depracateToDistribute[dim];
                else
                    return depracateToDistribute[templateDimsOrder[dim]];
            }
        }
        
        bool IsAllDeprecated() const
        {
            bool ret = true;
            for (int z = 0; z < dimSize; ++z)
                ret = ret && depracateToDistribute[z];
            return ret;
        }

        const VECTOR<bool>& GetDeprecetedDims() const { return depracateToDistribute; }

        int GetTypeSize() const { return typeSize; }

        STRING AddTemplateClone(const VECTOR<dist> &newDist)
        {
            auto it = templateClones.find(newDist);
            if (it == templateClones.end())
                it = templateClones.insert(it, std::make_pair(newDist, shortName + STRING("_r") + TO_STR(templateClones.size())));
            return it->second;
        }

        void ClearTemplateClones()
        {
            templateClones.clear();
            templateDimsOrder.clear(); 
            orderedSizes.clear();
            orderedSizesExpr.clear();
        }

        const MAP<VECTOR<dist>, STRING>& GetAllClones() const { return templateClones; }

        void AddNewTemplateDimsOrder(const VECTOR<int> &newOrder) { templateDimsOrder = newOrder; }

        VECTOR<int> GetNewTemplateDimsOrder() const { return templateDimsOrder; }

        void SetDimSizesToMaxMin(bool notCopyToExpr = false)
        {            
            for (int i = 0; i < dimSize; ++i)
                sizes[i] = std::make_pair((int)INT_MAX, (int)INT_MIN);

            if (!notCopyToExpr)
            {
                for (int i = 0; i < sizesExpr.size(); ++i)
                {
                    sizesExpr[i].first.second.first = sizes[i].first;
                    sizesExpr[i].second.second.first = sizes[i].second;
                }
            }
        }

        bool IsOmpThreadPrivate() const { return ompThreadPrivate; }

        ~Array() 
        {
            for (auto &templ : templateInfo)
                delete templ.second;
        }
    };

    
    struct UnaryAccess
    {
        UnaryAccess()
        {
            line = -1;
            type = -1;
            underFunctionPar = -1;
            fName = "";
            count = 0;
        }

        UnaryAccess(const PAIR<int, char>& info)
        {
            line = info.first;
            type = info.second;
            underFunctionPar = -1;
            fName = "";
            count = 1;
        }

        UnaryAccess(const PAIR<int, char>& info, const STRING &f, const int parN)
        {
            line = info.first;
            type = info.second;
            underFunctionPar = parN;
            fName = f;
            count = 1;
        }

        STRING PrintInfo() const
        {
            STRING out = "#" + std::to_string(count) + " of ";
            if (type == 0)
                out += "READ ";
            else if(type == 1)
                out += "WRITE ";
            else
                out += "UNKN ";
            out += "on line " + std::to_string(line);
            if (underFunctionPar != -1)
                out += " in '#" + std::to_string(underFunctionPar + 1) + "' par of function call '" + fName + "'";
            return out;
        }

        bool operator==(const UnaryAccess &left) const
        {
            return (line == left.line && type == left.type && 
                    underFunctionPar == left.underFunctionPar && fName == left.fName);
        }

        bool operator!=(const UnaryAccess& left) const
        {
            return !(*this == left);
        }

        int line;
        int type; // R/W -> 0, 1
        int underFunctionPar;
        STRING fName;
        int count;
    };

    class ArrayAccessInfo
    {
    private:
        MAP<STRING, MAP<int, VECTOR<UnaryAccess>>> accessPatterns; // file -> MAP<LINE, info>
    public:
        void AddAccessInfo(const STRING& file, const PAIR<int, char> &info, const STRING fName = "", int underParN = -1)
        {
            auto it = accessPatterns.find(file);
            if (it == accessPatterns.end())
                it = accessPatterns.insert(it, std::make_pair(file, MAP<int, VECTOR<UnaryAccess>>()));

            bool found = false;
            UnaryAccess toAdd;
            if (underParN == -1)
                toAdd = UnaryAccess(info);
            else
                toAdd = UnaryAccess(info, fName, underParN);

            auto itMap = it->second.find(info.first);
            if (itMap == it->second.end())
                it->second[info.first].push_back(toAdd);
            else
            {
                for (int z = 0; z < itMap->second.size(); ++z)
                {
                    if (itMap->second[z] == toAdd)
                    {
                        found = true;
                        itMap->second[z].count++;
                        break;
                    }
                }

                if (found == false)
                {
                    if (underParN == -1)
                        itMap->second.push_back(toAdd);
                    else
                        itMap->second.push_back(toAdd);
                }
            }
        }

        void checkAndUpdate(const MAP<STRING, FuncInfo*>& allFuncs);
        const MAP<STRING, MAP<int, VECTOR<UnaryAccess>>>& GetAllAccessInfo() const { return accessPatterns; }
        const MAP<int, VECTOR<UnaryAccess>>* GetAccessInfoByFile(const STRING &file) const 
        {            
            auto it = accessPatterns.find(file);
            if (it == accessPatterns.end())
                return NULL;
            else
                return &(it->second); 
        }
    };

    void printArrayInfo(const STRING &file, const MAP<std::tuple<int, STRING, STRING>, PAIR<Array*, ArrayAccessInfo*>> &declaredArrays);
    void fixTypeOfArrayInfoWithCallGraph(MAP<std::tuple<int, STRING, STRING>, PAIR<Array*, ArrayAccessInfo*>>& declaredArrays, const MAP<STRING, FuncInfo*>& allFuncs);
}
#undef VECTOR
#undef STRING
#undef PAIR
#undef MAP
#undef SET
#undef TO_STR