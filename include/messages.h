#ifndef MESSAGES_H
#define MESSAGES_H

#include <string>

enum class MessageType {
    order,
    cancel,
    fetch
};

struct Message {
    bool fromClient = false;
    MessageType type;
    std::string data;
};

#endif