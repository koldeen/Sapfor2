#pragma once
#include <string>
#ifdef __SPF
#include "dvm.h"
#endif
enum typeMessage { WARR, ERROR, NOTE };

//Гайд по русификации сообщений смотри ниже.

// GROUP:
// 10xx - analysis
// 20xx - transform
// 30xx - parallel
// 50xx - checkpoint

// 10xx ANALISYS GROUP
//   01 "bad directive position, it can be placed only"
//   02 "variable '%s' is not used in loop"
//   03 "variable '%s' is not changed in loop"
//   04 "dimention of array '%s' is %d, but must be 1"
//   05 "type of array '%s' but must be INTEGER"
//   06 "type of variable '%s' must be array"
//   07 "array size can't be computed"
//   08 "size of array '%s' is %d, but you enter %d"
//   09 "array '%s' is private"
//   10 "only positive numbers are supported"
//   11 "no such expression '%s' on loop"
//   12 "More information is required about sizes of array '%s'"
//   13 "Function '%s' needs to be inlined ..."
//   14 "Found recursive chain calls: %s, this function will be ignored"
//   15 "This function is not called in current project"
//   16 "Can not calculate count of iterations for this loop, information about iterations in all loops in parallel regions '%s' will be ignored"
//   17 "Can not find declaration for symbol '%s' in current scope"
//   18 "This loop does not have END DO format"
//   19 "Include '%s' has executable operators"
//   20 "Active DVM directives are not supported yet"
//   21 "array ref '%s' has more than one loop's variables"
//   22 "array ref '%s' has indirect access"
//   23 "can not calculate index expression for array ref '%s'"
//   24 "coefficient A in A*x+B is not positive for array ref '%s', inverse distribution in not supported yet"
//   25 "can not map write to array '%s' to this loop"
//   26 "write to non distributed array '%s' in this loop"
//   27 --- FREE
//   28 "Module with name '%s' must be placed in current file"
//   29 lowlevel warnings from private analyzer
//   30 lowlevel notes from private analyzer
//   31 "wrong parallel region identifier: variable '%s' was declared on line %d"
//   32 "wrong parallel region identifier: variable '%s' was declared in common block '%s'"
//   33 "parallel region '%s' is included in file '%s'"
//   34 "parallel regions '%s' and '%s' are crossed"
//   35 "parallel region '%s' has data statement(s)"
//   36 "Can not build align graph from user's DVM directives in this region"
//   37 "Array can not be distributed because of DVM's I/O constraints"
//   38 "An equivalence operator at line %d is not supported yet"
//   39 "Variabled '%s' and '%s' in one storage association (common block '%s') have different types" 
//   40 "First %d dimensions of array '%s' were deprecated to distributon due to function call '%s'"
//   41 "parallel region '%s' has line included in another region"
//   42 "distributed array in common block %s must have declaration in main unit"
//   43 "bad directive expression"
//   44 "Only pure procedures were supported"
//   45 "function's argument '%s' does not have declaration statement"
//   46 "mismatch of count formal and actual parameters "
//   47 "inconsistent array use"
//   48 "the same function name in different places was found"
//   49 "reasons of non pure function" 
//   50 "count of PROGRAM unit"
//   51 "Detected mpi call, turn on special regime of paralyzing"
//   52 "error in user DVM intervals"
//   53 "variable in shrink clause must be arrayy in file '%s' on line %d"
//   54 "length of mask for array '%s' must be %d, but you enter only %d dimenions in file '%s' on line %d"
//   55 "wrong mask value in %d position: it can be only 0 or 1 in file '%s' on line %d"
//   56 "array '%s' in shrink clause must be also declared in private clause in file '%s' on line %d"

// 20xx TRANSFORM GROUP
//   01 "can not convert array assign to loop"
//   02 "converted arithmetic IF to simple IF"
//   03 "can not convert to END DO loop"
//   04 "convert to END DO loop"
//   05 "loops on lines %d and %d were combined"
//   06 "substitute statement function with name '%s'"
//   07 "Internal error during unparsing process has occurred"
//   08 "Can not do PRIVATE EXPANSION for this loop - privates not found"
//   09 "Can not split this loop because of dependecy: %s"
//   10 "This loop has indirect child loops  and can not be splitted\n"
//   11 

// 30xx PARALLEL GROUP
//   01 "add across dependencies by array '%s' to loop"
//   02 "add private scalar '%s' to loop on line %d"
//   03 "add reduction scalar '%s' with operation '%s' to loop on line %d"
//   04 "unknown type of reduction scalar '%s'"
//   05 "unknown scalar dependencies by '%s' (try to specify its type)"
//   06 "... prevents parallelization"
//   07 "Can not create distributed link for array '%s': dim size of this array is '%d' and it is not equal '%d'"
//   08 "internal error in analysis, parallel directives will not be generated for this file!"
//   09 "Added remote access for array ref '%s' can significantly reduce performance"
//   10 "Can not find arrays for distribution for parallel region '%s', ignored"
//   11 "Arrays have different align rules in this loop according to their write accesses"
//   12 "parallel regions %shave common function '%s' which is used inside them"
//   13 "parallel regions %shave local array '%s' which is used inside them"
//   14 "parallel region '%s' has common array '%s' which is used inside and outside region"
//   15 "parallel region '%s' does not have DVM interval for fragment"
//   16 "expected only assign operands in DVM interval"
//   17 "parallel region '%s' does not have copying of array '%s' in DVM interval"
//   18 "parallel region '%s' does not have copying of common array '%s' in DVM interval"
//   19 "Can not find execution time for this loop, try to get times statistic"
//   20 "detected distributed and non distributed array links by function's calls for array %s\n"
//   21 "empty parallel regions is forbidden"
//   22 "Can not find align rules"

// 40xx LOW LEVEL WARNINGS
//   01 
//   02 Wrong pure declaration - INTENT mismatch

// 50xx CHECKPOINT GROUP
//   01 "The first argument must be TIME or ITER and the second must be integer in INTERVAL clause."
//   02 "CHECKPOINT directive with %s clause can be only at executable code section."
//   03 "CHECKPOINT directive with FILES clause must contain integer value."
//   04 "Variable '%s' in %s clause must be declared at the same module."
//   05 "Illegal option in TYPE clause."
//   06 "%s clause can be used only once."
//   07 "Variable '%s' can't be used in FILES and EXCEPT clauses at the same time."

extern int langOfMessages;
struct Messages
{
private:
    //explicit Messages(const typeMessage type, const int line, const std::string &value_) : Messages(type, line, value_, 0) { }
    explicit Messages(const typeMessage type, const int line, const std::wstring &value_, const int group) : type(type), line(line), group(group)
    {
        value = value_;
        //check for \n at the end
        if (value[value.size() - 1] == '\n')
            value.erase(value.begin() + value.size() - 1);                
    }
public:
    explicit Messages(const typeMessage type, const int line, const std::wstring &rus, const std::wstring &eng, const int group) : 
        Messages(type, line, (langOfMessages == 1) ? rus : eng, group) { }

    std::wstring toString()
    {
        std::wstring retVal = L"|";
        retVal += std::to_wstring((int)type) + L" ";
        retVal += std::to_wstring(line) + L" ";
        retVal += std::to_wstring(group);
        retVal += L"|" + value;
        return retVal; 
    }

public:
    typeMessage type;
    int group;
    int line;
    std::wstring value;
};

// from Utils.cpp
#ifdef _WIN32
extern void printStackTrace();
#else
static void printStackTrace() { };
#endif

#if __SPC
#define printInternalError(file, line) do {\
    char buf[512];\
    sprintf(buf, "Internal error at line %d and file %s\n", line, file);\
    addToGlobalBufferAndPrint(buf);\
    throw(-1);\
} while (0)
#else
#define printInternalError(file, line) do {\
    printStackTrace(); \
    char buf[512];\
    sprintf(buf, "Internal error at line %d and file %s\n", line, file);\
    addToGlobalBufferAndPrint(buf);\
\
    if (SgStatement::getCurrProcessFile() != "" && SgStatement::getCurrProcessLine() != -1)\
    { \
       sprintf(buf, "Internal error in user code at line %d and file %s\n", SgStatement::getCurrProcessLine(), SgStatement::getCurrProcessFile().c_str());\
       addToGlobalBufferAndPrint(buf);\
    } \
    throw(-1);\
} while (0)
#endif

#define checkNull(address, file, line) do { \
    if ((address) == NULL) \
        printInternalError(file, line); \
} while (0)

//TODO: count of string len of all parameters
#define allocAndPrint(buf, format, ...) do { \
   const int bufLen = 32 * 1024 * 1024;\
   buf = new char[bufLen];\
   const int countW = sprintf(buf, format, ##__VA_ARGS__);\
   if (countW + 1 > bufLen) \
   { \
        delete []buf; \
        printInternalError(__FILE__, __LINE__);\
   } \
} while (0)

#ifdef _WIN32
#define allocAndPrintLong(buf, format, ...) do { \
   const int bufLen = 32 * 1024 * 1024;\
   buf = new wchar_t[bufLen];\
   const int countW = swprintf(buf, format, ##__VA_ARGS__);\
   if (countW + 1 > bufLen) \
   { \
        delete []buf; \
        printInternalError(__FILE__, __LINE__);\
   } \
} while (0)
#else
#define allocAndPrintLong(buf, format, ...) do { \
   const int bufLen = 32 * 1024 * 1024;\
   buf = new wchar_t[bufLen];\
   const int countW = swprintf(buf, bufLen, format, ##__VA_ARGS__);\
   if (countW + 1 > bufLen) \
   { \
        delete []buf; \
        printInternalError(__FILE__, __LINE__);\
   } \
} while (0)
#endif

#define __spf_printToBuf(outval, format, ...) do {\
    char *buf = NULL; \
    allocAndPrint(buf, format, ##__VA_ARGS__); \
    outval = std::string(buf);\
    delete []buf;\
} while (0)

#define __spf_printToLongBuf(outval, format, ...) do {\
    wchar_t *buf = NULL; \
    allocAndPrintLong(buf, format, ##__VA_ARGS__); \
    outval = std::wstring(buf);\
    delete []buf;\
} while (0)

#define __spf_print(needPrint, format, ...) do {\
    if (needPrint == 1) {\
        char *buf = NULL; \
        allocAndPrint(buf, format, ##__VA_ARGS__); \
        addToGlobalBufferAndPrint(buf);\
        delete []buf;\
    } \
} while (0)

// Сводобный - R173
// Гайд по русификации сообщений: При добавлении нового сообщения, меняется последний сводобный идентификатор.
// В этом файле остаются только спецификаторы, для которых будет заполнен текст. Полный текст пишется в файле
// russian_errors_text.txt. Специикаторы там тоже сохраняются, по ним в визуализаторе будет восстановлен 
// закодированный текст.

//russian messages
//1001
static const wchar_t *R1 = L"R1:%ls#%ls#%ls";
static const wchar_t* RR1_1 = L"RR1_1:";
static const wchar_t* RR1_2 = L"RR1_2:";
static const wchar_t* RR1_3 = L"RR1_3:";
static const wchar_t* RR1_4 = L"RR1_4:";
static const wchar_t* RR1_5 = L"RR1_5:";
static const wchar_t* RR1_6 = L"RR1_6:";
static const wchar_t* RR1_7 = L"RR1_7:";
static const wchar_t* RR1_8 = L"RR1_8:";

static const wchar_t *R2 = L"R2:";
static const wchar_t *R3 = L"R3:";
static const wchar_t *R4 = L"R4:%s";
static const wchar_t *R5 = L"R5:%s";
static const wchar_t *R6 = L"R6:%s";
static const wchar_t *R7 = L"R7:";
static const wchar_t *R8 = L"R8:";
static const wchar_t *R9 = L"R9:";
static const wchar_t *R10 = L"R10:%s";
static const wchar_t *R11 = L"R11:%s";
static const wchar_t *R12 = L"R12:";
static const wchar_t *R13 = L"R13:";
static const wchar_t *R14 = L"R14:";
static const wchar_t *R15 = L"R15:";
static const wchar_t *R16 = L"R16:";
static const wchar_t *R17 = L"R17:";
static const wchar_t *R18 = L"R18:";
static const wchar_t *R19 = L"R19:%d#%d";
static const wchar_t *R20 = L"R20:";
//1002
static const wchar_t *R21 = L"R21:%s";
static const wchar_t *R22 = L"R22:%s";
//1003
static const wchar_t *R23 = L"R23:%s";
static const wchar_t *R24 = L"R24:%s";
//1004
static const wchar_t *R25 = L"R25:%s#%d";
//1005
static const wchar_t *R26 = L"R26:%s";
//1006
static const wchar_t *R27 = L"R27:%s";
static const wchar_t *R28 = L"R28:%s";
static const wchar_t *R29 = L"R29:%s";
//1007
static const wchar_t *R30 = L"R30:";
//1008
static const wchar_t *R31 = L"R31:%s#%d#%d";
static const wchar_t *R32 = L"R32:%s#%d#%d";
//1009
static const wchar_t *R33 = L"R33:%s";
static const wchar_t *R34 = L"R34:%s";
//1010
static const wchar_t *R35 = L"R35:";
//1011
static const wchar_t *R36 = L"R36:%s";
//1012
static const wchar_t *R37 = L"R37:%s";
static const wchar_t* R149 = L"R149:%s";
//1013
static const wchar_t *R38 = L"R38:%s";
static const wchar_t *R39 = L"R39:%s#%s#%s#%s#%d#%s";
static const wchar_t *R40 = L"R40:%s";
static const wchar_t *R41 = L"R41:%s#%s#%d#%s";
static const wchar_t *R42 = L"R42:%s#%s#%s";
static const wchar_t *R43 = L"R43:%s#%s#%d#%d";
static const wchar_t *R44 = L"R44:%s#%s";
static const wchar_t *R45 = L"R45:%s#%d#%d";
//1014
static const wchar_t *R46 = L"R46:%s";
//1015
static const wchar_t *R47 = L"R47:";
//1016
static const wchar_t *R48 = L"R48:%s";
//1017
static const wchar_t *R49 = L"R49:%s";
//1018
static const wchar_t *R50 = L"R50:";
static const wchar_t *R51 = L"R51:";
//1019
static const wchar_t *R52 = L"R52:%s";
//1020
static const wchar_t *R53 = L"R53:";
//1021
static const wchar_t *R54 = L"R54:%s";
static const wchar_t *R55 = L"R55:%s";
//1022
static const wchar_t *R56 = L"R56:%s";
//1023
static const wchar_t *R57 = L"R57:%s";
//1024
static const wchar_t *R58 = L"R58:%s";
//1025
static const wchar_t *R59 = L"R59:%s";
//1026
static const wchar_t *R60 = L"R60:%s";
static const wchar_t *R61 = L"R61:%s";
//1027
//--- FREE
//1028
static const wchar_t *R62 = L"R62:%s";
//1029 && 1030
static const wchar_t* R158 = L"R158:%s";
static const wchar_t* R159 = L"R159:%s";
static const wchar_t* R160 = L"R160:%s";
static const wchar_t* R161 = L"R161:%s";
static const wchar_t* R162 = L"R162:%s";
static const wchar_t* R163 = L"R163:%s";
static const wchar_t* RR158_1 = L"RR158_1:";
//1031
static const wchar_t *R63 = L"R63:%s#%d";
//1032
static const wchar_t *R64 = L"R64:%s#%s";
//1033
static const wchar_t *R65 = L"R65:%s#%s";
//1034
static const wchar_t *R66 = L"R66:%s#%s";
//1035
//--- TODO
//1036
static const wchar_t *R67 = L"R67:";
//1037
static const wchar_t *R68 = L"R68:%s";
//1038
static const wchar_t *R69 = L"R69:";
static const wchar_t *R70 = L"R70:";
//1039
static const wchar_t *R71 = L"R71:%s#%s#%s#%s#%d#%s#%d";
//1040
static const wchar_t *R72 = L"R72:%d#%s#%s";
static const wchar_t *R73 = L"R73:%s#%s";
//1041
static const wchar_t *R74 = L"R74:%s";
//1042
static const wchar_t *R75 = L"R75:%s#%s";
//1043
static const wchar_t *R76 = L"R76:";
static const wchar_t *R77 = L"R77:%d#%d#%d";
static const wchar_t *R78 = L"R78:%s#%d";
//1044
static const wchar_t *R79 = L"R79:";
static const wchar_t *R80 = L"R80:";
//1045
static const wchar_t *R81 = L"R81:%s#%s";
//1046
static const wchar_t *R82 = L"R82:%s";
static const wchar_t *R83 = L"R83:%s";
static const wchar_t *R84 = L"R84:%s";
//1047
static const wchar_t *R85 = L"R85:%d#%s";
static const wchar_t *R86 = L"R86:%s";
static const wchar_t *R87 = L"R87:%s";
static const wchar_t *R88 = L"R88:%s";
static const wchar_t *R89 = L"R89:%s";
static const wchar_t *R90 = L"R90:%s";
static const wchar_t *R91 = L"R91:%s";
static const wchar_t *R164 = L"R164:%s";
//1048
static const wchar_t *R92 = L"R92:%s#%s#%d#%s#%d";
//1049
static const wchar_t *R93 = L"R93:";
//1050
static const wchar_t *R146 = L"R146:";
static const wchar_t *R147 = L"R147:";
//1051
static const wchar_t *R148 = L"R148:";
//1052
static const wchar_t *R150 = L"R150:";
//1053
static const wchar_t *R154 = L"R154:%s";
//1054
static const wchar_t *R155 = L"R155:%s#%d#%d#%s";
//1055
static const wchar_t *R156 = L"R156:%d#%s#%s";
//1056
static const wchar_t *R157 = L"R157:%s#%s";

//2001
static const wchar_t *R94 = L"R94:";
static const wchar_t *R95 = L"R95:";
//2002
static const wchar_t *R96 = L"R96:";
static const wchar_t *R97 = L"R97:";
//2003
static const wchar_t *R98 = L"R98:";
//2004
static const wchar_t *R99 = L"R99:";
//2005
static const wchar_t *R100 = L"R100:%d#%d";
//2006
static const wchar_t *R101 = L"R101:%s";
//2007
static const wchar_t *R102 = L"R102:";
static const wchar_t *R103 = L"R103:";
//2008
// -- TODO 
//2009
static const wchar_t *R104 = L"R104:%s";
//2010
static const wchar_t *R105 = L"R105:";
static const wchar_t *R106 = L"R106:%s";
static const wchar_t *R107 = L"R107:%s";
//2011

//3001
static const wchar_t *R108 = L"R108:%s";
//3002
static const wchar_t *R109 = L"R109:%s#%d";
//3003
static const wchar_t *R110 = L"R110:%s#%s#%d";
//3004
static const wchar_t *R111 = L"R111:%s";
//3005
static const wchar_t *R112 = L"R112:%s";
//3006
static const wchar_t *R113 = L"R113:";
static const wchar_t *R114 = L"R114:";
static const wchar_t *R115 = L"R115:";
static const wchar_t *R116 = L"R116:";
static const wchar_t *R117 = L"R117:";
static const wchar_t *R118 = L"R118:";
static const wchar_t *R119 = L"R119:";
static const wchar_t *R120 = L"R120:";
static const wchar_t *R121 = L"R121:";
static const wchar_t *R122 = L"R122:";
static const wchar_t *R123 = L"R123:";
static const wchar_t *R144 = L"R144:";
static const wchar_t *R145 = L"R145:";
//--TODO R124 R125 про неопределенную длину зависимости 
//3007
static const wchar_t *R126 = L"R126:%s#%d#%d";
static const wchar_t *R127 = L"R127:";
//3008
static const wchar_t *R128 = L"R128:";
//3009
static const wchar_t *R129 = L"R129:%s";
//3010
static const wchar_t *R130 = L"R130:";
static const wchar_t *R131 = L"R131:";
//3011
static const wchar_t *R132 = L"R132:%s#%s";
//3012
static const wchar_t *R133 = L"R133:%s#%s";
//3013
static const wchar_t *R134 = L"R134:%s#%s";
static const wchar_t *R152 = L"R152:%s#%s";
//3014
static const wchar_t *R135 = L"R135:%s#%s";
//3015
static const wchar_t *R136 = L"R136:%s";
//3016
static const wchar_t *R137 = L"R137:";
//3017
static const wchar_t *R138 = L"R138:%s#%s";
//3018
static const wchar_t *R139 = L"R139:%s#%s";
//3019
//--- TODO предиктор
//3020
static const wchar_t *R140 = L"R140:%s";
static const wchar_t *R141 = L"R141:%s";
static const wchar_t* R153 = L"R153:%s";
static const wchar_t *R142 = L"R142:%s";
//3021
static const wchar_t* R151 = L"R151:";
//3022
static const wchar_t* R171 = L"R171:%s";

//4001
//---TODO ошибки из SAGE
//4002
static const wchar_t *R143 = L"R143:";

//5001
static const wchar_t *R165 = L"R165:";
//5002
static const wchar_t *R166 = L"R166:%s";
//5003
static const wchar_t *R167 = L"R167:";
//5004
static const wchar_t *R168 = L"R168:%s#%s";
//5005
static const wchar_t *R169 = L"R169:";
//5006
static const wchar_t *R170 = L"R170:%s";
//5007
static const wchar_t *R172 = L"R172:%s";