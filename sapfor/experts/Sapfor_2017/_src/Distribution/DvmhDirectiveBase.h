#pragma once

#include <vector>
#include <string>

typedef enum lang : int { LANG_C, LANG_F } language;
typedef enum dist : int { BLOCK, NONE } distType;

namespace Distribution
{    
    class Array;
}
namespace DIST = Distribution;

struct Directive
{
    lang langType;
    std::string file;
    int line;
    int col;

    Directive () { }
    Directive(const Directive &dir)
    {
        langType = dir.langType;
        file = dir.file;
        line = dir.line;
        col = dir.col;
    }
};

struct AlignRuleBase
{
public:
    static const std::vector<std::string> alignNames;

public:
    std::string GenRuleBase() const;
    std::string toString();

public:
    DIST::Array *alignArray;
    DIST::Array *alignWith;
    std::vector<std::pair<int, int>> alignRule;
    std::vector<std::pair<int, std::pair<int, int>>> alignRuleWith;
};

struct DistrVariantBase
{
public:
    std::vector<dist> distRule;

public:
    DistrVariantBase(const std::vector<dist> &distRule) : distRule(distRule) { }
    std::string GenRuleBase(const std::vector<int> &newOrder) const;
};
