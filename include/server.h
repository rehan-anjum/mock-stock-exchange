#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <functional>
#include <memory>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>

#include "messageHandler.h"

class Server {
private:
    std::string ip_address;
    int my_port;
    int my_socket;
    int new_socket;
    long incoming_message;

    struct sockaddr_in my_socketAddress; // Server address
    unsigned int socket_address_length;

    MessageHandler* handler; // Message handler

    std::string server_message; // Message to send to client


public:
    Server(std::string ip, int port);
    ~Server();
    void start_server();
    void start_listening();
    void accept_connection(int client_socket);
    void attach_handler(MessageHandler& handler);
    void close_server();

};
