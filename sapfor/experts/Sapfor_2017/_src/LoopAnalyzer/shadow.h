#pragma once

#include <map>
#include <vector>
#include <string>
#include <set>

struct FuncInfo;
struct LoopGraph;
struct ShadowNode;

typedef enum node : int { PARALLEL_DIR = 0, FUNCTION_CALL, PROCEDURE_CALL, STOP, RETURN, START, END } nodeType;

struct ShadowElement
{
    std::vector<std::pair<int, int>> bounds;
    std::map<FuncInfo*, std::string> origNameByProc;
    bool corner;

    ShadowElement() { }
    ShadowElement(const std::vector<std::pair<int, int>>& bounds,
                  const std::pair<FuncInfo*, std::string>& origName, 
                  bool corner) : bounds(bounds), corner(corner)
    {
        origNameByProc[origName.first] = origName.second;
    }

    bool operator==(const ShadowElement& left) const
    {
        return bounds == left.bounds && origNameByProc == left.origNameByProc && corner == left.corner;
    }
};

struct NextNode
{
    ShadowNode* shNode;
    std::set<DIST::Array*> writeTo;
    bool isBackWard;

    NextNode() { }
    NextNode(ShadowNode* shNode, const std::set<DIST::Array*>& writeTo, bool isBackWard = false)
        : shNode(shNode), writeTo(writeTo), isBackWard(isBackWard)
    { }

    bool operator==(const NextNode& left) const
    {
        return (shNode == left.shNode) && (writeTo == left.writeTo);
    }

    bool operator<(const NextNode& left) const
    {
        return shNode < left.shNode;
    }
};

struct PrevNode
{
    ShadowNode* shNode;
    bool* isBackWard;

    PrevNode() { }
    PrevNode(ShadowNode* shNode, bool* isBackWard = NULL)
        : shNode(shNode), isBackWard(isBackWard)
    { }

    bool operator==(const PrevNode& left) const
    {
        return shNode == left.shNode;
    }
};

struct ShadowNode
{
    void *info;
    nodeType type;

    //file and line
    std::pair<FuncInfo*, int> location;

    std::map<DIST::Array*, std::vector<ShadowElement>> shadows;
    std::map<DIST::Array*, std::vector<ShadowElement>> newShadows;

    std::vector<NextNode> next;
    std::vector<PrevNode> prev;

    ShadowNode(void * info, nodeType type, FuncInfo* func, int line) : info(info), type(type), location(std::make_pair(func, line)) { }

    void MoveShadow(const std::pair<DIST::Array*, std::vector<ShadowElement>>& shadowAdd)
    {
        for (auto& elem : shadowAdd.second)
            newShadows[shadowAdd.first].push_back(elem);
    }

    void MergeNewShadowElements()
    {
        for (auto& elemByArray : newShadows)
        {
            ShadowElement newElems;
            for (int z = 0; z < elemByArray.second.size(); ++z)
            {
                if (z == 0)
                    newElems = elemByArray.second[0];
                else
                {
                    newElems.corner |= elemByArray.second[z].corner;
                    for (auto& fElem : elemByArray.second[z].origNameByProc)
                        newElems.origNameByProc[fElem.first] = fElem.second;
                    int k = 0;
                    for (auto& bound : elemByArray.second[z].bounds)
                    {
                        newElems.bounds[k].first = std::max(newElems.bounds[k].first, bound.first);
                        newElems.bounds[k].second = std::max(newElems.bounds[k].second, bound.second);
                        ++k;
                    }
                }
            }

            if (elemByArray.second.size())
            {
                elemByArray.second.clear();
                elemByArray.second.push_back(newElems);
            }
        }
    }
};

void GroupShadow(const std::map<std::string, std::vector<FuncInfo*>>& funcs, 
                 const std::map<std::string, std::vector<LoopGraph*>>& loops,
                 const DIST::Arrays<int>& allArrays, 
                 const std::map<DIST::Array*, std::set<DIST::Array*>>& arrayLinksByFuncCalls);
