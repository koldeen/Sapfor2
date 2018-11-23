//
// Created by baa on 15.12.17.
//

#ifndef FTRANSFORM_TEST_HPP
#define FTRANSFORM_TEST_HPP
#include <string>
#include <vector>


namespace SageTransform {
    class TestUtils {
    public:
        static bool compareStrict(const char *fileName1, const char *fileName2);
        static bool compareFortranSources(const char *fileName1, const char *fileName2);
        static bool compileAndCompareOutputs(const char *fileName1, const char *fileName2);
        static bool compileAndCompareOutputs(const char *workFolder, const char *fileName1, const char *fileName2);
    private:
        static std::vector<std::string> readFileLines(const char *fileName);
        static bool compileAndRun(const char *fileName, const char *exeName, const char *outputName);
    };
}
#endif //FTRANSFORM_TEST_HPP
