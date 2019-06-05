#pragma once
#include <string>

enum typeMessage { WARR, ERROR, NOTE };
extern std::pair<std::string, int> currProcessing; // file and line, default ["", -1]

// GROUP:
// 10xx - analysis
// 20xx - transform
// 30xx - parallel

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
//   27 "array '%s' in function '%s' is not a private, this functionality has not supported yet"
//   28 "Module with name '%s' must be placed in current file"
//   29 lowlevel warnings from private analyzer
//   30 lowlevel notes from private analyzer
//   31 "wrong parallel region identifier: variable '%s' was declarated on line %d"
//   32 "wrong parallel region identifier: variable '%s' was declarated in common block '%s'"
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
//   19  "Can not find execution time for this loop, try to get times statistic"
//   20  "detected distributed and non distributed array links by function's calls for array %s\n"

// 40xx LOW LEVEL WARNINGS
//   01 
//   02 Wrong pure declaration - INTENT mismatch

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
        //check for '.' at the end
        if (value[value.size() - 1] != '.')
            value += '.';
        //check for capital letter
#ifdef _WIN32
        const wchar_t fS = value[0];
        if (fS >= L'a' && fS <= L'z')
            value[0] = L'A' + (value[0] - L'a');
        if (fS >= L'а' && fS <= L'я')
            value[0] = L'А' + (value[0] - L'а');
#endif
        //TODO: convert to upper case for test between '___'
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
    if (currProcessing.first != "" && currProcessing.second != -1)\
    { \
       sprintf(buf, "Internal error in user code at line %d and file %s\n", currProcessing.second, currProcessing.first.c_str());\
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

//russian messages
#ifdef __SPF
//1001
static const wchar_t *R1 = L"Неверное расположение директивы: можно располагать только %ls %ls %ls";
static const wchar_t *R2 = L"Неверное выражение: слишком много переменных цикла";
static const wchar_t *R3 = L"Неверное выражение: возможно только вида a * i + b";
static const wchar_t *R4 = L"Неверное расположение директивы: для области '%s' ожидается 'SPF END PARALLEL_REG_DIR', а была получена 'SPF PARALLEL_REG_DIR'";
static const wchar_t *R5 = L"Неверное расположение директивы: для области '%s' ожидается 'SPF END PARALLEL_REG_DIR'";
static const wchar_t *R6 = L"Неверное расположение директивы: для области '%s' ожидается 'SPF END PARALLEL_REG_DIR'";
static const wchar_t *R7 = L"Неверное расположение директивы: ожидается 'SPF PARALLEL_REG_DIR', а была получена 'SPF END PARALLEL_REG_DIR'";
static const wchar_t *R8 = L"Неверное расположение директивы: ожидается 'SPF PARALLEL_REG_DIR' в той же области видимости";
static const wchar_t *R9 = L"Неверное расположение директивы: ожидается 'SPF PARALLEL_REG_DIR'";
static const wchar_t *R10 = L"Не правильная расстановка области распараллеливания: есть несколько входов во фрагмент '%s', вызванные оператором ENTRY";
static const wchar_t *R11 = L"Не правильная расстановка области распараллеливания: есть несколько входов во фрагмент '%s', вызванные оператором GOTO";
static const wchar_t *R12 = L"Неправильное расположение строк: можно выбирать строки только в исполняемой части кода";
static const wchar_t *R13 = L"Неправильное расположение строк: начало не может быть больше конца";
static const wchar_t *R14 = L"Неправильное расположение строк: начало и конец при расширении не могут лежать в разных областях";
static const wchar_t *R15 = L"Неправильное положение строки: начало и конец не могут быть в неявных фрагментах";
static const wchar_t *R16 = L"Неправильное положение строк: начало и конец не могут быть в разных функциях";
static const wchar_t *R17 = L"Неправильное расположение строк: выделенный фрагмент при расширении не должен включать фрагменты разных областей";
static const wchar_t *R18 = L"Неправильное расположение строк: начало и конец должны быть в одной области видимости";
static const wchar_t *R19 = L"Неправильное расположение строк %d-%d: нельзя объединить фрагменты в разных областях видимости";
static const wchar_t *R20 = L"Неправильное расположение строк: начало и конец должны быть в одной области видимости";
//1002
static const wchar_t *R21 = L"Переменная '%s' не используется в цикле";
static const wchar_t *R22 = L"Переменная '%s' не используется в цикле";
//1003
static const wchar_t *R23 = L"Переменная '%s' не изменяется в цикле";
static const wchar_t *R24 = L"Переменная '%s' не изменяется в цикле";
//1004
static const wchar_t *R25 = L"Размерность массива '%s' %d, а должна быть 1";
//1005
static const wchar_t *R26 = L"Тип массива '%s' долежен быть INTEGER";
//1006
static const wchar_t *R27 = L"Типом переменной '%s' должен быть массив";
static const wchar_t *R28 = L"Переменная '%s' не является массивом";
static const wchar_t *R29 = L"Переменная '%s' не является массивом";
//1007
static const wchar_t *R30 = L"Размер массива не может быть вычислен";
//1008
static const wchar_t *R31 = L"Размер массива '%s' %d, а вы вводите %d";
static const wchar_t *R32 = L"Размерность массива '%s' %d, а вы вводите %d";
//1009
static const wchar_t *R33 = L"Массив '%s' является приватным";
static const wchar_t *R34 = L"Массив '%s' является приватным";
#endif