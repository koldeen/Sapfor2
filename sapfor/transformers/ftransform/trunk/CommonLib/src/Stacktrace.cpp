//
// Created by Bulanov on 15.08.17.
//
#include "Stacktrace.hpp"

#ifdef _WIN32
#elif __APPLE__
#elif __linux__

#include <execinfo.h>  // for backtrace
#include <cxxabi.h> // for __cxa_demangle

#else
#endif

using namespace SageTransform;

std::string Stacktrace::getTrace(int skip) {
    std::string result;
#ifdef _WIN32
    result = "<stacktrace not supported on Windows>";
#elif __APPLE__
    result.push_back("<stacktrace not supported on Apple system>");
#elif __linux__
#define BT_BUF_SIZE 100
    int j, nptrs;
    void *buffer[BT_BUF_SIZE];
    char **strings;

    nptrs = backtrace(buffer, BT_BUF_SIZE);
    //printf("backtrace() returned %d addresses\n", nptrs);

    /* The call backtrace_symbols_fd(buffer, nptrs, STDOUT_FILENO)
       would produce similar output to the following: */

    strings = backtrace_symbols(buffer, nptrs);
    if (strings == NULL) {
        //perror("backtrace_symbols");
        result.append("<Error getting stacktrace by backtrace>");
    } else {
        int status = -1;
        char *demangled = NULL;
        char *original = NULL;
        for (j = skip; j < nptrs; j++) {
            std::string traceLine;
            original = strings[j];
            demangled = NULL;//abi::__cxa_demangle(original, 0, 0, &status);
            if (status == 0) {
                traceLine.append(demangled);
            } else {
                traceLine.append(original);
            }
            if (demangled) {
                free(demangled);
            }
            result.append(traceLine).append("\n");
        }
    }
    if (strings) free(strings);
#else
    result.push_back("<Unrecognised system type. stacktrace not supported>");
#endif
    return result;
}
