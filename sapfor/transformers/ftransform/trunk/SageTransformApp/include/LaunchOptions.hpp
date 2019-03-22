//
// Created by baa on 15.08.17.
//

#ifndef FTRANSFORM_LAUNCHOPTIONS_H
#define FTRANSFORM_LAUNCHOPTIONS_H

#include <string>

class LaunchOptions {
public:
    static LaunchOptions fromArgs(const int argc, const char **argv);

    bool isSilent() const;

    bool hasProjectFile() const;

    const char *getProjectFile() const;

private:
    bool mSilent;

    bool mHasProjectFile;
    const char *mProjectFile;

    LaunchOptions();

    static bool matchAnyOption(const char *input, const char *op1, const char *op2);
};


#endif //FTRANSFORM_LAUNCHOPTIONS_H
