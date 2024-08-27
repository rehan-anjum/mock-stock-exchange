#include "orderbook.hpp"
#include "order.hpp"
#include "enums.hpp"

Orderbook::Orderbook() {}

Orderbook::~Orderbook() {}

void Orderbook::add_order(double price, int quantity, OrderSide side) {
    Order currentOrder = Order(price, quantity, side);
    auto orderPointer = std::make_shared<Order>(currentOrder);
    side == OrderSide::Buy ? bids_[price].push_back(orderPointer) : asks_[price].push_back(orderPointer);
    orders_[currentOrder.getId()] = orderPointer;
    ++numOrders;
}

void Orderbook::remove_order(uint64_t id) {
    if (orders_.find(id) == orders_.end()) {
        throw std::logic_error("Order not found");
        return;
    }
    auto associatedOrder = orders_[id];
    if (associatedOrder->getBookSide() == OrderSide::Buy) {
        auto &bids = bids_[associatedOrder->getPrice()];
        bids.erase(std::remove(bids.begin(), bids.end(), associatedOrder), bids.end());
    } else {
        auto &asks = asks_[associatedOrder->getPrice()];
        asks.erase(std::remove(asks.begin(), asks.end(), associatedOrder), asks.end());
    }
    orders_.erase(id);
    --numOrders;
}

void Orderbook::match_trades() {
    // Implement trade matching logic here

}