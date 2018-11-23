void Message_Add(char * str);
void Exit(int c);
void ErrAssert(char *t);

#ifdef MIN
    #undef MIN
#endif

#ifdef MAX
    #undef MAX
#endif

static int inline MIN(int X, int Y) { return ((X) < (Y) ? (X) : (Y)); }
static int inline MAX(int X, int Y) { return  ((X) > (Y) ? (X) : (Y)); }
