#include "../Utils/leak_detector.h"

#include <cstdio>
#include <cstring>
#include <vector>
#include <set>
#include <string>

#include "dvm.h"
#include "verifications.h"
#include "../Utils/utils.h"
#include "../Utils/SgUtils.h"
#include "../Utils/errors.h"
#include "../Distribution/DvmhDirective.h"

using std::vector;
using std::string;
using std::set;
using std::pair;

bool IncludeChecker(SgFile *file, const string &fileName, vector<Messages> &currMessages)
{
    int funcNum = file->numberOfFunctions();
    bool checkOK = true;

    for (int i = 0; i < funcNum; ++i)
    {
        SgStatement *st = file->functions(i);
        SgStatement *lastNode = st->lastNodeOfStmt();
        int lastLine = 1;
        while (st != lastNode)
        {
            currProcessing.second = st->lineNumber();
            if (st == NULL)
            {
                __spf_print(1, "internal error in analysis, parallel directives will not be generated for this file!\n");
                break;
            }

            if (st->variant() == CONTAINS_STMT)
                break;

            if (st->fileName() == fileName)
                lastLine = st->lineNumber();

            if (isSgExecutableStatement(st) && !isSPF_stat(st) && !isDVM_stat(st))
            {
                if (st->fileName() != fileName)
                {
                    __spf_print(1, "  ERROR: include '%s' at line %d has executable operators\n", st->fileName(), lastLine);

                    string currM;
                    __spf_printToBuf(currM, "Include '%s' has executable operators", st->fileName());
                    currMessages.push_back(Messages(ERROR, lastLine, currM, 1019));
                    checkOK = false;
                }
            }

            st = st->lexNext();
        }
    }

    return checkOK;
}