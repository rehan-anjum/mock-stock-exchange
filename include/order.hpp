#ifndef ORDER_HPP
#define ORDER_HPP

#include <iostream>
#include "enums.hpp"

class Order {
    private:
        double price;
        int quantity;
        OrderSide side;
        uint64_t timestamp;
        uint64_t id;

    public:

        Order(double price_, int quantity_, OrderSide side_);
        OrderSide getBookSide();
        double getPrice();
        int getQuantity();
        uint64_t getTimestamp();
        uint64_t getId();

};

#endif