/* debug.c,v 1.1.1.2 1992/07/10 02:42:51 davew Exp */

#include "include/portable.h"
#include <stdio.h>
#include "include/debug.h"
#include "include/missing.h"

int n_strange_occurances = 0;
FILE *debug2;

void strange_occurance(char *message)
{
    n_strange_occurances++;
    fprintf(debug2, message);
}

