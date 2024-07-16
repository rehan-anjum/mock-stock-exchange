#include "server.h"
#include "string"

int main() {
    using namespace server;

    Server server = Server("0.0.0.0", 8080);

    server.start_server();

    while(true) {
        std::string message;
        std::getline(std::cin, message);
        if (message == "exit") {
            break;
        }
    }


    server.close_server();
}