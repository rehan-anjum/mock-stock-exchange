#include <iostream>
#include "client.h"

int main() {
    TCPClient client("0.0.0.0", 8080);
    
    client.startClient();

    while (true) {
        std::string message;
        std::getline(std::cin, message);
        if (message == "exit") {
            break;
        }

        client.sendMessage(message);
    }
    
    client.closeClient();

    return 0;
}
