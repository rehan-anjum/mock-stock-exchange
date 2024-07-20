#include <string>
#include "server.h"
#include "exchange.h"
#include "messageHandler.h"

int main() {

    Server server = Server("0.0.0.0", 8080);
    Exchange exchange = Exchange();
    MessageHandler handler = MessageHandler(&exchange);

    server.attach_handler(handler);

    server.start_server();

    server.close_server();
    return 0;
}
