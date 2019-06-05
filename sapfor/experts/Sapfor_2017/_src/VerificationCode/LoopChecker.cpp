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
using std::wstring;
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
            currProcessing.second = st->lineNumber();
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
#if _WIN32
                    currMessages.push_back(Messages(ERROR, st->lineNumber(), L"Данный цикл не в END DO формате", L"This loop does not have END DO format", 1018));
#endif                    
                    checkOK = false;
                }
            }

            if (st->variant() == FORALL_NODE || st->variant() == FORALL_STAT)
            {
                __spf_print(1, "  ERROR: Loop on line %d does not have END DO\n", st->lineNumber());
#if _WIN32
                currMessages.push_back(Messages(ERROR, st->lineNumber(), L"Данный цикл не в END DO формате", L"This loop does not have END DO format", 1018));
#endif          
                checkOK = false;
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
            currProcessing.second = st->lineNumber();
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
            currProcessing.second = st->lineNumber();
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
#if _WIN32
                    currMessages[st->fileName()].push_back(Messages(WARR, st->lineNumber(), L"Оператор EQUIVALENCE не поддерживается на данный момент", L"An equivalence operator is not supported yet", 1038));
#endif
                }
            }

            if (st->variant() == PAUSE_NODE)
            {
                checkOK = false;
                __spf_print(1, "The PAUSE operator is not supported yet at line %d of file %s\n", st->lineNumber(), st->fileName());
#if _WIN32
                currMessages[st->fileName()].push_back(Messages(ERROR, st->lineNumber(), L"Оператор PAUSE является запрещенным в параллельной программе", L"An PAUSE operator is deprecated to parallel", 1038));
#endif
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
                    wstring messageE, messageR;
                    __spf_printToLongBuf(messageE, L"Variables '%s' and '%s' in one storage association (common block '%s') have different types (files - %s:%d and %s:%d)",
                        to_wstring(vars[i].getName()).c_str(), to_wstring(vars[j].getName()).c_str(), to_wstring(block.first).c_str(),
                        to_wstring(vars[i].getDeclarated()->fileName()).c_str(), vars[i].getDeclarated()->lineNumber(),
                        to_wstring(vars[j].getDeclarated()->fileName()).c_str(), vars[j].getDeclarated()->lineNumber());
#if _WIN32
                    __spf_printToLongBuf(messageR, L"Переменные '%s' и '%s' находятся в одной области ассоциации (common block '%s'), но имеют разные типы (файлы - %s:%d и %s:%d)",
                        to_wstring(vars[i].getName()).c_str(), to_wstring(vars[j].getName()).c_str(), to_wstring(block.first).c_str(),
                        to_wstring(vars[i].getDeclarated()->fileName()).c_str(), vars[i].getDeclarated()->lineNumber(),
                        to_wstring(vars[j].getDeclarated()->fileName()).c_str(), vars[j].getDeclarated()->lineNumber());
#endif
                    const int line = currUse->getDeclaratedPlace()->lineNumber();
                    currMessages.push_back(Messages(typeMessage, line, messageR, messageE, 1039));
                }
            }
        }
    }
    
    return checkOK;
}

bool FunctionsChecker(SgFile *file, map<string, pair<string, int>> &funcNames, map<string, vector<Messages>> &currMessages)
{
    int funcNum = file->numberOfFunctions();
    bool checkOK = true;

    for (int i = 0; i < funcNum; ++i)
    {
        SgStatement *st = file->functions(i);
        SgStatement *lastNode = st->lastNodeOfStmt();
        int lastLine = 1;
        
        if (st->controlParent()->variant() == GLOBAL)
        {
            string funcName = st->symbol()->identifier();
            auto it = funcNames.find(funcName);
            if (it == funcNames.end())
                funcNames[funcName] = make_pair(file->filename(), st->lineNumber());
            else
            {
                __spf_print(1, "the same function name in different places was found: func %s, palces %s:%d and %s:%d\n", 
                            it->first.c_str(), it->second.first.c_str(), it->second.second, file->filename(), st->lineNumber());
#if _WIN32
                wstring messageE, messageR;
                __spf_printToLongBuf(messageE, L"Function '%s' was declarated in more that one palce: '%s':%d и '%s':%d",
                                                to_wstring(funcName).c_str(), to_wstring(it->second.first).c_str(),
                                                it->second.second, to_wstring(file->filename()).c_str(), st->lineNumber());

                __spf_printToLongBuf(messageR, L"Функция '%s' с одинаковым именем была объявлена в более, чем одном месте: в файле '%s':%d и '%s':%d",
                                                to_wstring(funcName).c_str(), to_wstring(it->second.first).c_str(), 
                                                it->second.second, to_wstring(file->filename()).c_str(), st->lineNumber());

                currMessages[st->fileName()].push_back(Messages(ERROR, st->lineNumber(), messageR, messageE, 1048));
                currMessages[it->second.first].push_back(Messages(ERROR, it->second.second, messageR, messageE, 1048));
#endif
                checkOK = false;
            }
        }
    }

    return checkOK;
}
