#include "CreateInterTree.h"

std::vector<FileIntervals> fileIntervals;

//Debug funcs
void printTree(Interval* inter)
{
    if(!(inter->ifInclude))
        return;

    std::cout << inter->tag << " ";
    std::cout << "Begin " << tag[inter->begin->variant()] << " " << inter->begin->lineNumber() << " " << std::endl;

    for(int i = 0; i < inter->includes.size(); i++)
        printTree(inter->includes[i]);

    for(int i = 0; i < inter->ends.size(); i++)
    {
        std::cout << inter->tag << " ";
        std::cout << "End " << inter->exit_levels[i] << " " << tag[inter->ends[i]->variant()] << std::endl;
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

static void findIntervals(Interval* interval, SgStatement* &currentSt, int level)
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

        if(currentVar == GOTO_NODE)
        {

        }

        if(currentVar == ASSGOTO_NODE)
        {

        }

        if(currentVar == COMGOTO_NODE)
        {

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

        findIntervals(inter, currentSt, level + 1);
    }
}

void createInterTree(SgFile *file)
{
    FileIntervals fi;

    int funcNum = file->numberOfFunctions();

    for (int i = 0; i < funcNum; i++)
    {
        Interval* func_inters = new Interval();

        SgStatement* begin = file->functions(i)->lexNext();
        while(!isSgExecutableStatement(begin)) 
            begin = begin->lexNext();
        func_inters->begin = begin;
        
        func_inters->ends.push_back(file->functions(i)->lastNodeOfStmt());
        func_inters->exit_levels.push_back(0);

        SgStatement* currentSt = func_inters->begin;
        findIntervals(func_inters, currentSt, 1);

        fi.intervals.push_back(func_inters);
    }

    fileIntervals.push_back(fi);

    for(int i = 0; i < fi.intervals.size(); i++)
        printTree(fi.intervals[i]);
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

void insertIntervals()
{
    for(int i = 0; i < fileIntervals.size(); i++)
        for(int j = 0; j < fileIntervals[i].intervals.size(); j++)
            insertTree(fileIntervals[i].intervals[j]);
}

//Profiling funcs
static std::vector<FileProfile> parseProfiles(std::vector<std::string> &filenames)
{
    std::vector<FileProfile> fileProfiles;
    std::ifstream file;
    std::string line;

    for(int i = 0; i < filenames.size(); i++)
    {
        FileProfile f;
        file.open(filenames[i]);

        while(!file.eof())
        {
            std::getline(file, line);

            int pos_type = line.find(":");
            std::string type = line.substr(0, pos_type);

            if(type == "lcount")
            {
                std::string nums = line.substr(pos_type + 1);
                int pos_com = nums.find(",");

                int line_num = std::stoi(nums.substr(0, pos_com));
                int calls_num = std::stoi(nums.substr(pos_com + 1));

                f.profile[line_num] = calls_num;
            }
        }

        file.close();
        fileProfiles.push_back(f);
    }

    return fileProfiles;
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

static void assignCallsToFile(FileIntervals &fi, FileProfile &fp)
{
    for(int i = 0; i < fi.intervals.size(); i++)
        assignRec(fi.intervals[i], fp);
}

void assignCallsToAllFiles(std::vector<std::string> filenames)
{
    std::vector<FileProfile> fileProfiles = parseProfiles(filenames);

    for(int i = 0; i < fileIntervals.size(); i++)
        assignCallsToFile(fileIntervals[i], fileProfiles[i]);
}

//Deleting intervals funcs
static void removeNode(Interval* inter, int threshold)
{
    if(inter->calls > threshold)
        inter->ifInclude = false;

    for(int i = 0; i < inter->includes.size(); i++)
        removeNode(inter->includes[i], threshold);
}

static void removeFromFile(FileIntervals &fi, int threshold)
{
    for(int i = 0; i < fi.intervals.size(); i++)
        removeNode(fi.intervals[i], threshold);
}

void removeNodes(int threshold)
{
    for(int i = 0; i < fileIntervals.size(); i++)
        removeFromFile(fileIntervals[i], threshold);
}