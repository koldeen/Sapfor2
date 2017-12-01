#pragma once

#include <string>
#include <set>
#include <map>

#include "AstWrapper.h"

bool isSPF_NoInline(SgStatement *stPrev);

template<typename fillType>
void fillPrivatesFromComment(SgStatement *st, std::set<fillType> &privates);

template<typename fillType>
void fillReductionsFromComment(SgStatement *st, std::map<std::string, std::set<fillType>> &reduction);

template<typename fillType>
void fillReductionsFromComment(SgStatement *st, std::map<std::string, std::set<std::tuple<fillType, fillType, int>>> &reduction);

template<typename fillType>
void fillShadowAcrossFromComment(const int type, SgStatement *st, std::vector<std::pair<std::pair<fillType, std::string>, std::vector<std::pair<int, int>>>> &data);

template<typename fillType>
void fillRemoteFromComment(SgStatement *st, std::map<std::pair<fillType, std::string>, Expression*> &remote, bool isFull = false);