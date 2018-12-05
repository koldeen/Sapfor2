#include "../Utils/leak_detector.h"
//#define _CRT_SECURE_NO_WARNINGS

#include <iomanip>
#include <vector>
#include <map>
#include <set>

#ifdef _MSC_VER
/*Windows*/
#include <io.h>
#else
/*Unix*/
#include <sys/types.h>
#include <dirent.h>
#endif

#include "../Distribution/Distribution.h"
#include "../Distribution/DvmhDirective.h"
#include "../GraphLoop/graph_loops.h"

#include "PredictorInterface.h"
#include "PredictorModel.h"


using std::vector;
using std::map;
using std::set;
using std::to_string;

//from xp.cpp
vector<struct routine> routines;
int curr_routine;
int curr_gvar;
vector<vect_int> all_Gvar; // array[Nsubr] - a global variant
int  *Fvar; // array[Nsubr+1] - the first variant for i-th subroutine	// so that  Fvar[Nsubr]==Nvars
vector<one_routine_all_scheme> all_scheme;
vector<struct var> vars;
struct res *result, curr;
vector<struct expr> expressions;
//extern ofstream log_file;
vector<struct task_var> task_variants;
int curr_task_var;
int default_task_var;
long main_routine_line;
float RemoteTime;

//TaskVariant *CurrTaskVariant;
int loop_rank;
long lastLR;
bool last_body_is_loop;
int curr_proc_set;
vector<vect_long> proc_set;

vector<struct mach> mach_set;
vector<struct proc_set> proc_sets;
int curr_mach;

const char* CONFIG_ProcSet = "*.cps";
const char* CONFIG_MachSet = "*.cms";
const char* CONFIG_TaskSet = "*.cts";

// xp-settings max_dim=10
const char max_dim = 10;

struct dis_pat //шаблон распределения
{
    int rank;
    char dim[max_dim]; //0=*, 1=BLOCK
};

struct ali_pat //шаблон выравнивания
{
    int rank;
    long varid; //индекс переменной в таблице vars
    long axis[max_dim]; //стоит использовать вектор
    long coef[max_dim];
    long cons[max_dim];
};

struct circle
{
    int rank;
    double time; //время в каких-то единицах, идеально в секундах. Я использую секунды.
    long init[max_dim]; //стоит использовать вектор
    long last[max_dim];
    long step[max_dim];
};

struct reduct
{
    bool is; // есть ли она вообще для этого параллельного цикла
    int loc_type;
    long red_arr_len;
    int red_arr_type;
};

struct shadow
{
    bool is; // есть ли она вообще для этого параллельного цикла
    struct var *v; //ссылка на массив, элементы которого будут передаваться
    bool is_wid; //заданы ли теневые грани в этой директиве, или надо брать по умолчанию
    bool corner;
    int rank;
    int low_wid[max_dim]; //если заданы то эти вектора тоже долны быть заданы.
    int hi_wid[max_dim];
};

struct across
{
    bool is; // есть ли она вообще для этого параллельного цикла
    struct var *v; //ссылка на массив, элементы которого зависят по данным
    int low_wid[max_dim]; //границы зависимости (тоже лучше вектора)
    int hi_wid[max_dim];
};

struct remote
{
    long loop_addr_ref;
    struct var *v; //ссылка на массив, элементы которого располагаются удаленно
    long axis[max_dim]; //удаленные элементы (тоже лучше вектора)
    long coef[max_dim];
    long cons[max_dim];
};

struct remote lastrem;

vector<struct reduct> r_few;
vector<struct shadow> s_few;
vector<struct across> a_few;
vector<struct remote> rem_few;


/*
struct seq_loop
{	long beg_line;
    long end_line;
    long times;
    bool ifgoto; //флаг того, что надо пробегать цикл, а не умножать время витка на его количество
};
*/



long cur_amv, cur_ps; //попробую без cur_amv_ptr (считая его = cur_amv)
long addr;

Interval *SeqLoopInterval;
Interval *RemoteCommInterval;
long cur_res, result_cnt;

void Interval_node::print(int level)
{
    int i;

    for (i = 0; i < level; i++)
        printf(" ");

    if (this->inter != NULL)
    {
        if (this->iter_count == -1)
            printf("interval[line=%d]=%.15f (seq=%.15f)\n", this->line, this->inter->Execution_time, this->inter->GetPred(_Productive_CPU_time));
        else
            printf("interval[line=%d]=%.15f (seq=%.15f) times=%.0f\n", this->line, this->inter->Execution_time, this->inter->GetPred(_Productive_CPU_time), this->iter_count);
    }
    else
        printf("interval[line=%d] NULL times=%.0f\n", this->line, this->iter_count);

    for (i = 0; i < this->children.size(); i++)
        this->children[i]->print(level + 2);
}

void Interval_node::calc(double times)
{
    int i;

    printf("Calc loop %d\n", this->line);

    for (i = 0; i < children.size(); i++)
    {
        if (this->iter_count != -1)
        {
            printf("  call calc for loop %d child=%d\n", this->line, children[i]->line);
            children[i]->calc(this->iter_count * times);
        }
        else
            children[i]->calc(times);
    }

    if (this->inter == NULL)
    {
        Interval *tmp_inter;
        tmp_inter = new Interval(0);
        tmp_inter->Integrate();

        for (i = 0; i < children.size(); i++)
            tmp_inter->copy_poss(children[i]->inter, 1, 1);

        this->inter = tmp_inter;
        inter->CalcIdleAndImbalance();
        inter->Integrate();

        if (children.size() == 1)
        {
            for (i = 0; i < children[0]->children.size(); i++)
                this->children.push_back(children[0]->children[i]);

            this->children.erase(children.begin());
        }

    }
    else
    {
        Interval *tmp_inter;
        tmp_inter = new Interval(0);
        tmp_inter->Integrate();

        tmp_inter->copy(inter);

        inter = new Interval(0);
        inter->Integrate();

        inter->copy_poss(tmp_inter, 0, times);
        inter->CalcIdleAndImbalance();

        printf("try to integrate loop %d  times=%f\n", this->line, times);
        inter->Integrate();
    }
}

//поиск вглубь и снизу
Interval_node *find_node(Interval_node *parent, long line)
{
    int i;
    Interval_node *res, *res_best;

    res = NULL;
    for (i = 0; i < parent->children.size(); i++)
    {
        res = find_node(parent->children[i], line);
        if (res != NULL)
            return res;
    }

    if (parent->line == line)
        return parent;
    else
        return NULL;
}

//поиск вглубь
Interval_node *find_node_of_closest_parent(Interval_node *root, struct loop *curr_loop)
{
    int i;
    Interval_node *node;

    struct loop *tmp_loop;

    tmp_loop = curr_loop;

    while (tmp_loop != NULL)
    {
        node = find_node(root, tmp_loop->line);
        if (node != NULL)
            return node;

        tmp_loop = tmp_loop->parent;
    }

    return NULL;
}


void Interval_node::add(struct loop *curr_loop, Interval *tmp_inter, int type, double times)
{
    int i;
    Interval_node *tmp_node, *node;
    Interval *save_inter;

    //	printf("Inter::add %d %d type=%d times=%d \n",curr_loop->line, curr_loop, type, (long)times);
    printf("Inter::add loop=%d times=%d \n", curr_loop->line, (long)times);
    //	printf("node line=%d\n",this->line);

    tmp_node = new Interval_node;
    tmp_node->inter = new Interval(0);
    tmp_node->line = curr_loop->line;
    tmp_node->type = type;
    tmp_node->iter_count = times;
    if (tmp_inter == NULL)
        tmp_node->inter = NULL;
    else
    {
        tmp_node->inter->copy(tmp_inter);
        tmp_node->inter->CalcIdleAndImbalance();
        tmp_node->inter->Integrate();
    }

    this->children.push_back(tmp_node);
}

// процедура позволяет две вещи - расписывать число повторений (times) по дереву
// и записывать в дерево интервалы, когда указано tmp_inter!=NULL
void Interval_node::insert(struct loop *curr_loop, Interval *tmp_inter, int type, double times)
{
    int i;
    Interval_node *node;

    if (curr_loop == NULL)
        return;

    if (tmp_inter != NULL)
    {
        node = find_node_of_closest_parent(this, curr_loop);

        //		printf("tmp_inter!=NULL\n");

        if (node != NULL)
        {
            //			printf("insert::node=%d  curr_loop->line=%d\n",node->line, curr_loop->line);

            for (i = 0; i < node->children.size(); i++)
            {
                if (node->children[i]->line == curr_loop->line)
                {
                    node = node->children[i];
                    break;
                }
            }
            //			printf("insert::node=%d\n",node->line);

            node->add(curr_loop, tmp_inter, type, times);
        }
        else
        {
            //			printf("insert::node=NULL curr_loop->line=%d\n",curr_loop->line);
            this->add(curr_loop, tmp_inter, type, times);
        }
    }
    else
    {
        node = find_node_of_closest_parent(this, curr_loop);

        if (node != NULL)
            node->add(curr_loop, tmp_inter, type, times);
        else
            this->add(curr_loop, tmp_inter, type, times);

    }
}

struct loop* Find_loop_id_tree(struct loop* curr_loop, int line)
{
    int i;
    struct loop* res;

    if (curr_loop == NULL)
        return NULL;

    if (curr_loop->line == line)
        return curr_loop;

    for (i = 0; i < curr_loop->children.size(); i++)
    {
        res = Find_loop_id_tree(curr_loop->children[i], line);
        if (res != NULL)
            return res;
    }

    return NULL;
}

struct loop* Find_loop_id_tree(int line)
{
    int i;
    struct loop* res;

    for (i = 0; i < routines.size(); i++)
    {
        res = Find_loop_id_tree(routines[i].root, line);
        if (res != NULL)
            return res;
    }
    return NULL;
}

//===================================================================================================
void setVectorCallRet(FuncCall *f)
{
    int k;
    // если у каждого процессора своя мощность, то надо заполнить вектор vcall_time следующим образом. 
    // В предикторе это делалось автоматически при чтении трассы из файла


    f->vcall_time.resize(currentVM->getProcCount());
    for (k = 0; k < currentVM->getProcCount(); k++)
        f->vcall_time[k] = f->call_time / currentVM->getProcPower(k);

    f->vret_time.resize(currentVM->getProcCount());
    for (k = 0; k < currentVM->getProcCount(); k++)
        f->vret_time[k] = f->ret_time / currentVM->getProcPower(k);
    //printf("Func call\n");

}

int	printInterval(Interval *inter)
{
    int proc_no;

    for (proc_no = 0; proc_no < MPSProcCount(); proc_no++)
    {
        printf("proc[%d].Execution_time = %.8f\n", proc_no, inter->GetProcPred(proc_no, _Execution_time));
        printf("proc[%d].CPU_time = %.8f\n", proc_no, inter->GetProcPred(proc_no, _CPU_time));
        printf("proc[%d].CPU_time_usr = %.8f   and 2x=%.8f\n", proc_no, inter->GetProcPred(proc_no, _CPU_time_usr), 2 * inter->GetProcPred(proc_no, _CPU_time_usr));
        printf("proc[%d].CPU_time_sys = %.8f\n", proc_no, inter->GetProcPred(proc_no, _CPU_time_sys));
        printf("proc[%d].Lost_time = %.8f\n", proc_no, inter->GetProcPred(proc_no, _Lost_time));
        printf("proc[%d].Insuff_parallelism_usr = %.8f\n", proc_no, inter->GetProcPred(proc_no, _Insuff_parallelism_usr));
        printf("proc[%d].Insuff_parallelism_sys = %.8f\n", proc_no, inter->GetProcPred(proc_no, _Insuff_parallelism_sys));
        printf("proc[%d].Communication = %.8f\n", proc_no, inter->GetProcPred(proc_no, _Communication));
        printf("proc[%d].Idle = %.8f\n", proc_no, inter->GetProcPred(proc_no, _Idle));
        printf("\n");
    }
    return 0;
}

//====================================== model ====================================================================
//============== 
static long arrayAddr = 1;
static long arrayAddrPtr = 10000;
static long ids = 1;
static long loopIds = 1;
static long redShIds = 1;

static map<DIST::Array*, long> mapArrayAddrs;
static map<DIST::Array*, long> mapArrayAddrsPtr;
static map<DIST::Array*, long> mapIds;
static map<LoopGraph*, long> mapLoopIds;

template<typename T>
static long getId(T object, map<T, long> &dict, long &counter)
{
    auto it = dict.find(object);
    if (it == dict.end())
        dict[object] = counter++;
    return dict[object];
}

static int Model_distr(DIST::Array *array, const DistrVariant *distrVar, FILE *printOut = NULL)
{
    string debug = "";
    {
        FuncCall f;
        f.func_id = crtamv_;
        crtamv_Info *tmp_params = new crtamv_Info;
        f.call_params = (void *)tmp_params; // point to parameters

        tmp_params->AM_ID = cur_amv; //possible not
        tmp_params->ID = getId(array, mapIds, ids); //для различия

        auto sizes = array->GetSizes();
        tmp_params->SizeArray.resize(sizes.size());
        const int rank = (int)sizes.size();
        for (int i = rank - 1; i >= 0; --i)
            tmp_params->SizeArray[rank - 1 - i] = sizes[i].second - sizes[i].first + 1;
        tmp_params->StaticSign = 0; //possible not

        cur_amv = tmp_params->ID;

        f.call_time = 0.00000100;		// call time
        f.ret_time = 0.00000100;		// return time
        setVectorCallRet(&f);

        if (printOut)
        {
            debug += "crtamv SizeArray=";
            printf("crtamv SizeArray=");
            for (int i = 0; i < tmp_params->SizeArray.size(); ++i)
                debug += " " + to_string(tmp_params->SizeArray[i]);
            debug += "\n";
        }

        f.crtamv();
    }

    {
        FuncCall f;
        f.func_id = distr_;
        distr_Info *tmp_params = new distr_Info;
        f.call_params = (void *)tmp_params; // point to parameters

        tmp_params->ID = cur_amv;
        tmp_params->PSRef = cur_ps;
        tmp_params->AxisArray.resize(0);
        tmp_params->DistrParamArray.resize(0);

        for (int i = 0; i < array->GetDimSize(); ++i)
        {
            if (distrVar->distRule[i] == dist::BLOCK)
            {
                tmp_params->AxisArray.push_back(array->GetDimSize() - i);
                tmp_params->DistrParamArray.push_back(0); //possible not
            }
        }

        if (printOut)
        {
            debug += "distr AxisArray=";
            for (int i = 0; i < tmp_params->AxisArray.size(); ++i)
                debug += " " + to_string(tmp_params->AxisArray[i]);
            debug += "\n";
        }

        f.call_time = 0.00000100;		// call time
        f.ret_time = 0.00000100;		// return time
        setVectorCallRet(&f);

        f.distr();
    }

    {
        FuncCall f;
        f.func_id = crtda_;
        crtda_Info* tmp_params = new crtda_Info;
        f.call_params = (void *)tmp_params; // point to parameters

        const int rank = array->GetDimSize();

        tmp_params->ArrayHeader = getId(array, mapArrayAddrs, arrayAddr);//для различия
        tmp_params->ArrayHandlePtr = getId(array, mapArrayAddrsPtr, arrayAddrPtr);//для различия
        tmp_params->ReDistrSign = 0; //poss not 3
        tmp_params->StaticSign = 0; //poss not
        tmp_params->TypeSize = array->GetTypeSize();
        tmp_params->SizeArray.resize(rank);
        tmp_params->LowShdWidthArray.resize(rank);
        tmp_params->HiShdWidthArray.resize(rank);
                
        auto sizes = array->GetSizes();
        auto shadow = array->GetShadowSpec();
        for (int i = rank - 1; i >= 0; --i)
        {
            tmp_params->SizeArray[rank - 1 - i] = sizes[i].second - sizes[i].first + 1;
            tmp_params->LowShdWidthArray[rank - 1 - i] = shadow[i].first;
            tmp_params->HiShdWidthArray[rank - 1 - i] = shadow[i].second;
        }

        f.call_time = 0.00000100;		// call time
        f.ret_time = 0.00000100;		// return time
        setVectorCallRet(&f);

        if (printOut)
        {
            debug += "d crtda " + array->GetName() + "addr=" + to_string(tmp_params->ArrayHeader) + "\n";
            debug += "d crtda SizeArray=";

            for (int i = 0; i < tmp_params->SizeArray.size(); ++i)
                debug += " " + to_string(tmp_params->SizeArray[i]);
            debug += "\n";

            debug += "d crtda LowShdWidthArray=";            
            for (int i = 0; i < tmp_params->LowShdWidthArray.size(); ++i)
                debug += " " + to_string(tmp_params->LowShdWidthArray[i]);
            debug += "\n";

            debug += "d crtda HiShdWidthArray=";
            for (int i = 0; i < tmp_params->HiShdWidthArray.size(); ++i)
                debug += " " + to_string(tmp_params->HiShdWidthArray[i]);
            debug += "\n";
        }

        f.crtda();
    }

    {
        FuncCall f;
        f.func_id = align_;
        align_Info* tmp_params = new align_Info;
        f.call_params = (void *)tmp_params; // point to parameters

        tmp_params->ArrayHeader = getId(array, mapArrayAddrs, arrayAddr);//для различия
        tmp_params->ArrayHandlePtr = getId(array, mapArrayAddrsPtr, arrayAddrPtr);//для различия
        tmp_params->PatternRef = cur_amv;
        tmp_params->PatternRefPtr = cur_amv;
        tmp_params->PatternType = 1; //AMView

        tmp_params->AxisArray.resize(array->GetDimSize());
        tmp_params->CoeffArray.resize(array->GetDimSize());
        tmp_params->ConstArray.resize(array->GetDimSize());
        const int rank = array->GetDimSize();
        for (int i = 0; i < rank; ++i)
        {
            tmp_params->AxisArray[i] = i + 1;
            if (distrVar->distRule[rank - 1 - i] == dist::BLOCK)
                tmp_params->ConstArray[i] = 0 - array->GetSizes()[rank - 1 - i].first;
            else
                tmp_params->ConstArray[i] = 0;
            tmp_params->CoeffArray[i] = 1;
        }

        if (printOut)
        {
            debug += "d align AxisArray=";
            for (int i = 0; i < tmp_params->AxisArray.size(); ++i)
                debug += " " + to_string(tmp_params->AxisArray[i]);
            debug += "\n";
        }
        f.call_time = 0.00000100;		// call time
        f.ret_time = 0.00000100;		// return time
        setVectorCallRet(&f);

        f.align();
    }

    if (printOut)
        fprintf(printOut, "%s", debug.c_str());
    return 0;
}

static int Model_align(DIST::Array *array, const int regId, FILE *printOut = NULL)
{
    DIST::Array *templ = array->GetTemplateArray(regId);
    auto rule = array->GetAlignRulesWithTemplate(regId);
    auto links = array->GetLinksWithTemplate(regId);

    const int rank = array->GetDimSize();
    string debug = "";
    {
        FuncCall f;
        f.func_id = crtda_;
        crtda_Info* tmp_params = new crtda_Info;
        f.call_params = (void *)tmp_params; // point to parameters

        tmp_params->ArrayHeader = getId(array, mapArrayAddrs, arrayAddr);//для различия
        tmp_params->ArrayHandlePtr = getId(array, mapArrayAddrsPtr, arrayAddrPtr);//для различия
        tmp_params->ReDistrSign = 0;
        tmp_params->StaticSign = 0; //poss not
        tmp_params->TypeSize = array->GetTypeSize(); //ch!!!
        tmp_params->SizeArray.resize(rank);
        tmp_params->LowShdWidthArray.resize(rank);
        tmp_params->HiShdWidthArray.resize(rank);

        auto shadow = array->GetShadowSpec();
        debug += "v1->rank=" + to_string(rank) + "  s->rank=" + to_string(shadow.size()) + "\n";
        debug += "Sh_low ";
        for (int i = 0; i < shadow.size(); ++i)
            debug += " " + to_string(shadow[i].first);
        debug += "\n";
        debug += "Sh_high ";        
        for (int i = 0; i < shadow.size(); ++i)
            debug += " " + to_string(shadow[i].second);
        debug += "\n";

        auto sizes = array->GetSizes();
        for (int i = rank - 1; i >= 0; --i)
        {
            tmp_params->SizeArray[rank - 1 - i] = sizes[i].second - sizes[i].first + 1;
            tmp_params->LowShdWidthArray[rank - 1 - i] = shadow[i].first;
            tmp_params->HiShdWidthArray[rank - 1 - i] = shadow[i].second;
        }

        f.call_time = 0.00000100;		// call time
        f.ret_time = 0.00000100;		// return time
        setVectorCallRet(&f);

        debug += "a crtda SizeArray=";
        for (int i = 0; i < tmp_params->SizeArray.size(); ++i)
            debug += " " + to_string(tmp_params->SizeArray[i]);
        debug += "\n";
        debug += "a crtda LowShdWidthArray=";        
        for (int i = 0; i < tmp_params->LowShdWidthArray.size(); ++i)
            debug += " " + to_string(tmp_params->LowShdWidthArray[i]);
        debug += "\n";
        debug += "a crtda HiShdWidthArray=";
        for (int i = 0; i < tmp_params->HiShdWidthArray.size(); ++i)
            debug += " " + to_string(tmp_params->HiShdWidthArray[i]);
        debug += "\n";
        f.crtda();
    }

    {
        FuncCall f;
        f.func_id = align_;
        align_Info* tmp_params = new align_Info;
        f.call_params = (void *)tmp_params; // point to parameters

        tmp_params->ArrayHeader = getId(array, mapArrayAddrs, arrayAddr);//для различия
        tmp_params->ArrayHandlePtr = getId(array, mapArrayAddrsPtr, arrayAddrPtr);//для различия
        tmp_params->PatternRef = getId(templ, mapArrayAddrsPtr, arrayAddrPtr); //для различия
        tmp_params->PatternRefPtr = getId(templ, mapArrayAddrs, arrayAddr); //для различия
        tmp_params->PatternType = 2; //Distr

        tmp_params->AxisArray.resize(rank);
        tmp_params->CoeffArray.resize(rank);
        tmp_params->ConstArray.resize(rank);
        for (int i = 0; i < rank; ++i)
        {
            if (links[rank - 1 - i] == -1)
            {
                tmp_params->AxisArray[i] = -1;
                tmp_params->CoeffArray[i] = 0;
                tmp_params->ConstArray[i] = 0;
            }
            else
            {
                tmp_params->AxisArray[i] = i + 1;
                tmp_params->CoeffArray[i] = rule[rank - 1 - i].first;
                tmp_params->ConstArray[i] = rule[rank - 1 - i].second - array->GetSizes()[rank - 1 - i].first;
            }
        }

        f.call_time = 0.00000100;		// call time
        f.ret_time = 0.00000100;		// return time
        setVectorCallRet(&f);

        debug += "a align AxisArray=";
        for (int i = 0; i < tmp_params->AxisArray.size(); ++i)
            debug += " " + to_string(tmp_params->AxisArray[i]);
        debug += "\n";

        f.align();
    }

    if (printOut)
        fprintf(printOut, "%s", debug.c_str());
    return 0;
}

int Model_rem(remote *rem)
{
    int i;
    long RID;

    RemoteTime = RemoteTime + 0.000010;
    return 0;

    //	printf("  model rem %s\n", rem->v->name);
    {
        FuncCall f;
        f.func_id = crtrbp_;
        crtrbp_Info* tmp_params = new crtrbp_Info;

        f.call_params = (void *)tmp_params; // point to parameters


        tmp_params->ID = 0xf00000 + rem->v->addr;//для различия
        tmp_params->RemArrayHeader = 0x100000 + rem->v->addr;
        tmp_params->StaticSign = 0; //may be not always
        tmp_params->PSRef = 0;
        tmp_params->IsLocal = 0; // нет такого параметра в RTS
        tmp_params->CoordArray; //это координаты рассылаемого элемента


        f.call_time = 0.00000100;		// call time
        f.ret_time = 0.00000100;		// return time
        setVectorCallRet(&f);
        f.crtrbp();
    }


    //	 если remote относится к циклу	
    {
        FuncCall f;
        f.func_id = crtrbl_;
        crtrbl_Info* tmp_params = new crtrbl_Info;
        f.call_params = (void *)tmp_params; // point to parameters

        tmp_params->BufferHeader = 0xf00000 + rem->v->addr;//для различия
        RID = tmp_params->BufferHeader;
        addr++; //надо отказываться от этого параметра
        tmp_params->RemArrayHeader = 0x100000 + rem->v->addr;

        tmp_params->AxisArray.resize(rem->v->rank);
        tmp_params->CoeffArray.resize(rem->v->rank);
        tmp_params->ConstArray.resize(rem->v->rank);
        for (i = 0; i < rem->v->rank; i++)
        {
            tmp_params->AxisArray[i] = rem->axis[i];
            tmp_params->CoeffArray[i] = rem->coef[i];
            tmp_params->ConstArray[i] = rem->cons[i];
        }

        tmp_params->LoopRef = rem->loop_addr_ref; //may be always equal lastLR:
        tmp_params->StaticSign = 0; //may be not always


        f.call_time = 0.00000100;		// call time
        f.ret_time = 0.00000100;		// return time
        setVectorCallRet(&f);

        f.crtrbl();
    }

    {
        FuncCall f;
        f.func_id = loadrb_;
        loadrb_Info* tmp_params = new loadrb_Info;
        f.call_params = (void *)tmp_params; // point to parameters

        tmp_params->ID = RID;
        tmp_params->RenewSign = 1; //may be always

        f.call_time = 0.00000100;		// call time
        f.ret_time = 0.00000100;		// return time
        setVectorCallRet(&f);

        f.loadrb();
    }

    {
        FuncCall f;
        f.func_id = waitrb_;
        waitrb_Info* tmp_params = new waitrb_Info;
        f.call_params = (void *)tmp_params; // point to parameters

        tmp_params->ID = RID;

        f.call_time = 0.00000100;		// call time
        f.ret_time = 0.00000100;		// return time
        setVectorCallRet(&f);

        f.waitrb();
    }

    return 0;
}

static int findPosInParallel(vector<string> &parallel, const string &find)
{
    int ret = -1;
    for (int z = 0; z < parallel.size(); ++z)
        if (parallel[z] == find)
            return z + 1;
    return ret;
}

static bool shadowExist(const ParallelDirective *directive)
{
    for (auto &sh : directive->shadowRenew)
        for (auto &elem : sh.second)
            if (elem.first != 0 || elem.second != 0)
                return true;
    return false;
}

extern vector<DIST::Array*> fillArraysFromDir(Statement *loopSt);
//==============
static int Model_par(LoopGraph *loop, ParallelDirective *directive, FILE *printOut = NULL)
{
    long LR = -1, RID = -1, RIDG = -1, SHG = -1, SHG1 = -1, SHG2 = -1;
    string debug = "";

    //TODO: count of reduction elems
    if (directive->reduction.size() || directive->reductionLoc.size()) //REDUCTION
    {
        {
            FuncCall f;
            f.func_id = crtrg_;
            crtrg_Info* tmp_params = new crtrg_Info;
            f.call_params = (void *)tmp_params; // point to parameters

            RID = (redShIds++);
            tmp_params->ID = RID;//для различия
            
            f.call_time = 0.00000100;		// call time
            f.ret_time = 0.00000100;		// return time
            setVectorCallRet(&f);

            f.crtrg();
        }

        RIDG = (redShIds++);
        for (auto &redG : directive->reduction)
        {
            for (auto &red : redG.second)
            {
                FuncCall f;
                f.func_id = crtred_;
                crtred_Info* tmp_params = new crtred_Info;
                f.call_params = (void *)tmp_params; // point to parameters

                tmp_params->ID = RIDG; //для различия
                tmp_params->LocElmLength = 0;
                tmp_params->RedArrayLength = 1; // count of elem
                tmp_params->RedArrayType = 1; // INT TYPE

                f.call_time = 0.00000100;		// call time
                f.ret_time = 0.00000100;		// return time
                setVectorCallRet(&f);

                f.crtred();
            }
        }

        for (auto &redG : directive->reductionLoc)
        {
            for (auto &red : redG.second)
            {
                FuncCall f;
                f.func_id = crtred_;
                crtred_Info* tmp_params = new crtred_Info;
                f.call_params = (void *)tmp_params; // point to parameters

                tmp_params->ID = RIDG; //для различия
                tmp_params->LocElmLength = std::get<2>(red); // count of loc elem
                tmp_params->RedArrayLength = 1; // count of elem
                tmp_params->RedArrayType = 1; // INT TYPE

                f.call_time = 0.00000100;		// call time
                f.ret_time = 0.00000100;		// return time
                setVectorCallRet(&f);

                f.crtred();
            }
        }
    }

    //PARLOOP
    {
        FuncCall f;
        f.func_id = crtpl_;
        crtpl_Info* tmp_params = new crtpl_Info;
        f.call_params = (void *)tmp_params; // point to parameters

        LR = tmp_params->ID = getId(loop, mapLoopIds, loopIds);
        tmp_params->Rank = directive->parallel.size();

        f.call_time = 0.00000100;		// call time
        f.ret_time = 0.00000100;		// return time
        setVectorCallRet(&f);

        f.crtpl();

        //TODO!!!
        /*for (i = 0; i < rem_few.size(); i++)
            rem_few[i].loop_addr_ref = LR;*/
    }

    // TODO: add CORNER
    if (shadowExist(directive)) //SHADOW RENEW
    {
        {
            FuncCall f;
            f.func_id = crtshg_;
            crtshg_Info *tmp_params = new crtshg_Info;
            f.call_params = (void *)tmp_params; // point to parameters

            tmp_params->ShadowGroupRef = (redShIds++);//для различия
            SHG = tmp_params->ShadowGroupRef;
            tmp_params->StaticSign = 0; //poss not

            f.call_time = 0.00000100;		// call time
            f.ret_time = 0.00000100;		// return time
            setVectorCallRet(&f);

            f.crtshg();
        }
        
        auto arraysInShadow = fillArraysFromDir(loop->loop);        
        for (int j = 0; j < directive->shadowRenew.size(); ++j)
        {
            DIST::Array *shArray = NULL;
            for (auto &elem : arraysInShadow)
                if (elem->GetName() == directive->shadowRenew[j].first.second)
                    shArray = elem;
            checkNull(shArray, __FILE__, __LINE__);

            FuncCall f;
            f.func_id = inssh_;
            inssh_Info* tmp_params = new inssh_Info;
            f.call_params = (void *)tmp_params; // point to parameters

            tmp_params->ShadowGroupRef = SHG;
            tmp_params->ArrayHandlePtr = getId(shArray, mapArrayAddrsPtr, arrayAddrPtr);
            tmp_params->ArrayHeader = getId(shArray, mapArrayAddrs, arrayAddr);
            tmp_params->FullShdSign = 0; //poss not
            tmp_params->HiShdWidthArray.resize(0);
            tmp_params->LowShdWidthArray.resize(0);

            const int rank = shArray->GetDimSize();
            for (int z = 0; z < rank; ++z)
            {
                tmp_params->HiShdWidthArray.push_back(directive->shadowRenew[j].second[rank - 1 - z].second);
                tmp_params->LowShdWidthArray.push_back(directive->shadowRenew[j].second[rank - 1 - z].first);
            }

            f.call_time = 0.00000100;		// call time
            f.ret_time = 0.00000100;		// return time
            setVectorCallRet(&f);

            debug += "ins_sh  " + shArray->GetShortName() + "  ArrayPtr=" + to_string(tmp_params->ArrayHeader) + "\n";
            f.inssh();
        }
        
        {
            FuncCall f;
            f.func_id = strtsh_;
            strtsh_Info* tmp_params = new strtsh_Info;
            f.call_params = (void *)tmp_params; // point to parameters

            tmp_params->ID = SHG;

            f.call_time = 0.00000100;		// call time
            f.ret_time = 0.00000100;		// return time
            setVectorCallRet(&f);

            f.strtsh();
        }

        {
            FuncCall f;
            f.func_id = waitsh_;
            waitsh_Info* tmp_params = new waitsh_Info;
            f.call_params = (void *)tmp_params; // point to parameters

            tmp_params->ID = SHG;

            f.call_time = 0.00000100;		// call time
            f.ret_time = 0.00000100;		// return time
            setVectorCallRet(&f);

            f.waitsh();
        }
    }

    if (directive->across.size()) // ACROSS
    {
        /*
        {
            FuncCall f;
            f.func_id = crtshg_;
            crtshg_Info* tmp_params = new crtshg_Info;
            f.call_params = (void *)tmp_params; // point to parameters

            tmp_params->ShadowGroupRef = 0xb00000 + addr;//для различия
            SHG1 = tmp_params->ShadowGroupRef;
            tmp_params->StaticSign = 0; //poss not

            addr++;

            f.call_time = 0.00000100;		// call time
            f.ret_time = 0.00000100;		// return time
            setVectorCallRet(&f);

            f.crtshg();
        }

        for (int j = 0; j < a_few.size(); ++j)
        {
            FuncCall f;
            f.func_id = insshd_;
            inssh_Info* tmp_params = new inssh_Info;
            f.call_params = (void *)tmp_params; // point to parameters

            tmp_params->ShadowGroupRef = SHG1;
            tmp_params->ArrayHandlePtr = 0x200000 + a_few[j].v->addr;//было 0xd00000
            tmp_params->ArrayHeader = 0x100000 + a_few[j].v->addr;
            tmp_params->MaxShdCount = 1; //poss not
            tmp_params->LowShdWidthArray.resize(a_few[j].v->rank);
            tmp_params->HiShdWidthArray.resize(a_few[j].v->rank);
            tmp_params->ShdSignArray.resize(a_few[j].v->rank);
            for (int i = 0; i < a_few[j].v->rank; ++i)
            {
                tmp_params->HiShdWidthArray[i] = 0; //poss inverse
                tmp_params->LowShdWidthArray[i] = a_few[j].low_wid[i];
                tmp_params->ShdSignArray[i] = 3; //poss not
            }

            f.call_time = 0.00000100;		// call time
            f.ret_time = 0.00000100;		// return time
            setVectorCallRet(&f);

            f.insshd();
        }

        {
            FuncCall f;
            f.func_id = crtshg_;
            crtshg_Info* tmp_params = new crtshg_Info;
            f.call_params = (void *)tmp_params; // point to parameters

            tmp_params->ShadowGroupRef = 0xb00000 + addr;//для различия
            SHG2 = tmp_params->ShadowGroupRef;
            tmp_params->StaticSign = 0; //poss not

            addr++;

            f.call_time = 0.00000100;		// call time
            f.ret_time = 0.00000100;		// return time
            setVectorCallRet(&f);

            f.crtshg();
        }

        for (int j = 0; j < a_few.size(); ++j)
        {
            FuncCall f;
            f.func_id = insshd_;
            inssh_Info* tmp_params = new inssh_Info;
            f.call_params = (void *)tmp_params; // point to parameters

            tmp_params->ShadowGroupRef = SHG2;
            tmp_params->ArrayHandlePtr = 0x200000 + a_few[j].v->addr;//было 0xd00000
            tmp_params->ArrayHeader = 0x100000 + a_few[j].v->addr;
            tmp_params->MaxShdCount = 1; //poss not
            tmp_params->LowShdWidthArray.resize(a_few[j].v->rank);
            tmp_params->HiShdWidthArray.resize(a_few[j].v->rank);
            tmp_params->ShdSignArray.resize(a_few[j].v->rank);
            for (int i = 0; i < a_few[j].v->rank; ++i)
            {
                tmp_params->HiShdWidthArray[i] = a_few[j].hi_wid[i];
                tmp_params->LowShdWidthArray[i] = 0; //poss inverse
                tmp_params->ShdSignArray[i] = 5; //poss not
            }

            f.call_time = 0.00000100;		// call time
            f.ret_time = 0.00000100;		// return time
            setVectorCallRet(&f);

            f.insshd();
        }*/
    }


    //PARLOOP
    {        
        FuncCall f;
        f.func_id = mappl_;
        mappl_Info* tmp_params = new mappl_Info;
        f.call_params = (void *)tmp_params; // point to parameters
        
        tmp_params->LoopRef = LR; //тот что и в crtpl
        tmp_params->PatternRef = getId(directive->arrayRef, mapArrayAddrsPtr, arrayAddrPtr); //для различия 
        tmp_params->PatternRefPtr = getId(directive->arrayRef, mapArrayAddrs, arrayAddr); //для различия
        tmp_params->PatternType = 2; //DisArray

        const int rank = directive->arrayRef->GetDimSize();
        tmp_params->AxisArray.resize(rank);
        tmp_params->CoeffArray.resize(rank);
        tmp_params->ConstArray.resize(rank);
        for (int i = 0; i < rank; ++i)
        {
            if (directive->on[i].first == "*")
            {
                tmp_params->AxisArray[rank - 1 - i] = -1;
                tmp_params->CoeffArray[rank - 1 - i] = 0;
                tmp_params->ConstArray[rank - 1 - i] = 0;
            }
            else
            {
                tmp_params->AxisArray[rank - 1 - i] = findPosInParallel(directive->parallel, directive->on[i].first);
                tmp_params->CoeffArray[rank - 1 - i] = directive->on[i].second.first;
                tmp_params->ConstArray[rank - 1 - i] = directive->on[i].second.second;
            }
        }

        const int loopRank = directive->parallel.size();
        tmp_params->InInitIndexArray.resize(loopRank);
        tmp_params->InLastIndexArray.resize(loopRank);
        tmp_params->InStepArray.resize(loopRank);

        LoopGraph *currL = loop;
        for (int i = 0; i < loopRank; ++i, currL = currL->children[0])
        {
            tmp_params->InInitIndexArray[i] = currL->startVal;
            tmp_params->InLastIndexArray[i] = currL->endVal;
            tmp_params->InStepArray[i] = currL->stepVal;
            
            if (i == loopRank - 1)
                break;
            if (currL->children.size() == 0)
                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
        }
        
        f.call_time = 0.00000100;		// call time
        f.ret_time = 0.00000100;		// return time
        setVectorCallRet(&f);

        debug += "mappl AxisArray=";        
        for (int i = 0; i < tmp_params->AxisArray.size(); ++i)
            debug += " " + to_string(tmp_params->AxisArray[i]);
        debug += "\n";        
        f.mappl();
    }

    if (directive->reduction.size() | directive->reductionLoc.size()) //REDUCTION
    {
        FuncCall f;
        f.func_id = insred_;
        insred_Info* tmp_params = new insred_Info;
        f.call_params = (void *)tmp_params; // point to parameters

        tmp_params->RG_ID = RID;//для различия
        tmp_params->RV_ID = RIDG;//для различия

        f.call_time = 0.00000100;		// call time
        f.ret_time = 0.00000100;		// return time
        setVectorCallRet(&f);

        f.insred();
    }


    if (directive->across.size()) //ACROSS
    {
        /*
        FuncCall f;
        f.func_id = across_;
        across_Info* tmp_params = new across_Info;
        f.call_params = (void *)tmp_params; // point to parameters

        tmp_params->AcrossType = 0; //poss not
        tmp_params->NewShadowGroupRef = SHG1;
        tmp_params->OldShadowGroupRef = SHG2;
        tmp_params->PipeLinePar = 0; //poss not
        tmp_params->CondPipeLine = 0; //poss not
        tmp_params->ErrPipeLine = 9; //poss not

        f.call_time = 0.00000100;		// call time
        f.ret_time = 0.00000100;		// return time
        setVectorCallRet(&f);

        f.across();*/
    }

    if (directive->remoteAccess.size())
    {
        //TODO:
        /*for (i = 0; i < rem_few.size(); i++)
            Model_rem(&rem_few[i]);
        rem_few.resize(0);*/
    }


    //PARLOOP
    {
        FuncCall f;
        f.func_id = dopl_;
        dopl_full_Info *tmp_params = new dopl_full_Info;
        f.call_params = (void *)tmp_params; // point to parameters

        tmp_params->ID = LR; //тот что и в crtpl
        tmp_params->ReturnVar = 1;

        f.call_time = 0.00000100;		// call time
        f.ret_time = 0.00000100;		// return time
        setVectorCallRet(&f);

        f.dopl();
    }

    {
        FuncCall f;
        f.func_id = dopl_;
        dopl_full_Info* tmp_params = new dopl_full_Info;
        f.call_params = (void *)tmp_params; // point to parameters

        tmp_params->ID = LR;//тот что и в crtpl
        tmp_params->ReturnVar = 0;

        //TODO: loop time!
        f.call_time = 100;		        // call time, c->time - это время цикла!
        f.ret_time = 0.00000100;		// return time
        setVectorCallRet(&f);

        f.dopl();
    }

    {
        FuncCall f;
        f.func_id = endpl_;
        endpl_Info* tmp_params = new endpl_Info;
        f.call_params = (void *)tmp_params; // point to parameters

        tmp_params->ID = LR; //тот что и в crtpl

        f.call_time = 0.00000100;		// call time
        f.ret_time = 0.00000100;		// return time
        setVectorCallRet(&f);

        f.endpl();
    }


    if (directive->reduction.size() || directive->reductionLoc.size()) //REDUCTION
    {        
        {
            FuncCall f;
            f.func_id = strtrd_;
            strtrd_Info* tmp_params = new strtrd_Info;
            f.call_params = (void *)tmp_params; // point to parameters

            tmp_params->ID = RID;//для различия

            f.call_time = 0.00000100;		// call time
            f.ret_time = 0.00000100;		// return time
            setVectorCallRet(&f);

            f.strtrd();
        }

        {
            FuncCall f;
            f.func_id = waitrd_;
            waitrd_Info* tmp_params = new waitrd_Info;
            f.call_params = (void *)tmp_params; // point to parameters

            tmp_params->ID = RID;//для различия

            f.call_time = 0.00000100;		// call time
            f.ret_time = 0.00000100;		// return time
            setVectorCallRet(&f);

            f.waitrd();
        }        
    }

    if (printOut)
        fprintf(printOut, "%s", debug.c_str());
    return 0;
}

//============== 
int Model_par(var *v1, ali_pat *d, circle *c, reduct *r, shadow *s, across *a)
{
    int i, j;
    long LR, RID, SHG, SHG1, SHG2;
    
    if (r->is) //REDUCTION
    {
        {
            FuncCall f;
            f.func_id = crtrg_;
            crtrg_Info* tmp_params = new crtrg_Info;
            f.call_params = (void *)tmp_params; // point to parameters

            tmp_params->ID = 0xed0000 + addr;//для различия
            RID = addr;

            addr++;

            f.call_time = 0.00000100;		// call time
            f.ret_time = 0.00000100;		// return time
            setVectorCallRet(&f);

            f.crtrg();
        }

        for (j = 0; j < r_few.size(); j++)
        {
            FuncCall f;
            f.func_id = crtred_;
            crtred_Info* tmp_params = new crtred_Info;
            f.call_params = (void *)tmp_params; // point to parameters

            tmp_params->ID = 0xe10000 + RID;//для различия
            tmp_params->LocElmLength = r_few[j].loc_type;
            tmp_params->RedArrayLength = r_few[j].red_arr_len;
            tmp_params->RedArrayType = r_few[j].red_arr_type;

            f.call_time = 0.00000100;		// call time
            f.ret_time = 0.00000100;		// return time
            setVectorCallRet(&f);

            f.crtred();
        }
    }

    //PARLOOP
    {
        FuncCall f;
        f.func_id = crtpl_;
        crtpl_Info* tmp_params = new crtpl_Info;
        f.call_params = (void *)tmp_params; // point to parameters

        tmp_params->ID = 0xc00000 + addr;//для различия
        LR = tmp_params->ID;
        tmp_params->Rank = c->rank;

        addr++;

        f.call_time = 0.00000100;		// call time
        f.ret_time = 0.00000100;		// return time
        setVectorCallRet(&f);

        f.crtpl();

        for (i = 0; i < rem_few.size(); i++)
            rem_few[i].loop_addr_ref = LR;
    }

    if (s->is) //SHADOW RENEW
    {
        // не знаю куда задать CORNER
        {
            FuncCall f;
            f.func_id = crtshg_;
            crtshg_Info* tmp_params = new crtshg_Info;
            f.call_params = (void *)tmp_params; // point to parameters

            tmp_params->ShadowGroupRef = 0xb00000 + addr;//для различия
            SHG = tmp_params->ShadowGroupRef;
            tmp_params->StaticSign = 0; //poss not

            addr++;

            f.call_time = 0.00000100;		// call time
            f.ret_time = 0.00000100;		// return time
            setVectorCallRet(&f);

            f.crtshg();
        }

        for (j = 0; j < s_few.size(); j++)
        {
            FuncCall f;
            f.func_id = inssh_;
            inssh_Info* tmp_params = new inssh_Info;
            f.call_params = (void *)tmp_params; // point to parameters

            tmp_params->ShadowGroupRef = SHG;
            tmp_params->ArrayHandlePtr = 0x200000 + s_few[j].v->addr; //было 0xd00000
            tmp_params->ArrayHeader = 0x100000 + s_few[j].v->addr;
            tmp_params->FullShdSign = 0;//poss not
            tmp_params->HiShdWidthArray.resize(0);
            tmp_params->LowShdWidthArray.resize(0);
            if (!(s_few[j].is_wid))
            {
                for (i = 0; i < s_few[j].v->rank; i++)
                {
                    tmp_params->HiShdWidthArray.push_back(-1);
                    tmp_params->LowShdWidthArray.push_back(-1);
                }
            }
            else
            {
                for (i = 0; i < s_few[j].v->rank; i++)
                {
                    tmp_params->HiShdWidthArray.push_back(s_few[j].hi_wid[i]);
                    tmp_params->LowShdWidthArray.push_back(s_few[j].low_wid[i]);
                }
            }

            f.call_time = 0.00000100;		// call time
            f.ret_time = 0.00000100;		// return time
            setVectorCallRet(&f);

            printf("ins_sh  %s  ArrayPtr=%d\n", s_few[j].v->name, tmp_params->ArrayHeader);
            f.inssh();
        }

        {
            FuncCall f;
            f.func_id = strtsh_;
            strtsh_Info* tmp_params = new strtsh_Info;
            f.call_params = (void *)tmp_params; // point to parameters

            tmp_params->ID = SHG;

            f.call_time = 0.00000100;		// call time
            f.ret_time = 0.00000100;		// return time
            setVectorCallRet(&f);

            f.strtsh();
        }

        {
            FuncCall f;
            f.func_id = waitsh_;
            waitsh_Info* tmp_params = new waitsh_Info;
            f.call_params = (void *)tmp_params; // point to parameters

            tmp_params->ID = SHG;

            f.call_time = 0.00000100;		// call time
            f.ret_time = 0.00000100;		// return time
            setVectorCallRet(&f);

            f.waitsh();
        }
    }

    if (a->is) // ACROSS
    {
        {
            FuncCall f;
            f.func_id = crtshg_;
            crtshg_Info* tmp_params = new crtshg_Info;
            f.call_params = (void *)tmp_params; // point to parameters

            tmp_params->ShadowGroupRef = 0xb00000 + addr;//для различия
            SHG1 = tmp_params->ShadowGroupRef;
            tmp_params->StaticSign = 0; //poss not

            addr++;

            f.call_time = 0.00000100;		// call time
            f.ret_time = 0.00000100;		// return time
            setVectorCallRet(&f);

            f.crtshg();
        }

        for (j = 0; j < a_few.size(); j++)
        {
            FuncCall f;
            f.func_id = insshd_;
            inssh_Info* tmp_params = new inssh_Info;
            f.call_params = (void *)tmp_params; // point to parameters

            tmp_params->ShadowGroupRef = SHG1;
            tmp_params->ArrayHandlePtr = 0x200000 + a_few[j].v->addr;//было 0xd00000
            tmp_params->ArrayHeader = 0x100000 + a_few[j].v->addr;
            tmp_params->MaxShdCount = 1; //poss not
            tmp_params->LowShdWidthArray.resize(a_few[j].v->rank);
            tmp_params->HiShdWidthArray.resize(a_few[j].v->rank);
            tmp_params->ShdSignArray.resize(a_few[j].v->rank);
            for (i = 0; i < a_few[j].v->rank; i++)
            {
                tmp_params->HiShdWidthArray[i] = 0; //poss inverse
                tmp_params->LowShdWidthArray[i] = a_few[j].low_wid[i];
                tmp_params->ShdSignArray[i] = 3; //poss not
            }

            f.call_time = 0.00000100;		// call time
            f.ret_time = 0.00000100;		// return time
            setVectorCallRet(&f);

            f.insshd();
        }

        {
            FuncCall f;
            f.func_id = crtshg_;
            crtshg_Info* tmp_params = new crtshg_Info;
            f.call_params = (void *)tmp_params; // point to parameters

            tmp_params->ShadowGroupRef = 0xb00000 + addr;//для различия
            SHG2 = tmp_params->ShadowGroupRef;
            tmp_params->StaticSign = 0; //poss not

            addr++;

            f.call_time = 0.00000100;		// call time
            f.ret_time = 0.00000100;		// return time
            setVectorCallRet(&f);

            f.crtshg();
        }

        for (j = 0; j < a_few.size(); j++)
        {
            FuncCall f;
            f.func_id = insshd_;
            inssh_Info* tmp_params = new inssh_Info;
            f.call_params = (void *)tmp_params; // point to parameters

            tmp_params->ShadowGroupRef = SHG2;
            tmp_params->ArrayHandlePtr = 0x200000 + a_few[j].v->addr;//было 0xd00000
            tmp_params->ArrayHeader = 0x100000 + a_few[j].v->addr;
            tmp_params->MaxShdCount = 1; //poss not
            tmp_params->LowShdWidthArray.resize(a_few[j].v->rank);
            tmp_params->HiShdWidthArray.resize(a_few[j].v->rank);
            tmp_params->ShdSignArray.resize(a_few[j].v->rank);
            for (i = 0; i < a_few[j].v->rank; i++)
            {
                tmp_params->HiShdWidthArray[i] = a_few[j].hi_wid[i];
                tmp_params->LowShdWidthArray[i] = 0; //poss inverse
                tmp_params->ShdSignArray[i] = 5; //poss not
            }

            f.call_time = 0.00000100;		// call time
            f.ret_time = 0.00000100;		// return time
            setVectorCallRet(&f);

            f.insshd();
        }
    }


    //PARLOOP
    {
        FuncCall f;
        f.func_id = mappl_;
        mappl_Info* tmp_params = new mappl_Info;
        f.call_params = (void *)tmp_params; // point to parameters

        tmp_params->LoopRef = LR;//тот что и в crtpl
        tmp_params->PatternRef = 0x200000 + v1->addr;
        tmp_params->PatternRefPtr = 0x100000 + v1->addr;
        tmp_params->PatternType = 2; //DisArray

        tmp_params->AxisArray.resize(d->rank);
        tmp_params->CoeffArray.resize(d->rank);
        tmp_params->ConstArray.resize(d->rank);
        for (i = 0; i < d->rank; i++)
        {
            tmp_params->AxisArray[i] = d->axis[i];
            tmp_params->CoeffArray[i] = d->coef[i];
            tmp_params->ConstArray[i] = d->cons[i];
        }

        tmp_params->InInitIndexArray.resize(c->rank);
        tmp_params->InLastIndexArray.resize(c->rank);
        tmp_params->InStepArray.resize(c->rank);
        for (i = 0; i < c->rank; i++)
        {
            tmp_params->InInitIndexArray[i] = c->init[i];
            tmp_params->InLastIndexArray[i] = c->last[i];
            tmp_params->InStepArray[i] = c->step[i];
        }

        f.call_time = 0.00000100;		// call time
        f.ret_time = 0.00000100;		// return time
        setVectorCallRet(&f);

        printf("mappl AxisArray=");
        for (i = 0; i < tmp_params->AxisArray.size(); i++)
            printf(" %d", tmp_params->AxisArray[i]);
        printf("\n");

        f.mappl();
    }

    if (r->is) //REDUCTION
    {
        FuncCall f;
        f.func_id = insred_;
        insred_Info* tmp_params = new insred_Info;
        f.call_params = (void *)tmp_params; // point to parameters

        tmp_params->RG_ID = 0xed0000 + RID;//для различия
        tmp_params->RV_ID = 0xe10000 + RID;//для различия

        f.call_time = 0.00000100;		// call time
        f.ret_time = 0.00000100;		// return time
        setVectorCallRet(&f);

        f.insred();
    }


    if (a->is) //ACROSS
    {
        FuncCall f;
        f.func_id = across_;
        across_Info* tmp_params = new across_Info;
        f.call_params = (void *)tmp_params; // point to parameters

        tmp_params->AcrossType = 0; //poss not
        tmp_params->NewShadowGroupRef = SHG1;
        tmp_params->OldShadowGroupRef = SHG2;
        tmp_params->PipeLinePar = 0; //poss not
        tmp_params->CondPipeLine = 0; //poss not
        tmp_params->ErrPipeLine = 9; //poss not

        f.call_time = 0.00000100;		// call time
        f.ret_time = 0.00000100;		// return time
        setVectorCallRet(&f);

        f.across();
    }

    if (rem_few.size() != 0)
    {
        for (i = 0; i < rem_few.size(); i++)
            Model_rem(&rem_few[i]);
        rem_few.resize(0);
    }


    //PARLOOP
    {
        FuncCall f;
        f.func_id = dopl_;
        dopl_full_Info* tmp_params = new dopl_full_Info;
        f.call_params = (void *)tmp_params; // point to parameters

        tmp_params->ID = LR;//тот что и в crtpl
        tmp_params->ReturnVar = 1;

        f.call_time = 0.00000100;		// call time
        f.ret_time = 0.00000100;		// return time
        setVectorCallRet(&f);

        f.dopl();
    }

    {
        FuncCall f;
        f.func_id = dopl_;
        dopl_full_Info* tmp_params = new dopl_full_Info;
        f.call_params = (void *)tmp_params; // point to parameters

        tmp_params->ID = LR;//тот что и в crtpl
        tmp_params->ReturnVar = 0;

        f.call_time = c->time - 0.00000100;		// call time
        f.ret_time = 0.00000100;		// return time
        setVectorCallRet(&f);

        f.dopl();
    }

    {
        FuncCall f;
        f.func_id = endpl_;
        endpl_Info* tmp_params = new endpl_Info;
        f.call_params = (void *)tmp_params; // point to parameters

        tmp_params->ID = LR;//тот что и в crtpl

        f.call_time = 0.00000100;		// call time
        f.ret_time = 0.00000100;		// return time
        setVectorCallRet(&f);

        f.endpl();
    }


    if (r->is) //REDUCTION
    {
        {
            FuncCall f;
            f.func_id = strtrd_;
            strtrd_Info* tmp_params = new strtrd_Info;
            f.call_params = (void *)tmp_params; // point to parameters

            tmp_params->ID = 0xed0000 + RID;//для различия

            f.call_time = 0.00000100;		// call time
            f.ret_time = 0.00000100;		// return time
            setVectorCallRet(&f);

            f.strtrd();
        }

        {
            FuncCall f;
            f.func_id = waitrd_;
            waitrd_Info* tmp_params = new waitrd_Info;
            f.call_params = (void *)tmp_params; // point to parameters

            tmp_params->ID = 0xed0000 + RID;//для различия

            f.call_time = 0.00000100;		// call time
            f.ret_time = 0.00000100;		// return time
            setVectorCallRet(&f);

            f.waitrd();
        }
    }

    lastLR = LR;
    return 0;
}

//============== Model switch
int Model(int scheme_id, long line_beg, long line_end)  //возвращает номер следующей команды
{
    int i, j, k, q;
    int mode = 1, seq_index;
    double poss, p, t1, t2;

    vector <struct dir_bin_data> dir_bin = all_scheme[curr_routine][scheme_id].v_dir_bin;
    vector <struct seq_loop> seq_loops = all_scheme[curr_routine][scheme_id].seq_loops;

    if (all_scheme[curr_routine][scheme_id].Interval_tree == NULL)
        all_scheme[curr_routine][scheme_id].Interval_tree = new Interval_node;


    cout << "Model " << line_beg << ".." << line_end << "\n";
    //	log_file<< "Model " << line_beg <<".." << line_end<<"\n";

    if (line_end == -1)
    {
        printf("Not set end of seq loop\n");
        exit(-1);
    }

    //!!! very brutal - need to delete seq_loops //debugggg
    seq_loops.resize(0);


    for (j = 0; j < result_cnt; j++)
    {
        result[j].line = line_beg;
    }

    rem_few.resize(0);

    //for(i=line_beg;i<=line_end;i++)
    while (1)
    {
        //склейка контекстов
        for (i = 0; i < result_cnt; i++)
            for (j = i + 1; j < result_cnt; j++)
            {
                if (result[i].line == result[j].line && result[i].line <= line_end)
                {
                    if (mode) printf("svertka %d << %d << %d   ", i, j, result_cnt - 1);
                    p = result[i].poss + result[j].poss;
                    result[i].inter_mid->copy_poss(result[j].inter_mid, result[i].poss / p, result[j].poss / p);
                    if (mode) printf("exec %f\n", result[i].inter_mid->GetProcPred(0, _Execution_time));

                    result[i].poss += result[j].poss;
                    for (t1 = 0.0, t2 = 0.0, k = 0; k < MPSProcCount(); k++)
                    {
                        t1 += result[i].inter_min->GetProcPred(k, _Execution_time);
                        t2 += result[j].inter_min->GetProcPred(k, _Execution_time);
                    }
                    if (t1 > t2) result[i].inter_min->copy(result[j].inter_min);

                    for (t1 = 0.0, t2 = 0.0, k = 0; k < MPSProcCount(); k++)
                    {
                        t1 += result[i].inter_max->GetProcPred(k, _Execution_time);
                        t2 += result[j].inter_max->GetProcPred(k, _Execution_time);
                    }
                    if (t1 < t2) result[i].inter_max->copy(result[j].inter_max);

                    //копируем из конца в освободившуюся середину результат
                    result[j].inter_mid = result[result_cnt - 1].inter_mid;
                    result[j].inter_min = result[result_cnt - 1].inter_min;
                    result[j].inter_max = result[result_cnt - 1].inter_max;
                    result[j].line = result[result_cnt - 1].line;
                    result[j].poss = result[result_cnt - 1].poss;
                    result_cnt--;
                    j--;

                }
            }

        if (mode)
            for (j = 0; j < result_cnt; j++)
            {
                //				printf("res %d = %f %d exec=%f (%f - %f)\n",i,result[i].poss,result[i].line,result[i].inter_mid->GetProcPred(0,_Execution_time),result[i].inter_min->GetProcPred(0,_Execution_time),result[i].inter_max->GetProcPred(0,_Execution_time));
                printf("res = %d exec[0]=%f  cpu_usr[0]=%f\n", result[j].line, result[j].inter_mid->GetProcPred(0, _Execution_time), result[j].inter_mid->GetProcPred(0, _CPU_time_usr));
            }


        // cur_res = result c минимальным номером строки.
        for (j = 1, cur_res = 0; j < result_cnt; j++)
        {
            printf("j=%d res_line=%d\n", j, result[j].line);
            if (result[j].line < result[cur_res].line) cur_res = j;
        }

        if (result[cur_res].line > line_end) break; //выход из while

        i = result[cur_res].line; //для краткости

        if (mode) printf("\ncur_res=%d\n", cur_res);

        for (j = 0; j < seq_loops.size(); j++)
            if (i == seq_loops[j].beg_line) break;
        seq_index = j;


        //never
        if (0 && i != line_beg && seq_index < seq_loops.size()) //seq_loops[seq_index].times!=0 
        {
            if (seq_loops[seq_index].ifgoto == true)
            {
                for (j = 0; j < seq_loops[seq_index].times; j++)
                {
                    if (mode) printf("circle iter=%d (%d, %d)\n", j, seq_loops[seq_index].beg_line, seq_loops[seq_index].end_line);
                    result[cur_res].line = seq_loops[seq_index].beg_line;
                    Model(scheme_id, seq_loops[seq_index].beg_line, seq_loops[seq_index].end_line);
                    //				result[cur_res].line=is_loop[i].end_line;
                }
            }
            else
            {
                Interval *tmp_mid = new Interval(0);
                Interval *tmp_min = new Interval(0);
                Interval *tmp_max = new Interval(0);

                Interval *tmp_res = new Interval(0);



                if (mode) printf("circle fast = (%d, %d)\n", seq_loops[seq_index].beg_line, seq_loops[seq_index].end_line);
                result[cur_res].line = seq_loops[seq_index].beg_line;

                if (seq_loops[seq_index].times >= 1)
                {
                    tmp_mid->copy(result[cur_res].inter_mid);
                    tmp_min->copy(result[cur_res].inter_min);
                    tmp_max->copy(result[cur_res].inter_max);

                    //первая итерация
                    //моделирование последовательной ее части
                    result[cur_res].inter_mid->copy_poss(SeqLoopInterval, 1, seq_loops[seq_index].iter_time);
                    result[cur_res].inter_min->copy_poss(SeqLoopInterval, 1, seq_loops[seq_index].iter_time);
                    result[cur_res].inter_max->copy_poss(SeqLoopInterval, 1, seq_loops[seq_index].iter_time);

                    //моделирование вложенной части
                    Model(scheme_id,/*s, is_loop,*/seq_loops[seq_index].beg_line, seq_loops[seq_index].end_line);

                    tmp_mid->copy_poss(result[cur_res].inter_mid, -1, 1); //получить разницу
                    tmp_min->copy_poss(result[cur_res].inter_min, -1, 1); //получить разницу
                    tmp_max->copy_poss(result[cur_res].inter_max, -1, 1); //получить разницу

                    tmp_res->copy(tmp_mid);

                    //printInterval(tmp_res);


                    //все последующие
                    if (seq_loops[seq_index].times >= 2)
                    {
                        tmp_mid->copy(result[cur_res].inter_mid);
                        tmp_min->copy(result[cur_res].inter_min);
                        tmp_max->copy(result[cur_res].inter_max);

                        //моделирование последовательной ее части
                        result[cur_res].inter_mid->copy_poss(SeqLoopInterval, 1, seq_loops[seq_index].iter_time);
                        result[cur_res].inter_min->copy_poss(SeqLoopInterval, 1, seq_loops[seq_index].iter_time);
                        result[cur_res].inter_max->copy_poss(SeqLoopInterval, 1, seq_loops[seq_index].iter_time);

                        Interval *new_res;

                        //insert EMPTY interval for adding par intervals
                        all_scheme[curr_routine][scheme_id].Interval_tree->insert(Find_loop_id_tree(seq_loops[seq_index].loop_line), NULL, 0, seq_loops[seq_index].times);

                        //моделирование вложенной части
                        Model(scheme_id,/*s, is_loop,*/seq_loops[seq_index].beg_line, seq_loops[seq_index].end_line);

                        tmp_mid->copy_poss(result[cur_res].inter_mid, -1, 1); //получить разницу
                        tmp_min->copy_poss(result[cur_res].inter_min, -1, 1); //получить разницу
                        tmp_max->copy_poss(result[cur_res].inter_max, -1, 1); //получить разницу

//						tmp_mid->Integrate();				tmp_min->Integrate();				tmp_max->Integrate();
//						printf("TMP mid - %.10f   min - %.10f   max - %.10f\n",tmp_mid->GetExecTime(),tmp_min->GetExecTime(),tmp_max->GetExecTime());
//						tmp_res->Integrate();	
//						printf("TMP res - %.10f\n",tmp_res->GetExecTime());

                        new_res = new Interval(0);
                        new_res->Integrate();

                        //						new_res->copy_poss(tmp_mid, 0, 1); 
                        new_res->copy_poss(tmp_mid, 0, (seq_loops[seq_index].times - 2));

                        new_res->CalcIdleAndImbalance();
                        new_res->Integrate(); //You can Integrate only once - because it corresponding to the entrance into interval

                        all_scheme[curr_routine][scheme_id].results.push_back(new_res);
                        all_scheme[curr_routine][scheme_id].res_lines.push_back(seq_loops[seq_index].loop_line);

                        //						all_scheme[curr_routine][scheme_id].Interval_tree->insert(Find_loop_id_tree(seq_loops[seq_index].loop_line), NULL, 0, -1);

                        new_res = new Interval(0);
                        new_res->Integrate();

                        new_res->copy_poss(SeqLoopInterval, 0, seq_loops[seq_index].iter_time);

                        all_scheme[curr_routine][scheme_id].Interval_tree->insert(Find_loop_id_tree(seq_loops[seq_index].loop_line), new_res, 1, -1);
                        //all_scheme[curr_routine][scheme_id].Interval_tree->insert(Find_loop_id_tree(seq_loops[seq_index].loop_line), new_res, 1, +1);


//						all_scheme[curr_routine][scheme_id].Interval_tree->print(0);

                        result[cur_res].inter_mid->copy_poss(tmp_mid, 1, (seq_loops[seq_index].times - 2)); //прибавит времена остальных витков
                        result[cur_res].inter_max->copy_poss(tmp_max, 1, (seq_loops[seq_index].times - 2)); //прибавит времена остальных витков
                        result[cur_res].inter_min->copy_poss(tmp_min, 1, (seq_loops[seq_index].times - 2)); //прибавит времена остальных витков

//						printInterval(tmp_mid);
//						printf("************** %.0f\n",seq_loops[seq_index].times-1);

                        tmp_res->copy_poss(tmp_mid, 1, seq_loops[seq_index].times - 1);

                        //						printInterval(tmp_res);


                        //						tmp_res->Integrate();	
                        //						printf("TMP res - %.10f\n",tmp_res->GetExecTime());
                    }



                    tmp_res->CalcIdleAndImbalance();
                    tmp_res->Integrate(); //You can Integrate only once - because it corresponding to the entrance into interval

                    all_scheme[curr_routine][scheme_id].results.push_back(tmp_res);
                    all_scheme[curr_routine][scheme_id].res_lines.push_back(seq_loops[seq_index].loop_line);


                }

                result[cur_res].line = seq_loops[seq_index].end_line + 1;

                //				result[cur_res].inter_mid->copy(tmp_res); 
                //				result[cur_res].inter_min->copy(tmp_res); //не высчитываю
                //				result[cur_res].inter_max->copy(tmp_res); //не высчитываю

            }
            //			i=is_loop[i].end_line; //потому что обработана не только первая строка но и весь цикл.
        }
        else
        {
            int dir_type = 0;

            if (i >= dir_bin.size())
            {
                printf("ERROR in MODEL: No dir %d\n", i);
                break;
            }
            dir_type = dir_bin[i].data[0];

            //CurrInterval->copy(NullInterval); // reset CurrInterval

            if (1 || mode) printf("scheme=%d directive=%d i=%d \n", scheme_id, dir_type, i);
            if (1 || mode)
            {
                printf("str dir=%s\n", all_scheme[curr_routine][scheme_id].v_dir_str[i].c_str());
                printf("bin dir=");
                for (q = 0; q < dir_bin[i].data.size(); q++)
                    printf("%d ", dir_bin[i].data[q]);
                printf("\n");
            }
            //			if(i>=4)
            //				i=i;
            //			cout<<"directive="<<dir_type<<"\n";

            switch (dir_type)
            {
            case 1:
            {
                struct shadow s;
                struct dis_pat d;

                d.rank = dir_bin[i].data[2];
                s.rank = d.rank;

                for (j = 0; j < d.rank; j++)
                {
                    d.dim[j] = dir_bin[i].data[j + 3];
                }
                q = j + 3;
                for (j = 0; j < s.rank; j++)
                {
                    s.low_wid[j] = dir_bin[i].data[2 * j + q];
                    s.hi_wid[j] = dir_bin[i].data[2 * j + q + 1];
                }

                // !!!!!!!!!!!! Model_distr(&vars[dir_bin[i].data[1]], &d, &s);
                break;
            }

            case 2:
            {	struct ali_pat d;
            struct shadow s;
            // для красоты - и не передавать еще один параметр			d.varid=dir_bin[i].data[2];
            // тут целая манипуляция с переворачиванием индексов выравнивания за счет особенностей фортрана 
                // и особенностей реализации выравнивания в DVM со стороны выравненного массива на выравниваемый а не наоборот как может показаться
            s.rank = vars[dir_bin[i].data[1]].rank;
            d.rank = vars[dir_bin[i].data[2]].rank;
            q = dir_bin[i].data[3];

            //отменяем
            //						//начинаются с конца
            //						for(j=0; j<q; j++)
            //							if(d.rank>j)
            //							{
            //								d.axis[d.rank-j-1]=dir_bin[i].data[3*j+4];
            //								d.coef[d.rank-j-1]=dir_bin[i].data[3*j+5];
            //								d.cons[d.rank-j-1]=dir_bin[i].data[3*j+6];
            //							}
                                    //начинаются с начала
            for (j = 0; j < q; j++)
                if (d.rank > j)
                {
                    d.axis[j] = dir_bin[i].data[3 * j + 4];
                    d.coef[j] = dir_bin[i].data[3 * j + 5];
                    d.cons[j] = dir_bin[i].data[3 * j + 6];
                }

            //остальные размножаются
//						for(j=0; j<d.rank-q; j++)
//						{
//							d.axis[j]=-1;
//							d.coef[j]=0;
//							d.cons[j]=0;
//						}
            for (j = q; j < d.rank; j++)
            {
                d.axis[j] = -1;
                d.coef[j] = 0;
                d.cons[j] = 0;
            }

            for (j = 0; j < s.rank; j++)
            {
                s.low_wid[j] = dir_bin[i].data[3 * q + 2 * j + 4];
                s.hi_wid[j] = dir_bin[i].data[3 * q + 2 * j + 5];
            }


            printf("Align koeff resort = ");
            for (j = 0; j < d.rank; j++)
                printf("Axis %d Koeff %d %d  \n", d.axis[j], d.coef[j], d.cons[j]);

            //!!!!!!!!!!
            //Model_align(&vars[dir_bin[i].data[1]], &vars[dir_bin[i].data[2]], &d, &s);

            break;
            }

            case 3:
            {
                struct ali_pat d;
                struct circle c;
                struct reduct r;
                struct shadow s;
                struct across a;

                //!!!надо бы перевернуть выравнивание слево направо

                r.is = dir_bin[i].data[1] != 0;
                s.is = dir_bin[i].data[2] != 0;
                a.is = dir_bin[i].data[3] != 0;
                r_few.resize(dir_bin[i].data[1]);
                s_few.resize(dir_bin[i].data[2]);
                a_few.resize(dir_bin[i].data[3]);

                d.varid = dir_bin[i].data[5]; //ch new
                d.rank = dir_bin[i].data[6]; //ch

                k = 7; //ch
                for (j = 0; j < d.rank; j++)
                {
                    d.axis[j] = dir_bin[i].data[k++];
                    d.coef[j] = dir_bin[i].data[k++];
                    d.cons[j] = dir_bin[i].data[k++];
                }
                c.rank = dir_bin[i].data[k++];

                //начальное значение, чтобы вычислить кол-во всех итераций
                c.time = 1.0;
                for (j = 0; j < c.rank; j++)
                {
                    c.init[j] = dir_bin[i].data[k++];
                    c.last[j] = dir_bin[i].data[k++];
                    c.step[j] = dir_bin[i].data[k++];
                    c.time = c.time*(c.last[j] - c.init[j] + 1) / c.step[j];
                }
                printf("iters=%.0f\n", c.time);
                //						if(c.time<0) 
                //							getchar();
                c.time = c.time*dir_bin[i].time / 1000000; //время всего цикла // учет числа витков для параллельного цикла
                c.time = c.time * (1000.0 / mach_set[curr_mach].proc_perf);  //учет производительности для параллельного цикла

                printf("time whole loop =%f sec\n", c.time);
                if (c.time < 0)
                    printf("time error\n");


                //						log_file<< "loop iter time ="<<c.time <<"\n";
                if (r.is)
                    for (q = 0; q < r_few.size(); q++)
                    {
                        //							if(mode) printf("reduction ");
                        //							log_file<<"reduction \n";
                        r.loc_type = dir_bin[i].data[k++];
                        r.red_arr_len = dir_bin[i].data[k++];
                        r.red_arr_type = dir_bin[i].data[k++];
                        r_few[q] = r;
                    }

                if (s.is)
                    for (q = 0; q < s_few.size(); q++)
                    {
                        //							log_file<<"shadow_renew \n";
                        s.is_wid = ((dir_bin[i].data[k++] == 1) ? 1 : 0);
                        s.corner = ((dir_bin[i].data[k++] == 1) ? 1 : 0);

                        printf("shadow_renew \n");
                        printf("zzz %d %d %d \n", dir_bin[i].data[k - 1], dir_bin[i].data[k], dir_bin[i].data[k + 1]);
                        s.v = &vars[dir_bin[i].data[k++]];

                        if (s.is_wid == 1)
                        {
                            //надо перевернуть, потому что переворачивать при построении директивы сейчас уже трудно
                            for (j = s.v->rank - 1; j >= 0; j--)
                            {
                                s.low_wid[j] = dir_bin[i].data[k++];
                                s.hi_wid[j] = dir_bin[i].data[k++];
                            }
                        }

                        //							if(mode) printf("shadow_renew ");
                        s_few[q] = s;

                    }

                if (a.is)
                    for (q = 0; q < a_few.size(); q++)
                    {
                        a.v = &vars[dir_bin[i].data[k++]];
                        //надо перевернуть, потому что переворачивать при построении директивы сейчас уже трудно
                        for (j = a.v->rank - 1; j >= 0; j--)
                        {
                            a.low_wid[j] = dir_bin[i].data[k++];
                            a.hi_wid[j] = dir_bin[i].data[k++];
                        }

                        //							if(mode) printf("across ");
                        a_few[q] = a;
                    }

                //						static int ccc=0;
                //						ccc++;
                //						printf("ccc=%d\n",ccc);
                //						if(ccc>=18) 
                //							j=0;
                //							exit(0);
                Model_par(&vars[d.varid], &d, &c, &r, &s, &a); //в структуре только флаги, остальное в векторах

                Interval *tmp_res = new Interval(0);
                tmp_res->copy(CurrInterval);
                //						tmp_res->CalcIdleAndImbalance();
                //						tmp_res->Integrate();


                for (q = 0; q < all_scheme[curr_routine][scheme_id].res_lines.size(); q++)
                {
                    if (all_scheme[curr_routine][scheme_id].res_lines[q] == dir_bin[i].data[4])
                        break;
                }
                if (1 || q >= all_scheme[curr_routine][scheme_id].res_lines.size())
                {
                    tmp_res->CalcIdleAndImbalance();
                    tmp_res->Integrate();
                    all_scheme[curr_routine][scheme_id].results.push_back(tmp_res);
                    all_scheme[curr_routine][scheme_id].res_lines.push_back(dir_bin[i].data[4]);

                    all_scheme[curr_routine][scheme_id].Interval_tree->insert(Find_loop_id_tree(dir_bin[i].data[4]), tmp_res, 0, -1);


                }
                else
                {
                    all_scheme[curr_routine][scheme_id].results[q]->copy_poss(tmp_res, 1, 1);
                }

                break;
            }
            case 4: // IF //пока только с GOTO и без ELSE
                if (mode) printf("goto ");
                poss = 0.5;
                j = 4; // куда GOTO
                if (j < i) if (mode) printf("error: jump back - cannot make prediction - so ignore goto");//ссылка назад

                //else goto next
                p = result[cur_res].poss;
                result[cur_res].poss = p * (1 - poss);
                result[cur_res].line = i;
                //						result[cur_res].go=false;

                                        //true
                result[result_cnt].poss = p * poss;
                result[result_cnt].line = j;
                //						result[result_cnt].go=true;
                result[result_cnt].inter_mid->copy(result[cur_res].inter_mid);
                result[result_cnt].inter_mid->copy_poss(CurrInterval, 1, 1); //add
                result[result_cnt].inter_min->copy(result[cur_res].inter_min);
                result[result_cnt].inter_min->copy_poss(CurrInterval, 1, 1); //add
                result[result_cnt].inter_max->copy(result[cur_res].inter_max);
                result[result_cnt].inter_max->copy_poss(CurrInterval, 1, 1); //add

                result_cnt++;


                break;
            case 5:
            {
                //вызывать перед ПарЛупом (код 3)

                //struct remote rem;
                k = 2;
                lastrem.v = &vars[dir_bin[i].data[k++]];
                lastrem.loop_addr_ref = lastLR; //may be always

                for (j = 0; j < lastrem.v->rank; j++)
                {
                    lastrem.axis[j] = dir_bin[i].data[3 * j + 3];
                    lastrem.coef[j] = dir_bin[i].data[3 * j + 4];
                    lastrem.cons[j] = dir_bin[i].data[3 * j + 5];
                }

                //						rem_few.push_back(lastrem);

                Model_rem(&lastrem);
                break;
            }
            /* //теперь другая схема.. трасса уже есть, вызовы там подставлены
                            case 6: //call subroutine
                                {
                                    //scheme_id уже неактуален, потому что каждая схема идет вместе с ее функцией

                                    int t;

                                    printf("call in routine %d ",curr_routine,i);
                                    k=curr_routine;

                                    for(j=0;j<routines.size();j++)
                                        if(routines[j].id==dir_bin[i].data[1])
                                            break;
                                    curr_routine=j;

                                    for(j=0;j<all_Gvar[curr_gvar].size();j++)
                                        if(Fvar[j]>all_Gvar[curr_gvar][curr_routine])
                                            break;

                                    printf("call routine %d  sch %d\n",curr_routine, all_Gvar[curr_gvar][curr_routine]-Fvar[j-1]);
                                    j=all_Gvar[curr_gvar][curr_routine]-Fvar[j-1];

            //						printf("now model %d  till %d\n",curr_routine, all_scheme[curr_routine][j].v_dir_bin.size()-1);

                                    t=result[cur_res].line;
                                    result[cur_res].line=0;
                                    Model(j,0,all_scheme[curr_routine][j].v_dir_bin.size()-1);
                                    result[cur_res].line=t;

                                    curr_routine=k;

                                    printf("now returned into rout %d   line=%d\n",k,i);
                                    break;
                                }
            */

            case 7:
                if (dir_bin[i].data[2] == 0) //begin of seq loop
                {
                    int save_i = i;
                    Interval *res;

                    float SaveRemoteTime = RemoteTime;


                    printf(" dir_bin[save_i].data[3]=%d   dir_bin[save_i].time=%f  seq_whole_loop_time=%f\n", dir_bin[save_i].data[3], dir_bin[save_i].time, dir_bin[save_i].time * dir_bin[save_i].data[3] / 1000000);

                    //		printf("Interval_tree\n");
                    //		all_scheme[curr_routine][scheme_id].Interval_tree->print(0);

                    if (dir_bin[save_i].data[1] != main_routine_line)
                    {
                        //insert EMPTY interval for adding par intervals
                        all_scheme[curr_routine][scheme_id].Interval_tree->insert(Find_loop_id_tree(dir_bin[save_i].data[1]), NULL, 0, dir_bin[save_i].data[3]);
                    }

                    //		printf("Interval_tree\n");
                    //		all_scheme[curr_routine][scheme_id].Interval_tree->print(0);

                    res = new Interval(0);	//new oper
                    res->Integrate();		//new oper
//						RemoteInterval->Integrate();
                    res->copy_poss(CurrInterval, 0, 1);

                    //						printf("result[cur_res].inter_mid Execution_time=%.15f\n",result[cur_res].inter_mid->GetProcPred(0,_Execution_time));
                    //						printf("seq_loop=%d beg RemoteTime=%.15f\n",dir_bin[save_i].data[1], RemoteTime-SaveRemoteTime);

                                            //моделирование вложенной части
                    i = Model(scheme_id, save_i + 1, save_i + 100000);
                    printf("end of Model seq loop=%d\n", dir_bin[save_i].data[1]);

                    //						RemoteInterval->Integrate();
                    //						printf("result[cur_res].inter_mid Execution_time=%.15f\n",result[cur_res].inter_mid->GetProcPred(0,_Execution_time));
                    printf("seq_loop=%d beg RemoteTime=%.15f\n", dir_bin[save_i].data[1], RemoteTime - SaveRemoteTime);

                    res->copy_poss(CurrInterval, -1, 1);
                    //was						res=new Interval(0);
                    //was						res->Integrate();	

                                            // для последовательных циклов моделируем выполнение только одной итерации. Умножение на число витков будет при объединении интервалов по дереву
                    res->copy_poss(SeqLoopInterval, 1, dir_bin[save_i].time * (1000.0 / mach_set[curr_mach].proc_perf)); //учет производительности
                    res->copy_poss(RemoteCommInterval, 1, RemoteTime - SaveRemoteTime);

                    //						printf("SeqLoopIntervalTime=%.15f\n",SeqLoopInterval->GetProcPred(0,_Execution_time));
                    //						printf("ProcTime=%.15f\n",res->GetProcPred(0,_Execution_time));

                    //						printf("Find_loop_id_tree(dir_bin[save_i].data[1]=%d\n",Find_loop_id_tree(dir_bin[save_i].data[1]));

                    all_scheme[curr_routine][scheme_id].Interval_tree->insert(Find_loop_id_tree(dir_bin[save_i].data[1]), res, 1, -1);

                    //		printf("Interval_tree\n");
                    //		all_scheme[curr_routine][scheme_id].Interval_tree->print(0);


                }
                else
                {
                    return i + 1;
                }

                break;
            case 8:  //INHERIT

                break;
            case 10:
                if (1 || mode) printf("END");
                break;
            };

            if (mode) printf("\n");

            result[cur_res].line++;
            if (dir_type <= 3) //no dir_type==5
            {
                result[cur_res].inter_mid->copy_poss(CurrInterval, 1, 1); //add
                result[cur_res].inter_min->copy_poss(CurrInterval, 1, 1); //add
                result[cur_res].inter_max->copy_poss(CurrInterval, 1, 1); //add
            }

            //			printf("all_scheme[curr_routine][scheme_id].results.size()=%d\n",all_scheme[curr_routine][scheme_id].results.size());
            //			for(j=0;j<all_scheme[curr_routine][scheme_id].results.size();j++)
            //				all_scheme[curr_routine][scheme_id].results[j]->CalcIdleAndImbalance();//try kart

        }
        //		printInterval();


    }

    return 0;
}

static int multiply(const vector<int> &array_) 
{
    int res = 1;
    for (size_t i = 0; i < array_.size(); ++i)
        res *= array_[i];
    return res;
}

static vector<int> get_divisors(size_t N) 
{
    vector<int> res;
    res.push_back(N);

    if (N > 1) 
    {
        int k = N / 2;
        for (size_t i = k; i > 1; --i) 
            if (N % i == 0)
                res.push_back(i);        
        res.push_back(1);
    }
    return res;
}

static void recGen(vector<int> divisors, vector<int> &matrix, size_t index, int procNum, vector<vector<int>> &result) 
{
    if (index < matrix.size()) 
    {
        for (size_t i = 0; i < divisors.size(); i++) 
        {
            matrix[index] = divisors[i];
            recGen(divisors, matrix, index + 1, procNum, result);
        }
    }
    else 
    {
        if (multiply(matrix) == procNum)
            result.push_back(matrix);
    }
}

vector<vector<int>> generate_matrixes(int procNum, int dim) 
{
    vector<vector<int>> result;
    vector<int> divisors = get_divisors(procNum);

    vector<int> matrix(dim);
    recGen(divisors, matrix, 0, procNum, result);
    return result;
}

void predictScheme(const int regId, const vector<pair<DIST::Array*, const DistrVariant*>> &distVar, 
                   const set<DIST::Array*> &allArrays, const map<LoopGraph*, ParallelDirective*> &dirsToPredict)
{    
    ps = new PS(mach_MYRINET, 4, 7.0, 0.004, 512); //MVS15k between nodes
    //ps = new PS(mach_MYRINET, 4, 0.0, 0.0, 512); //fastest communications

    vector<long> testTopology = { 2, 2 };
    //set configuration of PS
    ps->setTopology(testTopology);

    vector<long>	lb;
    vector<long>	ASizeArray;
    mach_Type		AMType;
    int				AnumChanels = 1;
    double			Ascale = 1.0;
    double			ATStart;
    double			ATByte;
    double			AProcPower;
    vector<double>  AvProcPower;

    ps->nextPS(lb, ASizeArray, AMType, AnumChanels, Ascale, ATStart, ATByte, AProcPower, AvProcPower);

    rootVM = new VM(ASizeArray, AMType, AnumChanels, Ascale, ATStart / 1000000.0, ATByte / 1000000.0, AProcPower, AvProcPower);
    currentVM = rootVM;
    rootProcCount = rootVM->getProcCount();

    // времена работы каждого процессора
    procElapsedTime = new double[rootProcCount];
    for (int i = 0; i < rootProcCount; ++i)
        procElapsedTime[i] = 0.0;

    MinSizesOfAM.clear();
    int maxSizeDist = 0;
    for (auto &elem : distVar)
    {
        DIST::Array *array = elem.first;
        const DistrVariant *var = elem.second;

        int countBlock = 0;
        for (int z = 0; z < var->distRule.size(); ++z)
            if (var->distRule[z] == dist::BLOCK)
                ++countBlock;
        maxSizeDist = std::max(maxSizeDist, countBlock);
    }
    MinSizesOfAM.resize(maxSizeDist);
    std::fill(MinSizesOfAM.begin(), MinSizesOfAM.end(), 0);
    for (auto &elem : distVar)
    {
        DIST::Array *array = elem.first;
        const DistrVariant *var = elem.second;
        auto sizes = array->GetSizes();
        int countBlock = 0;
        for (int z = 0, dim = 0; z < var->distRule.size(); ++z)
        {
            if (var->distRule[z] == dist::BLOCK)
            {
                MinSizesOfAM[dim] = std::max(MinSizesOfAM[dim], (long)(sizes[z].second - sizes[z].first + 1));
                dim++;
            }
        }
    }

    for (auto &var : distVar)
        Model_distr(var.first, var.second);
    for (auto &array : allArrays)
        if (!array->isTemplate() && !array->isLoopArray())
            Model_align(array, regId);

    for (auto &dir : dirsToPredict)
    {
        CurrInterval = new Interval(0);
        Model_par(dir.first, dir.second);
        CurrInterval->CalcIdleAndImbalance();
        CurrInterval->Integrate();
        printf("loop %d exec time = %f\n", dir.first->lineNum, CurrInterval->GetExecTime());
        delete CurrInterval;
    }

    delete rootVM;
    delete ps;
}