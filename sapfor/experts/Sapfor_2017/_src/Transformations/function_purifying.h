#pragma once

void intentInsert(const std::vector<FuncInfo*>& allFuncInfo);
void intentInsert(FuncInfo* func);
void setPureStatus(const std::map<std::string, std::vector<FuncInfo*>>& allFuncInfo);

void commonTransfer(const std::map<std::string, std::vector<FuncInfo*>>& allFuncInfo, const std::map<std::string, CommonBlock>& commonBlocks);
void saveTransfer(const std::map<std::string, std::vector<FuncInfo*>>& allFuncInfo);
void moduleTransfer(const std::map<std::string, std::vector<FuncInfo*>>& allFuncInfo);