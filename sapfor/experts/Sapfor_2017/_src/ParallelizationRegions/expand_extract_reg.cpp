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
    if (reg && reg->GetName() != "DEFAULT")
    {
        auto regLines = reg->GetLines(fileName, line);
        if (regLines && regLines->isImplicit())
            return true; // error
    }
    return false;
}

static bool hasOwnControlParent(SgStatement *start, SgStatement *end)
{
    if (start == end)
        return true;
    return (end->variant() != CONTROL_END && start->controlParent() == end->controlParent() ||
            end->variant() == CONTROL_END && start->controlParent() == end->controlParent()->controlParent());
}

bool expandExtractReg(const string &fileName,
                      const int startLine,
                      const int endLine,
                      const vector<ParallelRegion*> &regions,
                      vector<Messages> &messagesForFile,
                      const bool toDelete)
{
    bool error = false;

    if (SgFile::switchToFile(fileName) != -1)
    {
        SgStatement *begin = SgStatement::getStatementByFileAndLine(fileName, startLine);
        SgStatement *end = SgStatement::getStatementByFileAndLine(fileName, endLine);

        // check user lines
        // 2. запрещено располагать N1 и N2 в неисполняемых операторах
        int errorLine;
        bool localError = false;

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
            
            std::wstring bufw;
            __spf_printToLongBuf(bufw, L"bad directive position: it can be placed only after all DATA statements");
            messagesForFile.push_back(Messages(ERROR, errorLine, bufw, 1001));

            error = true;
        }

        // 1. N1 <= N2
        if (startLine > endLine)
        {
            __spf_print(1, "bad lines position: end line %d must be greater or equel begin line %d\n", endLine, startLine);

            std::wstring bufw;
            __spf_printToLongBuf(bufw, L"bad lines position: end line %d must be greater or equel begin line %d", endLine, startLine);
            messagesForFile.push_back(Messages(ERROR, endLine, bufw, 1001));

            error = true;
        }

        // 2. запрещено располагать N1 и N2 во фрагментах разных ОР и неявных строках
        auto beginReg = getRegionByLine(regions, fileName, startLine);
        auto endReg = getRegionByLine(regions, fileName, endLine);

        if (!toDelete && beginReg && endReg && beginReg != endReg)
        {
            __spf_print(1, "bad lines position: begin and end lines can not be placed at differect regions\n");

            std::wstring bufw;
            __spf_printToLongBuf(bufw, L"bad lines position: begin and end lines can not be placed at differect regions");
            messagesForFile.push_back(Messages(ERROR, endLine, bufw, 1001));

            error = true;
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

            std::wstring bufw;
            __spf_printToLongBuf(bufw, L"bad lines position: begin and end lines can not be placed at region implicit lines");
            messagesForFile.push_back(Messages(ERROR, errorLine, bufw, 1001));

            error = true;
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

            std::wstring bufw;
            __spf_printToLongBuf(bufw, L"bad lines position: begin and end lines can not include fragments of different regions at extending operation");
            messagesForFile.push_back(Messages(ERROR, startLine, bufw, 1001));

            error = true;
        }

        // use cases
        if (beginReg && beginReg->GetName() != "DEFAULT")
            beginLines = beginReg->GetLines(fileName, startLine);

        if (endReg && endReg->GetName() != "DEFAULT")
            endLines = endReg->GetLines(fileName, endLine);

        // delete all internal fragments
        for (auto &regLines : internalLines)
        {
            for (auto &lines : regLines.second)
            {
                lines->stats.first->GetOriginal()->lexPrev()->deleteStmt();
                lines->stats.second->GetOriginal()->lexNext()->deleteStmt();
            }
        }

        localError = false;

        if (beginLines && !endLines)
        {
            if (!toDelete)
            {
                if (hasOwnControlParent(beginLines->stats.first->GetOriginal(), end))
                {
                    insertEndParReg(end);
                    beginLines->stats.second->GetOriginal()->lexNext()->deleteStmt();
                }
                else
                {
                    errorLine = endLine;
                    localError = true;
                }
            }
            else
            {
                insertEndParReg(begin->lexPrev());
                beginLines->stats.second->GetOriginal()->lexNext()->deleteStmt();
            }
        }
        else if (endLines && !beginLines)
        {
            if (!toDelete)
            {
                if (hasOwnControlParent(begin, endLines->stats.first->GetOriginal()))
                {
                    insertParRegDir(begin, endReg->GetName());
                    endLines->stats.first->GetOriginal()->lexPrev()->deleteStmt();
                }
                else
                {
                    errorLine = startLine;
                    localError = true;
                }
            }
            else
            {
                insertParRegDir(end->lexNext(), endReg->GetName());
                endLines->stats.first->GetOriginal()->lexPrev()->deleteStmt();
            }
        }
        else if (!beginLines && !endLines)
        {
            if (!toDelete)
            {
                string regName;
                // TODO: create correct new region name
                if (internalLines.size())
                    regName = internalLines.begin()->first->GetName();
                else
                    regName = "reg" + to_string(regions.size() + 1);

                if (hasOwnControlParent(begin, end))
                    insertParRegDirs(begin, end, regName);
                else
                {
                    __spf_print(1, "bad lines %d-%d position: expected lines with the same scope for creating region fragment\n", startLine, endLine);

                    std::wstring bufw;
                    __spf_printToLongBuf(bufw, L"bad lines position: expected lines with the same scope for creating region fragment");
                    messagesForFile.push_back(Messages(ERROR, endLine, bufw, 1001));

                    error = true;
                }
            }
        }
        else if (beginLines && endLines)
        {
            if (!toDelete)
            {
                if (beginLines != endLines && hasOwnControlParent(beginLines->stats.first->GetOriginal(), endLines->stats.first->GetOriginal()))
                {
                    beginLines->stats.second->GetOriginal()->lexNext()->deleteStmt();
                    endLines->stats.first->GetOriginal()->lexPrev()->deleteStmt();
                }
                else
                {
                    __spf_print(1, "bad lines %d-%d position: can not extend region fragments with different scope\n", startLine, endLine);

                    std::wstring bufw;
                    __spf_printToLongBuf(bufw, L"bad lines %d-%d position: can not extend region fragments with different scope");
                    messagesForFile.push_back(Messages(ERROR, endLine, bufw, 1001));

                    error = true;
                }
            }
            else
            {
                int errorLine1, errorLine2, printLine;
                localError = false;

                if (hasOwnControlParent(beginLines->stats.first->GetOriginal(), begin))
                {
                    if (startLine == beginLines->lines.first)
                        beginLines->stats.first->GetOriginal()->lexPrev()->deleteStmt();
                    else
                        insertEndParReg(begin->lexPrev());
                }
                else
                {
                    localError = true;
                    errorLine1 = beginLines->lines.first;
                    errorLine2 = startLine;
                    printLine = startLine;
                }

                if (hasOwnControlParent(endLines->stats.first->GetOriginal(), end))
                {
                    if (endLine == endLines->lines.second)
                        endLines->stats.second->GetOriginal()->lexNext()->deleteStmt();
                    else
                        insertParRegDir(end->lexNext(), endReg->GetName());
                }
                else
                {
                    localError = true;
                    errorLine1 = endLine;
                    errorLine2 = endLines->lines.second;
                    printLine = endLine;
                }

                if (beginLines != endLines)
                {
                    beginLines->stats.second->GetOriginal()->lexNext()->deleteStmt();
                    endLines->stats.first->GetOriginal()->lexPrev()->deleteStmt();
                }

                if (localError)
                {
                    __spf_print(1, "bad lines %d-%d position: expected line with the same scope for extracting region fragment\n", errorLine1, errorLine2);

                    std::wstring bufw;
                    __spf_printToLongBuf(bufw, L"bad lines position: expected line with the same scope for extracting region fragment");
                    messagesForFile.push_back(Messages(ERROR, printLine, bufw, 1001));

                    error = true;
                }
            }
        }

        if (localError)
        {
            __spf_print(1, "bad lines position: expected lines with the same control parent on line %d\n", errorLine);

            std::wstring bufw;
            __spf_printToLongBuf(bufw, L"bad lines position: expected lines with the same control parent");
            messagesForFile.push_back(Messages(ERROR, errorLine, bufw, 1001));

            error = true;
        }
    }
    else
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

    return error;
}
