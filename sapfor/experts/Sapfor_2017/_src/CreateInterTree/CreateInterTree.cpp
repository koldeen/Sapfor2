#include "CreateInterTree.h"
#include "../Utils/SgUtils.h"
#include "../Utils/utils.h"
#include "../GraphCall/graph_calls_func.h"

using std::string;
using std::vector;
using std::list;
using std::map;
using std::pair;
using std::set;
using std::cout;
using std::endl;
using std::fstream;

static long int getNextTag()
{
    static long int INTERVAL_TAG = 0;
    return INTERVAL_TAG++;
}

//Debug funcs
static void printTree(SpfInterval* inter, fstream &file, int level)
{
    if (!(inter->ifInclude))
    {
        for (int i = 0; i < inter->nested.size(); i++)
            printTree(inter->nested[i], file, level + 1);
        return;
    }

    if (!inter->begin->switchToFile())
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

    for (int i = 0; i < level; i++)
        file << "  ";
    file << "  Begin INTERVAL #" << inter->tag << " (var " << tag[inter->begin->variant()];
    if (inter->begin->variant() == PROC_HEDR || inter->begin->variant() == FUNC_HEDR)
    {
        string name(inter->begin->symbol()->identifier());
        convertToUpper(name);
        file << ", " << name;
    }
    file << ", gcov_calls " << inter->calls_count << ") ";
    file << " [" << inter->lineFile.first << ", " << inter->lineFile.second << "]";
    if (inter->parent == NULL && level != 0)
        file << " -- through PROC_CALL --";
    file << "\n";

    for (int i = 0; i < inter->nested.size(); i++)
        printTree(inter->nested[i], file, level + 1);

    for (int i = 0; i < inter->ends.size(); i++)
    {
        for (int i = 0; i < level; i++)
            file << "  ";
        file << "  End INTERVAL #" << inter->tag << " (exit lvl " << inter->exit_levels[i] << ", var " << tag[inter->ends[i]->variant()] << ") ";
        file << "line " << inter->ends[i]->lineNumber() << endl;
    }
    if (level == 0)
        file << endl;
}

void saveIntervals(const string &fileName, map<string, vector<SpfInterval*>> &intervals)
{
    fstream file_intervals;

    file_intervals.open(fileName, fstream::out);
    for (auto &byfile : intervals)
    {
        file_intervals << "**** INTERVALS FOR FILE '" << byfile.first << "'\n";
        for (auto &interval : byfile.second)
            printTree(interval, file_intervals, 0);
    }
    file_intervals.close();
}

//Labels funcs
static void matchGotoLabels(SgStatement *st, map<int, vector<int>> &gotoStmts)
{
    map<int, vector<int>> labelsRef;

    findAllRefsToLables(st, labelsRef, false);

    for (auto &key : labelsRef)
        for (auto &it : key.second)
            gotoStmts[it].push_back(key.first);
}

static void findAllLabels(SgStatement* st, map<int, int> &labelsRef)
{
    SgStatement* end = st->lastNodeOfStmt();

    while (st != end)
    {
        if (st->hasLabel())
            labelsRef[st->label()->id()] = st->lineNumber();

        st = st->lexNext();
    }
}

//Nested intervals removal
static int getNestedLevel(SgStatement* loop_stmt)
{
    int depth = 0;
    SgStatement *current_loop = loop_stmt->lexNext();
    SgStatement *controlEnd = current_loop->lastNodeOfStmt();

    while (isSgForStmt(current_loop) && isSgControlEndStmt(controlEnd)) {
        current_loop = current_loop->lexNext();
        controlEnd = controlEnd->lexPrev();
        depth++;
    }

    return depth;
}

static void removeNestedIntervals(SpfInterval* interval)
{
    if (isSgForStmt(interval->begin))
    {
        int depth = getNestedLevel(interval->begin);
        SpfInterval *current_interval = interval;

        for (int i = 0; i < depth; i++)
        {
            current_interval = current_interval->nested[0];
            current_interval->ifInclude = false;
        }
    }

    for (auto &include : interval->nested)
        removeNestedIntervals(include);
}

// Merge trees functions.
static int compareIntervals(SpfInterval* interval1, SpfInterval* interval2)
{
    SgStatement* begin_st_1 = interval1->begin;
    while (!isSgExecutableStatement(begin_st_1) || isSPF_stat(begin_st_1) || isDVM_stat(begin_st_1))
        begin_st_1 = begin_st_1->lexNext();

    SgStatement* begin_st_2 = interval2->begin;
    while (!isSgExecutableStatement(begin_st_2) || isSPF_stat(begin_st_2) || isDVM_stat(begin_st_2))
        begin_st_2 = begin_st_2->lexNext();

    int begin_1 = begin_st_1->lineNumber();
    int begin_2 = begin_st_2->lineNumber();
    int end_1 = interval1->ends[0]->lineNumber();
    int end_2 = interval2->ends[0]->lineNumber();

    if((begin_1 == begin_2 && end_1 == end_2) || end_1 <= begin_2 || begin_1 >= end_2)
        return 0;

    if(begin_1 <= begin_2 && end_1 >= end_2)
        return 1;

    return -1;
}

static void insertIntervalIntoTree(vector<SpfInterval*> &tree, SpfInterval* userInterval)
{
    bool ifDeleteNested = false;

    for(int i = 0; i < tree.size(); i++)
    {
        int compare_result = compareIntervals(tree[i], userInterval);

        if(compare_result == 0)
            continue;

        if(compare_result > 0)
        {
            int amount = 0;

            for(int j = 1; j < tree[i]->ends.size(); j++)
            {
                int endLineNumber = tree[i]->ends[j]->lineNumber();

                if(endLineNumber >= userInterval->begin->lineNumber() && endLineNumber <= userInterval->ends[0]->lineNumber())
                {
                    userInterval->ends.push_back(tree[i]->ends[j]);
                    userInterval->exit_levels.push_back(0);

                    tree[i]->ends[j] = NULL;
                }

                amount++;
            }

            tree[i]->ends.erase(std::remove_if(tree[i]->ends.begin(), tree[i]->ends.end(), [](SgStatement* stmt) {return (stmt == NULL);}), tree[i]->ends.end());
            for(int j = 0; j < amount; j++)
                tree[i]->exit_levels.pop_back();

            insertIntervalIntoTree(tree[i]->nested, userInterval);
            return;
        }

        userInterval->nested.push_back(tree[i]);
        userInterval->parent = tree[i]->parent;
        tree[i]->parent = userInterval;
        tree[i] = userInterval;

        if(ifDeleteNested)
            tree[i] = NULL;
        else
            ifDeleteNested = true;
    }

    tree.erase(std::remove_if(tree.begin(), tree.end(), [](SpfInterval* interval) {return (interval == NULL);}), tree.end());
}

static void mergeTrees(vector<SpfInterval*> &fileIntervals, vector<SpfInterval*> &userIntervals)
{
    for(auto &userInterval : userIntervals)
        insertIntervalIntoTree(fileIntervals, userInterval);
}

// Calibrate interval exits.
static void calibrateExits(vector<SpfInterval*> fileIntervals, map<int, int> &labelsRef, map<int, vector<int>> &gotoStmts, int level)
{
    for(auto &interval : fileIntervals)
    {
        for(int i = 1; i < interval->ends.size(); i++)
        {
            int variant = interval->ends[i]->variant();
            int &exit_level = interval->exit_levels[i];

            if (variant == RETURN_STAT || variant == STOP_STAT || variant == EXIT_STMT)
                exit_level = level;

            if (variant == EXIT_STMT)
                exit_level = 1;

            vector<int>& labels = gotoStmts[interval->ends[i]->lineNumber()];

            for (auto it = labels.begin(); it != labels.end(); it++)
            {
                int label_line = labelsRef[*it];
                int depth = 0;

                SpfInterval* searchInterval = interval;
                while (label_line < searchInterval->begin->lineNumber() || label_line > searchInterval->ends[0]->lineNumber())
                {
                    searchInterval = searchInterval->parent;
                    depth++;
                }

                exit_level = depth;
            }
        }

        calibrateExits(interval->nested, labelsRef, gotoStmts, level + 1);
    }
}

static void removeUserIntervals(SgFile *file)
{
    for (SgStatement* st = file->firstStatement(); st; st = st->lexNext())
    {
        const int var = st->variant();
        if (var == DVM_INTERVAL_DIR || var == DVM_EXIT_INTERVAL_DIR || var == DVM_ENDINTERVAL_DIR)
        {            
            //move comment to next statement
            if (st->comments())
            {
                const char* comms = st->comments();
                string comments(comms);
                st->delComments();

                SgStatement* next = st->lexNext();
                if (next)
                    next->addComment(comments.c_str());
            }

            st = st->lexPrev();
            st->lexNext()->deleteStmt();
        }
    }
}

// Find intervals functions.
static void findUserIntervals(SgStatement *startSt, vector<SpfInterval*> &userIntervals)
{
    SpfInterval *currentInterval = NULL;

    SgStatement *endSt = startSt->lastNodeOfStmt();
    SgStatement *currentSt = startSt;

    while (currentSt != endSt)
    {
        if(currentSt->variant() == DVM_INTERVAL_DIR)
        {
            SgStatement* begin = currentSt;
            while (isDVM_stat(begin))
                begin = begin->lexNext();

            SpfInterval *inter = new SpfInterval();
            inter->begin = begin;
            inter->lineFile = std::make_pair(begin->lineNumber(), begin->fileName());
            inter->parent = currentInterval;
            inter->tag = getNextTag();

            userIntervals.push_back(inter);

            currentInterval = inter;
        
            //currentSt = currentSt->lexPrev();
            //currentSt->lexNext()->deleteStmt();
        }

        if(currentSt->variant() == DVM_EXIT_INTERVAL_DIR)
        {
            //currentSt = currentSt->lexPrev();
            //currentSt->lexNext()->deleteStmt();
        }

        if(currentSt->variant() == DVM_ENDINTERVAL_DIR)
        {
            if (currentInterval == NULL)
                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
            
            SgStatement* end = currentSt;
            while(isDVM_stat(end))
                end = end->lexPrev();
            
            currentInterval->ends.push_back(end);
            currentInterval->exit_levels.push_back(0);

            currentInterval = currentInterval->parent;

            //currentSt = currentSt->lexPrev();
            //currentSt->lexNext()->deleteStmt();
        }

        currentSt = currentSt->lexNext();
    } 
}

static void findIntervals(SpfInterval *interval, map<int, int> &labelsRef, map<int, vector<int>> &gotoStmts, SgStatement *&currentSt)
{
    int currentVar = -1;
    SgStatement* endStatement = interval->parent ? interval->ends[0] : interval->begin->lastNodeOfStmt();

    while (currentSt != endStatement && currentVar != CONTAINS_STMT)
    {
        currentSt = currentSt->lexNext();
        currentVar = currentSt->variant();

        if (currentSt->fileName() != string(interval->begin->fileName()))
            continue;

        if (currentVar == RETURN_STAT || currentVar == STOP_STAT || currentVar == EXIT_STMT || currentVar == CONTAINS_STMT)
        {
            if (endStatement != currentSt)
            {
                interval->ends.push_back(currentSt);
                interval->exit_levels.push_back(0);
            }
        }

        if (gotoStmts.find(currentSt->lineNumber()) != gotoStmts.end() && currentVar != LOGIF_NODE)
        {
            vector<int>& labels = gotoStmts[currentSt->lineNumber()];

            for (auto it = labels.begin(); it != labels.end(); it++)
            {
                int label_line = labelsRef[*it];

                if (label_line < interval->begin->lineNumber() || label_line > interval->ends[0]->lineNumber())
                {
                    interval->ends.push_back(currentSt);
                    interval->exit_levels.push_back(0);
                }
            }
        }

        if (currentSt == endStatement || currentVar != FOR_NODE)
            continue;

        SpfInterval* inter = new SpfInterval();
        inter->begin = currentSt;
        inter->ends.push_back(currentSt->lastNodeOfStmt());
        inter->lineFile = std::make_pair(currentSt->lineNumber(), currentSt->fileName());
        inter->parent = interval;
        inter->exit_levels.push_back(0);
        inter->tag = getNextTag();
        interval->nested.push_back(inter);

        findIntervals(inter, labelsRef, gotoStmts, currentSt);
    }
}

void createInterTree(SgFile *file, vector<SpfInterval*> &fileIntervals, bool nested_on)
{
    int funcNum = file->numberOfFunctions();
    
    for (int i = 0; i < funcNum; i++)
    {
        map<int, int> labelsRef;           // id => line
        map<int, vector<int>> gotoStmts;   // line => label_ids
        vector<SpfInterval*> userIntervals;

        // Find labels.
        findAllLabels(file->functions(i), labelsRef);
        matchGotoLabels(file->functions(i), gotoStmts);

        // Find user intervals.
        findUserIntervals(file->functions(i), userIntervals);

        SpfInterval *func_inters = new SpfInterval();

        // Set begining of the interval.
        func_inters->begin = file->functions(i);
        func_inters->lineFile = std::make_pair(func_inters->begin->lineNumber(), file->functions(i)->fileName());
        func_inters->tag = getNextTag();

        // Set ending of the interval.
        SgStatement *lastNode = func_inters->begin->lastNodeOfStmt()->lexPrev();
        while (isDVM_stat(lastNode) || isSPF_stat(lastNode))
            lastNode = lastNode->lexPrev();

        SgStatement *prevLastNode = lastNode->lexPrev();
        while (isDVM_stat(prevLastNode) || isSPF_stat(prevLastNode))
            prevLastNode = prevLastNode->lexPrev();

        if (lastNode->variant() == RETURN_STAT || lastNode->variant() == EXIT_STMT || lastNode->variant() == STOP_STAT)
        {
            bool cond = false;
            if (lastNode->lexNext()->variant() == CONTROL_END)
                if (isSgProgHedrStmt(lastNode->lexNext()->controlParent()))
                    cond = true;

            if (cond)
                func_inters->ends.push_back(lastNode);
            else
                func_inters->ends.push_back(prevLastNode);
        }
        else
            func_inters->ends.push_back(lastNode);

        func_inters->exit_levels.push_back(0);

        // Find inner intervals.
        SgStatement *currentSt = func_inters->begin;
        findIntervals(func_inters, labelsRef, gotoStmts, currentSt);

        vector<SpfInterval*> oneInterval;
        oneInterval.push_back(func_inters);

        mergeTrees(oneInterval, userIntervals);
        calibrateExits(oneInterval, labelsRef, gotoStmts, 1);

        fileIntervals.push_back(oneInterval[0]);
    }

    if (nested_on)
        for (auto &interval : fileIntervals)
            removeNestedIntervals(interval);
}

//SpfInterval insertion funcs
static void LogIftoIfThen(SgStatement *stmt)
{
    SgControlEndStmt *control = new SgControlEndStmt();
    stmt->setVariant(IF_NODE);
    stmt->lexNext()->insertStmtAfter(*control, *stmt);

    if (stmt->numberOfAttributes(OMP_MARK) > 0)
        control->addAttribute(OMP_MARK);
}

static void insertTree(SpfInterval* interval, const string &fileName)
{
    if (interval->ifInclude && interval->begin->fileName() == fileName)
    {
        SgStatement* beg_inter = new SgStatement(DVM_INTERVAL_DIR);
        SgExpression* expr = new SgValueExp(interval->tag);
        beg_inter->setExpression(0, *expr);

        SgStatement* end_inter = new SgStatement(DVM_ENDINTERVAL_DIR);

        // Skip to executables.
        SgStatement* beginSt = interval->begin;
        while (!isSgExecutableStatement(beginSt) || isSPF_stat(beginSt) || isDVM_stat(beginSt))
            beginSt = beginSt->lexNext();

        if (beginSt->lexPrev()->variant() == LOGIF_NODE)
            LogIftoIfThen(beginSt->lexPrev());
        
        // Insert begining
        beginSt->insertStmtBefore(*beg_inter, *beginSt->controlParent());
        beg_inter->setlineNumber(beginSt->lineNumber());

        interval->ends[0]->insertStmtAfter(*end_inter, *beginSt->controlParent());

        for (int i = 1; i < interval->ends.size(); i++)
        {
            int depth = interval->exit_levels[i];
            SpfInterval* curr_inter = interval->parent;

            SgExprListExp* expli = new SgExprListExp(*(new SgValueExp(interval->tag)));
            SgExprListExp* curr_list_elem = expli;

            for (int j = 1; j < depth; j++)
            {
                if(curr_inter->ifInclude)
                {
                    curr_list_elem->setRhs(new SgExprListExp(*(new SgValueExp(curr_inter->tag))));
                    curr_list_elem = curr_list_elem->next();
                }

                curr_inter = curr_inter->parent;
            }

            curr_list_elem->setRhs(NULL);
            SgStatement* exit_inter = new SgStatement(DVM_EXIT_INTERVAL_DIR);
            exit_inter->setExpression(0, *expli);

            if (interval->ends[i]->lexPrev()->variant() == LOGIF_NODE)
                LogIftoIfThen(interval->ends[i]->lexPrev());

            interval->ends[i]->insertStmtBefore(*exit_inter, *interval->ends[i]->controlParent());
        }
    }

    for (int i = 0; i < interval->nested.size(); i++)
        insertTree(interval->nested[i], fileName);
}

void insertIntervals(SgFile *file, const vector<SpfInterval*> &fileIntervals)
{
    const string currFile = file->filename();
    removeUserIntervals(file);
    for (auto &interval : fileIntervals)
        insertTree(interval, currFile);
}

//Profiling funcs
static map<int, long long> parseProfiles(fstream &file)
{
    map<int, long long> fileProfile;
    string line;

    while (!file.eof())
    {
        getline(file, line);

        auto pos_type = line.find(":");
        string type = line.substr(0, pos_type);

        if (type == "lcount")
        {
            if ((int)line.size() >= pos_type + 1)
                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
            string nums = line.substr(pos_type + 1);
            auto pos_com = nums.find(",");

            auto line_num = stoi(nums.substr(0, pos_com));
            if ((int)nums.size() >= pos_com + 1)
                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
            long long calls_num = stoll(nums.substr(pos_com + 1));

            fileProfile[line_num] = calls_num;
        }
    }

    return fileProfile;
}

static void assignRec(SpfInterval* inter, map<int, long long> &fp)
{
    for (int i = 0; i < inter->nested.size(); i++)
        assignRec(inter->nested[i], fp);

    inter->calls_count = fp[inter->begin->lineNumber()];
}

void assignCallsToFile(const string &baseFilename, vector<SpfInterval*> &intervals)
{
    fstream file;
    file.open(baseFilename + ".gcov", fstream::in);

    if (!file.good())
        return;

    map<int, long long> fileProfile = parseProfiles(file);

    file.close();

    for (auto &interval : intervals)
        assignRec(interval, fileProfile);
}

//Deleting intervals funcs
static void removeNode(SpfInterval* inter, long long threshold)
{
    if (inter->calls_count >= threshold)
        inter->ifInclude = false;

    for (int i = 0; i < inter->nested.size(); i++)
        removeNode(inter->nested[i], threshold);
}

static void fillListWithValues(list<long long> &interval_calls, SpfInterval* interval)
{
    auto it = interval_calls.begin();

    for(; it != interval_calls.end(); it++)
        if(interval->calls_count < *it)
        {
            interval_calls.insert(it, interval->calls_count);
            break;
        }

    if(it == interval_calls.end())
        interval_calls.push_back(interval->calls_count);

    for (auto &i : interval->nested)
        fillListWithValues(interval_calls, i);
}

void removeNodes(int threshold, vector<SpfInterval*> &intervals, vector<string> &include_functions)
{
    if (threshold == 100)
        return;

    for (auto &interval : intervals)
    {
        string func_name = interval->begin->symbol()->identifier();

        if (find(include_functions.begin(), include_functions.end(), func_name) != include_functions.end())
            continue;

        list<long long> interval_calls;
        fillListWithValues(interval_calls, interval);

        int amount = interval_calls.size() / 100.f * threshold;
        auto it = interval_calls.begin();
        advance(it, amount);

        removeNode(interval, *it);
    }
}

void createMapOfinterval(map<int, SpfInterval*> &mapIntervals, const vector<SpfInterval*> &intervals)
{
    for (auto &inter : intervals)
    {
        auto it = mapIntervals.find(inter->begin->lineNumber());
        if (it != mapIntervals.end())
            continue;
        mapIntervals[inter->begin->lineNumber()] = inter;
        createMapOfinterval(mapIntervals, inter->nested);
    }    
}

void initTimeForIntervalTree(const int numOfTopologies, vector<SpfInterval*> &intervals)
{
    for (auto &inter : intervals)
    {
        inter->predictedTimes.resize(numOfTopologies);
        inter->predictedRemoteTimes.resize(numOfTopologies);

        std::fill(inter->predictedTimes.begin(), inter->predictedTimes.end(), -1);
        std::fill(inter->predictedRemoteTimes.begin(), inter->predictedRemoteTimes.end(), 0);

        initTimeForIntervalTree(numOfTopologies, inter->nested);
    }
}

void aggregatePredictedTimes(vector<SpfInterval*> &itervals)
{
    for (auto &interval : itervals)
    {
        if (interval->predictedTimes.size() && interval->predictedTimes[0] != -1)
            continue;

        if (interval->nested.size())
            aggregatePredictedTimes(interval->nested);

        for (int topo = 0; topo < interval->predictedTimes.size(); ++topo)
        {
            double newTimeSum = 0;
            for (auto &nestedI : interval->nested)
            {
                if (nestedI->predictedTimes[topo] == -1)
                    newTimeSum += nestedI->exec_time + nestedI->predictedRemoteTimes[topo];
                else
                    newTimeSum += nestedI->predictedTimes[topo] + nestedI->predictedRemoteTimes[topo];
            }
            interval->predictedTimes[topo] = newTimeSum;
        }
    }
}

SpfInterval* getMainInterval(SgProject *project, const map<string, vector<SpfInterval*>> &intervals, map<string, vector<Messages>> &SPF_messages)
{
    SgStatement *mainUnit = findMainUnit(project, SPF_messages);
    SpfInterval *mainIterval = NULL;
    checkNull(mainUnit, convertFileName(__FILE__).c_str(), __LINE__);

    auto itMainVec = intervals.find(mainUnit->fileName());
    if (itMainVec == intervals.end())
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

    if (itMainVec->second.size() == 0)
        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
    else if (itMainVec->second.size() > 1)
    {
        for (auto &elem : itMainVec->second)
            if (elem->begin->variant() == PROG_HEDR)
                mainIterval = elem;
        checkNull(mainIterval, convertFileName(__FILE__).c_str(), __LINE__);
    }
    else
        mainIterval = itMainVec->second[0];

    return mainIterval;
}

SpfInterval* findNearestUp(const map<SgStatement*, SpfInterval*> &intervals, SgStatement *st)
{
    SpfInterval *found = NULL;

    while (st)
    {
        auto it = intervals.find(st);
        if (it != intervals.end())
        {
            found = it->second;
            break;
        }
        else
            st = st->controlParent();
    }
    checkNull(found, convertFileName(__FILE__).c_str(), __LINE__);
    return found;
}

SpfInterval* findNearestDown(const map<SgStatement*, SpfInterval*> &intervals, SgStatement *st)
{
    SpfInterval *found = NULL;

    while (st)
    {
        auto it = intervals.find(st);
        if (it != intervals.end())
        {
            found = it->second;
            break;
        }
        else
            st = st->lexNext();
    }
    checkNull(found, convertFileName(__FILE__).c_str(), __LINE__);
    return found;
}

static FuncInfo* getFunc(const string &file, const int line, const map<string, FuncInfo*> &allFuncs)
{
    for (auto &func : allFuncs)
        if (func.second->linesNum.first == line && func.second->fileName == file)
            return func.second;    
    
    printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
    return NULL;
}

static void createMapOfIntervals(const vector<SpfInterval*> &intervals, map<SgStatement*, SpfInterval*> &intervalsBySt)
{
    for (auto &interval : intervals)
        intervalsBySt[interval->begin] = interval;

    for (auto &interval : intervals)
        if (interval->nested.size())
            createMapOfIntervals(interval->nested, intervalsBySt);
}

static void insertAndSort(SpfInterval *nearest, SpfInterval *toInsert, SgStatement *stLine)
{
    if (nearest->nested.size() == 0)
        nearest->nested.push_back(toInsert);
    else
    {
        const int line = stLine->lineNumber();
        for (int z = 0; z < nearest->nested.size(); ++z)
        {
            if (nearest->nested[z]->parent)
            {
                if (nearest->nested[z]->lineFile.first > line)
                {
                    nearest->nested.insert(nearest->nested.begin() + z, toInsert);
                    return;
                }
            }
        }
                
        nearest->nested.push_back(toInsert);
    }
}

void uniteIntervalsBetweenProcCalls(map<string, vector<SpfInterval*>> &intervals, const map<string, vector<FuncInfo*>> &allFuncInfo)
{
    map<string, map<SgStatement*, SpfInterval*>> intervalsBySt;
    for (auto &byFile : intervals)
        createMapOfIntervals(byFile.second, intervalsBySt[byFile.first]);

    map<string, FuncInfo*> allFuncs;
    createMapOfFunc(allFuncInfo, allFuncs);

    for (auto &byFile : intervals)
    {
        for (auto &intvl : byFile.second)
        {
            if (intvl->begin->variant() != PROG_HEDR)
            {
                if (!intvl->begin->switchToFile())
                    printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

                auto funcSt = intvl->begin;
                const string name = intvl->begin->symbol()->identifier();
                auto currF = getFunc(funcSt->fileName(), funcSt->lineNumber(), allFuncs);
                for (auto &callsTo : currF->callsTo)
                {
                    if (SgFile::switchToFile(callsTo->fileName) == -1)
                        printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
                    for (auto &callsFrom : callsTo->pointerDetailCallsFrom)
                    {
                        SgStatement *base = NULL;
                        if (callsFrom.second == PROC_STAT)
                        {
                            base = (SgStatement*)callsFrom.first;
                            if (base->symbol()->identifier() != name)
                                base = NULL;
                        }
                        else if (callsFrom.second == FUNC_CALL)
                        {
                            SgExpression *ex = (SgExpression*)callsFrom.first;
                            if (ex->symbol()->identifier() == name)
                                base = SgStatement::getStatmentByExpression(ex);
                        }

                        if (base == NULL)
                            continue;
                        else
                        {
                            auto itI = intervalsBySt.find(callsTo->fileName);
                            if (itI == intervalsBySt.end())
                                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);

                            auto nearest = findNearestUp(itI->second, base);
                            insertAndSort(nearest, intvl, base);
                        }
                    }
                }
            }
        }
    }
}