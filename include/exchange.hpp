#ifndef EXCHANGE_H
#define EXCHANGE_H

#include <string>
#include <vector>
#include <map>

class Exchange {

    private:
        const int orderbookSize = 50;

    public:
        Exchange();
        void addOrder(double size, double price, bool isBuy);


};

#endif