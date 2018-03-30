#pragma once

// ANALISYS 
extern "C" { __declspec(dllexport) int SPF_GetGraphLoops(int *options, short *projName, short *&result, short *&output, int *&outputSize, short *&outputMessage, int *&outputMessageSize); }
extern "C" { __declspec(dllexport) int SPF_GetGraphFunctions(int *options, short *projName, short *&result, short *&output, int *&outputSize, short *&outputMessage, int *&outputMessageSize); }
extern "C" { __declspec(dllexport) int SPF_GetPassesState(int *&passInfo); }
extern "C" { __declspec(dllexport) int SPF_GetArrayDistribution(int *options, short *projName, short *&result, short *&output, int *&outputSize, short *&outputMessage, int *&outputMessageSize, uint64_t availMemory, int quality); }
extern "C" { __declspec(dllexport) int SPF_GetVersionAndBuildDate(short *&result); }
extern "C" { __declspec(dllexport) int SPF_GetIntrinsics(short *&result); }
extern "C" { __declspec(dllexport) int SPF_SetFunctionsToInclude(int *options, short *projName, short *&result, short *&output, int *&outputSize, short *&outputMessage, int *&outputMessageSize); }
extern "C" { __declspec(dllexport) int SPF_GetAllDeclaratedArrays(int *options, short *projName, short *&result, short *&output, int *&outputSize, short *&outputMessage, int *&outputMessageSize); }
extern "C" { __declspec(dllexport) int SPF_GetFileLineInfo(int *options, short *projName, short *&result, short *&output, int *&outputSize, short *&outputMessage, int *&outputMessageSize); }
extern "C" { __declspec(dllexport) int SPF_GetIncludeDependencies(int *options, short *projName, short *&result); }

// CODE TRANSFORMATION 
extern "C" { __declspec(dllexport) int SPF_CorrectCodeStylePass(int *options, short *projName, short *folderName, short *&output, int *&outputSize, short *&outputMessage, int *&outputMessageSize); }
extern "C" { __declspec(dllexport) int SPF_RemoveDvmDirectives(int *options, short *projName, short *folderName, short *&output, int *&outputSize, short *&outputMessage, int *&outputMessageSize); }
extern "C" { __declspec(dllexport) int SPF_InsertIncludesPass(int *options, short *projName, short *folderName, char *filesToInclude, short *&output, int *&outputSize, short *&outputMessage, int *&outputMessageSize); }
extern "C" { __declspec(dllexport) int SPF_LoopEndDoConverterPass(int *options, short *projName, short *folderName, short *&output, int *&outputSize, short *&outputMessage, int *&outputMessageSize); }
extern "C" { __declspec(dllexport) int SPF_CreateParallelVariant(int *options, short *projName, short *folderName, int64_t *variants, int *varLen, short *&output, int *&outputSize, short *&outputMessage, int *&outputMessageSize); }

extern "C" { __declspec(dllexport) void SPF_deleteAllAllocatedData(); }
extern "C" { __declspec(dllexport) int  SPF_SetDistributionFlagToArray(char *key, int flag); }

void createNeededException();