#pragma once

#include <vector>
#include <string>
#include "dvm.h"

SgExpression* createAndSetNext(const int side, const int variant, SgExpression *p);
std::vector<SgExpression*> genSubscripts(const std::vector<std::pair<int, int>> &shadowRenew, const std::vector<std::pair<int, int>> &shadowRenewShifts);
std::pair<SgExpression*, SgExpression*> genShadowSpec(SgFile *file, const std::pair<std::string, const std::vector<std::pair<int, int>>> &shadowSpecs);
void correctShadowSpec(SgExpression *spec, const std::vector<std::pair<int, int>> &shadowSpecs);