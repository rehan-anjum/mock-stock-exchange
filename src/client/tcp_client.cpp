#include <iostream>
#include "client.h"

int main() {
    Client client("0.0.0.0", 8080);

    client.start_client();

    while (true) {
        std::string message;
        std::getline(std::cin, message);
        std::cout << "Sent message: " << message << std::endl;
        if (message == "exit") {
            break;
        }

        client.send_message(message);
        client.receive_message();
    }
    
    client.close_client();

    return 0;
}
