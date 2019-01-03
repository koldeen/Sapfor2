#include "loops_splitter.h"

#include "../LoopAnalyzer/loop_analyzer.h"
#include "../Utils/errors.h"
#include <string>
#include <vector>

/*удалить от сих*/
//#include "dvm.h"
//#include "../GraphLoop/graph_loops.h"
/*до сих*/

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
    openDependencies.clear();
    for(depNode* node : parentDepGraph->getNodes())
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
                if(!outLine && openDependencies.find(outLine) == openDependencies.end())
                    openDependencies.insert(outLine);
            }
        }
}

static void initialSinceTillSetup(int loopNum, LoopGraph* parentGraph, SgStatement*& since, SgStatement*& till)
{
    since = parentGraph->children[loopNum]->loop->GetOriginal();
    till = since->lastNodeOfStmt()->lexNext();
    if(loopNum == 0) //если это первый цикл, захватим с ним проие операторы перед ним.
        since = parentGraph->loop->GetOriginal()->lexNext();

    //till выставим на следующий цикл или на конец родительского цикла.
    while(till->variant() != FOR_NODE && till->variant() != CONTROL_END)
        till = till->lastNodeOfStmt()->lexNext();

}

static bool dependencyAlreadyEnclosed(int lineNum, vector<pair<SgStatement*, SgStatement*>>& borders)
{
    for(auto border : borders)
        if(lineInsideBorder(lineNum, border))
            return true;
    return false;
}

void expandCopyBorders(LoopGraph* parentGraph, vector<int>& loopNums, vector<pair<SgStatement*, SgStatement*>>& borders, set<int> openDependencies)
{
    for(int lineNumOfDependecy : openDependencies)
    {
        if(dependencyAlreadyEnclosed(lineNumOfDependecy, borders))
            continue;

        SgStatement *since = NULL, *till = NULL;
        auto loopNumIt = loopNums.begin();
        for(; loopNumIt != loopNums.end(); loopNumIt++)
        {
            since = till = NULL;
            initialSinceTillSetup(*loopNumIt, parentGraph, since, till);
            if(lineInsideBorder(lineNumOfDependecy, make_pair(since, till)))
                break;
        }
        if(since == NULL || till == NULL) //зависимости вне цикла? ну уж нет.
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

        loopNums.erase(loopNumIt);
        borders.push_back(make_pair(since, till));
    }
}

static bool setupSplitBorders(LoopGraph* parentGraph, vector<int>& loopNums, vector<pair<SgStatement*, SgStatement*>>& borders, 
                              depGraph* parentDepGraph, map<SgExpression*, string>& collection)
{
    if(loopNums.size() <= 1) //остался один подцикл, оставим его на месте и прекратим разделение
        return false;

    borders.clear();
    auto loopNumIt = loopNums.begin();
    SgStatement *since, *till;

    if(parentDepGraph == NULL) //Нет зависимостей, можно взять очередной цикл из loopNums.
    {

        initialSinceTillSetup(*loopNumIt, parentGraph, since, till);
        loopNums.erase(loopNumIt);
        borders.push_back(make_pair(since, till));
        return true;
    }


    initialSinceTillSetup(*loopNumIt, parentGraph, since, till);
    borders.push_back(make_pair(since, till));
    loopNums.erase(loopNumIt);

    set<int> openDependencies;
    setupOpenDependencies(openDependencies, borders, parentDepGraph, collection);
    while(openDependencies.size() > 0)
    {
        expandCopyBorders(parentGraph, loopNums, borders, openDependencies);
        setupOpenDependencies(openDependencies, borders, parentDepGraph, collection);
    }

    if(loopNums.size() == 0) //В попытке удовлетворить зависимости, мы захватили все оставшиея подциклы.
        return false;
    return true;

}

static void moveStatements(SgForStmt *newLoop, vector<pair<SgStatement*,SgStatement*>>& borders)
{
    SgStatement *lastInserted = newLoop;
    for(auto& border : borders)
    {
        SgStatement *toMoveStmt = border.first;
        while(toMoveStmt != border.second)
        {
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
    /*SgStatement* st = parentGraph->loop->GetOriginal()->lexNext();
    int directLoops = 0;
    while(st->variant() != CONTROL_END)
    {
        if(st->variant() == FOR_NODE)
            directLoops++;
        st = st->lastNodeOfStmt()->lexNext();
    }
       
    if(directLoops != parentGraph->children.size())
    {
        printf("Loop on line %d has indirect child loops and cannot be splitted\n", parentGraph->loop->GetOriginal()->lineNumber());
        return true;
    }*/

    int countOfInderect = 0;
    for (auto &chLoop : parentGraph->children)
        countOfInderect += chLoop->children.size();

    if (countOfInderect != 0)
    {
        messages.push_back(Messages(WARR, parentGraph->loop->GetOriginal()->lineNumber(), "This loop has indirect child loops and can not be splitted", 2010));
        __spf_print(1, "This loop has indirect child loops  and can not be splitted on line %d\n", parentGraph->lineNum);
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
                    messages.push_back(Messages(WARR, parentGraph->lineNum, str, 2009));
                    __spf_print(1, "%s on line %d\n", str.c_str(), parentGraph->lineNum);
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

    //Номера подиклов, которые стоит попробовать вытащить в отдельный цикл
    vector<int> loopNums(lowestParentGraph->children.size());
    for (int i = 0; i < lowestParentGraph->children.size(); ++i)
        loopNums[i] = i;

    if (loopNums.size() <= 1)
    {
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
        return -1;
    }
    //Вектор пар since-till, новые циклы будут формироваться из фрагментов с since включительно, по till не включительно
    vector<pair<SgStatement*, SgStatement*>> borders;
    //Граф с зависимостями
    const set<string> privVars;
    depGraph *lowestParentDepGraph = getDependenciesGraph(lowestParentGraph, current_file, &privVars);
    //Коллекция с выражениями, которые проходили unparse
    map<SgExpression*, string> collection;
    if (hasUnexpectedDependencies(lowestParentGraph, lowestParentDepGraph, messages))
        return -1;
    while (setupSplitBorders(lowestParentGraph, loopNums, borders, lowestParentDepGraph, collection) && borders.size() > 0)
        moveStatements(createNewLoop(loopGraph), borders);

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
