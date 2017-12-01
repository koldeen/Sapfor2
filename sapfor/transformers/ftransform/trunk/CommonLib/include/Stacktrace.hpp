//
// Created by baa on 15.08.17.
//

#ifndef FTRANSFORM_BACKTRACE_H
#define FTRANSFORM_BACKTRACE_H

#include <string>
#include <vector>

namespace SageTransform {
    class Stacktrace {
    public:
        static std::string getTrace(int skip = 1);
    };
}
#endif //FTRANSFORM_BACKTRACE_H
