#pragma once
#include <set>
#include <vector>
#include <map>
#include <string>

bool inliner(const std::string& fileName, const std::string& funcName, const int lineNumber, const std::map<std::string, std::vector<FuncInfo*>>& allFuncInfo, std::map<std::string, std::vector<Messages>>& SPF_messages, std::map<SgStatement*, std::set<SgSymbol*>>& newSymbsToDeclare, int deepLvl = 0);
bool inliner(const std::string& allInFunc, const std::map<std::string, std::vector<FuncInfo*>>& allFuncInfo, std::map<std::string, std::vector<Messages>>& SPF_messages, std::map<SgStatement*, std::set<SgSymbol*>>& newSymbsToDeclare, int deepLvl = 0);
void createDeclarations(const std::map<SgStatement*, std::set<SgSymbol*>>& newSymbsToDeclare);