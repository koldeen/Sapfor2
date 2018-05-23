#include "CreateInterTree.h"

std::vector<FileIntervals> fileIntervals;

//Debug funcs
void printTree(Interval* inter, int depth = 0)
{
    if(!(inter->ifInclude))
        return;

    for(int i = 0; i < depth; i++) std::cout << "  ";
    std::cout << "Begin " << tag[inter->begin->variant()] << " " << inter->calls << " " << std::endl;

    for(int i = 0; i < inter->includes.size(); i++)
        printTree(inter->includes[i], depth + 1);

    for(int i = 0; i < inter->ends.size(); i++)
    {
        for(int j = 0; j < depth; j++) std::cout << "  ";
        std::cout << "End " << i << " " << tag[inter->ends[i]->variant()] << std::endl;
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

static void findIntervals(Interval* interval, SgStatement* &currentSt)
{
    bool if_has_call;
    int currentVar;

    while(currentSt != interval->ends[0])
    {
        currentSt = currentSt->lexNext();

        if_has_call = checkIfHasCall(currentSt->expr(0)) || checkIfHasCall(currentSt->expr(1)) || checkIfHasCall(currentSt->expr(2));
        currentVar = currentSt->variant();

        if(currentVar == GOTO_NODE)
        {
            continue;
        }

        if(currentVar == RETURN_STAT || currentVar == EXIT_STMT)
            interval->ends.push_back(currentSt);

        if(currentSt == interval->ends[0])
        {
            continue;
        }

        if(currentVar != FOR_NODE && currentVar != PROG_HEDR && currentVar != FUNC_HEDR && currentVar != PROC_HEDR & currentVar != PROC_STAT && !if_has_call)
            continue;

        Interval* inter = new Interval();
        inter->begin = currentSt;
        inter->ends.push_back(currentSt->lastNodeOfStmt());
        interval->includes.push_back(inter);

        findIntervals(inter, currentSt);
    }
}

void createInterTree(SgFile *file)
{
    FileIntervals fi;

    int funcNum = file->numberOfFunctions();

    for (int i = 0; i < funcNum; i++)
    {
        Interval* func_inters = new Interval();
        func_inters->begin = file->functions(i);
        func_inters->ends.push_back(func_inters->begin->lastNodeOfStmt());

        SgStatement* currentSt = func_inters->begin;
        findIntervals(func_inters, currentSt);

        fi.intervals.push_back(func_inters);
    }

    fileIntervals.push_back(fi);
}

//Interval insertion funcs
static void insertTree(Interval* interval, int &i_inter)
{
    SgStatement* beg_inter = new SgStatement(DVM_INTERVAL_DIR);
    SgExpression* expr = new SgValueExp(i_inter);
    beg_inter->setExpression(0, *expr);
    i_inter++;

    SgStatement* end_inter = new SgStatement(DVM_ENDINTERVAL_DIR);

    interval->begin->insertStmtAfter(*beg_inter, *interval->begin->controlParent());
    interval->ends[0]->insertStmtAfter(*end_inter, *interval->ends[0]->controlParent());

    for(int i = 0; i < interval->includes.size(); i++)
        insertTree(interval->includes[i], i_inter);
}

void insertIntervals()
{
    int i_inter;

    for(int i = 0; i < fileIntervals.size(); i++)
    {
        i_inter = 0;
        for(int j = 0; j < fileIntervals[i].intervals.size(); j++)
            insertTree(fileIntervals[i].intervals[j], i_inter);
    }
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

    inter->calls = fp.profile[inter->begin->lineNumber()];
}

static void assignCallsToFile(FileIntervals &fi, FileProfile &fp)
{
    for(int i = 0; i < fi.intervals.size(); i++)
    {
        fi.intervals[i]->calls = fp.profile[fi.intervals[i]->begin->lineNumber()];
        assignRec(fi.intervals[i], fp);
    }
}

void assignCallsToAllFiles(std::vector<std::string> filenames)
{
    for(int i = 0; i < filenames.size(); i++)
        filenames[i] = filenames[i].append(".gcov");

    std::vector<FileProfile> fileProfiles = parseProfiles(filenames);

    for(int i = 0; i < fileIntervals.size(); i++)
        assignCallsToFile(fileIntervals[i], fileProfiles[i]);
}

//Deleting intervals funcs
static void removeNode(Interval* inter, int threshold)
{
    std::vector<Interval*> &func = inter->includes;
    for(int i = 0; i < func.size(); i++)
       if(func[i]->calls > threshold)
       {
            for(int j = 0; j < func[i]->includes.size(); j++)
                func.push_back(func[i]->includes[j]);
            func[i]->ifInclude = false;
        } 
        else
            removeNode(func[i], threshold);
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