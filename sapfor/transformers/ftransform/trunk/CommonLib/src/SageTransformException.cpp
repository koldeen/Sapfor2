//
// Created by baa on 16.08.17.
//

#include "SageTransformException.hpp"
#include "Stacktrace.hpp"

SageTransform::SageTransformException::SageTransformException(std::string message) {
    mMessage = message;
    mStacktrace = Stacktrace::getTrace(2);
}

std::string SageTransform::SageTransformException::toString() {
    return "SageTransformException: " + mMessage + "\n" + mStacktrace;
}
