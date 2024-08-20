#ifndef EXCHANGE_H
#define EXCHANGE_H

#include <string>
#include <vector>
#include <map>

struct Order {
    int size;
    int id;
    double price;
    bool isBuy;

    Order(int size, double price, bool isBuy) : size(size), price(price), isBuy(isBuy) {}

    bool operator<(const Order& other) const {
        return price < other.price;
    }

    bool operator>(const Order& other) const {
        return price > other.price;
    }

    bool operator==(const Order& other) const {
        return price == other.price;
    }

};

class Exchange {

    private:
        const int orderbookSize = 50;

    public:
        Exchange();
        void addOrder(double size, double price, bool isBuy);


};

#endif