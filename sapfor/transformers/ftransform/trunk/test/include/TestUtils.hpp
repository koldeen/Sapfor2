//
// Created by baa on 15.12.17.
//

#ifndef FTRANSFORM_TEST_HPP
#define FTRANSFORM_TEST_HPP
#include <string>

namespace SageTransform {
    class TestUtils {
    public:
        static bool compare(const char *fileName1, const char *fileName2);
    private:
        static std::string readFile(const char *fileName);
    };
}
#endif //FTRANSFORM_TEST_HPP
