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
//   27 --- FREE
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
#ifdef _WIN32
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
static const wchar_t *R26 = L"Тип массива '%s' должен быть INTEGER";
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
//1010
static const wchar_t *R35 = L"Разрешены только положительные числа";
//1011
static const wchar_t *R36 = L"Нет такого выражения '%s' в цикле";
//1012
static const wchar_t *R37 = L"Невозможно определить размеры массива '%s'";
static const wchar_t* R149 = L"Невозможно определить размеры цикла '%s'";
//1013
static const wchar_t *R38 = L"Отличается количество формальных и фактических параметров для функции '%s'"; //Требуется выполнить подстановку функции '%s', так как 
static const wchar_t *R39 = L"Отличается тип фактического (%s : %s) и формального (%s : %s) %d-го параметра для функции '%s'"; //Требуется выполнить подстановку функции '%s', так как 
static const wchar_t *R40 = L"Требуется выполнить подстановку функции '%s', так как можно передавать массивы только целиком";
static const wchar_t *R41 = L"Требуется выполнить подстановку функции '%s' из-за обращения к неприватному массиву '%s' в цикле на строке %d %s";
static const wchar_t *R42 = L"Требуется выполнить подстановку функции '%s' из-за обращения к неприватному массиву '%s' %s";
static const wchar_t *R43 = L"Требуется подставить функцию '%s' из-за разной размерности массива %s', передаваемого в качестве параметра: размерность формального параметра = %d и фактического параметра = %d";
static const wchar_t *R44 = L"Обнаружено несоответствие типов в функции '%s' в формальном и фактическом параметре для массива '%s'\n";
static const wchar_t *R45 = L"Необходимо подставить функцию '%s', так как через параметр %d передается итерационная переменная цикла на строке %d и она используется в индексном выражении в обращении к массиву в теле этой функции";
//1014
static const wchar_t *R46 = L"Была найдена рекурсивная цепочка вызовов: %s, данная функция исключена из рассмотрения";
//1015
static const wchar_t *R47 = L"Данная функция не вызывается в данном проекте";
//1016
static const wchar_t *R48 = L"Невозможно вычислить количество итераций данного цикла, информация о количестве итераций для всех остальных циклов в области распараллеливания '%s' будет проигнорирована";
//1017
static const wchar_t *R49 = L"Невозможно найти определение для символа '%s' в данной области видимости";
//1018
static const wchar_t *R50 = L"Данный цикл не в END DO формате";
static const wchar_t *R51 = L"Данный цикл не в END DO формате";
//1019
static const wchar_t *R52 = L"Включаемый файл '%s' содержит исполняемые операторы, что запрещено к распараллеливанию в системе SAPFOR";
//1020
static const wchar_t *R53 = L"Активные DVM-директивы не поддерживаются (необходимо включить опцию <<Учитывать DVM-директивы>>)";
//1021
static const wchar_t *R54 = L"Обращение к массиву '%s' содержит более одной индексной переменной циклов";
static const wchar_t *R55 = L"Обращение к массиву '%s' не содержит итерационных переменных циклов";
//1022
static const wchar_t *R56 = L"Обращение к массиву '%s' имеет косвенную адресацию";
//1023
static const wchar_t *R57 = L"Невозможно вычислить индексное выражение в обращении к массиву '%s'";
//1024
static const wchar_t *R58 = L"Коэффициент A в линейном обращении A*x+B к массиву '%s' не может быть отрицательным, так как инверсное распределение не поддерживается";
//1025
static const wchar_t *R59 = L"Невозможно сопоставить обращение к массиву на запись '%s' с данными циклом";
//1026
static const wchar_t *R60 = L"Обнаружен оператор записи в нераспределенный массив '%s', связанный с данным циклом";
static const wchar_t *R61 = L"Обнаружен оператор записи в нераспределенный массив '%s', связанный с данным циклом";
//1027
//--- FREE
//1028
static const wchar_t *R62 = L"Описание модуля '%s' должно находиться в данном файле";
//1029
//--- TODO
//1030
//--- TODO
//1031
static const wchar_t *R63 = L"Неверное имя области: имя '%s' уже объявлено на строке %d";
//1032
static const wchar_t *R64 = L"Неверное имя области: имя '%s' уже объявлено в common-блоке '%s'";
//1033
static const wchar_t *R65 = L"Область распараллеливания '%s' включает саму себя в файле '%s'";
//1034
static const wchar_t *R66 = L"Неверное расположение области: не существует common-блока в файле %s со следующими массивами:%s";
//1035
//--- TODO
//1036
static const wchar_t *R67 = L"Невозможно построить дерево выравнивания в данной области распараллеливания, используя пользовательские DVM-директивы";
//1037
static const wchar_t *R68 = L"Массив '%s' не может быть распределен из-за ограничений ввода/вывода, накладываемых DVM системой";
//1038
static const wchar_t *R69 = L"Оператор PAUSE является запрещенным в параллельной программе";
static const wchar_t *R70 = L"Оператор EQUIVALENCE не поддерживается на данный момент";
//1039
static const wchar_t *R71 = L"Переменные '%s' и '%s' находятся в одной области ассоциации (common block '%s'), но имеют разные типы (файлы - %s:%d и %s:%d)";
//1040
static const wchar_t *R72 = L"Первые %d измерений массива '%s' запрещены к распределению из-за передачи к функцию '%s'";
static const wchar_t *R73 = L"Первое измерение массива '%s' запрещено к распределению из-за передачи в функцию '%s'";
//1041
static const wchar_t *R74 = L"Область распараллеливания '%s'содержит строку, которая включена в другую область";
//1042
static const wchar_t *R75 = L"Распределенный массив '%s' состоящий в common блоке '%s' должен иметь описание в главной программной единице";
//1043
static const wchar_t *R76 = L"Неверное выражение в директиве: ожидается список переменных";
static const wchar_t *R77 = L"Неверное выражение в директиве: ожидается %d тесно-вложенных циклов на строке %d, но их всего %d";
static const wchar_t *R78 = L"Неверное выражение в директиве: ожидается переменная '%s' на позиции %d";
//1044
static const wchar_t *R79 = L"Поддерживаются функции только без побочных эффектов";
static const wchar_t *R80 = L"Поддерживаются функции только без побочных эффектов";
//1045
static const wchar_t *R81 = L"Аргумент '%s' функции '%s' не имеет оператора описания";
//1046
static const wchar_t *R82 = L"Количество формальных и фактических параметров не одинаково для вызова данной функции '%s'";
static const wchar_t *R83 = L"Количество формальных и фактических параметров не одинаково для вызова данной функции '%s'";
static const wchar_t *R84 = L"Количество формальных и фактических параметров не одинаково для вызова данной функции '%s'";
//1047
static const wchar_t *R85 = L"%d измерение массива '%s' не может быть распределено из-за различных отображений на циклы в операциях присваиваний";
static const wchar_t *R86 = L"Массив '%s' не может быть распределен, так как все его измерения запрещены к распределению";
static const wchar_t *R87 = L"Массив '%s' не может быть распределен";
static const wchar_t *R88 = L"Массив '%s' не может быть распределен";
static const wchar_t *R89 = L"Массив '%s' не может быть распределен";
static const wchar_t *R90 = L"Массив '%s' не может быть распределен из-за использования RESHAPE";
static const wchar_t *R91 = L"Массив '%s' не может быть распределен";
//1048
static const wchar_t *R92 = L"Функция '%s' с одинаковым именем была объявлена в более, чем одном месте: в файле '%s':%d и '%s':%d";
//1049
static const wchar_t *R93 = L"Функция не является чистой (без побочных эффектов) из-за наличия данного оператора";
//1050
static const wchar_t *R146 = L"Найдена более, чем одна главная программная единица (PROGRAM)";
static const wchar_t *R147 = L"Не найдена ни одна главная программная единица (PROGRAM)";
//1051
static const wchar_t *R148 = L"Обнаружены вызовы MPI-функций, включен режим специальный режим распараллеливания MPI-программ";
//1052
static const wchar_t *R150 = L"Ошибка в расстановке пользовательских интервалов - не удалось найти конец интервала";
//1053
static const wchar_t *R154 = L"Ошибка в выражении SHRINK клаузы: переменная должна быть массивом в файле '%s'";
//1054
static const wchar_t *R155 = L"Длина маски для массива '%s' должна быть равна %d, но указано только %d измерений в файле '%s'";
//1055
static const wchar_t *R156 = L"Ошибка в выражении маски на %d позиции массива '%s': в качестве значения могут быть только 0 и 1 в файле '%s'";
//1056
static const wchar_t *R157 = L"Массив '%s' в директиве shrink также должен быть объявлен в директиве private в файле '%s'";

//2001
static const wchar_t *R94 = L"Невозможно автоматически преобразовать данное присваивание к циклу";
static const wchar_t *R95 = L"Невозможно автоматически преобразовать данное присваивание к циклу";
//2002
static const wchar_t *R96 = L"Арифметический IF был преобразован в IF-ENDIF";
static const wchar_t *R97 = L"Вычисляемый GOTO был преобразован в IF-ENDIF";
//2003
static const wchar_t *R98 = L"Невозможно автоматически преобразовать цикл в END DO формат";
//2004
static const wchar_t *R99 = L"Цикл был преобразован в END DO формат";
//2005
static const wchar_t *R100 = L"Циклы на строках %d и %d были объединены";
//2006
static const wchar_t *R101 = L"Была выполнена подстановка макроса с именем '%s'";
//2007
static const wchar_t *R102 = L"Возникла непредвиденная ситуация во время генерации выходного текста";
static const wchar_t *R103 = L"Возникла непредвиденная ситуация во время генерации выходного текста";
//2008
// -- TODO 
//2009
static const wchar_t *R104 = L"Невозможно разделить данный цикл из-за следующей зависимости: %s";
//2010
static const wchar_t *R105 = L"Данный цикл содержит косвенные подциклы, поэтому не может быть разделен";
static const wchar_t *R106 = L"У данного цикла есть ограничение на распараллеливание (в строке ";
static const wchar_t *R107 = L"У данного цикла есть зависимости, которые нельзя проанализировать, поэтому он не может быть разделен (в строке ";

//3001
static const wchar_t *R108 = L"Добавлена across-зависимость к массиву '%s' в цикле";
//3002
static const wchar_t *R109 = L"Добавлена приватная переменная '%s' к циклу на строке %d";
//3003
static const wchar_t *R110 = L"Добавлена редукционная переменная '%s' с типом операции '%s' к циклу на строке %d";
//3004
static const wchar_t *R111 = L"Неизвестный тип редукционной операции по скаляру '%s'";
//3005
static const wchar_t *R112 = L"Неизвестная зависимость по скалярной переменной '%s' (попробуйте вручную специфицировать ее тип)";
//3006
static const wchar_t *R113 = L"Неизвестная зависимость по массиву препятствует распараллеливанию данного цикла";
static const wchar_t *R114 = L"Неизвестная зависимость по скаляру препятствует распараллеливанию данного цикла";
static const wchar_t *R115 = L"Внешние или внутренние операторы перехода (GOTO) препятствуют распараллеливанию данного цикла";
static const wchar_t *R116 = L"Операторы ввода/вывода препятствуют распараллеливанию данного цикла";
static const wchar_t *R117 = L"Операторы STOP препятствуют распараллеливанию данного цикла";
static const wchar_t *R118 = L"Обнаружены конфликтные присваивания, которые препятствуют распараллеливанию данного цикла";
static const wchar_t *R119 = L"Невозможность сопоставить обращение к массиву на запись препятствует распараллеливанию данного цикла";
static const wchar_t *R120 = L"Косвенная адресация по распределяемому массиву препятствует распараллеливанию данного цикла";
static const wchar_t *R121 = L"Обращение к нераспределенному массиву на запись препятствует распараллеливанию данного цикла";
static const wchar_t *R122 = L"Найдены различные правила выравнивания массивов, используемых на запись в данном цикле, препятствует распараллеливанию";
static const wchar_t *R123 = L"Процедуры с побочным эффектном препятствуют распараллеливанию данного цикла";
static const wchar_t *R144 = L"Обнаружено не прямоугольное пространство итераций, что препятствует распараллеливанию данного цикла";
static const wchar_t *R145 = L"Обнаружены DVM интервалы внутри цикла, что препятствует распараллеливанию данного цикла";
//--TODO R124 R125 про неопределенную длину зависимости 
//3007
static const wchar_t *R126 = L"Невозможно создать с шаблоном для массива '%s': размерность массива '%d' и это не равно '%d'";
static const wchar_t *R127 = L"Невозможно сопоставить выравнивания массивов, передаваемых в процедуру";
//3008
static const wchar_t *R128 = L"Внутренняя ошибка анализа, распараллеливание не будет выполнено для данного файла!";
//3009
static const wchar_t *R129 = L"Добавленный REMOTE_ACCESS для обращения к массиву '%s' может привести к сильному замедлению";
//3010
static const wchar_t *R130 = L"Не обнаружены массивы или свободные циклы для распределения в данном проекте";
static const wchar_t *R131 = L"Не обнаружены массивы или свободные циклы для распределения в данной области распараллеливания";
//3011
static const wchar_t *R132 = L"У массивов '%s' и '%s' разные правила выравнивания согласно обращению на запись в в данном цикле";
//3012
static const wchar_t *R133 = L"Области распараллеливания %sимеют общую используемую функцию '%s'";
//3013
static const wchar_t *R134 = L"Области распараллеливания %sимеют общий используемый локальный массив '%s'";
static const wchar_t *R152 = L"Области распараллеливания %sимеют общий используемый массив из модуля '%s'";
//3014
static const wchar_t *R135 = L"Область распараллеливания '%s' содержит common-массив '%s', используемый в области и вне её";
//3015
static const wchar_t *R136 = L"Область распараллеливания '%s' не имеет DVM-интервала для фрагмента";
//3016
static const wchar_t *R137 = L"Невозможно считать DVM-статистику для получения времен";
//3017
static const wchar_t *R138 = L"Область распараллеливания '%s' не содержит копирования массива '%s' в DVM-интервале";
//3018
static const wchar_t *R139 = L"Область распараллеливания '%s' не содержит копирования массива '%s' в DVM-интервале";
//3019
//--- TODO предиктор
//3020
static const wchar_t *R140 = L"Обнаружен массив '%s', являющийся параметром функции, в которую передаются как распределенные, так и не распределенные массивы. Возможно, стоит запретить к распределению обнаруженные массивы, либо продублировать соответствующую функцию.\n";
static const wchar_t *R141 = L"Обнаружен распределяемый массив '%s', передаваемый в качестве параметра в процедуру\n";
static const wchar_t* R153 = L"Обнаружен не распределяемый массив '%s', передаваемый в качестве параметра в процедуру\n";
static const wchar_t *R142 = L"Для массива '%s' не удается найти единого распределения, внутренняя ошибка системы.\n";
//3021
static const wchar_t* R151 = L"Пустые области распараллеливания недопускаются.\n";

//4001
//---TODO ошибки из SAGE
//4002
static const wchar_t *R143 = L"Неверное объявление PURE функции - отсутствуют операторы INTENT";

#endif