#include "../Utils/leak_detector.h"
#include "dvm.h"

#include "./gcov_info.h"
#include "./gCov_parser_func.h"
#include "./createParallelRegions.h"

#include <stdio.h>
#include <map>
#include <iostream>

using namespace std;

int perform_time(SgFile *file, SgStatement *src,  map<int, Gcov_info> &gCovInfo, int rec_level)
{
    SgStatement* stmt = src;
    Gcov_info info = gCovInfo[stmt->lineNumber()];
    int count = 0;

    switch (stmt->variant()) 
    {  
        case PROC_CALL:
        {
            // PROC_HEDR
            SgCallStmt* call = (SgCallStmt*)src;
            //  SgStatement* tmp = call->
            //  while (tmp->variant() != RETURN_STAT)
            {

            }
            break;
        }
        case IF_NODE:
        case LOGIF_NODE:
        case ELSEIF_NODE:
        {
            SgIfStmt* ifSt = (SgIfStmt*)src;
            SgStatement* tmp = ifSt->trueBody();
            int t = 0;
            while (tmp->variant() != CONTROL_END)
            {
                t += perform_time(file, tmp, gCovInfo);
                tmp = tmp->lexNext();
            }
            count += (info.getBranches()[0].getPercent()) * t;
            t = 0;
            tmp = ifSt->falseBody();
            while (tmp && tmp->variant() != CONTROL_END)
            {
                t += perform_time(file, tmp, gCovInfo);
                tmp = tmp->lexNext();
            }
            count += (info.getBranches()[1].getPercent()) * t;
            break;
        }
        case WHILE_NODE:
        {
            SgWhileStmt* whileSt = (SgWhileStmt*)src;
            SgStatement* tmp = whileSt->body();
            while (tmp->variant() != CONTROL_END)
            {
                count += perform_time(file, tmp, gCovInfo);
                tmp = tmp->lexNext();
            }
            break;
        }
        case FOR_NODE:
        {
            SgForStmt* forSt = (SgForStmt*)src;
            SgStatement* tmp = forSt->body();
            while (tmp->variant() != CONTROL_END)
            {
                count += perform_time(file, tmp, gCovInfo);
                tmp = tmp->lexNext();
            }
            break;
        }
        default:
            count += info.getExecutedCount();
    }

    return count;
}


// void createParallelRegions(file, file->firstStatement(), getObjectForFileFromMap(file_name, gCovInfo)) 
// {}
