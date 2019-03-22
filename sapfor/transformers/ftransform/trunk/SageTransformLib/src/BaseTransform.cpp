//
// Created by baa on 13.09.17.
//

#include "BaseTransform.hpp"

vector<string> &SageTransform::BaseTransform::getMessages() {
    return messages;
}

void SageTransform::BaseTransform::addMessage(int type, int line, string &value) {
    //format from SAPFOR_2017
    string newMessage = "|" + std::to_string(type) + " " + std::to_string(line) + "|" + value;
    messages.push_back(newMessage);
}

void SageTransform::BaseTransform::clearMessages() {
    messages.clear();
}

bool SageTransform::BaseTransform::getSuppressThrows() {
    return suppressThrows;
}

void SageTransform::BaseTransform::setSuppressThrows(bool inSuppressThrows) {
    suppressThrows = inSuppressThrows;
}
