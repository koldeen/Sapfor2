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
using std::wstring;

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
        
    insertBeforeThis->insertStmtBefore(*newGlobalLoop, *insertBeforeThis->controlParent());
    //copy attributes
    if (insertBeforeThis->numberOfAttributes())
        newGlobalLoop->addAttributeTree(insertBeforeThis->getAttribute(0));

    SgStatement *lowestInsertedFor = insertBeforeThis;
    for (int i = 0; i < globalLoop->perfectLoop; ++i) //пройти по всем enddo
        lowestInsertedFor = lowestInsertedFor->lexPrev();

    return (SgForStmt*)lowestInsertedFor->lexPrev(); //самый внутренний цикл
}

static inline bool lineInsideBorder(int lineNumber, pair<SgStatement*, SgStatement*> border)
{
    return lineNumber >= border.first->lineNumber() && lineNumber < border.second->lineNumber();
}

static void setupOpenDependencies(set<int>& openDependencies, const vector<pair<SgStatement*, SgStatement*>> &borders,
                                    vector<depGraph*> &depGraphs, map<SgExpression*, string> &collection)
{
    for(depGraph* dependencyGraph : depGraphs) {
    for(depNode* node : dependencyGraph->getNodes()) {
        if ((!isEqExpressions(node->varin, node->varout, collection)) && (node->varin != node->varout) )
        {
            bool hasDependency = false;
            for (int i = 1; i < node->knowndist.size(); ++i) {
/*                if((node->typedep == ARRAYDEP) && (node->kinddep == 0)) //FLOW
                    continue;
                if((node->typedep == ARRAYDEP) && (node->kinddep == 2)) //OUTPUT
                    continue;*/
                //ANTI and REDUCE
                hasDependency |= (node->knowndist[i] == 0) || ((node->knowndist[i] == 1) && (node->distance[i] != 0));
//                hasDependency |= (node->knowndist[i] != 0) || ((node->knowndist[i] == 0) && !(node->distance[i] & DEPZERO));
//                hasDependency |= (node->knowndist[i] != 0) || (node->distance[i] !=0);
            }

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


                if(!inIncluded && !outIncluded)
                    continue;

/*                if((!inIncluded && openDependencies.find(inLine) == openDependencies.end()) ||
                    (!outIncluded && openDependencies.find(outLine) == openDependencies.end()))
                {
                    printf("\n");
                    node->displayDep();
                    printf("%d %d adding: ", node->knowndist[1], node->distance[1]);
                }*/

                if(!inIncluded && openDependencies.find(inLine) == openDependencies.end())
                    openDependencies.insert(inLine);
                if(!outIncluded && openDependencies.find(outLine) == openDependencies.end())
                    openDependencies.insert(outLine);
            }
        }
    }
    }
}

static void addReachingDefinitionsDependencies(set<int> &openDependencies, const vector<pair<SgStatement*, SgStatement*>> &borders, 
                                               map<SgStatement*, pair<set<SgStatement*>, set<SgStatement*>>> &requireReachMap)
{
    for(auto &border : borders)
    {
        for(SgStatement* current = border.first; current != border.second; current = current->lexNext())
        {
            auto found = requireReachMap.find(current);
            if(found != requireReachMap.end())
            {
                for (auto it = found->second.first.begin(); it != found->second.first.end(); ++it)
                {
                    int lineNumber = (*it)->lineNumber();
                    bool included = false;
                    for(auto &b : borders)
                    {
                        if (lineInsideBorder(lineNumber, b))
                        {
                            included = true;
                            break;
                        }
                    }
                    if(!included && openDependencies.find(lineNumber) == openDependencies.end())
                    {
                        //printf("rd %d -> %d\n", current->lineNumber(), lineNumber);
                        openDependencies.insert(lineNumber);
                    }
                }
                for (auto it = found->second.second.begin(); it != found->second.second.end(); ++it)
                {
                    int lineNumber = (*it)->lineNumber();
                    bool included = false;
                    for(auto &b : borders)
                    {
                        if (lineInsideBorder(lineNumber, b))
                        {
                            included = true;
                            break;
                        }
                    }
                    if(!included && openDependencies.find(lineNumber) == openDependencies.end())
                    {
                        //printf("2 rd %d -> %d\n", current->lineNumber(), lineNumber);
                        openDependencies.insert(lineNumber);
                    }
                }

            }
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

static void expandCopyBorders(SgStatement *globalSince, SgStatement *globalTill, vector<pair<SgStatement*, SgStatement*>> &borders,
                              set<int> openDependencies)
{
//    printf("since-till %d - %d\n", globalSince->lineNumber(), globalTill->lineNumber());

    for(int lineNumOfDependecy : openDependencies)
    {
        if(dependencyAlreadyEnclosed(lineNumOfDependecy, borders))
            continue;

        SgStatement *since = NULL, *till = NULL;
        since = globalSince;


        for(since = globalSince; since != globalTill; since = since->lastNodeOfStmt()->lexNext())
        {
            if(since->lineNumber() <= lineNumOfDependecy && since->lastNodeOfStmt()->lineNumber() >= lineNumOfDependecy)
//            if(since->lineNumber() == lineNumOfDependecy)
            {
                till = since->lastNodeOfStmt()->lexNext();
                break;
            }
        }

//        printf("linenum of dependency %d\n", lineNumOfDependecy);

        if(since == globalTill) //зависимости вне основного цикла? ну уж нет.
            printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

//        printf("added: %d - %d\n", since->lineNumber(), till->lineNumber());
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

vector<LoopGraph*> getLoopsFrom(vector<pair<SgStatement*, SgStatement*>>& borders, LoopGraph *parentGraph) {
    vector<LoopGraph*> result;
    for(LoopGraph *loop : parentGraph->children) {
        for(pair<SgStatement*, SgStatement*> &frag : borders)
            if(loop->lineNum >= frag.first->lineNumber() && loop->lineNumAfterLoop <= frag.second->lineNumber())
                result.push_back(loop);
    }

    return result;
}

vector<depGraph*> getDepGraphsFor(vector<LoopGraph*> &loops, LoopGraph *parentGraph) {

    vector<depGraph*> result;
    const set<string> privVars;
    for(auto loop : loops)
        result.push_back(getDependenciesGraph(parentGraph, current_file, &privVars));
    return result;
}

bool continueSplitting(SgStatement* globalSince, SgStatement* globalTill, vector<pair<SgStatement*, SgStatement*>>& borders) {
    //Если вырежем опять, исходный цикл останется пустым
    return !(borders.size() == 1 && borders[0].first == globalSince && borders[0].second == globalTill);
}

static bool setupSplitBorders(LoopGraph* parentGraph, SgStatement* globalSince, SgStatement* globalTill,
                              vector<pair<SgStatement*, SgStatement*>>& borders,
                              depGraph* parentDepGraph, map<SgExpression*, string>& collection)
{
    //Каким-то образом, мы вырезали всё из цикла и хотим продолжать.
    if(globalSince == globalTill)
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

    borders.clear();
    SgStatement *since, *till;

    since = globalSince;
    till = since->lastNodeOfStmt()->lexNext();

    borders.push_back(make_pair(since, till));

    vector<LoopGraph*> loops = getLoopsFrom(borders, parentGraph);
    vector<depGraph*> depGraphs = getDepGraphsFor(loops, parentGraph);

//    printf("Initial fragment: %d - %d\n", since->lineNumber(), till->lineNumber());
//      printf("%s\n", since->unparse());

    map<SgStatement*, pair<set<SgStatement*>, set<SgStatement*>>> requireReachMap = buildRequireReachMapForLoop(globalSince, globalTill);

    set<int> openDependencies;
    setupOpenDependencies(openDependencies, borders, depGraphs, collection);
    addReachingDefinitionsDependencies(openDependencies, borders, requireReachMap);
    while(openDependencies.size() > 0)
    {
/*       printf("Dependencies:\n", globalSince->lineNumber(), globalTill->lineNumber());
        for(auto& it : openDependencies)
            printf(" %d,", it);
        printf("\n");*/

        expandCopyBorders(globalSince, globalTill, borders, openDependencies);
        openDependencies.clear();

        loops = getLoopsFrom(borders, parentGraph);
        depGraphs = getDepGraphsFor(loops, parentGraph);
        setupOpenDependencies(openDependencies, borders, depGraphs, collection);
        addReachingDefinitionsDependencies(openDependencies, borders, requireReachMap);
    }
/*
    for (auto &fragment : borders)
        printf("frag %d - %d\n", fragment.first->lineNumber(), fragment.second->lineNumber());
*/


    glueBorders(borders);

    return continueSplitting(globalSince, globalTill, borders);
}

static void moveStatements(SgForStmt *newLoop, const vector<pair<SgStatement*, SgStatement*>> &fragments)
{
    SgStatement *lastInserted = newLoop->lastNodeOfStmt();
    SgStatement* cp = lastInserted->controlParent();

    for (auto &fragment : fragments)
    {
        SgStatement *toMoveStmt = fragment.first;
        while (toMoveStmt != fragment.second)
        {
            //printf("move st from line %d\n", toMoveStmt->lineNumber());
            SgStatement *st = toMoveStmt;
            toMoveStmt = toMoveStmt->lastNodeOfStmt()->lexNext();

            lastInserted->insertStmtBefore(*st->extractStmt(), *cp);
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
#ifdef _WIN32
        messages.push_back(Messages(ERROR, parentGraph->loop->GetOriginal()->lineNumber(), L"Данный цикл содержит косвенные подциклы, поэтому не может быть разделен", L"This loop has indirect child loops and can not be splitted", 2010));
#endif
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

                    wstring strR, strE;
                    __spf_printToLongBuf(strE, L"Can not split this loop because of dependecy: %s", to_wstring(node->displayDepToStr()).c_str());
#ifdef _WIN32
                    __spf_printToLongBuf(strR, L"Невозможно разделить данный цикл из-за следующей зависимости: %s", to_wstring(node->displayDepToStr()).c_str());
#endif
                    messages.push_back(Messages(WARR, parentGraph->lineNum, strR, strE, 2009));
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
#ifdef _WIN32
        messages.push_back(Messages(ERROR, loopGraph->lineNum,
                            L"У данного цикла есть ограничение на распараллеливание (в строке " + std::to_wstring(lowestParentGraph->lineNum) + L")",
                            L"This loop has limits to parallel (reason: loop on line " + std::to_wstring(lowestParentGraph->lineNum) + L")",
                            2010));
#endif
        __spf_print(1, "%d loop has limits to parallel (reason: loop on line %d)\n", loopGraph->lineNum, lowestParentGraph->lineNum);
        return -1;
    }
    //Коллекция с выражениями, которые проходили unparse
    map<SgExpression*, string> collection;
    if (hasUnexpectedDependencies(lowestParentGraph, lowestParentDepGraph, messages))
    {
#ifdef _WIN32
        messages.push_back(Messages(ERROR, loopGraph->lineNum, 
                           L"У данного цикла есть зависимости, которые нельзя проанализировать, поэтому он не может быть разделен (в строке " + std::to_wstring(lowestParentGraph->lineNum) + L")", 
                           L"This loop has unexpected dependencies and can not be splitted (reason: loop on line " + std::to_wstring(lowestParentGraph->lineNum) + L")",
                           2010));
#endif
        __spf_print(1, "%d loop has unexpected dependencies and can not be splitted (reason: loop on line %d)\n", loopGraph->lineNum, lowestParentGraph->lineNum);
        return -1;
    }


    SgStatement *globalSince, *globalTill;
    globalSince = lowestParentGraph->loop->GetOriginal()->lexNext();
    globalTill = lowestParentGraph->loop->GetOriginal()->lastNodeOfStmt();

//    printf("global %d %d\n", globalSince->lineNumber(), globalTill->lineNumber());


/*    auto definitions = getReachingDefinitionsExt(globalSince);
    for(auto& it : definitions)
    {
        printf("%s: ", it.first.getVarName().c_str());
        for(auto& itt : it.second)
            printf("%s from %s, ", itt->getUnparsed().c_str(), itt->getFrom() ? itt->getFrom()->unparse() : "(nowhere)");
        printf("\n");
    }*/


    vector<pair<SgStatement*, SgStatement*>> parts;
    for(SgStatement* since = globalSince; since != globalTill; since = since->lastNodeOfStmt()->lexNext())
        parts.push_back(make_pair(since, since->lastNodeOfStmt()));

    //Сам процесс разделения 
    //Берётся первый оператор цикла, это начальный фрагмент. Высчитываются зависимости, фрагмент расширяется на них.
    //Когда все зависимости удовлетворены, фрагменты вырезаются и вставялются в новый цикл. Затем берётся следующий оператор из оставшихся.
    //Последний расширенный фрагмент не вырезается, а остаётся в оиргинальном цикле.
    while (setupSplitBorders(lowestParentGraph, globalSince, globalTill, borders, lowestParentDepGraph, collection) && borders.size() > 0)
    {
/*        printf("global since %d, global till %d\n", globalSince->lineNumber(), globalTill->lineNumber());
        printf("result fragment: ");
        for(auto& it : borders)
            printf("%d - %d, ", it.first->lineNumber(), it.second->lineNumber());
        printf("\n");*/
        moveStatements(createNewLoop(loopGraph), borders);
        globalSince = lowestParentGraph->loop->GetOriginal()->lexNext();        
    }
    return 0;
}


int splitLoops(SgFile *file, vector<LoopGraph*> &loopGraphs, vector<Messages> &messages)
{
    map<int, LoopGraph*> mapLoopGraph;
    createMapLoopGraph(loopGraphs, mapLoopGraph);
    int totalErr = 0;

    for (int i = 0; i < file->numberOfFunctions(); ++i)
    {
        ControlFlowGraph* cfg = BuildUnfilteredReachingDefinitionsFor(file->functions(i));
 //       if(string(file->filename()) == "z_solve.f")
 //           showDefsOfGraph(cfg);
    }

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
                int err = splitLoop(loop, messages, deep);
                if (err != 0)
                    totalErr = -1;
            }
        }
    }
    deleteAllocatedExpressionValues(file->functions(0)->getFileId());
    return totalErr;
}
