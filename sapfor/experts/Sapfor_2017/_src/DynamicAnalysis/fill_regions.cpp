#include "../Utils/leak_detector.h"
#include "dvm.h"

#include "./gcov_info.h"
#include "./gCov_parser_func.h"
#include "./fill_regions.h"

#include <stdio.h>
#include <map>
#include <iostream>

using namespace std;

int perform_time(SgFile *file, SgStatement *src,  map<int, Gcov_info> &gCovInfo)
{
    SgStatement* stmt = src;
    Gcov_info info = gCovInfo[stmt->lineNumber()];
    int count = 0;

    switch (stmt->variant()) 
    {
        case IF_NODE:
        {
            SgIfStmt* ifSt = (SgIfStmt*)src;
            count += (info.getBranches()[0].getPercent()) * perform_time(file, ifSt->trueBody(), gCovInfo);
            count += (info.getBranches()[1].getPercent()) * perform_time(file, ifSt->falseBody(), gCovInfo);
            break;
        }
        case LOOP_NODE:
            // ??
        case WHILE_NODE:
        {
            SgWhileStmt* whileSt = (SgWhileStmt*)src;
            // ??
            count += perform_time(file, whileSt->body(), gCovInfo);
            break;
        }
        case FOR_NODE:
        {
            SgForStmt* forSt = (SgForStmt*)src;
            count += perform_time(file, forSt->body(), gCovInfo);
            break;
        }
        default:
            count += info.getExecutedCount();
    }

    return count;
}
