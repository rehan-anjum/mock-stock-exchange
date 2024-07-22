#include <iostream>
#include "exchange.h"

Exchange::Exchange() {}

void addOrder(double size, double price, bool isBuy) {
    if (isBuy) {
        std::cout << "Buy order: " << size << " at " << price << std::endl;
    } else {
        std::cout << "Sell order: " << size << " at " << price << std::endl;
    }
}