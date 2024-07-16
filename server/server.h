#include <iostream>
#include <string>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>

class Server {
    public:
        Server(std::string ip, int port);
        ~Server();
        void start_server();
        void close_server();
    private:
        std::string ip_address;
        int my_port;
        int my_socket;
        int new_socket;
        long incoming_message;

        struct sockaddr_in my_socketAddress; // Server address
        unsigned int socket_address_length;

        std::string server_message; // Message to send to client

        void start_listening();
        void accept_connection(int new_socket);
};
