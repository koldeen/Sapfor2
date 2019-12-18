//
// Created by Vladislav Volodkin on 12/17/19.
//

#ifndef SAPFOR_EXCEPTIONS_H
#define SAPFOR_EXCEPTIONS_H
#include <exception>

class NotMergeable : public std::exception
{
public:
    char * what () {
        return "regions can not be merged";
    }
};

class NotImplemented : public std::exception
{
public:
    char * what () {
        return "provided input not supported yet";
    }
};

#endif //SAPFOR_EXCEPTIONS_H
