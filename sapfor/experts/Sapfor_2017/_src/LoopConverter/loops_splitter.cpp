#include "loops_splitter.h"

#include "../LoopAnalyzer/loop_analyzer.h"
#include "../ExpressionTransform/expr_transform.h"
#include "../Utils/errors.h"
#include <string>
#include <vector>

using std::string;
using std::vector;
using std::map;
using std::set;
using std::pair;
using std::make_pair;

static SgForStmt* createNewLoop(LoopGraph *globalLoop)
{
    SgStatement *insertBeforeThis = globalLoop->loop->GetOriginal();
    SgStatement *newLoop = NULL;
    LoopGraph *curLoopGraph = globalLoop;
    vector<LoopGraph*> graphs(globalLoop->perfectLoop);

    for (int i = 0; i < globalLoop->perfectLoop; ++i) {
        graphs[i] = curLoopGraph;
        if (curLoopGraph->children.size())
            curLoopGraph = curLoopGraph->children[0];
    }

    for (int i = graphs.size() - 1; i > 0; --i) {
        SgForStmt* curForStmt = (SgForStmt*)graphs[i]->loop->GetOriginal();
        newLoop = new SgForStmt(curForStmt->doName(), curForStmt->start(), curForStmt->end(), curForStmt->step(), newLoop);
    }

    SgForStmt *curForStmt = (SgForStmt*)graphs[0]->loop->GetOriginal();
    SgForStmt *newGlobalLoop = new SgForStmt(curForStmt->doName(), curForStmt->start(), curForStmt->end(), curForStmt->step(), newLoop);

    insertBeforeThis->insertStmtBefore(*newGlobalLoop);

    SgStatement *lowestInsertedFor = insertBeforeThis;
    for (int i = 0; i < globalLoop->perfectLoop; ++i) //пройти по всем enddo
        lowestInsertedFor = lowestInsertedFor->lexPrev();
    return (SgForStmt*)lowestInsertedFor->lexPrev(); //самый внутренний цикл
}

static inline bool lineInsideBorder(int lineNumber, pair<SgStatement*, SgStatement*> border)
{
    return lineNumber >= border.first->lineNumber() && lineNumber < border.second->lineNumber();
}

static void setupOpenDependencies(set<int>& openDependencies, vector<pair<SgStatement*, SgStatement*>>& borders,
                                  depGraph* parentDepGraph, map<SgExpression*, string> &collection)
{
    for(depNode* node : parentDepGraph->getNodes()) {
        if ((!isEqExpressions(node->varin, node->varout, collection)) && (node->varin != node->varout))
        {
            bool hasDependency = false;
            for (int i = 1; i < node->knowndist.size(); ++i)
                hasDependency |= (node->knowndist[i] == 0 || node->distance[i] != 0);
            if (hasDependency)
            {
                int inLine = node->stmtin->lineNumber();
                int outLine = node->stmtout->lineNumber();
                bool inIncluded = false, outIncluded = false;

                for (auto border : borders)
                {
                    if (lineInsideBorder(inLine, border))
                        inIncluded = true;
                    if (lineInsideBorder(outLine, border))
                        outIncluded = true;
                }

                if(!inIncluded && openDependencies.find(inLine) == openDependencies.end())
                    openDependencies.insert(inLine);
                if(!outIncluded && openDependencies.find(outLine) == openDependencies.end())
                    openDependencies.insert(outLine);
            }
        }
    }
}

static void addReachingDefinitionsDependencies(set<int>& openDependencies, vector<pair<SgStatement*, SgStatement*>>& borders, map<SgStatement*, pair<set<SgStatement*>, set<SgStatement*>>> &requireReachMap)
{
    for(auto& border : borders)
    {
        for(SgStatement* current = border.first; ; current = current->lexNext())
        {
            auto found = requireReachMap.find(current);
            if(found != requireReachMap.end())
            {
                for (auto it = found->second.first.begin(); it != found->second.first.end(); ++it)
                {
                    int lineNumber = (*it)->lineNumber();
                    bool included = false;
                    for(auto& b : borders)
                    {
                        if (lineInsideBorder(lineNumber, b))
                        {
                            included = true;
                            break;
                        }
                    }
                    if(!included && openDependencies.find(lineNumber) == openDependencies.end())
                        openDependencies.insert(lineNumber);

                }
                for (auto it = found->second.second.begin(); it != found->second.second.end(); ++it)
                {
                    int lineNumber = (*it)->lineNumber();
                    bool included = false;
                    for(auto& b : borders)
                    {
                        if (lineInsideBorder(lineNumber, b))
                        {
                            included = true;
                            break;
                        }
                    }
                    if(!included && openDependencies.find(lineNumber) == openDependencies.end())
                        openDependencies.insert(lineNumber);
                }

            }

            if(current == border.second)
                break;
        }
    }
}

static bool dependencyAlreadyEnclosed(int lineNum, vector<pair<SgStatement*, SgStatement*>>& borders)
{
    for(auto border : borders)
        if(lineInsideBorder(lineNum, border))
            return true;
    return false;
}

static void expandCopyBorders(SgStatement* globalSince, SgStatement* globalTill, vector<pair<SgStatement*, SgStatement*>>& borders,
                       set<int> openDependencies)
{
    for(int lineNumOfDependecy : openDependencies)
    {
        if(dependencyAlreadyEnclosed(lineNumOfDependecy, borders))
            continue;

        SgStatement *since = NULL, *till = NULL;
        since = globalSince;

        for(since = globalSince; since != globalTill; since = since->lexNext()) {

            if(since->lineNumber() == lineNumOfDependecy) {
                till = since->lastNodeOfStmt()->lexNext();
                break;
            }
        }

        if(since == globalTill) //зависимости вне вне основного цикла? ну уж нет.
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

        borders.push_back(make_pair(since, till));
    }
}

static void glueBorders(vector<pair<SgStatement*, SgStatement*>> &borders) 
{
    if (borders.size() <= 1)
        return;
    map<pair<int, int>, pair<SgStatement*, SgStatement*>> bordersMap;
    for (int z = 0; z < borders.size(); ++z)
        bordersMap[make_pair(borders[z].first->lineNumber(), borders[z].second->lineNumber())] = borders[z];

    borders.clear();
    for (auto &elem : bordersMap)
    {
        //printf("** frag %d - %d\n", elem.first.first, elem.first.second);
        borders.push_back(elem.second);
    }

    bool needToUpdate = true;    
    while (needToUpdate)
    {
        needToUpdate = false;
        vector<pair<SgStatement*, SgStatement*>> newBorders;
        newBorders.push_back(borders[0]);
        int lastIdx = 0;
        for (int z = 1; z < borders.size(); ++z)
        {
            if (newBorders[lastIdx].second == borders[z].first)
                newBorders[lastIdx].second = borders[z].second;
            else
            {
                newBorders.push_back(borders[z]);
                lastIdx++;
            }
        }
        if (newBorders.size() != borders.size())
        {
            borders = newBorders;
            needToUpdate = (borders.size() > 1);
        }
    }
    //for (int z = 0; z < borders.size(); ++z)
    //    printf("*** frag %d - %d\n", borders[z].first->lineNumber(), borders[z].second->lineNumber());
}

static bool setupSplitBorders(LoopGraph* parentGraph, SgStatement* globalSince, SgStatement* globalTill,
                              vector<pair<SgStatement*, SgStatement*>>& borders,
                              depGraph* parentDepGraph, map<SgExpression*, string>& collection)
{
    //Каким-то образом, мы вырезали всё из цикла и хотем продолжать.
    if(globalSince == globalTill)
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);


    borders.clear();
    SgStatement *since, *till;

    since = globalSince;
    till = since->lastNodeOfStmt()->lexNext();

    /*
     * since-till может быть одним одним операторм, захватить тогда больше?
     */

    if(parentDepGraph == NULL) //Нет зависимостей, можно взять изначальный фрагмент без измененений
    {
        borders.push_back(make_pair(since, till));
        return true;
    }

    borders.push_back(make_pair(since, till));
    map<SgStatement*, pair<set<SgStatement*>, set<SgStatement*>>> requireReachMap =  buildRequireReachMap(globalSince, globalTill);

    set<int> openDependencies;
    setupOpenDependencies(openDependencies, borders, parentDepGraph, collection);
    addReachingDefinitionsDependencies(openDependencies, borders, requireReachMap);
    while(openDependencies.size() > 0)
    {
        expandCopyBorders(globalSince, globalTill, borders, openDependencies);
        openDependencies.clear();
        setupOpenDependencies(openDependencies, borders, parentDepGraph, collection);
        addReachingDefinitionsDependencies(openDependencies, borders, requireReachMap);
    }

    glueBorders(borders);

    //Если вырежем опять, исходный цикл останется пустым
    if(borders.size() == 1 && borders[0].first == globalSince && borders[0].second == globalTill)
        return false;

    return true;
}

static void moveStatements(SgForStmt *newLoop, const vector<pair<SgStatement*,SgStatement*>> &borders)
{
    SgStatement *lastInserted = newLoop;
    
    for(auto& border : borders)
    {
        //printf("frag %d - %d, %s %s\n", border.first->lineNumber(), border.second->lineNumber(), border.first->fileName(), border.second->fileName());
        SgStatement *toMoveStmt = border.first;
        while(toMoveStmt != border.second)
        {
            //printf("move st from line %d\n", toMoveStmt->lineNumber());
            SgStatement *st = toMoveStmt->copyPtr();
            lastInserted->insertStmtAfter(*st);
            lastInserted = lastInserted->lexNext()->lastNodeOfStmt();           

            SgStatement *toDelete = toMoveStmt;
            toMoveStmt = toMoveStmt->lastNodeOfStmt()->lexNext();
            toDelete->deleteStmt();
        }
    }
}

static bool hasIndirectChildLoops(LoopGraph* parentGraph, vector<Messages> &messages)
{
    SgStatement* st = parentGraph->loop->GetOriginal()->lexNext();
    int directLoops = 0;
    while(st->variant() != CONTROL_END)
    {
        if(st->variant() == FOR_NODE)
            directLoops++;
        st = st->lastNodeOfStmt()->lexNext();
    }
       
    if(directLoops != parentGraph->children.size())
    {
        messages.push_back(Messages(ERROR, parentGraph->loop->GetOriginal()->lineNumber(), L"This loop has indirect child loops and can not be splitted", 2010));
        __spf_print(1, "This loop has indirect child loops and can not be splitted on line %d\n", parentGraph->lineNum);
        return true;
    }
    else
        return false;
}

static bool hasUnexpectedDependencies(LoopGraph* parentGraph, depGraph* parentDepGraph, vector<Messages> &messages)
{
    bool has = false;
    int countOfMessages = 10;
    int idxOfMessages = 0;

    for (depNode* node : parentDepGraph->getNodes())
    {
        if (node->typedep != ARRAYDEP)
        {
            bool privateInChild = false;
            for (LoopGraph* childGraph : parentGraph->children)
            {
                SgStatement *childLoop = childGraph->loop->GetOriginal();
                if (lineInsideBorder(node->stmtin->lineNumber(), make_pair(childLoop, childLoop->lastNodeOfStmt()->lexNext())))
                    privateInChild = node->typedep == PRIVATEDEP;
            }
            has |= !privateInChild;
            if (!privateInChild)
            {
                if (idxOfMessages < countOfMessages)
                {
                    idxOfMessages++;
                    string str;
                    __spf_printToBuf(str, "Can not split this loop because of dependecy: %s", node->displayDepToStr().c_str());
                    __spf_print(1, "%s on line %d\n", str.c_str(), parentGraph->lineNum);

                    std::wstring strw;
                    __spf_printToLongBuf(strw, L"Can not split this loop because of dependecy: %s", to_wstring(node->displayDepToStr()).c_str());
                    messages.push_back(Messages(WARR, parentGraph->lineNum, strw, 2009));                    
                }
            }
        }
    }
    return has;
}


static int splitLoop(LoopGraph *loopGraph, vector<Messages> &messages, const int deep)
{    
    LoopGraph *lowestParentGraph = loopGraph;
    for (int i = 0; i < std::min(loopGraph->perfectLoop, deep); ++i)
        if (lowestParentGraph->children.size() == 1)
            lowestParentGraph = lowestParentGraph->children[0];

    if (hasIndirectChildLoops(lowestParentGraph, messages))
        return -1;

    //Вектор пар since-till, новые циклы будут формироваться из фрагментов с since включительно, по till не включительно
    vector<pair<SgStatement*, SgStatement*>> borders;
    //Граф с зависимостями
    const set<string> privVars;
    depGraph *lowestParentDepGraph = getDependenciesGraph(lowestParentGraph, current_file, &privVars);
    if (lowestParentGraph->hasLimitsToSplit())
    {
        messages.push_back(Messages(ERROR, loopGraph->lineNum,
                            L"This loop has limits to parallel (reason: loop on line " + std::to_wstring(lowestParentGraph->lineNum) + L")",
                            2010));
        __spf_print(1, "%d loop has limits to parallel (reason: loop on line %d)\n", loopGraph->lineNum, lowestParentGraph->lineNum);
        return -1;
    }
    //Коллекция с выражениями, которые проходили unparse
    map<SgExpression*, string> collection;
    if (hasUnexpectedDependencies(lowestParentGraph, lowestParentDepGraph, messages))
    {
        messages.push_back(Messages(ERROR, loopGraph->lineNum, 
                           L"This loop has unexpected dependencies and can not be splitted (reason: loop on line " + std::to_wstring(lowestParentGraph->lineNum) + L")", 
                           2010));
        __spf_print(1, "%d loop has unexpected dependencies and can not be splitted (reason: loop on line %d)\n", loopGraph->lineNum, lowestParentGraph->lineNum);
        return -1;
    }


    SgStatement *globalSince, *globalTill;
    globalSince = lowestParentGraph->loop->GetOriginal()->lexNext();
    globalTill = lowestParentGraph->loop->GetOriginal()->lastNodeOfStmt()->lexNext();

    vector<pair<SgStatement*, SgStatement*>> parts;
    for(SgStatement* since = globalSince; since != globalTill; since = since->lastNodeOfStmt()->lexNext())
        parts.push_back(make_pair(since, since->lastNodeOfStmt()));

//    while (setupSplitBorders(lowestParentGraph, parts, borders, lowestParentDepGraph, collection) && borders.size() > 0)
//        ;

    //Сам процесс разделения    
    while (setupSplitBorders(lowestParentGraph, globalSince, globalTill, borders, lowestParentDepGraph, collection) && borders.size() > 0)
    {
        moveStatements(createNewLoop(loopGraph), borders);
        globalSince = lowestParentGraph->loop->GetOriginal()->lexNext();
    }

    //Исходный цикл остался с пустым телом
    loopGraph->loop->deleteStmt();
    return 0;
}


int splitLoops(SgFile *file, vector<LoopGraph*> &loopGraphs, vector<Messages> &messages)
{
    map<int, LoopGraph*> mapLoopGraph;
    createMapLoopGraph(loopGraphs, mapLoopGraph);
    int totalErr = 0;

    for (auto &loopPair : mapLoopGraph)
    {
        LoopGraph *loop = loopPair.second;
        auto attrsTr = getAttributes<SgStatement*, SgStatement*>(loop->loop->GetOriginal(), set<int>{ SPF_TRANSFORM_DIR });
        for (auto attr : attrsTr)
        {
            SgExpression *list = attr->expr(0);
            if (list->lhs()->variant() == SPF_FISSION_OP)
            {
                checkNull(list->lhs()->lhs(), convertFileName(__FILE__).c_str(), __LINE__);

                SgExprListExp *listExp = isSgExprListExp(list->lhs()->lhs());
                checkNull(listExp, convertFileName(__FILE__).c_str(), __LINE__);
                const int deep = listExp->length();
                //TODO: use deep!
                int err = splitLoop(loop, messages, deep);
                if (err != 0)
                    totalErr = -1;
            }
        }
    }  

    return totalErr;
}
