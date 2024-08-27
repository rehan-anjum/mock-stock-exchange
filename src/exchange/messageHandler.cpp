#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <memory>
#include "messages.hpp"
#include "messageHandler.hpp"

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
            message->type = MessageType::Order;

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
            message->type = MessageType::Cancel;
            int id;
            stream >> id;
            // exchange->cancelOrder(id);
        } else if (s == "fetch") {
            message->type = MessageType::Fetch;
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
        if (messages.back()->type == MessageType::Order) {
            return "Order received";
        } else if (messages.back()->type == MessageType::Cancel) {
            return "Order cancelled";
        } else {
            return "Orderbook fetched";
        }
    } catch (std::invalid_argument& e) {
        return e.what();
    }
    

}