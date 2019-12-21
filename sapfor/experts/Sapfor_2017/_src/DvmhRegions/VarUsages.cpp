//
// Created by Vladislav Volodkin on 12/21/19.
//

#include "VarUsages.h"


void VarUsages::insert(VarUsages &to_insert)
{
    undefined |= to_insert.undefined;

    reads.insert(to_insert.reads.begin(), to_insert.reads.end());
    writes.insert(to_insert.writes.begin(), to_insert.writes.end());
}