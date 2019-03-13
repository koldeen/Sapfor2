#include "ParRegions_func.h"
#include "expand_extract_reg.h"

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

static bool checkIfLineIsImplicit(const ParallelRegion *reg, const string &fileName, const int line)
{
    if (reg)
    {
        auto regLines = reg->GetLines(fileName, line);
        if (regLines && regLines->isImplicit())
            return true; // error
    }

    return false;
}

bool expandExtractReg(const string &fileName,
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
        auto beginReg = getRegionByLine(regions, fileName, startLine);
        auto endReg = getRegionByLine(regions, fileName, endLine);

        // check user lines
        // 2. запрещено располагать N1 и N2 в неисполняемых операторах
        bool localError = false;
        int errorLine;

        if (!(isSgExecutableStatement(end) || end->variant() == ENTRY_STAT))
        {
            localError = true;
            errorLine = endLine;
        }

        if (!(isSgExecutableStatement(begin) || begin->variant() == ENTRY_STAT))
        {
            localError = true;
            errorLine = startLine;
        }
        
        if (localError)
        {
            __spf_print(1, "bad directive position on line %d: it can be placed only after all DATA statements\n", errorLine);
            
            string message;
            __spf_printToBuf(message, "bad directive position: it can be placed only after all DATA statements");
            messagesForFile.push_back(Messages(ERROR, errorLine, message, 1001));

            error = false;
        }

        // 1. N1 <= N2
        if (startLine > endLine)
        {
            __spf_print(1, "bad lines position: end line %d must be greater or equel begin line %d\n", endLine, startLine);

            string message;
            __spf_printToBuf(message, "bad lines position: end line %d must be greater or equel begin line %d", endLine, startLine);
            messagesForFile.push_back(Messages(ERROR, endLine, message, 1001));

            error = false;
        }

        // 2. запрещено располагать N1 и N2 во фрагментах разных ОР и неявных строках
        if (beginReg && endReg && beginReg != endReg)
        {
            __spf_print(1, "bad lines position: begin and end lines can not be placed at differect regions\n");

            string message;
            __spf_printToBuf(message, "bad lines position: begin and end lines can not be placed at differect regions");
            messagesForFile.push_back(Messages(ERROR, endLine, message, 1001));

            error = false;
        }

        localError = false;

        if (checkIfLineIsImplicit(endReg, fileName, endLine))
        {
            localError = true;
            errorLine = endLine;
        }

        if (checkIfLineIsImplicit(beginReg, fileName, startLine))
        {
            localError = true;
            errorLine = startLine;
        }

        if (localError)
        {
            __spf_print(1, "bad lines position on line %d: begin and end lines can not be placed at region implicit lines\n", errorLine);

            string message;
            __spf_printToBuf(message, "bad lines position: begin and end lines can not be placed at region implicit lines");
            messagesForFile.push_back(Messages(ERROR, errorLine, message, 1001));

            error = false;
        }

        // 3. при добавлении запрещено содержать внутри отрезка [N1,N2] фрагменты разных ОР
        const ParallelRegionLines *beginLines = NULL, *endLines = NULL;
        map<const ParallelRegion*, vector<const ParallelRegionLines*>> internalLines;

        for (auto &reg : regions)
        {
            auto regLines = reg->GetLines(fileName);

            for (auto &lines : *regLines)
            {
                if (!lines.isImplicit())
                {
                    /*
                    if (startLine >= lines.lines.first && startLine <= lines.lines.second)
                        beginLines = &lines;

                    if (endLine >= lines.lines.first && endLine <= lines.lines.second)
                        endLines = &lines;
                    */
                    if (startLine < lines.lines.first && endLine > lines.lines.second)
                    {
                        auto it = internalLines.find(reg);
                        if (it == internalLines.end())
                            it = internalLines.insert(it, make_pair(reg, vector<const ParallelRegionLines*>()));
                        it->second.push_back(&lines);
                    }
                }
            }
        }

        if (!toDelete && internalLines.size() > 1)
        {
            __spf_print(1, "bad lines position on line %d: begin and end lines can not include fragments of different regions at extending operation\n", startLine);

            string message;
            __spf_printToBuf(message, "bad lines position: begin and end lines can not include fragments of different regions at extending operation");
            messagesForFile.push_back(Messages(ERROR, startLine, message, 1001));

            error = false;
        }

        // TODO: испрвить неразличимость внутренних операторов и CONTROL_END
        if (!(startLine <= endLine && (begin->controlParent() == end->controlParent() || end->variant() == CONTROL_END && begin == end->controlParent())))
        {
            __spf_print(1, "bad lines %d-%d position: expected lines with the same scope outside fragment\n", startLine, endLine);

            string message;
            __spf_printToBuf(message, "bad lines position: expected lines with the same scope outside fragment");
            messagesForFile.push_back(Messages(ERROR, startLine, message, 1001));

            error = true;
        }

        // TODO: добавить проверку на фрагменты из разных ОР
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
                __spf_printToBuf(message, "bad user option: you can only create region '%s' with lines %d-%d on line %d", regName.c_str(), startLine, endLine);
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
                    if (startLine >= lines.lines.first && startLine <= lines.lines.second)
                        beginLines = &lines;

                    if (endLine >= lines.lines.first && endLine <= lines.lines.second)
                        endLines = &lines;

                    if (startLine < lines.lines.first && endLine > lines.lines.second)
                        internalLines.push_back(&lines);
                }
            }

            for (auto &intLines : internalLines)
            {
                intLines->stats.first->lexPrev()->deleteStmt();
                intLines->stats.second->lexNext()->deleteStmt();
            }

            bool localError = false;
            int errorLine;

            if (!toDelete)
            {
                if (beginLines && !endLines)
                {
                    if (end->controlParent() == beginLines->stats.first->controlParent())
                    {
                        insertEndParReg(end);
                        beginLines->stats.second->lexNext()->deleteStmt();
                    }
                    else
                    {
                        errorLine = endLine;
                        localError = true;
                    }
                }
                else if (endLines && !beginLines)
                {
                    if (begin->controlParent() == endLines->stats.first->controlParent())
                    {
                        insertParRegDir(begin, regName);
                        endLines->stats.first->lexPrev()->deleteStmt();
                    }
                    else
                    {
                        errorLine = startLine;
                        localError = true;
                    }
                }
                else if (!beginLines && !endLines)
                    insertParRegDirs(begin, end, regName);
            }
            else
            {
                if (beginLines)
                {
                    if (begin->controlParent() == beginLines->stats.first->controlParent())
                    {
                        insertEndParReg(begin->lexPrev());
                        beginLines->stats.second->lexNext()->deleteStmt();
                    }
                    else
                    {
                        errorLine = startLine;
                        localError = true;
                    }
                }

                if (endLines)
                {
                    if (end->controlParent() == endLines->stats.first->controlParent())
                    {
                        insertParRegDir(end, regName);
                        endLines->stats.first->lexPrev()->deleteStmt();
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
