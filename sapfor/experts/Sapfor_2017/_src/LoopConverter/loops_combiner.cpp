#include "loops_combiner.h"

#include "../LoopAnalyzer/loop_analyzer.h"
#include "../ExpressionTransform/expr_transform.h"
#include "../Utils/errors.h"
#include <string>
#include <vector>

using std::string;
using std::vector;
using std::map;
using std::set;
using std::pair;
using std::make_pair;


/**
 * Проверить, что объединение возможно.
 */
static bool combinationIsPossible(vector<LoopGraph*> &loopGraphs) {
    return false;
}

/**
 * Переименовать итерационные переменные цикла, который мы соединяем с основным.
 */
static void renameIterationVariables(LoopGraph* main, LoopGraph* added) {

    int perfectLoop = main->perfectLoop;

    for(int i = 0; i < perfectLoop; ++i) {



        if(i != perfectLoop - 1) {
            main = main->children[0];
            added = added->children[0];
        }
    }
}

/**
 * Собственно объединение
 */
static void combine(vector<LoopGraph*> &loopGraphs) {

}

int combineLoops(SgFile *file, vector<LoopGraph*> &loopGraphs, vector<Messages> &messages)
{
    printf("Hey!\n");



    return 0;
}
