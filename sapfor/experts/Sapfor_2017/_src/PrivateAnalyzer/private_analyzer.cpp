#include "../Utils/leak_detector.h"

#include <cstdio>
#include <cstring>
#include <vector>
#include <set>
#include <string>
#include <vector>

#include "../GraphCall/graph_calls.h"
#include "private_analyzer.h"
#include "dvm.h"


using std::vector;

void PrivateAnalyzer(SgFile *file, vector<FuncInfo*> &funcs)
{    
    for (int i = 0; i < funcs.size(); ++i)
        if (funcs[i]->doNotAnalyze == false && funcs[i]->deadFunction == false)
            Private_Vars_Analyzer(funcs[i]->funcPointer);
}