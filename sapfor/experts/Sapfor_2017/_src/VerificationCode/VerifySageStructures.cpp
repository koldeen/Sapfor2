#include "../leak_detector.h"

#include <cstdio>
#include <cstring>
#include <vector>
#include <set>
#include <string>

#include "dvm.h"
#include "verifications.h"
#include "../utils.h"

int VerifyFile(SgFile *file)
{
    int funcNum = file->numberOfFunctions();

    int isError = 0;
    for (int i = 0; i < funcNum; ++i)
    {
        SgStatement *st = file->functions(i);
        SgStatement *lastNode = st->lastNodeOfStmt();

        startLineControl(file->filename(), st->lineNumber(), lastNode->lineNumber());
        while (st != lastNode)
        {
            if (st == NULL)
            {
                print(1, "Found errors in Sage structures in file %s, -1\n", file->filename());
                isError = -1;
                break;
            }
            else if (checkThisLine(st->fileName(), st->lineNumber()) == -1)
            {
                print(1, "Found errors in Sage structures in file %s, -2\n", file->filename());
                isError = -2;
                break;
            }
            st = st->lexNext();
        }

        if (isError != 0)
            break;
    }

    return isError;
}