#ifndef MESSAGES_H
#define MESSAGES_H

#include <string>
#include "enums.hpp"

struct Message {
    bool fromClient = false;
    MessageType type;
    std::string data;
};

#endif