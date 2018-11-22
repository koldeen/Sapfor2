#include "../Utils/leak_detector.h"

#include <cstdio>
#include <map>
#include <string>
#include <algorithm>

#include "dvm.h"
#include "verifications.h"

#include "../ParallelizationRegions/ParRegions.h"
#include "../Utils/utils.h"
#include "../Utils/SgUtils.h"
#include "../Utils/errors.h"

using std::vector;
using std::map;
using std::pair;
using std::string;
using std::make_pair;
using std::set;

bool EndDoLoopChecker(SgFile *file, vector<Messages> &currMessages)
{
    int funcNum = file->numberOfFunctions();
    bool checkOK = true;

    for (int i = 0; i < funcNum; ++i)
    {
        SgStatement *st = file->functions(i);
        SgStatement *lastNode = st->lastNodeOfStmt();

        while (st != lastNode)
        {
            currProcessing.second = st;
            if (st == NULL)
            {
                __spf_print(1, "internal error in analysis, parallel directives will not be generated for this file!\n");
                break;
            }

            if (st->variant() == CONTAINS_STMT)
                break;

            if (st->variant() == FOR_NODE)
            {
                SgForStmt *currSt = (SgForStmt*)st;
                if (currSt->isEnddoLoop() == 0)
                {
                    __spf_print(1, "  ERROR: Loop on line %d does not have END DO\n", st->lineNumber());
                    currMessages.push_back(Messages(ERROR, st->lineNumber(), "This loop does not have END DO format", 1018));
                    checkOK = false;
                }
            }
            st = st->lexNext();
        }
    }
    return checkOK;
}
 
bool DvmDirectiveChecker(SgFile *file, map<string, vector<int>> &errors, const int keepDvmDirectives, const int ignoreDvmChecker)
{
    if (keepDvmDirectives != 0)
        return true;

    int funcNum = file->numberOfFunctions();
    bool checkOK = true;
    __spf_print(1, "  ignoreDvmChecker = %d\n", ignoreDvmChecker);

    for (int i = 0; i < funcNum; ++i)
    {
        SgStatement *st = file->functions(i);
        SgStatement *lastNode = st->lastNodeOfStmt();

        for ( ; st != lastNode; st = st->lexNext())
        {
            currProcessing.second = st;
            if (st->variant() == CONTAINS_STMT)
                break;

            if (isDVM_stat(st) && (st->variant() != DVM_INTERVAL_DIR && st->variant() != DVM_ENDINTERVAL_DIR))
            {
                errors[st->fileName()].push_back(st->lineNumber());
                checkOK = false;
            }
        }
    }

    return checkOK;
}

bool EquivalenceChecker(SgFile *file, const string &fileName, const vector<ParallelRegion*> &regions, map<string, vector<Messages>> &currMessages)
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
            currProcessing.second = st;
            lastLine = st->lineNumber();
            if (st == NULL)
            {
                __spf_print(1, "internal error in analysis, parallel directives will not be generated for this file!\n");
                break;
            }

            if ((st->variant() == EQUI_LIST) || (st->variant() == EQUI_STAT))
            {
                bool needToReport = false;
                if (getRegionByLine(regions, st->fileName(), lastLine))
                {
                    checkOK = false;
                    needToReport = true;
                }
                else
                    needToReport = true;

                if (needToReport)
                {
                    __spf_print(1, "The equivalence operator is not supported yet at line %d of file %s\n", st->lineNumber(), st->fileName());
                    currMessages[st->fileName()].push_back(Messages(WARR, st->lineNumber(), "An equivalence operator is not supported yet", 1038));
                }
            }

            st = st->lexNext();
        }
    }
    return checkOK;
}

bool CommonBlockChecker(SgFile *file, const string &fileName, const map<string, CommonBlock> &commonBlocks, vector<Messages> &currMessages)
{
    bool checkOK = true;

    for (auto block : commonBlocks)
    {
        auto vars = block.second.getVariables();

        for (int i = 0; i < vars.size(); i++)
        {
            int pos = vars[i].getPosition();
            varType type = vars[i].getType();

            //only this file
            bool needToSkip = true;
            const CommonVariableUse *currUse = NULL;
            for (auto &elem : vars[i].getAllUse())
            {
                if (elem.getFile() == file)
                {
                    needToSkip = false;
                    currUse = &elem;
                }
            }

            if (needToSkip)
                continue;

            for (int j = i + 1; j < vars.size(); j++)
            {
                bool needToReport = false;
                auto typeMessage = NOTE;

                if ((vars[j].getPosition() == pos) &&
                    ((vars[j].getType() == ARRAY && type != ARRAY) || (vars[j].getType() != ARRAY && type == ARRAY)))
                {
                    DIST::Array *array = NULL;
                    if (vars[j].getType() == ARRAY)
                        array = getArrayFromDeclarated(vars[j].getDeclarated(), vars[j].getName());
                    else
                        array = getArrayFromDeclarated(vars[i].getDeclarated(), vars[i].getName());

                    if (array == NULL)
                        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

                    if (array->GetNonDistributeFlag())
                        typeMessage = WARR;
                    else
                    {
                        checkOK = false;
                        typeMessage = ERROR;
                    }
                    needToReport = true;
                }
                else if (vars[j].getPosition() == pos && vars[j].getType() != type)
                {
                    typeMessage = WARR;
                    needToReport = true;
                }

                if (needToReport)
                {
                    string message;
                    __spf_printToBuf(message, "Variables '%s' and '%s' in one storage association (common block '%s') have different types",
                        vars[i].getName().c_str(), vars[j].getName().c_str(), block.first.c_str());
                    __spf_print(1, "%s\n", message.c_str());

                    const int line = currUse->getDeclaratedPlace()->lineNumber();
                    currMessages.push_back(Messages(typeMessage, line, message, 1039));
                }
            }
        }
    }
    
    return checkOK;
}
