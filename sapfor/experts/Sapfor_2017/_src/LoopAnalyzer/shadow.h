#pragma once

#include "dvm.h"
#include <map>
#include <vector>
#include <string>
#include <set>

struct ShadowNode
{
    void *dir;
    //                                  origin_Name   uniqName                   bounds
    std::vector<std::pair<std::pair<std::string, std::string>, std::vector<std::pair<int, int>>>> shadows;
    std::set<std::string> corner;

    //                                  origin_Name   uniqName                   bounds
    std::vector<std::pair<std::pair<std::string, std::string>, std::vector<std::pair<int, int>>>> newShadows;
    std::set<std::string> newCorner;

    std::vector<std::pair<ShadowNode*, std::set<std::string>>> next;
    std::vector<ShadowNode*> prev;

    ShadowNode(void *dir) : dir(dir) { }
    void moveShadow(std::pair<std::pair<std::string, std::string>, std::vector<std::pair<int, int>>> &shadow, std::set<std::string> &corner);
};