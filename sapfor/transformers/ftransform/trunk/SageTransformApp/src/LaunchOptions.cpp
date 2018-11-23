//
// Created by baa on 15.08.17.
//

#include "LaunchOptions.hpp"
#include <cstring>

LaunchOptions LaunchOptions::fromArgs(const int argc, const char **argv) {
    LaunchOptions result = LaunchOptions();
    for (int i = 1; i < argc; ++i) {
        if (matchAnyOption(argv[i], "-p", "--project")) {
            if (i + 1 >= argc) {
                throw std::string("Missing project value. Excepted a *.proj file.");
            } else {
                result.mHasProjectFile = true;
                result.mProjectFile = argv[i + 1];
                i++;
            }
        } else if (matchAnyOption(argv[i], "-s", "--silent")) {
            result.mSilent = true;
        }
    }
    return result;
}

LaunchOptions::LaunchOptions() {
    mSilent = false;
    mHasProjectFile = false;
    mProjectFile = nullptr;
}

bool LaunchOptions::isSilent() const {
    return mSilent;
}

bool LaunchOptions::hasProjectFile() const {
    return mHasProjectFile;
}

const char *LaunchOptions::getProjectFile() const {
    return mProjectFile;
}

bool LaunchOptions::matchAnyOption(const char *input, const char *op1, const char *op2) {
    return strcmp(input, op1) == 0 || strcmp(input, op2) == 0;
}
