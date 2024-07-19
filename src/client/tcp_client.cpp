#include <iostream>
#include "client.h"

int main() {
    TCPClient client("0.0.0.0", 8080);

    client.startClient();
    // client.connectToServer("0.0.0.0", 8080);

    while (true) {
        std::string message;
        std::getline(std::cin, message);
        std::cout << "Sent message: " << message << std::endl;
        if (message == "exit") {
            break;
        }

        client.sendMessage(message);
        client.receiveMessage();
    }
    
    client.closeClient();

    return 0;
}
