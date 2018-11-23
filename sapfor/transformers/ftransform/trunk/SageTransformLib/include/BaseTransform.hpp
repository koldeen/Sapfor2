//
// Created by baa on 13.09.17.
//

#ifndef FTRANSFORM_BASETRANSFORM_HPP
#define FTRANSFORM_BASETRANSFORM_HPP

#include <vector>
#include <string>

using std::vector;
using std::string;

namespace SageTransform {
    class BaseTransform {
    protected:
        vector<string> messages;

        bool suppressThrows;
    public:
        vector<string> &getMessages();

        void clearMessages();

        bool getSuppressThrows();

        void setSuppressThrows(bool inSuppressThrows);

    protected:
        void addMessage(int type, int line, string &value);

        BaseTransform() : suppressThrows(true) {};
    };
}


#endif //FTRANSFORM_BASETRANSFORM_HPP
