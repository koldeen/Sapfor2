#include "CreateInterTree.h"

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
static void printTree(Interval* inter, fstream& file, int level)
{
    if(!(inter->ifInclude))
        return;

    for(int i = 0; i < level; i++) file << " ";
    file << inter->tag << " ";    
    file << "Begin " << tag[inter->begin->variant()] << " " << inter->calls << endl;

    for(int i = 0; i < inter->includes.size(); i++)
        printTree(inter->includes[i], file, level + 1);

    for(int i = 0; i < inter->ends.size(); i++)
    {
        for(int i = 0; i < level; i++) file << " ";
        file << inter->tag << " ";
        file << "End " << inter->exit_levels[i] << " " << tag[inter->ends[i]->variant()] << endl;
    }
}

void saveIntervals(SgFile *file, vector<Interval*> &fileIntervals)
{
    fstream file_intervals;

    string filename = "_";
    filename += file->filename();
    filename += ".intervals.txt";

    file_intervals.open(filename, fstream::out);
    for(auto &interval : fileIntervals)
        printTree(interval, file_intervals, 0);
    file_intervals.close();
}

//Labels funcs
static void matchGotoLabels(SgStatement *st, map<int, vector<int>> &gotoStmts)
{
    map<int, vector<int>> labelsRef;

    findAllRefsToLables(st, labelsRef, false);

    for(auto &key : labelsRef)
        for(auto &it : key.second)
            gotoStmts[it].push_back(key.first);
}

static void findAllLabels(SgStatement* st, map<int, int> &labelsRef)
{
    SgStatement* end = st->lastNodeOfStmt();

    while(st != end)
    {
        if(st->hasLabel())
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
    
    while(isSgForStmt(current_loop) && isSgControlEndStmt(controlEnd)) {
        current_loop = current_loop->lexNext();
        controlEnd = controlEnd->lexPrev();
        depth++;
    }

    return depth;
}

static void removeNestedIntervals(Interval* interval)
{
    if(isSgForStmt(interval->begin))
    {
        int depth = getNestedLevel(interval->begin);
        Interval* current_interval = interval;

        for(int i = 0; i < depth; i++)
        {
            current_interval = current_interval->includes[0];
            current_interval->ifInclude = false;
        }
    }

    for(auto &include : interval->includes)
        removeNestedIntervals(include);
}

//Tree creation funcs
static void findIntervals(Interval* interval, map<int, int> &labelsRef, map<int, vector<int>> &gotoStmts, SgStatement* &currentSt, int level)
{
    int currentVar;

    while(currentSt != interval->ends[0])
    {
        currentSt = currentSt->lexNext();
        currentVar = currentSt->variant();

        if(currentVar == RETURN_STAT || currentVar == STOP_STAT)
        {
            interval->ends.push_back(currentSt);
            interval->exit_levels.push_back(level);
        }

        if(currentVar == EXIT_STMT)
        {
            interval->ends.push_back(currentSt);
            interval->exit_levels.push_back(1);   
        }

        if(gotoStmts.find(currentSt->lineNumber()) != gotoStmts.end() && currentVar != LOGIF_NODE)
        {
            vector<int>& labels = gotoStmts[currentSt->lineNumber()];

            for(auto it = labels.begin(); it != labels.end(); it++)
            {
                int label_line = labelsRef[*it];
                int depth = 0;

                Interval* labelSearch = interval;
                while(label_line < labelSearch->begin->lineNumber() || label_line >= labelSearch->begin->lastNodeOfStmt()->lineNumber())
                {
                    labelSearch = labelSearch->parent;
                    depth++;
                }

                interval->ends.push_back(currentSt);
                interval->exit_levels.push_back(depth);
            }
        }

        if(currentSt == interval->ends[0] || currentVar != FOR_NODE)
            continue;

        Interval* inter = new Interval();
        inter->begin = currentSt;
        inter->parent = interval;
        inter->ends.push_back(currentSt->lastNodeOfStmt());
        inter->exit_levels.push_back(0);
        inter->tag = getNextTag();
        interval->includes.push_back(inter);

        findIntervals(inter, labelsRef, gotoStmts, currentSt, level + 1);
    }
}

void createInterTree(SgFile *file, vector<Interval*> &fileIntervals, bool nested_on)
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

        Interval* func_inters = new Interval();

        func_inters->begin = file->functions(i);
        func_inters->tag = getNextTag();
        
        func_inters->ends.push_back(func_inters->begin->lastNodeOfStmt());
        func_inters->exit_levels.push_back(0);

        SgStatement* currentSt = func_inters->begin;
        findIntervals(func_inters, labelsRef, gotoStmts, currentSt, 1);

        fileIntervals.push_back(func_inters);
    }

    if(nested_on)
        for(auto &interval : fileIntervals)
            removeNestedIntervals(interval);
}

//Interval insertion funcs
static void LogIftoIfThen(SgStatement *stmt)
{
    SgControlEndStmt *control = new SgControlEndStmt();
    stmt->setVariant(IF_NODE);
    (stmt->lexNext())->insertStmtAfter(* control,*stmt);

    if (stmt->numberOfAttributes(OMP_MARK) > 0)
        control->addAttribute(OMP_MARK);
}

static void insertTree(Interval* interval)
{
    if(interval->ifInclude)
    {
        SgStatement* beg_inter = new SgStatement(DVM_INTERVAL_DIR);
        SgExpression* expr = new SgValueExp(interval->tag);
        beg_inter->setExpression(0, *expr);

        SgStatement* end_inter = new SgStatement(DVM_ENDINTERVAL_DIR);

        if(interval->begin->lexPrev()->variant() == LOGIF_NODE)
                LogIftoIfThen(interval->begin->lexPrev());

        if(interval->parent)
        {
            if(interval->begin->lexPrev()->variant() != DVM_INTERVAL_DIR || interval->ends[0]->lexNext()->variant() != DVM_ENDINTERVAL_DIR)
            {
                interval->begin->insertStmtBefore(*beg_inter, *interval->begin->controlParent());
                interval->ends[0]->insertStmtAfter(*end_inter, *interval->begin->controlParent());
            }
        }
        else
        {
            SgStatement* currentSt = interval->begin;
            while(!isSgExecutableStatement(currentSt)) currentSt = currentSt->lexNext();

            if(currentSt->variant() != DVM_INTERVAL_DIR || interval->ends[0]->lexPrev()->variant() != DVM_ENDINTERVAL_DIR)
            {
                currentSt->insertStmtBefore(*beg_inter, *currentSt->controlParent());
                interval->ends[0]->insertStmtBefore(*end_inter, *interval->ends[0]->controlParent());
            }
        }

        for(int i = 1; i < interval->ends.size(); i++)
        {
            int depth = interval->exit_levels[i];
            Interval* curr_inter = interval->parent;

            SgExprListExp* expli = new SgExprListExp(*(new SgValueExp(interval->tag)));
            SgExprListExp* curr_list_elem = expli;

            for(int j = 1; j < depth; j++)
            {
                curr_list_elem->setRhs(new SgExprListExp(*(new SgValueExp(curr_inter->tag))));
                
                curr_inter = curr_inter->parent;
                curr_list_elem = curr_list_elem->next();
            }

            curr_list_elem->setRhs(NULL);
            SgStatement* exit_inter = new SgStatement(DVM_EXIT_INTERVAL_DIR);
            exit_inter->setExpression(0, *expli);

            if(interval->ends[i]->lexPrev()->variant() == LOGIF_NODE)
                LogIftoIfThen(interval->ends[i]->lexPrev());

            if(interval->ends[i]->lexPrev()->variant() != DVM_EXIT_INTERVAL_DIR)
                interval->ends[i]->insertStmtBefore(*exit_inter, *interval->ends[i]->controlParent());
        }
    }

    for(int i = 0; i < interval->includes.size(); i++)
        insertTree(interval->includes[i]);
}

void insertIntervals(SgFile *file, const vector<Interval*> &fileIntervals)
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

static void assignRec(Interval* inter, FileProfile &fp)
{
    for(int i = 0; i < inter->includes.size(); i++)
        assignRec(inter->includes[i], fp);

    inter->calls = fp.profile[inter->begin->lineNumber()];
}

void assignCallsToFile(const string &baseFilename, vector<Interval*> &intervals)
{
    fstream file;
    file.open(baseFilename + ".gcov", fstream::in);

    if(!file.good())
        return;

    FileProfile fileProfile = parseProfiles(file);

    file.close();

    for(auto &interval : intervals)
        assignRec(interval, fileProfile);
}

//Deleting intervals funcs
static void removeNode(Interval* inter, long long threshold)
{
    if(inter->calls > threshold)
        inter->ifInclude = false;

    for(int i = 0; i < inter->includes.size(); i++)
        removeNode(inter->includes[i], threshold);
}

void removeNodes(long long threshold, vector<Interval*> &intervals, vector<string> &include_functions)
{
    if(threshold == 0)
        return;

    for (auto &interval : intervals)
    {
        string func_name = interval->begin->symbol()->identifier();

        if(include_functions.size() == 0 || find(include_functions.begin(), include_functions.end(), func_name) != include_functions.end())
            removeNode(interval, threshold);    
    }
}