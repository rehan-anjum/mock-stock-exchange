#ifndef EXCHANGE_H
#define EXCHANGE_H

#include <string>
#include <vector>
#include <map>

class Exchange {

    private:
        std::map<double, double> buyOrders;
        std::map<double, double> sellOrders;

    public:
        Exchange();
        void addOrder(double size, double price, bool isBuy);


};

#endif