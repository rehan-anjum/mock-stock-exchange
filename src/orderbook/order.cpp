#include "order.hpp"

Order::Order(double price_, int quantity_, OrderSide side_) : price(price_), quantity(quantity_), side(side_) {}

OrderSide Order::getBookSide() {
    return side;
}

double Order::getPrice() {
    return price;
}

int Order::getQuantity() {
    return quantity;
}

uint64_t Order::getTimestamp() {
    return timestamp;
}

uint64_t Order::getId() {
    return id;
}

