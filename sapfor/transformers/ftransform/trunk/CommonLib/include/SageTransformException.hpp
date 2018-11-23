//
// Created by baa on 16.08.17.
//

#ifndef FTRANSFORM_EXCEPTION_HPP
#define FTRANSFORM_EXCEPTION_HPP

#include <string>

namespace SageTransform {
    class SageTransformException {
    public:
        SageTransformException(std::string message);

        std::string toString();

    private:
        std::string mMessage;
        std::string mStacktrace;
    };
}


#endif //FTRANSFORM_EXCEPTION_HPP
