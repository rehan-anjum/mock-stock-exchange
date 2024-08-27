#ifndef ORDERBOOK_HPP
#define ORDERBOOK_HPP

#include <iostream>
#include <map>
#include <unordered_map>
#include "order.hpp"
#include "enums.hpp"

class Orderbook {
    private:
        /*
        The key is the price and the order objects contain the remaining order information.
        We use the unordered map to access order objects by ID in constant time, in case we want to remove an order. 
        */
        std::map<double, std::vector<std::shared_ptr<Order>>, std::greater<double>> bids_;
        std::map<double, std::vector<std::shared_ptr<Order>>, std::less<double>> asks_;
        std::unordered_map<uint64_t, std::shared_ptr<Order>> orders_;
        int numOrders = 0;
        void match_trades();

    public:
        Orderbook();
        ~Orderbook();

        void add_order(double price, int quantity, OrderSide side);
        void remove_order(uint64_t id);

};

#endif