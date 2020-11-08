#pragma once
#include <map>
#include <vector>
#include <set>
#include <string>

namespace Distribution
{
    class Array;
    class ArrayAccessInfo;
    template<typename vType> class Arrays;
}
namespace DIST = Distribution;

std::string OnlyExt(const char *filename);
std::string OnlyName(const char *filename);
std::string FullNameWithExt(const char* filename);

void printHelp(const char **passNames, const int lastPass);
void convertToLower(std::string &str);
void convertToUpper(std::string &str);

void printVersion(const std::string = "");
const std::string printVersionAsFortranComm();
std::string convertFileName(const char *file);
void printBlanks(const int sizeOfBlank, const int countOfBlanks);

void addToGlobalBufferAndPrint(const std::string &toPrint);
void clearGlobalBuffer();
const std::string& getGlobalBuffer();
std::wstring to_wstring(const std::string);
void convertBuffers(short*& resultM, int*& resultSizeM, short*& result, int*& resultSize);
void clearGlobalMessagesBuffer();
void copyIncludes(const std::set<std::string> &allIncludeFiles, const std::map<std::string, std::map<int, std::set<std::string>>> &commentsToInclude, const char *folderName, bool keepSpfDirs, int removeDvmDirs = 0);

std::string splitDirective(const std::string &in);
std::string splitDirectiveFull(const std::string &in_);

void splitString(const std::string &strIn, const char delim, std::vector<std::string> &result, bool withQuotes = false);
void splitString(const std::wstring& strIn, const char delim, std::vector<std::wstring>& result, bool withQuotes = false);

bool isSPF_comment(const std::string& bufStr);
bool isDVM_comment(const std::string& bufStr);

void sortFilesBySize(const char *proj_name);

void uniteVectors(const std::vector<std::pair<std::pair<std::string, std::string>, std::vector<std::pair<int, int>>>> &first,
                  const std::vector<std::pair<std::pair<std::string, std::string>, std::vector<std::pair<int, int>>>> &second,
                  std::vector<std::pair<std::pair<std::string, std::string>, std::vector<std::pair<int, int>>>> &result);

void deletePointerAllocatedData(bool delLocal = false);
void startLocalColletion();
void finishLocalColletion();
void deleteLeaks();

unsigned getUniqArrayId();

bool isAllRulesEqualWithoutArray(const std::vector<std::vector<std::tuple<DIST::Array*, int, std::pair<int, int>>>> &allRules);
bool isAllRulesEqual(const std::vector<std::vector<std::tuple<DIST::Array*, int, std::pair<int, int>>>> &allRules);
bool isAllRulesEqual(const std::vector<std::vector<std::pair<int, int>>> &allRules);
bool isAllRulesEqual(const std::vector<std::vector<int>> &allRules);

int getNextNegativeLineNumber();
void findAndReplaceDimentions(std::vector<std::tuple<DIST::Array*, int, std::pair<int, int>>> &rule, const DIST::Arrays<int> &allArrays);

extern "C" void removeFromCollection(void *pointer);
extern "C" void addToCollection(const int line, const char *file, void *pointer, int type);

std::vector<int> findLinksBetweenArrays(DIST::Array *from, DIST::Array *to, const uint64_t regionId);
#ifdef _WIN32
void printStackTrace();
#endif

template<typename objT>
objT& getObjectForFileFromMap(const char *fileName, std::map<std::string, objT> &mapObject);

bool isMpiFunction(const std::string& func);
std::map<DIST::Array*, DIST::ArrayAccessInfo*> createMapOfArrayAccess(const std::map<std::tuple<int, std::string, std::string>, std::pair<DIST::Array*, DIST::ArrayAccessInfo*>> &declaredArrays);

std::string readFileToStr(const std::string& name);
void writeFileFromStr(const std::string& name, const std::string& data);

std::pair<std::vector<std::string>, std::vector<std::string>> splitCommandLineForParse(char** argv, int argc);
