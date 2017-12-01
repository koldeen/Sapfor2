#pragma once
#include <string>

enum typeMessage { WARR, ERROR, NOTE };
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
    throw(-1);\
} while (0)


#define checkNull(address, file, line) do { \
    if ((address) == NULL) \
        printInternalError(file, line); \
} while (0)

#define printToBuf(outval, format, ...) do {\
        char buf[512];\
        sprintf(buf, format, ##__VA_ARGS__);\
        outval = string(buf);\
} while (0)
