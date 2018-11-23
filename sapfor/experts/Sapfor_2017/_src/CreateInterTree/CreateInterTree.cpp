#include "CreateInterTree.h"

using std::string;
using std::vector;
using std::map;
using std::cout;
using std::endl;
using std::ifstream;

//Debug funcs
void printTree(Interval* inter)
{
    if(!(inter->ifInclude))
        return;

    cout << inter->tag << " ";
    cout << "Begin " << tag[inter->begin->variant()] << " " << inter->calls << endl;

    for(int i = 0; i < inter->includes.size(); i++)
        printTree(inter->includes[i]);

    for(int i = 0; i < inter->ends.size(); i++)
    {
        cout << inter->tag << " ";
        cout << "End " << inter->exit_levels[i] << " " << tag[inter->ends[i]->variant()] << endl;
    }
}

//Labels funcs
static void matchGotoLabels(SgStatement *st, map<int, vector<int>> &gotoStmts)
{
    map<int, vector<int>> labelsRef;

    findAllRefsToLables(st, labelsRef);

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

//Tree creation funcs
static bool checkIfHasCall(SgExpression* exp)
{
    if(exp)
    {
        if(exp->variant() == FUNC_CALL)
            return true;

        return checkIfHasCall(exp->lhs()) || (checkIfHasCall(exp->rhs()));
    }

    return false;
}

static void findIntervals(Interval* interval, map<int, int> &labelsRef, map<int, vector<int>> &gotoStmts, SgStatement* &currentSt, int level)
{
    bool if_has_call;
    int currentVar;

    while(currentSt != interval->ends[0])
    {
        currentSt = currentSt->lexNext();

        if_has_call = checkIfHasCall(currentSt->expr(0)) || checkIfHasCall(currentSt->expr(1)) || checkIfHasCall(currentSt->expr(2));
        currentVar = currentSt->variant();

        if(currentVar == RETURN_STAT)
        {
            interval->ends.push_back(currentSt);
            interval->exit_levels.push_back(level);
        }

        if(currentVar == EXIT_STMT)
        {
            interval->ends.push_back(currentSt);
            interval->exit_levels.push_back(1);   
        }

        if(gotoStmts.find(currentSt->lineNumber()) != gotoStmts.end())
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

        if(currentSt == interval->ends[0] || currentVar != FOR_NODE && currentVar != PROC_STAT && !if_has_call)
            continue;

        Interval* inter = new Interval();
        inter->begin = currentSt;
        inter->parent = interval;
        inter->ends.push_back(currentSt->lastNodeOfStmt());
        inter->exit_levels.push_back(0);
        inter->tag = interval->tag + 1;
        interval->includes.push_back(inter);

        findIntervals(inter, labelsRef, gotoStmts, currentSt, level + 1);
    }
}

void createInterTree(SgFile *file, vector<Interval*> &fileIntervals)
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
        
        func_inters->ends.push_back(func_inters->begin->lastNodeOfStmt());
        func_inters->exit_levels.push_back(0);

        SgStatement* currentSt = func_inters->begin;
        findIntervals(func_inters, labelsRef, gotoStmts, currentSt, 1);

        fileIntervals.push_back(func_inters);
    }
}

//Interval insertion funcs
static void insertTree(Interval* interval)
{
    if(interval->ifInclude)
    {
        SgStatement* beg_inter = new SgStatement(DVM_INTERVAL_DIR);
        SgExpression* expr = new SgValueExp(interval->tag);
        beg_inter->setExpression(0, *expr);

        SgStatement* end_inter = new SgStatement(DVM_ENDINTERVAL_DIR);

        //while(!isSgExecutableStatement(begin)) 
         //   begin = begin->lexNext();

        interval->begin->insertStmtBefore(*beg_inter, *interval->begin->controlParent());
        if(interval->tag)
            interval->ends[0]->insertStmtAfter(*end_inter, *interval->ends[0]->controlParent());
        else
            interval->ends[0]->insertStmtBefore(*end_inter, *interval->ends[0]->controlParent());

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
static FileProfile parseProfiles(const string &filename)
{
    FileProfile fileProfile;
    ifstream file;
    string line;

    file.open(filename);

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
            int calls_num = stoi(nums.substr(pos_com + 1));

            fileProfile.profile[line_num] = calls_num;
        }
    }
    file.close();

    return fileProfile;
}

static void assignRec(Interval* inter, FileProfile &fp)
{
    for(int i = 0; i < inter->includes.size(); i++)
        assignRec(inter->includes[i], fp);

    if(inter->tag)
        inter->calls = fp.profile[inter->begin->lineNumber()];
    else
        inter->calls = fp.profile[inter->begin->controlParent()->lineNumber()];
}

void assignCallsToFile(const string &baseFilename, vector<Interval*> &intervals)
{
    FileProfile fileProfile = parseProfiles(baseFilename + ".gcov");

    for(auto &interval : intervals){
        assignRec(interval, fileProfile);
        printTree(interval);
    }
}

//Deleting intervals funcs
static void removeNode(Interval* inter, int threshold)
{
    if(inter->calls > threshold)
        inter->ifInclude = false;

    for(int i = 0; i < inter->includes.size(); i++)
        removeNode(inter->includes[i], threshold);
}

void removeNodes(int threshold, map<string, vector<Interval*>> &allIntervals)
{
    for (auto &byFile : allIntervals)
        for (auto &interval : byFile.second)
            removeNode(interval, threshold);    
}