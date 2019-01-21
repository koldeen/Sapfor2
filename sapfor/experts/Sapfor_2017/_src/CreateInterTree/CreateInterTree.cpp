#include "CreateInterTree.h"
#include "../Utils/SgUtils.h"
#include "../GraphCall/graph_calls_func.h"

using std::string;
using std::vector;
using std::map;
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
        return;

    for (int i = 0; i < level; i++)
        file << "  ";
    file << "  Begin INTERVAL #" << inter->tag << " (var " << tag[inter->begin->variant()] << ", gcov_calls " << inter->calls_count << ") ";
    file << " [" << inter->lineFile.first << ", " << inter->lineFile.second << "]\n";


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

static void removeNestedIntervals(SpfInterval *interval)
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

//Tree creation funcs
static void findIntervals(SpfInterval* interval, map<int, int> &labelsRef, map<int, vector<int>> &gotoStmts, SgStatement *&currentSt, int level)
{
    int currentVar;

    while (currentSt != interval->ends[0])
    {
        currentSt = currentSt->lexNext();
        currentVar = currentSt->variant();

        if (currentSt->fileName() != string(interval->begin->fileName()))
            continue;

        if (currentVar == RETURN_STAT || currentVar == STOP_STAT)
        {
            if (interval->ends[0] != currentSt)
            {
                interval->ends.push_back(currentSt);
                interval->exit_levels.push_back(level);
            }
        }

        if (currentVar == EXIT_STMT)
        {
            if (interval->ends[0] != currentSt)
            {
                interval->ends.push_back(currentSt);
                interval->exit_levels.push_back(1);
            }
        }

        if (gotoStmts.find(currentSt->lineNumber()) != gotoStmts.end() && currentVar != LOGIF_NODE)
        {
            vector<int>& labels = gotoStmts[currentSt->lineNumber()];

            for (auto it = labels.begin(); it != labels.end(); it++)
            {
                int label_line = labelsRef[*it];
                int depth = 0;

                SpfInterval* labelSearch = interval;
                while (label_line < labelSearch->begin->lineNumber() || label_line >= labelSearch->begin->lastNodeOfStmt()->lineNumber())
                {
                    labelSearch = labelSearch->parent;
                    depth++;
                }

                interval->ends.push_back(currentSt);
                interval->exit_levels.push_back(depth);
            }
        }

        if (currentSt == interval->ends[0] || currentVar != FOR_NODE)
            continue;

        SpfInterval* inter = new SpfInterval();
        inter->begin = currentSt;
        inter->lineFile = std::make_pair(currentSt->lineNumber(), currentSt->fileName());
        inter->parent = interval;
        inter->ends.push_back(currentSt->lastNodeOfStmt());
        inter->exit_levels.push_back(0);
        inter->tag = getNextTag();
        interval->nested.push_back(inter);

        findIntervals(inter, labelsRef, gotoStmts, currentSt, level + 1);
    }
}

void createInterTree(SgFile *file, vector<SpfInterval*> &fileIntervals, bool nested_on)
{
    int funcNum = file->numberOfFunctions();
    map<int, int> labelsRef;           // id => line
    map<int, vector<int>> gotoStmts;   // line => label_ids

    for (int i = 0; i < funcNum; i++)
    {
        // Find labels
        findAllLabels(file->functions(i), labelsRef);
        matchGotoLabels(file->functions(i), gotoStmts);
        //

        SpfInterval *func_inters = new SpfInterval();

        func_inters->begin = file->functions(i);
        func_inters->lineFile = std::make_pair(file->functions(i)->lineNumber(), file->functions(i)->fileName());
        func_inters->tag = getNextTag();

        SgStatement *lastNode = func_inters->begin->lastNodeOfStmt();
        SgStatement *prevLastNode = lastNode->lexPrev();
        while (isDVM_stat(prevLastNode) || isSPF_stat(prevLastNode))
            prevLastNode = prevLastNode->lexPrev();

        if (prevLastNode->variant() == RETURN_STAT || prevLastNode->variant() == EXIT_STMT)
            func_inters->ends.push_back(prevLastNode);
        else
            func_inters->ends.push_back(lastNode);
        func_inters->exit_levels.push_back(0);

        SgStatement *currentSt = func_inters->begin;
        findIntervals(func_inters, labelsRef, gotoStmts, currentSt, 1);

        fileIntervals.push_back(func_inters);
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

static void insertTree(SpfInterval* interval)
{
    if (interval->ifInclude)
    {
        SgStatement* beg_inter = new SgStatement(DVM_INTERVAL_DIR);
        SgExpression* expr = new SgValueExp(interval->tag);
        beg_inter->setExpression(0, *expr);

        SgStatement* end_inter = new SgStatement(DVM_ENDINTERVAL_DIR);

        if (interval->begin->lexPrev()->variant() == LOGIF_NODE)
            LogIftoIfThen(interval->begin->lexPrev());

        if (interval->parent)
        {
            if (interval->begin->lexPrev()->variant() != DVM_INTERVAL_DIR || interval->ends[0]->lexNext()->variant() != DVM_ENDINTERVAL_DIR)
            {
                interval->begin->insertStmtBefore(*beg_inter, *interval->begin->controlParent());
                beg_inter->setlineNumber(interval->begin->lineNumber());

                interval->ends[0]->insertStmtAfter(*end_inter, *interval->begin->controlParent());
            }
        }
        else
        {
            SgStatement* currentSt = interval->begin;
            while (!isSgExecutableStatement(currentSt) || isSPF_stat(currentSt) || isDVM_stat(currentSt))
                currentSt = currentSt->lexNext();

            if (currentSt->variant() != DVM_INTERVAL_DIR || interval->ends[0]->lexPrev()->variant() != DVM_ENDINTERVAL_DIR)
            {
                currentSt->insertStmtBefore(*beg_inter, *currentSt->controlParent());
                beg_inter->setlineNumber(currentSt->lineNumber());

                interval->ends[0]->insertStmtBefore(*end_inter, *interval->ends[0]->controlParent());
            }
        }

        for (int i = 1; i < interval->ends.size(); i++)
        {
            int depth = interval->exit_levels[i];
            SpfInterval* curr_inter = interval->parent;

            SgExprListExp* expli = new SgExprListExp(*(new SgValueExp(interval->tag)));
            SgExprListExp* curr_list_elem = expli;

            for (int j = 1; j < depth; j++)
            {
                curr_list_elem->setRhs(new SgExprListExp(*(new SgValueExp(curr_inter->tag))));

                curr_inter = curr_inter->parent;
                curr_list_elem = curr_list_elem->next();
            }

            curr_list_elem->setRhs(NULL);
            SgStatement* exit_inter = new SgStatement(DVM_EXIT_INTERVAL_DIR);
            exit_inter->setExpression(0, *expli);

            if (interval->ends[i]->lexPrev()->variant() == LOGIF_NODE)
                LogIftoIfThen(interval->ends[i]->lexPrev());

            if (interval->ends[i]->lexPrev()->variant() != DVM_EXIT_INTERVAL_DIR)
                interval->ends[i]->insertStmtBefore(*exit_inter, *interval->ends[i]->controlParent());
        }
    }

    for (int i = 0; i < interval->nested.size(); i++)
        insertTree(interval->nested[i]);
}

void insertIntervals(SgFile *file, const vector<SpfInterval*> &fileIntervals)
{
    for (auto &interval : fileIntervals)
        insertTree(interval);
}

//Profiling funcs
static FileProfile parseProfiles(fstream &file)
{
    FileProfile fileProfile;
    string line;

    while (!file.eof())
    {
        getline(file, line);

        int pos_type = line.find(":");
        string type = line.substr(0, pos_type);

        if (type == "lcount")
        {
            string nums = line.substr(pos_type + 1);
            int pos_com = nums.find(",");

            int line_num = stoi(nums.substr(0, pos_com));
            long long calls_num = stoll(nums.substr(pos_com + 1));

            fileProfile.profile[line_num] = calls_num;
        }
    }

    return fileProfile;
}

static void assignRec(SpfInterval* inter, FileProfile &fp)
{
    for (int i = 0; i < inter->nested.size(); i++)
        assignRec(inter->nested[i], fp);

    inter->calls_count = fp.profile[inter->begin->lineNumber()];
}

void assignCallsToFile(const string &baseFilename, vector<SpfInterval*> &intervals)
{
    fstream file;
    file.open(baseFilename + ".gcov", fstream::in);

    if (!file.good())
        return;

    FileProfile fileProfile = parseProfiles(file);

    file.close();

    for (auto &interval : intervals)
        assignRec(interval, fileProfile);
}

//Deleting intervals funcs
static void removeNode(SpfInterval* inter, long long threshold)
{
    if (inter->calls_count > threshold)
        inter->ifInclude = false;

    for (int i = 0; i < inter->nested.size(); i++)
        removeNode(inter->nested[i], threshold);
}

void removeNodes(long long threshold, vector<SpfInterval*> &intervals, vector<string> &include_functions)
{
    if (threshold == 0)
        return;

    for (auto &interval : intervals)
    {
        string func_name = interval->begin->symbol()->identifier();

        if (include_functions.size() == 0 || find(include_functions.begin(), include_functions.end(), func_name) != include_functions.end())
            removeNode(interval, threshold);
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

SpfInterval* getMainInterval(SgProject *project, const map<string, vector<SpfInterval*>> &intervals)
{
    SgStatement *mainUnit = findMainUnit(project);
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

void uniteIntervalsBetweenProcCalls(map<string, vector<SpfInterval*>> &intervals, const map<string, vector<FuncInfo*>> &allFuncInfo)
{
    map<string, map<SgStatement*, SpfInterval*>> intervalsBySt;
    for (auto &byFile : intervals)
        for (auto &interval : byFile.second)
            intervalsBySt[byFile.first][interval->begin] = interval;

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
                            bool inV = false;
                            for (auto &elem : nearest->nested)
                                if (elem == intvl)
                                    inV = true;
                            if (inV == false)
                                nearest->nested.push_back(intvl);
                        }
                    }
                }
            }
        }
    }
}