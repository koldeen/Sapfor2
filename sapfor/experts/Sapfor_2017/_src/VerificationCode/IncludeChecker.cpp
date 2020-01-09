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
using std::wstring;
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

                    wstring currE, currR;
                    __spf_printToLongBuf(currE, L"Include '%s' has executable operators", to_wstring(st->fileName()).c_str());
#ifdef _WIN32
                    __spf_printToLongBuf(currR, R52, to_wstring(st->fileName()).c_str());
#endif
                    currMessages.push_back(Messages(ERROR, lastLine, currR, currE, 1019));
                    checkOK = false;
                }
            }

            st = st->lexNext();
        }
    }

    return checkOK;
}