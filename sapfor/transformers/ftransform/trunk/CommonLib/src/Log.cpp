/*
 * Log.cpp
 */

#include "Log.hpp"

#include <ctime>   // localtime
#include <sstream> // stringstream
#include <iostream>

//copied from Sapfor_2017/_src/utils.h
#ifdef __SPF
//FIXME find more elegant solution than define
#include <cstdio>
extern void addToGlobalBufferAndPrint(const std::string &toPrint);
#define print(needPrint, format, ...) do {\
    if (needPrint == 1) {\
        char buf[512];\
        sprintf(buf, format, ##__VA_ARGS__);\
        addToGlobalBufferAndPrint(buf);\
    } \
} while (0)
#else
#define print(needPrint, format, ...) /* pass */
#endif

using namespace SageTransform;
int Log::logLevel = Log::LogLevel::DEBUG;
ostream * Log::outputStream = nullptr;

void Log::error(const string &msg) {
    if (Log::logLevel & Log::LogLevelMask::ERROR_MASK) {
        write("[ERROR]", msg);
    }
}

void Log::warn(const string & msg) {
    if (Log::logLevel & Log::LogLevelMask::WARN_MASK) {
        write("[WARN]", msg);
    }
}

void Log::info(const string & msg) {
	if (Log::logLevel & Log::LogLevelMask::INFO_MASK) {
        write("[INFO]", msg);
	}
}

void Log::debug(const string & msg) {
	if (Log::logLevel & Log::LogLevelMask::DEBUG_MASK) {
        write("[DEBUG]", msg);
	}
}

void Log::setLogLevel(LogLevel inLogLevel) {
	Log::logLevel = inLogLevel;
}

void Log::setLogOutputStream(ostream* stream) {
	Log::outputStream = stream;
}

void Log::write(const char * prefix, const string & msg) {
    std::stringstream ss;
    ss << prefix << ' ' << getTimestamp() << ' ' << msg << std::endl;
    if (outputStream != nullptr) {
        (*outputStream) <<  ss.str();
    } else {
        std::cout << ss.str();
    }
    print(1, "%s", ss.str().c_str());
}

//from https://stackoverflow.com/questions/17223096/outputting-date-and-time-in-c-using-stdchrono
string Log::getTimestamp() {
    std::stringstream ss;
    std::time_t t = std::time(NULL);
    char mbstr[100];
    if (std::strftime(mbstr, sizeof(mbstr), "%Y-%m-%d %X", std::localtime(&t))) {
        ss << mbstr;
    }
    return ss.str();
}
