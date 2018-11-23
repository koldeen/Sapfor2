#pragma once

#include <vector>
#include <string>
#include <set>
#include "dvm.h"
#include "../Utils/types.h"

SgExpression* createAndSetNext(const int side, const int variant, SgExpression *p);
std::vector<SgExpression*> genSubscripts(const std::vector<std::pair<int, int>> &shadowRenew, const std::vector<std::pair<int, int>> &shadowRenewShifts);
std::pair<SgExpression*, SgExpression*> genShadowSpec(SgFile *file, const std::pair<std::string, const std::vector<std::pair<int, int>>> &shadowSpecs);
void correctShadowSpec(SgExpression *spec, const std::vector<std::pair<int, int>> &shadowSpecs);
std::vector<std::tuple<DIST::Array*, int, std::pair<int, int>>> getAlignRuleWithTemplate(DIST::Array *array, const std::map<DIST::Array*, std::set<DIST::Array*>> &arrayLinksByFuncCalls, DIST::GraphCSR<int, double, attrType> &reducedG, const DIST::Arrays<int> &allArrays, const int regionId);