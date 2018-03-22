#pragma once
#include <string>
#include "dvm.h"

enum typeMessage { WARR, ERROR, NOTE };

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
//   26 "write to non distributed array '%s' to loop"
//   27 "array '%s' in function '%s' is not a private, this functionality has not supported yet"
//   28 "Module with name '%s' must be placed in current file"
//   29 lowlevel warnings from private analyzer
//   30 lowlevel notes from private analyzer

// 20xx TRANSFORM GROUP
//   01 "can not convert array assign to loop"
//   02 "converted arithmetic IF to simple IF"
//   03 "can not convert to END DO loop"
//   04 "convert to END DO loop"
//   05 "loops on lines %d and %d were combined"
//   06 "substitute statement function with name '%s'"
//   07 "Internal error during unparsing process has occurred"

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

struct Messages
{
public:
    explicit Messages(const typeMessage type, const int line, const std::string &value_) : Messages(type, line, value_, 0) { }
    explicit Messages(const typeMessage type, const int line, const std::string &value_, const int group) : type(type), line(line), group(group)
    {
        value = value_;
        //check for \n at the end
        if (value[value.size() - 1] == '\n')
            value.erase(value.begin() + value.size() - 1);
    }        

    std::string toString()
    {
        std::string retVal = "|";
        retVal += std::to_string((int)type) + " ";
        retVal += std::to_string(line) + " ";
        retVal += std::to_string(group);
        retVal += "|" + value;
        return retVal; 
    }

public:
    typeMessage type;
    int group;
    int line;
    std::string value;
};

#define printInternalError(file, line) do {\
    char buf[512];\
    sprintf(buf, "Internal error at line %d and file %s\n", line, file);\
    addToGlobalBufferAndPrint(buf);\
\
    if (currProcessing.first && currProcessing.second)\
    { \
       sprintf(buf, "Internal error in user code at line %d and file %s\n", currProcessing.second->lineNumber(), currProcessing.first->filename());\
       addToGlobalBufferAndPrint(buf);\
    } \
    throw(-1);\
} while (0)


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
        printInternalError(__FILE__, __LINE__);\
} while (0)

#define __spf_printToBuf(outval, format, ...) do {\
    char *buf = NULL; \
    allocAndPrint(buf, format, ##__VA_ARGS__); \
    outval = std::string(buf);\
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
