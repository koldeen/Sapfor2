/*
 * Log.hpp
 * Contains Logging functions
 */

#ifndef SRC_LOG_HPP_
#define SRC_LOG_HPP_

#include <string>
#include <ostream>

using std::string;
using std::ostream;

namespace SageTransform {
    class Log {
    public:
        enum LogLevel {
            DEBUG = 15 /*0b01111*/, INFO = 7 /*0b00111*/, WARN = 3 /*0b00011*/, ERROR = 1 /*0b00001*/};

        static void error(const string &msg);

        static void warn(const string &msg);

        static void info(const string &msg);

        static void debug(const string &msg);

        static void setLogLevel(LogLevel logLevel);

        static void setLogOutputStream(ostream *stream);

    private:
        enum LogLevelMask {
            DEBUG_MASK = 8 /*0b01000*/, INFO_MASK = 4 /*0b00100*/, WARN_MASK = 2 /*0b00010*/, ERROR_MASK = 1 /*0b00001*/};
        static int logLevel;
        static ostream *outputStream;

        static string getTimestamp();

        static void write(const char *prefix, const string &msg);
    };
}

#endif /* SRC_LOG_HPP_ */
