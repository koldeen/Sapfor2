#include <string>

#define printInternalError(file, line)

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

#define __spf_print(needPrint, format, ...) do {\
    if (needPrint == 1) {\
        char *buf = NULL; \
        allocAndPrint(buf, format, ##__VA_ARGS__); \
        addToGlobalBufferAndPrint(buf);\
        delete []buf;\
    } \
} while (0)

extern void addToGlobalBufferAndPrint(const std::string&);
extern std::string convertFileName(const char *file);

#if _WIN32 && NDEBUG
#define BOOST_STACKTRACE_USE_WINDBG
#include <boost/stacktrace.hpp>
void printStackTrace()
{
    /*__spf_print(1, "printStack\n");
    auto stack = boost::stacktrace::stacktrace().as_vector();
    for (auto &elem : stack)
    {
        const std::string fname = elem.name();
        const std::string file = elem.source_file();
        const int line = (int)elem.source_line();
        
        if (line)
            __spf_print(1, "%s %s : %d\n", fname.c_str(), convertFileName(file.c_str()).c_str(), line);
    }*/
}
#undef BOOST_STACKTRACE_USE_WINDBG
#else
void printStackTrace() { }
#endif