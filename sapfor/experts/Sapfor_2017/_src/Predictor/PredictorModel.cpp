#include "../Utils/leak_detector.h"
//#define _CRT_SECURE_NO_WARNINGS

#include <iomanip>
#include <vector>
#include <map>
#include <set>

#ifdef _MSC_VER
#include <io.h>
#else
#include <sys/types.h>
#include <dirent.h>
#endif

#include "../Distribution/Distribution.h"
#include "../Distribution/DvmhDirective.h"
#include "../GraphLoop/graph_loops.h"
#include "../ParallelizationRegions/ParRegions.h"

#include "PredictorInterface.h"
#include "PredictorModel.h"


using std::vector;
using std::map;
using std::set;
using std::to_string;

static void setVectorCallRet(FuncCall *f)
{
    // если у каждого процессора своя мощность, то надо заполнить вектор vcall_time следующим образом. 
    // В предикторе это делалось автоматически при чтении трассы из файла
    f->vcall_time.resize(currentVM->getProcCount());
    for (int k = 0; k < currentVM->getProcCount(); ++k)
        f->vcall_time[k] = f->call_time / currentVM->getProcPower(k);

    f->vret_time.resize(currentVM->getProcCount());
    for (int k = 0; k < currentVM->getProcCount(); ++k)
        f->vret_time[k] = f->ret_time / currentVM->getProcPower(k);    
}

static int printInterval(Interval *inter)
{
    for (int proc_no = 0; proc_no < MPSProcCount(); ++proc_no)
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
static long remIds = 1;

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
    long cur_amv, cur_ps = 999; //попробую без cur_amv_ptr (считая его = cur_amv)
    string debug = "";
    {
        FuncCall f;
        f.func_id = crtamv_;
        crtamv_Info *tmp_params = new crtamv_Info;
        f.call_params = (void *)tmp_params; // point to parameters

        tmp_params->ID = getId(array, mapIds, ids); //для различия
        cur_amv = tmp_params->ID;
        tmp_params->AM_ID = cur_amv; //possible not        

        auto sizes = array->GetSizes();
        tmp_params->SizeArray.resize(sizes.size());
        const int rank = (int)sizes.size();
        for (int i = rank - 1; i >= 0; --i)
            tmp_params->SizeArray[rank - 1 - i] = sizes[i].second - sizes[i].first + 1;
        tmp_params->StaticSign = 0; //possible not
        
        f.call_time = 0.00000100;		// call time
        f.ret_time = 0.00000100;		// return time
        setVectorCallRet(&f);

        if (printOut)
        {
            debug += "crtamv SizeArray=";
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

double Model_Single_Rem(const pair<DIST::Array*, vector<long>> &dirRem)
{
    long RID = -1;
    
    FuncCall f;
    f.func_id = crtrbp_;
    crtrbp_Info* tmp_params = new crtrbp_Info;

    f.call_params = (void *)tmp_params; // point to parameters

    RID = tmp_params->ID = (remIds++);//для различия
    tmp_params->RemArrayHeader = getId(dirRem.first, mapArrayAddrs, arrayAddr);
    tmp_params->StaticSign = 0; //may be not always
    tmp_params->PSRef = 0;
    tmp_params->IsLocal = 0;
    tmp_params->CoordArray = dirRem.second; //это координаты рассылаемого элемента

    f.call_time = 0.00000100;		// call time
    f.ret_time = 0.00000100;		// return time
    setVectorCallRet(&f);
    f.crtrbp();
    return f.ret_time + f.call_time;
}

static int findPosInParallel(vector<string> &parallel, const string &find)
{
    int ret = -1;
    for (int z = 0; z < parallel.size(); ++z)
        if (parallel[z] == find)
            return z + 1;
    return ret;
}

static bool shadowExist(vector<pair<pair<string, string>, vector<pair<int, int>>>> &shadows)
{
    for (auto &sh : shadows)
        for (auto &elem : sh.second)
            if (elem.first != 0 || elem.second != 0)
                return true;
    return false;
}

//==============
static int Model_par(LoopGraph *loop, ParallelDirective *directive, const set<DIST::Array*> &allArrays, FILE *printOut = NULL)
{
    long LR = -1, RID = -1, RIDG = -1, SHG = -1, SHG1 = -1, SHG2 = -1, REMID = -1;
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
    }

    // TODO: add CORNER
    if (shadowExist(directive->shadowRenew)) //SHADOW RENEW
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
        
        auto arraysInDir = fillArraysFromDir(loop->loop);
        for (int j = 0; j < directive->shadowRenew.size(); ++j)
        {
            DIST::Array *shArray = NULL;
            for (auto &elem : arraysInDir)
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
            tmp_params->FullShdSign = 0; //CORNER
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

    if (shadowExist(directive->across)) // ACROSS
    {        
        {
            FuncCall f;
            f.func_id = crtshg_;
            crtshg_Info* tmp_params = new crtshg_Info;
            f.call_params = (void *)tmp_params; // point to parameters

            tmp_params->ShadowGroupRef = (redShIds++);//для различия            
            SHG1 = tmp_params->ShadowGroupRef;
            tmp_params->StaticSign = 0; //poss not

            f.call_time = 0.00000100;		// call time
            f.ret_time = 0.00000100;		// return time
            setVectorCallRet(&f);

            f.crtshg();
        }

        auto arraysInDir = fillArraysFromDir(loop->loop);
        for (int j = 0; j < directive->across.size(); ++j)
        {
            DIST::Array *acArray = NULL;
            for (auto &elem : arraysInDir)
                if (elem->GetName() == directive->across[j].first.second)
                    acArray = elem;
            checkNull(acArray, __FILE__, __LINE__);

            FuncCall f;
            f.func_id = insshd_;
            inssh_Info* tmp_params = new inssh_Info;
            f.call_params = (void *)tmp_params; // point to parameters

            tmp_params->ShadowGroupRef = SHG1;
            tmp_params->ArrayHandlePtr = getId(acArray, mapArrayAddrsPtr, arrayAddrPtr);
            tmp_params->ArrayHeader = getId(acArray, mapArrayAddrs, arrayAddr);            
            tmp_params->MaxShdCount = 1; //poss not
            tmp_params->HiShdWidthArray.resize(0);
            tmp_params->LowShdWidthArray.resize(0);
            tmp_params->ShdSignArray.resize(0);

            const int rank = acArray->GetDimSize();
            for (int z = 0; z < rank; ++z)
            {
                tmp_params->HiShdWidthArray.push_back(0);
                tmp_params->LowShdWidthArray.push_back(directive->across[j].second[rank - 1 - z].first);
                tmp_params->ShdSignArray.push_back(3); //poss not
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

            tmp_params->ShadowGroupRef = (redShIds++);//для различия
            SHG2 = tmp_params->ShadowGroupRef;
            tmp_params->StaticSign = 0; //poss not

            f.call_time = 0.00000100;		// call time
            f.ret_time = 0.00000100;		// return time
            setVectorCallRet(&f);

            f.crtshg();
        }

        for (int j = 0; j < directive->across.size(); ++j)
        {
            DIST::Array *acArray = NULL;
            for (auto &elem : arraysInDir)
                if (elem->GetName() == directive->across[j].first.second)
                    acArray = elem;
            checkNull(acArray, __FILE__, __LINE__);

            FuncCall f;
            f.func_id = insshd_;
            inssh_Info* tmp_params = new inssh_Info;
            f.call_params = (void *)tmp_params; // point to parameters

            tmp_params->ShadowGroupRef = SHG2;
            tmp_params->ArrayHandlePtr = getId(acArray, mapArrayAddrsPtr, arrayAddrPtr);
            tmp_params->ArrayHeader = getId(acArray, mapArrayAddrs, arrayAddr);            
            tmp_params->MaxShdCount = 1; //poss not
            tmp_params->HiShdWidthArray.resize(0);
            tmp_params->LowShdWidthArray.resize(0);
            tmp_params->ShdSignArray.resize(0);

            const int rank = acArray->GetDimSize();
            for (int z = 0; z < rank; ++z)
            {
                tmp_params->HiShdWidthArray.push_back(directive->across[j].second[rank - 1 - z].second);
                tmp_params->LowShdWidthArray.push_back(0);
                tmp_params->ShdSignArray.push_back(5);
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


    if (shadowExist(directive->across)) //ACROSS
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

    // vector<int> -> -1 == full, 0  == one elem
    map<DIST::Array*, vector<long>> remoteAccess = fillRemoteInParallel(loop->loop);
    if (remoteAccess.size())
    {        
        auto arraysInDir = fillArraysFromDir(loop->loop);
        for (auto &rem : remoteAccess)
        {
            DIST::Array *remArray = rem.first;            

            {
                FuncCall f;
                f.func_id = crtrbl_;
                crtrbl_Info* tmp_params = new crtrbl_Info;
                f.call_params = (void *)tmp_params; // point to parameters

                tmp_params->BufferHeader = (remIds++);//для различия
                REMID = tmp_params->BufferHeader;
                tmp_params->RemArrayHeader = getId(remArray, mapArrayAddrs, arrayAddr);

                const int rank = remArray->GetDimSize();
                tmp_params->AxisArray.resize(rank);
                tmp_params->CoeffArray.resize(rank);
                tmp_params->ConstArray.resize(rank);

                for (int i = 0; i < rank; ++i)
                {
                    if (rem.second[i] == 0)
                    {
                        tmp_params->AxisArray[rank - 1 - i] = 0;
                        tmp_params->CoeffArray[rank - 1 - i] = 0;
                        tmp_params->ConstArray[rank - 1 - i] = 0;
                    }
                    else //if (rem.second[i] == 1)
                    {
                        tmp_params->AxisArray[rank - 1 - i] = -1;
                        tmp_params->CoeffArray[rank - 1 - i] = -1;
                        tmp_params->ConstArray[rank - 1 - i] = -1;
                    }                    
                }

                tmp_params->LoopRef = LR; //may be always equal lastLR:
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

                tmp_params->ID = REMID;
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

                tmp_params->ID = REMID;

                f.call_time = 0.00000100;		// call time
                f.ret_time = 0.00000100;		// return time
                setVectorCallRet(&f);

                f.waitrb();
            }
        }
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

        f.call_time = loop->executionTimeInSec; // call time, c->time - это время цикла!
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

static int multiply(const vector<long> &array_)
{
    int res = 1;
    for (long i = 0; i < array_.size(); ++i)
        res *= array_[i];
    return res;
}

static vector<long> get_divisors(long N)
{
    vector<long> res;
    res.push_back(N);

    if (N > 1) 
    {
        int k = N / 2;
        for (long i = k; i > 1; --i) 
            if (N % i == 0)
                res.push_back(i);        
        res.push_back(1);
    }
    return res;
}

static void recGen(vector<long> divisors, vector<long> &matrix, size_t index, int procNum, vector<vector<long>> &result)
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

static vector<vector<long>> generate_matrixes(int procNum, int dim)
{
    vector<vector<long>> result;
    vector<long> divisors = get_divisors(procNum);

    vector<long> matrix(dim);
    recGen(divisors, matrix, 0, procNum, result);
    return result;
}

static void addTimeMessage(map<string, vector<Messages>> &messagesByFile, const string file, const int line)
{
    string messg = "";
    __spf_printToBuf(messg, "Can not find execution time for this loop, try to get times statistic");
    messagesByFile[file].push_back(Messages(ERROR, line, messg, 3016));

    __spf_print(1, "%s on line %d\n", messg.c_str(), line);
}

vector<vector<long>> getTopologies(const int procNum, const int maxSizeDist)
{
    return generate_matrixes(procNum, maxSizeDist);
}

int predictScheme(ParallelRegion *reg, const vector<pair<DIST::Array*, const DistrVariant*>> &distVar,
                  const set<DIST::Array*> &allArrays, const map<LoopGraph*, ParallelDirective*> &dirsToPredict,
                  map<string, vector<SpfInterval*>> &intervals, map<string, vector<Messages>> &messagesByFile, 
                  const vector<std::tuple<DIST::Array*, vector<long>, pair<string, int>>> &allSingleRemotes,
                  const int maxSizeDist, const int procNum)
{
    map<string, map<SgStatement*, SpfInterval*>> intervalsBySt;
    for (auto &byFile : intervals)
    {
        map<int, SpfInterval*> tmp;
        createMapOfinterval(tmp, byFile.second);
        for (auto &interval : tmp)
            intervalsBySt[byFile.first][interval.second->begin] = interval.second;
    }

    int errCode = 0;

    MinSizesOfAM.clear();    
    MinSizesOfAM.resize(maxSizeDist);
    std::fill(MinSizesOfAM.begin(), MinSizesOfAM.end(), 0);

    map<string, map<int, SpfInterval*>> mapOfIntervals;
    for (auto &inter : intervals)
        createMapOfinterval(mapOfIntervals[inter.first], inter.second);

    vector<vector<long>> allTolopogies = generate_matrixes(procNum, maxSizeDist);

    for (int topIdx = 0; topIdx < allTolopogies.size(); ++topIdx)
    {
        //TStart and TByte in mkS, 
        ps = new PS(mach_ETHERNET, 1, 7.0, 0.001, procNum); //0.001 == 1Gb/s
        //ps = new PS(mach_ETHERNET, 1, 0.0, 0.0, procNum); //fastest communications

        //set configuration of PS
        ps->setTopology(allTolopogies[topIdx]);

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
                Model_align(array, reg->GetId());

        for (auto &dir : dirsToPredict)
        {
            if (dir.first->executionTimeInSec == -1.0)
            {
                addTimeMessage(messagesByFile, dir.first->fileName, dir.first->lineNum);
                continue;
                errCode = -1;
            }

            auto itByFile = mapOfIntervals.find(dir.first->fileName);
            if (itByFile == mapOfIntervals.end())
            {
                addTimeMessage(messagesByFile, dir.first->fileName, dir.first->lineNum);
                continue;
                errCode = -1;
            }
            auto itInterval = itByFile->second.find(dir.first->lineNum);
            if (itInterval == itByFile->second.end())
            {
                addTimeMessage(messagesByFile, dir.first->fileName, dir.first->lineNum);
                continue;
                errCode = -1;
            }
            else
            {
                CurrInterval = new Interval(0);
                Model_par(dir.first, dir.second, allArrays);
                CurrInterval->CalcIdleAndImbalance();
                CurrInterval->Integrate();

                itInterval->second->predictedTimes[topIdx] = CurrInterval->GetExecTime() * itInterval->second->exec_count;
                delete CurrInterval;
            }
            //printf("loop %d exec time = %f\n", dir.first->lineNum, CurrInterval->GetExecTime());            
        }

        for (auto &singleRem : allSingleRemotes)
        {
            pair<string, int> place = get<2>(singleRem);
            DIST::Array *array = get<0>(singleRem);
            auto coords = get<1>(singleRem);

            auto itFile = intervalsBySt.find(place.first);
            if (itFile == intervalsBySt.end())
                printInternalError(convertFileName(__FILE__).c_str(), __LINE__);
            auto nearestInt = findNearestDown(itFile->second, SgStatement::getStatementByFileAndLine(place.first, place.second));

            CurrInterval = new Interval(0);
            auto tmpPair = make_pair(array, coords);
            double singleRemTime = Model_Single_Rem(tmpPair);
            delete CurrInterval;

            nearestInt->predictedRemoteTimes[topIdx] = singleRemTime * nearestInt->exec_count;
        }

        delete rootVM;
        delete ps;

        if (errCode != 0)
            break;
    }

    return errCode;
}