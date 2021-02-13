#pragma once

#if _WIN32
// ANALISYS 
extern "C" { __declspec(dllexport) int SPF_GetGraphLoops(void*& context, int winHandler, short *options, short *projName, short *&result, short *&output, int *&outputSize, short *&outputMessage, int *&outputMessageSize); }
extern "C" { __declspec(dllexport) int SPF_GetGraphFunctions(void*& context, int winHandler, short *options, short *projName, short *&result, short *&output, int *&outputSize, short *&outputMessage, int *&outputMessageSize); }
extern "C" { __declspec(dllexport) int SPF_GetGraphVizOfFunctions(void*& context, short *options, short *projName, short *&result, short *&output, int *&outputSize, short *&outputMessage, int *&outputMessageSize); }
extern "C" { __declspec(dllexport) int SPF_GetArrayDistribution(void*& context, int winHandler, short *options, short *projName, short *&result, short *&output, int *&outputSize, short *&outputMessage, int *&outputMessageSize, int onlyAnalysis); }
extern "C" { __declspec(dllexport) int SPF_SetFunctionsToInclude(void*& context, int winHandler, short *options, short *projName, short *&result, short *&output, int *&outputSize, short *&outputMessage, int *&outputMessageSize); }
extern "C" { __declspec(dllexport) int SPF_GetAllDeclaratedArrays(void*& context, int winHandler, short *options, short *projName, short *&result, short *&output, int *&outputSize, short *&outputMessage, int *&outputMessageSize); }
extern "C" { __declspec(dllexport) int SPF_GetFileLineInfo(void*& context, int winHandler, short *options, short *projName, short *&result, short *&output, int *&outputSize, short *&outputMessage, int *&outputMessageSize); }
extern "C" { __declspec(dllexport) int SPF_GetIncludeDependencies(void*& context, int winHandler, short *options, short *projName, short *&result); }
extern "C" { __declspec(dllexport) int SPF_GetGCovInfo(void*& context, int winHandler, short *options, short *projName, short *&result, short *&output, int *&outputSize, short *&outputMessage, int *&outputMessageSize); }
extern "C" { __declspec(dllexport) int SPF_ParseFiles(void*& context, int winHandler, short *options, short* projName, short*& output, int*& outputSize, short*& outputMessage, int*& outputMessageSize); }
extern "C" { __declspec(dllexport) int SPF_StatisticAnalyzer(void*& context, int winHandler, short* options, short* pppaOptions, short*& output, int*& outputSize, short*& outputMessage, int*& outputMessageSize); }

extern "C" { __declspec(dllexport) int SPF_GetPassesState(void*& context, int *&passInfo); } // deprecated
extern "C" { __declspec(dllexport) int SPF_GetPassesStateStr(void*& context, short *&passInfo); }
extern "C" { __declspec(dllexport) int SPF_GetVersionAndBuildDate(void*& context, short *&result); }
extern "C" { __declspec(dllexport) int SPF_GetIntrinsics(void*& context, short *&result); }
extern "C" { __declspec(dllexport) void SPF_deleteAllAllocatedData(void*& context); }

// CODE TRANSFORMATION 
extern "C" { __declspec(dllexport) int SPF_CorrectCodeStylePass          (void*& context, int winHandler, short *options, short *projName, short *folderName, short *&output, int *&outputSize, short *&outputMessage, int *&outputMessageSize); }
extern "C" { __declspec(dllexport) int SPF_RemoveDvmDirectives           (void*& context, int winHandler, short *options, short *projName, short *folderName, short *&output, int *&outputSize, short *&outputMessage, int *&outputMessageSize); }
extern "C" { __declspec(dllexport) int SPF_RemoveDvmDirectivesToComments (void*& context, int winHandler, short *options, short *projName, short *folderName, short *&output, int *&outputSize, short *&outputMessage, int *&outputMessageSize); }
extern "C" { __declspec(dllexport) int SPF_InsertIncludesPass            (void*& context, int winHandler, short *options, short *projName, short *folderName, char *filesToInclude, short *&output, int *&outputSize, short *&outputMessage, int *&outputMessageSize); }
extern "C" { __declspec(dllexport) int SPF_ResolveParallelRegionConflicts(void*& context, int winHandler, short *options, short *projName, short *folderName, short *&output, int *&outputSize, short *&outputMessage, int *&outputMessageSize); }
extern "C" { __declspec(dllexport) int SPF_LoopEndDoConverterPass        (void*& context, int winHandler, short *options, short *projName, short *folderName, short *&output, int *&outputSize, short *&outputMessage, int *&outputMessageSize); }
extern "C" { __declspec(dllexport) int SPF_CreateParallelVariant         (void*& context, int winHandler, short *options, short *projName, short *folderName, int64_t *variants, int *varLen, short *&output, int *&outputSize, short *&outputMessage, int *&outputMessageSize, short *&predictorStats); }
extern "C" { __declspec(dllexport) int SPF_LoopFission                   (void*& context, int winHandler, short *options, short *projName, short *folderName, short *&output, int *&outputSize, short *&outputMessage, int *&outputMessageSize); }
extern "C" { __declspec(dllexport) int SPF_LoopUnion                     (void*& context, int winHandler, short *options, short* projName, short* folderName, short*& output, int*& outputSize, short*& outputMessage, int*& outputMessageSize); }
extern "C" { __declspec(dllexport) int SPF_PrivateExpansion              (void*& context, int winHandler, short *options, short *projName, short *folderName, short *&output, int *&outputSize, short *&outputMessage, int *&outputMessageSize); }
extern "C" { __declspec(dllexport) int SPF_PrivateShrinking              (void*& context, int winHandler, short *options, short* projName, short* folderName, short*& output, int*& outputSize, short*& outputMessage, int*& outputMessageSize); }
extern "C" { __declspec(dllexport) int SPF_CreateIntervalsTree           (void*& context, int winHandler, short *options, short *projName, short *folderName, short *&output, int *&outputSize, short *&outputMessage, int *&outputMessageSize); }
extern "C" { __declspec(dllexport) int SPF_RemoveDvmIntervals            (void*& context, int winHandler, short *options, short *projName, short *folderName, short *&output, int *&outputSize, short *&outputMessage, int *&outputMessageSize); }
extern "C" { __declspec(dllexport) int SPF_DuplicateFunctionChains       (void*& context, int winHandler, short *options, short* projName, short* folderName, short*& output, int*& outputSize, short*& outputMessage, int*& outputMessageSize); }
extern "C" { __declspec(dllexport) int SPF_InlineProcedures              (void*& context, int winHandler, short *options, short* projName, short* folderName, short* names, short*& output, int*& outputSize, short*& outputMessage, int*& outputMessageSize, int type); }
                                   int SPF_CreateCheckpoints             (void*& context, int winHandler, short* options, short* projName, short* folderName, short*& output, int*& outputSize, short*& outputMessage, int*& outputMessageSize);
                                   int SPF_InitDeclsWithZero             (void*& context, int winHandler, short* options, short* projName, short* folderName, short*& output, int*& outputSize, short*& outputMessage, int*& outputMessageSize);
//CODE MODIFICATION
extern "C" { __declspec(dllexport) int SPF_ModifyArrayDistribution    (void*& context, int winHandler, short *options, short* projName, short*& output, int*& outputSize, short*& outputMessage, int*& outputMessageSize, int regId, int64_t* toModify); }
extern "C" { __declspec(dllexport) int SPF_InlineProcedure            (void*& context, int winHandler, short* options, short* projName, short* folderName, short* name, short* file, int line, short*& output, int*& outputSize, short*& outputMessage, int*& outputMessageSize,                                           int& size, int*& sizes, short*& newFilesNames, short*& newFiles); }
extern "C" { __declspec(dllexport) int SPF_LoopUnionCurrent           (void*& context, int winHandler, short* options, short* projName, short* folderName, short* file, int line,              short*& output, int*& outputSize, short*& outputMessage, int*& outputMessageSize,                                           int& size, int*& sizes, short*& newFilesNames, short*& newFiles); }
extern "C" { __declspec(dllexport) int SPF_ChangeSpfIntervals         (void*& context, int winHandler, short* options, short* projName, short* folderName,                                     short*& output, int*& outputSize, short*& outputMessage, int*& outputMessageSize, short* fileNameToMod, int* toModifyLines, int& size, int*& sizes, short*& newFilesNames, short*& newFiles); }
extern "C" { __declspec(dllexport) int SPF_SetDistributionFlagToArray (void*& context, char* key, int flag); }
extern "C" { __declspec(dllexport) int SPF_SetDistributionFlagToArrays(void*& context, const char* keys, const char* flags); }
#endif

void createNeededException();
void RunSapforAsClient(int);

const std::wstring Sapfor_RunAnalysis(const char* name, const char* options_c, const char* projName_c, int winHandler);
const std::wstring Sapfor_RunTransformation(const char* name, const char* options_c, const char* projName_c, const char* folder_c, const char* addOpt_c, int winHandler);
const std::wstring Sapfor_RunModification(const char* name, const char* options_c, const char* projName_c, const char* folder_c, const char* addOpt1_c, const char* addOpt2_c, int winHandler);
void sendErrorCode(const std::wstring& message);

#ifdef JAVA
#include <jni.h>
extern "C" 
{    
    JNIEXPORT jcharArray JNICALL Java_components_Sapfor_SPF_1RunAnalysis      (JNIEnv*, jobject, jstring, jint, jstring, jstring);
    JNIEXPORT jcharArray JNICALL Java_components_Sapfor_SPF_1RunTransformation(JNIEnv*, jobject, jstring, jint, jstring, jstring, jstring, jstring);
    JNIEXPORT jcharArray JNICALL Java_components_Sapfor_SPF_1RunModification  (JNIEnv*, jobject, jstring, jint, jstring, jstring, jstring, jstring, jstring);
}
#endif
