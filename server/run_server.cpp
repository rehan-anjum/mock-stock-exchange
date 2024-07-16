#include "server.h"
#include "string"

int main() {

    Server server = Server("0.0.0.0", 8080);

    server.start_server();
    server.close_server();
}