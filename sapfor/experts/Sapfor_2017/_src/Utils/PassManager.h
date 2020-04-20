#pragma once

#include <map>
#include <set>
#include <vector>
#include "../Sapfor.h"

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
    FILE *file = fopen("pass_tree.txt", "w");
    if (!file)
        printf("ERROR in creating 'pass_tree.txt' file\n");
    else
    {
        fprintf(file, "digraph G {");
        for (auto it = passDepsIn.begin(); it != passDepsIn.end(); ++it)
        {
            for (int k = 0; k < it->second.size(); ++k)
                fprintf(file, "\"%s\" -> \"%s\";\n", passNames[it->first], passNames[it->second[k]]);
        }
        fprintf(file, "}\n");
        fclose(file);
        printf("write to 'pass_tree.txt' file complited\n");
    }
}

void InitPassesDependencies(map<passes, vector<passes>> &passDepsIn, set<passes> &passesIgnoreStateDone, bool printTree = false)
{
    if (passDepsIn.size() != 0)
        return;

    passDeps = &passDepsIn;

    Pass(PREPROC_SPF) <= Pass(CREATE_INTER_TREE);

    list({ CREATE_INTER_TREE, CORRECT_VAR_DECL }) << list({ GCOV_PARSER, PREDICT_SCHEME, INSERT_INTER_TREE });

    list({ FILE_LINE_INFO, BUILD_INCLUDE_DEPENDENCIES }) <= Pass(CORRECT_VAR_DECL);

    Pass(DEF_USE_STAGE1) <= Pass(DEF_USE_STAGE2);

    list({ VERIFY_DVM_DIRS, PRIVATE_CALL_GRAPH_STAGE1, PRIVATE_CALL_GRAPH_STAGE2, MACRO_EXPANSION, CONVERT_ASSIGN_TO_LOOP, DEF_USE_STAGE1, DEF_USE_STAGE2, FILL_PARALLEL_REG_FOR_SUBS, VERIFY_COMMON }) <= Pass(SUBST_EXPR) <= Pass(SUBST_EXPR_AND_UNPARSE);
        
    list({ VERIFY_DVM_DIRS, PRIVATE_CALL_GRAPH_STAGE1, PRIVATE_CALL_GRAPH_STAGE2, PRIVATE_CALL_GRAPH_STAGE4, FIND_FUNC_TO_INCLUDE }) <= Pass(PRIVATE_ANALYSIS_SPF);

    Pass(LOOP_GRAPH) <= Pass(PRIVATE_CALL_GRAPH_STAGE3) <= Pass(PRIVATE_ANALYSIS_SPF) <= list({ LOOP_ANALYZER_DATA_DIST_S0, LOOP_ANALYZER_DATA_DIST_S1, ONLY_ARRAY_GRAPH });
    
    Pass(CORRECT_VAR_DECL) <= list({ VERIFY_DVM_DIRS, PREPROC_SPF, VERIFY_ENDDO, VERIFY_INCLUDE, PREPROC_ALLOCATES, CHECK_FUNC_TO_INCLUDE, FILL_PAR_REGIONS_LINES, CONVERT_ASSIGN_TO_LOOP, VERIFY_COMMON, VERIFY_EQUIVALENCE, PRINT_PAR_REGIONS_ERRORS }) <= Pass(CODE_CHECKER_PASSES);

    list({ VERIFY_ENDDO, VERIFY_INCLUDE, PREPROC_SPF, PREPROC_ALLOCATES, GET_ALL_ARRAY_DECL, GCOV_PARSER }) << list({ CALL_GRAPH, MACRO_EXPANSION, DEF_USE_STAGE1 });

    list({ VERIFY_ENDDO, VERIFY_INCLUDE, PREPROC_ALLOCATES, FILL_PARALLEL_REG_FOR_SUBS }) << list({ GET_ALL_ARRAY_DECL, FILL_COMMON_BLOCKS }) <= Pass(PREPROC_SPF);

    Pass(CHECK_PAR_REG_DIR) <= Pass(FILL_PARALLEL_REG_FOR_SUBS);

    list({ GET_ALL_ARRAY_DECL, CALL_GRAPH2, CODE_CHECKER_PASSES, SUBST_EXPR }) << list({ LOOP_ANALYZER_DATA_DIST_S0, LOOP_ANALYZER_DATA_DIST_S1, ONLY_ARRAY_GRAPH });

    Pass(LOOP_ANALYZER_DATA_DIST_S0) <= Pass(LOOP_ANALYZER_DATA_DIST_S1) <= Pass(LOOP_ANALYZER_DATA_DIST_S2) <= Pass(CREATE_TEMPLATE_LINKS) <= Pass(LOOP_ANALYZER_COMP_DIST);

    list({ VERIFY_ENDDO, SUBST_EXPR, CONVERT_ASSIGN_TO_LOOP }) <= Pass(LOOP_GRAPH) <= Pass(CALL_GRAPH) <= Pass(CALL_GRAPH2);

    Pass(MACRO_EXPANSION) <= Pass(CALL_GRAPH);

    list({ PREPROC_SPF, PROCESS_IO }) <= Pass(CREATE_CHECKPOINTS);

    list({ FILL_COMMON_BLOCKS, GET_ALL_ARRAY_DECL }) <= Pass(VERIFY_COMMON) <= Pass(CREATE_CHECKPOINTS);

    Pass(CONVERT_SAVE_TO_MODULE) <= Pass(CREATE_CHECKPOINTS);

    Pass(FILL_PAR_REGIONS_LINES) <= Pass(VERIFY_EQUIVALENCE);
    
    Pass(LOOP_ANALYZER_DATA_DIST_S2) <= Pass(CREATE_NESTED_LOOPS);

    list({ CORRECT_VAR_DECL, PREPROC_SPF }) << list({ LOOP_GRAPH, CALL_GRAPH, CALL_GRAPH2 });

    list({ PREPROC_SPF, CALL_GRAPH2 }) <= Pass(FILL_PAR_REGIONS_LINES) <= list({ EXPAND_EXTRACT_PAR_REGION, CHECK_FUNC_TO_INCLUDE, FIND_FUNC_TO_INCLUDE, CHECK_ARGS_DECL });

    list({ PREPROC_SPF, CALL_GRAPH2, FILL_PAR_REGIONS_LINES }) <= Pass(FILL_PAR_REGIONS) <= Pass(RESOLVE_PAR_REGIONS);

    list({ REVERT_SUBST_EXPR, CONVERT_LOOP_TO_ASSIGN }) <= Pass(RESOLVE_PAR_REGIONS);

    Pass(REVERT_SUBST_EXPR) <= Pass(EXPAND_EXTRACT_PAR_REGION);
    
    Pass(FILL_PAR_REGIONS) <= Pass(PRINT_PAR_REGIONS_ERRORS);

    list({ PREPROC_SPF, CORRECT_VAR_DECL }) <= Pass(FILL_PAR_REGIONS_LINES);

    list({ LOOP_ANALYZER_COMP_DIST, CONVERT_LOOP_TO_ASSIGN }) << list({ CREATE_DISTR_DIRS, CREATE_PARALLEL_DIRS, INSERT_PARALLEL_DIRS });
    
    Pass(CALL_GRAPH2) <= list({ ONLY_ARRAY_GRAPH, CREATE_NESTED_LOOPS, FIND_FUNC_TO_INCLUDE, CHECK_FUNC_TO_INCLUDE, CHECK_ARGS_DECL, FUNCTION_CLEARING });

    list({ CORRECT_VAR_DECL, REVERT_SUBST_EXPR, VERIFY_INCLUDE } ) << list({ UNROLL_LOOPS, CONVERT_TO_ENDDO, CORRECT_CODE_STYLE, REMOVE_DVM_DIRS, REMOVE_DVM_DIRS_TO_COMMENTS, REMOVE_DVM_INTERVALS });

    list({ CALL_GRAPH2, CONVERT_LOOP_TO_ASSIGN, REVERT_SUBST_EXPR }) <= Pass(INLINE_PROCEDURES);

    Pass(CONVERT_LOOP_TO_ASSIGN) <= list({ CONVERT_TO_ENDDO, CORRECT_CODE_STYLE, INSERT_INCLUDES, REMOVE_DVM_DIRS, REMOVE_DVM_DIRS_TO_COMMENTS, REMOVE_DVM_INTERVALS, INLINE_PROCEDURES });

    list({ CORRECT_VAR_DECL, REVERT_SUBST_EXPR }) << list({ INSERT_INCLUDES, UNPARSE_FILE, SET_TO_ALL_DECL_INIT_ZERO });

    list({ CALL_GRAPH2, REVERT_SUBST_EXPR }) <= Pass(PRIVATE_ARRAYS_BREEDING);

    list({ GCOV_PARSER, CREATE_INTER_TREE, CALL_GRAPH, CALL_GRAPH2 }) <= Pass(CREATE_PARALLEL_REGIONS);

    list({ LOOP_ANALYZER_DATA_DIST_S1, REVERT_SUBST_EXPR }) << list({ LOOPS_SPLITTER, LOOPS_COMBINER });

    list({ PRIVATE_CALL_GRAPH_STAGE1, PRIVATE_CALL_GRAPH_STAGE2, MACRO_EXPANSION, CONVERT_ASSIGN_TO_LOOP, DEF_USE_STAGE1, DEF_USE_STAGE2, LOOP_GRAPH, CALL_GRAPH }) <= Pass(INSERT_REGIONS);

    list({ CALL_GRAPH2, REVERT_SUBST_EXPR, CONVERT_LOOP_TO_ASSIGN }) <= Pass(DUPLICATE_FUNCTIONS);

    passesIgnoreStateDone.insert({ CREATE_PARALLEL_DIRS, INSERT_PARALLEL_DIRS, INSERT_SHADOW_DIRS, EXTRACT_PARALLEL_DIRS, PRIVATE_ANALYSIS_SPF,
                                   EXTRACT_SHADOW_DIRS, REVERT_SUBST_EXPR, CREATE_REMOTES, UNPARSE_FILE, REMOVE_AND_CALC_SHADOW,
                                   REVERSE_CREATED_NESTED_LOOPS, PREDICT_SCHEME, CALCULATE_STATS_SCHEME, REVERT_SPF_DIRS, CLEAR_SPF_DIRS, TRANSFORM_SHADOW_IF_FULL,
                                   RESTORE_LOOP_FROM_ASSIGN, RESTORE_LOOP_FROM_ASSIGN_BACK, INSERT_REGIONS, REMOVE_COPIES, RESTORE_COPIES });
        
    //only for print
    if (printTree)
    {
        list({ CREATE_PARALLEL_DIRS, PRIVATE_ANALYSIS_SPF, CREATE_REMOTES, REVERT_SUBST_EXPR, UNPARSE_FILE, EXTRACT_PARALLEL_DIRS }) <= Pass(INSERT_PARALLEL_DIRS);
        depsToGraphViz(passDepsIn);
        exit(0);
    }
}
#undef list
