#pragma once

#include "../Utils/errors.h"

void ConverToEndDo(SgFile *file, std::vector<Messages> &messagesForFile);
std::vector<SgStatement*> createIfConditions(std::stack<SgExpression*>& conds, std::stack<SgStatement*>& ifBlocks, SgStatement *control);

struct SearchInfo
{
    SgExpression *expr;
    SgStatement *lastSt;
    bool none;
};