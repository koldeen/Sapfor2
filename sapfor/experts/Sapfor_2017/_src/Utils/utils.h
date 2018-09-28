#pragma once
#include <map>
#include <vector>
#include <set>
#include <string>

#include "../Distribution/Distribution.h"

std::string OnlyExt(const char *filename);
std::string OnlyName(const char *filename);
void printHelp();
void convertToLower(std::string &str);
void convertToUpper(std::string &str);

void printVersion();
const std::string printVersionAsFortranComm();
std::string convertFileName(const char *file);
void printBlanks(const int sizeOfBlank, const int countOfBlanks);

void addToGlobalBufferAndPrint(const std::string &toPrint);
void clearGlobalBuffer();
const std::string& getGlobalBuffer();
void convertGlobalBuffer(short *&result, int *&resultSize);
void clearGlobalMessagesBuffer();
void convertGlobalMessagesBuffer(short *&result, int *&resultSize);
void copyIncludes(const std::set<std::string> &allIncludeFiles, const std::map<std::string, std::map<int, std::set<std::string>>> &commentsToInclude, const char *folderName, int removeDvmDirs = 0);

std::string splitDirective(const std::string &in);
void splitString(const std::string &strIn, const char delim, std::vector<std::string> &result);

bool isSPF_comment(const std::string &bufStr);

void sortFilesBySize(const char *proj_name);

void uniteVectors(const std::vector<std::pair<std::pair<std::string, std::string>, std::vector<std::pair<int, int>>>> &first,
                  const std::vector<std::pair<std::pair<std::string, std::string>, std::vector<std::pair<int, int>>>> &second,
                  std::vector<std::pair<std::pair<std::string, std::string>, std::vector<std::pair<int, int>>>> &result);

void deletePointerAllocatedData();
unsigned getUniqArrayId();

bool isAllRulesEqual(const std::vector<std::vector<std::tuple<DIST::Array*, int, std::pair<int, int>>>> &allRules);
bool isAllRulesEqual(const std::vector<const std::vector<std::pair<int, int>>*> &allRules);
bool isAllRulesEqual(const std::vector<std::vector<int>> &allRules);

int getNextNegativeLineNumber();
void findAndReplaceDimentions(std::vector<std::tuple<DIST::Array*, int, std::pair<int, int>>> &rule, const DIST::Arrays<int> &allArrays);

extern "C" void removeFromCollection(void *pointer);
extern "C" void addToCollection(const int line, const char *file, void *pointer, int type);

#ifndef _WIN32
inline void sendMessage_1lvl(const std::wstring &toSend);
inline void sendMessage_2lvl(const std::wstring &toSend);
#else
extern void sendMessage_1lvl(const std::wstring &toSend);
extern void sendMessage_2lvl(const std::wstring &toSend);
#endif

std::vector<int> findLinksBetweenArrays(DIST::Array *from, DIST::Array *to, const int regionId);
#ifdef _WIN32
void printStackTrace();
#endif
