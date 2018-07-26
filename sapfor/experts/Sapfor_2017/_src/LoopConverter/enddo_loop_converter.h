#pragma once

#include "../Utils/errors.h"

void ConverToEndDo(SgFile *file, std::vector<Messages> &messagesForFile);

struct SearchInfo
{
    SgExpression *expr;
    SgStatement *lastSt;
    bool none;
};