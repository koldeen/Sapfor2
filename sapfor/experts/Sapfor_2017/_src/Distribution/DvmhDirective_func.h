#pragma once

#include <vector>
#include <string>
#include "dvm.h"

std::pair<SgExpression*, SgExpression*> genShadowSpec(SgFile *file, const std::pair<std::string, const std::vector<std::pair<int, int>>> &shadowSpecs);
void correctShadowSpec(SgExpression *spec, const std::vector<std::pair<int, int>> &shadowSpecs);