#include "ParRegions_func.h"
#include "extend_decrease_reg.h"

using std::map;
using std::pair;
using std::set;
using std::vector;
using std::string;
using std::to_string;
using std::make_pair;

static inline void insertParRegDir(SgStatement *start, const string &regName)
{
    // !SPF PARALLEL_REG regName
    SgStatement *regSt = new SgStatement(SPF_PARALLEL_REG_DIR);
    SgSymbol *regSymb = new SgSymbol(SPF_REGION_NAME, regName.c_str());
    regSt->setSymbol(*regSymb);
    start->insertStmtBefore(*regSt, *start->controlParent());
}

static inline void insertEndParReg(SgStatement *end)
{
    // !SPF END PARALLEL_REG
    SgStatement *regSt = new SgStatement(SPF_END_PARALLEL_REG_DIR);
    end->insertStmtAfter(*regSt, *end->controlParent());
}

static inline void insertParRegDirs(SgStatement *start, SgStatement *end, const string &regName)
{
    insertParRegDir(start, regName);
    insertEndParReg(end);
}

static inline void removeSt(SgStatement *st)
{
    if (st)
    {
        SgStatement *prev = st->lexPrev();
        SgStatement *next = st->lexNext();

        if (prev)
            prev->setLexNext(*next);
    }
}

bool extendDecreaseReg(const string &fileName,
                       const int startLine,
                       const int endLine,
                       const string &regName,
                       const vector<ParallelRegion*> &regions,
                       vector<Messages> &messagesForFile,
                       const bool toDelete)
{
    bool error = false;

    if (SgFile::switchToFile(fileName) != -1)
    {
        SgStatement *begin = SgStatement::getStatementByFileAndLine(fileName, startLine);
        SgStatement *end = SgStatement::getStatementByFileAndLine(fileName, endLine);

        // TODO: check user lines
        if (!(startLine < endLine && (begin->controlParent() == end->controlParent() || begin == end->controlParent())))
        {
            __spf_print(1, "bad lines position: expected lines with the same control parent on line %d\n", startLine);

            string message;
            __spf_printToBuf(message, "bad lines position: expected lines with the same control parent");
            messagesForFile.push_back(Messages(ERROR, startLine, message, 1001));

            error = true;
        }

        auto reg = getRegionByName(regions, regName);

        if (!reg)
        // can only add new region with user's fragment
        {
            if (!toDelete)
                insertParRegDirs(begin, end, regName);
            else
            {
                __spf_print(1, "bad user option: you can only create region '%s' with lines %d-%d on line %d\n", regName.c_str(), startLine, endLine, startLine);

                string message;
                __spf_printToBuf(message, "bad user option: you can only create region '%s' with lines %d-%d on line %d\n", regName.c_str(), startLine, endLine);
                messagesForFile.push_back(Messages(ERROR, startLine, message, 100500));

                error = true;
            }
        }
        else
        // can extend or decrease
        {
            const ParallelRegionLines *beginLines = NULL, *endLines = NULL;
            vector<const ParallelRegionLines*> internalLines;
            auto regLines = reg->GetLines(fileName);

            for (auto &lines : *regLines)
            {
                if (!lines.isImplicit())
                {
                    if (startLine > lines.lines.first && startLine < lines.lines.second)
                        beginLines = &lines;

                    if (endLine > lines.lines.first && endLine < lines.lines.second)
                        endLines = &lines;

                    if (startLine < lines.lines.first && endLine > lines.lines.second)
                        internalLines.push_back(&lines);
                }
            }

            for (auto &intLines : internalLines)
            {
                removeSt(intLines->stats.first->lexPrev());
                removeSt(intLines->stats.first->lexNext());
            }

            bool localError = false;
            int errorLine;

            if (!toDelete)
            {
                if (!beginLines)
                {
                    if (end->controlParent() == beginLines->stats.first->controlParent())
                    {
                        insertEndParReg(end);
                        removeSt(beginLines->stats.second->lexNext());
                    }
                    else
                    {
                        errorLine = endLine;
                        localError = true;
                    }
                }

                if (!endLines)
                {
                    if (begin->controlParent() == endLines->stats.first->controlParent())
                    {
                        insertParRegDir(begin, regName);
                        removeSt(endLines->stats.first->lexPrev());
                    }
                    else
                    {
                        errorLine = startLine;
                        localError = true;
                    }
                }
            }
            else
            {
                if (!beginLines)
                {
                    if (begin->controlParent() == beginLines->stats.first->controlParent())
                    {
                        insertEndParReg(begin->lexPrev());
                        removeSt(beginLines->stats.second->lexNext());
                    }
                    else
                    {
                        errorLine = startLine;
                        localError = true;
                    }
                }

                if (!endLines)
                {
                    if (end->controlParent() == endLines->stats.first->controlParent())
                    {
                        insertParRegDir(end, regName);
                        removeSt(endLines->stats.first->lexPrev());
                    }
                    else
                    {
                        errorLine = endLine;
                        localError = true;
                    }
                }
            }

            if (localError)
            {
                __spf_print(1, "bad lines position: expected lines with the same control parent on line %d\n", errorLine);

                string message;
                __spf_printToBuf(message, "bad lines position: expected lines with the same control parent");
                messagesForFile.push_back(Messages(ERROR, errorLine, message, 1001));

                error = true;
            }
        }
    }
    else
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

    return error;
}
