#pragma once

bool inliner(const std::string& fileName, const std::string& funcName, const int lineNumber, const std::map<std::string, std::vector<FuncInfo*>>& allFuncInfo, std::map<std::string, std::vector<Messages>>& SPF_messages);
