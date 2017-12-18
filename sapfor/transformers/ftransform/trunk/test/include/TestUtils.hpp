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
        static bool compareFortranSources(const char *fileName1, const char *fileName2);
    private:
        static std::string readFile(const char *fileName);
        static std::vector<std::string> readFileLines(const char *fileName);
    };
}
#endif //FTRANSFORM_TEST_HPP
