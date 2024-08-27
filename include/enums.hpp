#ifndef ENUMS_HPP
#define ENUMS_HPP

enum class MessageType {
    Order,
    Cancel,
    Fetch
};

enum class OrderSide {
    Buy,
    Sell
};

#endif