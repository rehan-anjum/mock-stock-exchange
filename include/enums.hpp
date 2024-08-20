#ifndef ENUMS_HPP
#define ENUMS_HPP

enum class MessageType {
    order,
    cancel,
    fetch
};

enum class OrderSide {
    buy,
    sell
};

#endif