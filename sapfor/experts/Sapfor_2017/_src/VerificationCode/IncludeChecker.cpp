#include "../leak_detector.h"

#include <cstdio>
#include <cstring>
#include <vector>
#include <set>
#include <string>

#include "dvm.h"
#include "verifications.h"
#include "../utils.h"
#include "../SgUtils.h"
#include "../Distribution/DvmhDirective.h"

using std::vector;
using std::string;
using std::set;
using std::pair;

void IncludeChecker(SgFile *file, const string &fileName, set<pair<string, int>> &errors)
{
    int funcNum = file->numberOfFunctions();

    for (int i = 0; i < funcNum; ++i)
    {
        SgStatement *st = file->functions(i);
        SgStatement *lastNode = st->lastNodeOfStmt();
        int lastLine = 1;
        while (st != lastNode)
        {
            currProcessing.second = st;
            if (st == NULL)
            {
                __spf_print(1, "internal error in analysis, parallel directives will not be generated for this file!\n");
                break;
            }

            if (st->fileName() == fileName)
                lastLine = st->lineNumber();

            if (isSgExecutableStatement(st) && !isSPF_stat(st) && !isDVM_stat(st))            
                if (st->fileName() != fileName)
                    errors.insert(std::make_pair(st->fileName(), lastLine));

            st = st->lexNext();
        }
    }
}