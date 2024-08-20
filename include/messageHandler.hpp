#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H

#include <string>
#include <vector>
#include <memory>
#include "messages.hpp"

class MessageHandler {

    private:
        std::vector<std::shared_ptr <Message>> messages;
        void* exchange;
        void processMessage(std::string data);

    public:
        MessageHandler(void* exchange);
        std::string addMessage(std::string data);

};

#endif