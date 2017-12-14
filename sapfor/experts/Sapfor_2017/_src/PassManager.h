#pragma once

#include <map>
#include <set>
#include <vector>
#include "transform.h"

using std::vector;
using std::map;
using std::set;

#define list vector<Pass>

static map<passes, vector<passes>> *passDeps;

class Pass
{
private:    
    passes name;
public:
    const Pass& operator<=(const Pass &right) const
    {
        if ((*passDeps).find(right.name) == (*passDeps).end())
            (*passDeps)[right.name] = vector<passes>();
        (*passDeps)[right.name].push_back(this->name);
        return right;
    }

    Pass& operator<=(Pass &right) const
    {
        if ((*passDeps).find(right.name) == (*passDeps).end())
            (*passDeps)[right.name] = vector<passes>();
        (*passDeps)[right.name].push_back(this->name);
        return right;
    }

    const list& operator<=(const list &right_vec) const
    {
        for (int i = 0; i < right_vec.size(); ++i)
        {
            if ((*passDeps).find(right_vec[i].name) == (*passDeps).end())
                (*passDeps)[right_vec[i].name] = vector<passes>();
            (*passDeps)[right_vec[i].name].push_back(this->name);
        }
        return right_vec;
    }

    friend const Pass& operator<=(const list &left_vec, const Pass &right)
    {
        if ((*passDeps).find(right.name) == (*passDeps).end())
            (*passDeps)[right.name] = vector<passes>();

        for (int i = 0; i < left_vec.size(); ++i)
            (*passDeps)[right.name].push_back(left_vec[i].name);

        return right;
    }

    friend const list& operator<<(const list &left_vec, const list &right_vec) 
    {
        for (int k = 0; k < right_vec.size(); ++k)
        {
            if ((*passDeps).find(right_vec[k].name) == (*passDeps).end())
                (*passDeps)[right_vec[k].name] = vector<passes>();

            for (int i = 0; i < left_vec.size(); ++i)
                (*passDeps)[right_vec[k].name].push_back(left_vec[i].name);
        }
        return right_vec;
    }

    Pass(passes name) : name(name) { }    
};

static void depsToGraphViz(const map<passes, vector<passes>> &passDepsIn)
{
    printf("digraph G {");
    for (auto it = passDepsIn.begin(); it != passDepsIn.end(); ++it)
    {
        for (int k = 0; k < it->second.size(); ++k)
            printf("\"%s\" -> \"%s\";\n", passNames[it->first], passNames[it->second[k]]);
    }
    printf("}\n");
}

void InitPassesDependencies(map<passes, vector<passes>> &passDepsIn, set<passes> &passesIgnoreStateDone)
{
    if (passDepsIn.size() != 0)
        return;

    passDeps = &passDepsIn;

    list({ FILE_LINE_INFO, BUILD_INCLUDE_DEPENDENCIES }) <= Pass(CORRECT_VAR_DECL);

    list({ PRIVATE_CALL_GRAPH_STAGE1, PRIVATE_CALL_GRAPH_STAGE2, MACRO_EXPANSION }) <= Pass(SUBST_EXPR) <= Pass(SUBST_EXPR_AND_UNPARSE);

    list({ PRIVATE_CALL_GRAPH_STAGE1, PRIVATE_CALL_GRAPH_STAGE2 }) <= Pass(PRIVATE_ANALYSIS_SPF);

    //Pass(LOOP_GRAPH) <= Pass(PRIVATE_CALL_GRAPH_STAGE3) <= Pass(PRIVATE_ANALYSIS_SPF);
    //Pass(PRIVATE_ANALYSIS_SPF) <= Pass(LOOP_ANALYZER_DATA_DIST_S1);

    Pass(CORRECT_VAR_DECL) <= list({ VERIFY_DVM_DIRS, PREPROC_SPF, VERIFY_ENDDO, VERIFY_INCLUDE, PREPROC_ALLOCATES, CHECK_FUNC_TO_INCLUDE, FILL_PAR_REGIONS_LINES }) <= Pass(CODE_CHECKER_PASSES);

    list({ VERIFY_ENDDO, VERIFY_INCLUDE, PREPROC_SPF, PREPROC_ALLOCATES, GET_ALL_ARRAY_DECL }) << list({ CALL_GRAPH, MACRO_EXPANSION });

    list({ VERIFY_ENDDO, VERIFY_INCLUDE, PREPROC_ALLOCATES }) <= Pass(GET_ALL_ARRAY_DECL) <= Pass(PREPROC_SPF);

    list({ CALL_GRAPH2, CODE_CHECKER_PASSES, SUBST_EXPR, GET_ALL_ARRAY_DECL }) <= Pass(LOOP_ANALYZER_DATA_DIST_S1);
    
    Pass(LOOP_ANALYZER_DATA_DIST_S1) <= Pass(LOOP_ANALYZER_DATA_DIST_S2) <= Pass(CREATE_TEMPLATE_LINKS) <= Pass(LOOP_ANALYZER_COMP_DIST);

    list({ VERIFY_ENDDO, SUBST_EXPR }) <= Pass(LOOP_GRAPH) <= Pass(CALL_GRAPH) <= Pass(CALL_GRAPH2);
        
    Pass(MACRO_EXPANSION) <= Pass(CALL_GRAPH);

    Pass(LOOP_ANALYZER_DATA_DIST_S2) <= Pass(CREATE_NESTED_LOOPS);

    list({ CORRECT_VAR_DECL, PREPROC_SPF }) << list({ LOOP_GRAPH, CALL_GRAPH, CALL_GRAPH2 });
        
    list({ PREPROC_SPF, CALL_GRAPH2 }) <= Pass(FILL_PAR_REGIONS_LINES);
    
    Pass(LOOP_ANALYZER_COMP_DIST) <= list({ CREATE_DISTR_DIRS, CREATE_PARALLEL_DIRS, INSERT_PARALLEL_DIRS });
    
    Pass(CALL_GRAPH2) <= list({ ONLY_ARRAY_GRAPH, CREATE_NESTED_LOOPS, FIND_FUNC_TO_INCLUDE });

    list({ CORRECT_VAR_DECL, REVERT_SUBST_EXPR, VERIFY_INCLUDE } ) << list({ UNROLL_LOOPS, CONVERT_TO_ENDDO, CORRECT_CODE_STYLE, REMOVE_DVM_DIRS });
    list({ CORRECT_VAR_DECL, REVERT_SUBST_EXPR }) << list({ INSERT_INCLUDES, INSERT_INCLUDES, UNPARSE_FILE });

    passesIgnoreStateDone.insert({ CREATE_PARALLEL_DIRS, INSERT_PARALLEL_DIRS, INSERT_SHADOW_DIRS, EXTRACT_PARALLEL_DIRS, PRIVATE_ANALYSIS_SPF,
                                   EXTRACT_SHADOW_DIRS, REVERT_SUBST_EXPR, CREATE_REMOTES, UNPARSE_FILE, REMOVE_AND_CALC_SHADOW });
        
    //only for print  
    //list({ CREATE_PARALLEL_DIRS, PRIVATE_ANALYSIS_SPF, CREATE_REMOTES, REVERT_SUBST_EXPR, UNPARSE_FILE, EXTRACT_PARALLEL_DIRS }) <= Pass(INSERT_PARALLEL_DIRS);
    //depsToGraphViz(passDepsIn);
    //exit(0);
}
#undef list
