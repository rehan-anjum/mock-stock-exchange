#include <cstring> 
#include <iostream> 
#include <string>
#include <sstream>
#include <thread>
#include <vector>
#include <functional>

#include <netinet/in.h> 
#include <sys/socket.h> 
#include <unistd.h> 

#include "server.h"

void log(const std::string &message) {
    std::cout << message << std::endl;
}

// exit with error
void error(const std::string &errorMessage) {
    log("ERROR: " + errorMessage);
    exit(1);
}

Server::Server(std::string ip, int port) : 
    ip_address(ip), my_port(port), my_socket(), new_socket(), incoming_message(), my_socketAddress(),
    socket_address_length(sizeof(my_socketAddress)), server_message("HELLO")
{
}

Server::~Server() {
    close_server();
}

void Server::start_server() {
    // Create a socket
    my_socket = socket(AF_INET, SOCK_STREAM, 0);

    if (my_socket < 0) {
        error("Could not create socket");
    }

    my_socketAddress.sin_family = AF_INET;
    my_socketAddress.sin_addr.s_addr = inet_addr(ip_address.c_str());
    my_socketAddress.sin_port = htons(my_port);

    // Bind the socket to the address and port number
    if (bind(my_socket, (struct sockaddr *)&my_socketAddress, sizeof(my_socketAddress)) < 0) {
        error("Could not bind socket to address");
    }

    // Listen for incoming connections
    start_listening();
}

void Server::start_listening() {
    if (listen(my_socket, 20) < 0) { 
        error("socket failed to listen");
    }

    std::ostringstream iss;
    iss << "Server listening on port " << my_port
        << " and IP address " << ip_address << std::endl;
    log(iss.str());
    log("Server ready to receive");

    std::vector<std::thread> threads;
    
    while (true) {
        new_socket = accept(my_socket, (struct sockaddr *)&my_socketAddress, (socklen_t *)&socket_address_length);

        if (new_socket < 0) {
            log("Could not accept connection");
            continue;
        }

        log("Connection accepted. Creating new thread to handle client");

        // Create a new thread to handle the connection
        threads.emplace_back([this](int socket) { accept_connection(socket); }, new_socket);
    }

    for (auto& th : threads) {
        if (th.joinable()) {
            th.join();
        }
    }
}

void Server::attach_handler(MessageHandler& handler) {
    this->handler = &handler;
}

void Server::accept_connection(int client_socket) {
    int bytes_received;
    const int BUFFER_SIZE = 30720;

    while (true) {
        // Receive a message from the client
        char buffer[BUFFER_SIZE] = {0};
        bytes_received = read(client_socket, buffer, BUFFER_SIZE);

        if (bytes_received < 0) {
            error("Could not receive message from client");
        } else if (bytes_received == 0) {
            log("Client disconnected");
            break;
        }

        log("Message received from client");
        log("Message: " + std::string(buffer)); // Print the message

        std::string client_message = "";

        try {
            client_message = handler->addMessage(std::string(buffer));
        } catch (std::invalid_argument& e) {
            client_message = "Invalid message: " + std::string(e.what());
        }

        // Send a message back to the client
        int send_status = write(client_socket, client_message.c_str(), client_message.size());

        if (send_status < 0) {
            error("Could not send back message to client");
        }
    }

    close(client_socket);
}

void Server::close_server() {
    close(my_socket);
    close(new_socket);
    exit(0);
}
