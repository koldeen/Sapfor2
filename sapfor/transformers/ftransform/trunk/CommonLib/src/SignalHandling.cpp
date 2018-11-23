//
// Created by baa on 28.08.17.
// Source: https://oroboro.com/stack-trace-on-crash/
//

#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <Stacktrace.hpp>
#include "SignalHandling.hpp"

using namespace SageTransform;

SignalHandling::SignalHandling() {
    signal(SIGABRT, abortHandler);
    signal(SIGSEGV, abortHandler);
#ifndef _WIN32
    signal(SIGBUS, abortHandler);
#endif
    signal(SIGILL, abortHandler);
    signal(SIGFPE, abortHandler);
}

void SignalHandling::abortHandler(int signum) {
    // associate each signal with a signal name string.
    const char *name = NULL;
    switch (signum) {
        case SIGABRT:
            name = "SIGABRT";
            break;
        case SIGSEGV:
            name = "SIGSEGV";
            break;
#ifndef _WIN32
        case SIGBUS:
            name = "SIGBUS";
            break;
#endif
        case SIGILL:
            name = "SIGILL";
            break;
        case SIGFPE:
            name = "SIGFPE";
            break;
        default:
            name = std::to_string(signum).c_str();
            break;
    }

    // Notify the user which signal was caught. We use printf, because this is the
    // most basic output function. Once you get a crash, it is possible that more
    // complex output systems like streams and the like may be corrupted. So we
    // make the most basic call possible to the lowest level, most
    // standard print function.
    if (name) {
        fprintf(stderr, "Caught signal %d (%s)\n", signum, name);
    } else {
        fprintf(stderr, "Caught signal %d\n", signum);
    }

    // Dump a stack trace.
    fprintf(stderr, "%s", Stacktrace::getTrace().c_str());

    // If you caught one of the above signals, it is likely you just
    // want to quit your program right now.
    exit(signum);
}
