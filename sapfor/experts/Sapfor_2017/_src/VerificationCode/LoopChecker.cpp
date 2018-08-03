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
                errors[st->fileName()].push_back(st->lineNumber());
        }
    }
    return checkOK;
}

bool EquivalenceChecker(SgFile *file, const string &fileName, vector<ParallelRegion*> &regions, vector<Messages> &currMessages)
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
				if (getRegionByLine(regions, st->fileName(), lastLine) == NULL) {
					checkOK = false;
					currMessages.push_back(Messages(ERROR, st->lineNumber(), "An equivalence operator at this line is not supported yet", 1038));
                }
				else
					__spf_print(1, "The equivalence operator is not supported yet\n");
			}

            st = st->lexNext();
        }
    }
    return checkOK;
}

bool CommonBlockChecker(SgFile *file, const string &fileName, const map<string, CommonBlock> &commonBlocks, vector<Messages> &currMessages)
{
	bool checkOK = true;

    for (auto block = commonBlocks.begin(); block != commonBlocks.end(); ++block)
    {
		auto vars = block->second.getVariables();

		for (auto var = vars.begin(); var != vars.end(); ++var)
		{
			int pos = var->getPosition();
			varType type = var->getType();

			for (auto anotherVar = vars.begin(); var != vars.end(); ++anotherVar)
			{
				if ((anotherVar->getPosition() == pos) &&
					((anotherVar->getType() == ARRAY && type != ARRAY) || (anotherVar->getType() != ARRAY && type == ARRAY)))
				{
					checkOK = false;
					// currMessages.push_back(Messages(ERROR, var->getName(), anotherVar->getName(), block->first, "Variables in one storage association (common block) have different types", 1039));
					__spf_print(1, "Variables '%s' and '%s' in one storage association (common block '%s') have different types", var->getName(), anotherVar->getName(), block->first);
				}
				else if (anotherVar->getPosition() == pos && anotherVar->getType() != type)
					__spf_print(1, "Variables '%s' and '%s' in one storage association (common block '%s') have different types", var->getName(), anotherVar->getName(), block->first);

			}
		}
    }
	
    return checkOK;
}

