#pragma once

#include <map>
#include <vector>
#include <string>
#include <set>

struct FuncInfo;
struct LoopGraph;

struct ShadowNode
{
    //parallel directive
    void *dir;
    //file and line
    std::pair<FuncInfo*, int> location;

    //                                                        bounds
    std::vector<std::pair<DIST::Array*, std::vector<std::pair<int, int>>>> shadows;
    std::set<DIST::Array*> corners;

    //                                                        bounds
    std::vector<std::pair<DIST::Array*, std::vector<std::pair<int, int>>>> newShadows;
    std::set<DIST::Array*> newCorners;

    std::vector<std::pair<ShadowNode*, std::set<DIST::Array*>>> next;
    std::vector<ShadowNode*> prev;

    ShadowNode(void *dir, FuncInfo* func, int line) : dir(dir), location(std::make_pair(func, line)) { }

    void MoveShadow(std::pair<DIST::Array*, std::vector<std::pair<int, int>>>& shadowIn, std::set<DIST::Array*>& cornerIn)
    {
        bool found = false;
        for (auto& elem : newShadows)
        {
            if (elem.first == shadowIn.first)
            {
                for (int i = 0; i < elem.second.size(); ++i)
                {
                    elem.second[i].first = std::max(elem.second[i].first, shadowIn.second[i].first);
                    elem.second[i].second = std::max(elem.second[i].second, shadowIn.second[i].second);
                }
                CompliteCorner(shadowIn, cornerIn);
                found = true;
                break;
            }
        }

        if (!found)
        {
            newShadows.push_back(shadowIn);
            CompliteCorner(shadowIn, cornerIn);
        }
    }

    bool IsBackDirection(const std::pair<FuncInfo*, int>& toCmp)
    {
        //cmp procedures
        if (location.first != toCmp.first)
            return false;

        //cmp lines
        if (location.second > toCmp.second)
            return true;
        else
            return false;
    }

private:
    void CompliteCorner(std::pair<DIST::Array*, std::vector<std::pair<int, int>>>& shadowIn, std::set<DIST::Array*>& cornerIn)
    {
        auto it = cornerIn.find(shadowIn.first);
        if (it != cornerIn.end())
        {
            newCorners.insert(*it);
            cornerIn.erase(it);
        }
    }
};

void GroupShadow(const std::map<std::string, std::vector<FuncInfo*>>& funcs, 
                 const std::map<std::string, std::vector<LoopGraph*>>& loops,
                 const DIST::Arrays<int>& allArrays, 
                 const std::map<DIST::Array*, std::set<DIST::Array*>>& arrayLinksByFuncCalls);
