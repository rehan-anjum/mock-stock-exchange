#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <memory>
#include "messages.h"
#include "messageHandler.h"

MessageHandler::MessageHandler(void* exchange) {
    this->exchange = exchange;
}

void MessageHandler::processMessage(std::string data) {
    std::shared_ptr<Message> message = std::make_shared<Message>();
    std::stringstream stream(data);
    std::string s;
    stream >> s;

    try {
        if (s == "order") {
            message->type = MessageType::order;

            double size, price = 0;
            bool isBuy = false;
            std::string side;
            stream >> size >> price >> side;

            if (side == "buy") {
                isBuy = true;
            } else if (side == "sell") {
                isBuy = false;
            } else {
                throw std::invalid_argument("Invalid order direction");
            }
            // exchange->addOrder(size, price, isBuy);
        } else if (s == "cancel") {
            message->type = MessageType::cancel;
            int id;
            stream >> id;
            // exchange->cancelOrder(id);
        } else if (s == "fetch") {
            message->type = MessageType::fetch;
            // exchange->fetchOrderbook();
        } else {
            throw std::invalid_argument("Invalid message type"); 
        }
        messages.push_back(message);
    } catch (std::invalid_argument& e) {
        throw e;
    }


}

std::string MessageHandler::addMessage(std::string data) {

    try {
        processMessage(data);
        if (messages.back()->type == MessageType::order) {
            return "Order received";
        } else if (messages.back()->type == MessageType::cancel) {
            return "Order cancelled";
        } else {
            return "Orderbook fetched";
        }
    } catch (std::invalid_argument& e) {
        return e.what();
    }
    

}