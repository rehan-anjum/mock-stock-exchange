#include <cstring> 
#include <iostream> 
#include <string>
#include <sstream>

#include <netinet/in.h> 
#include <sys/socket.h> 
#include <unistd.h> 

#include "server.h"

const std::string FETCH = "Fetch successful!";
const std::string BUY = "Buy successful!";
const std::string SELL = "Sell successful!";

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

    int bytes_received;

    new_socket = accept(my_socket, (struct sockaddr *)&my_socketAddress, (socklen_t *)&socket_address_length);

    while (true) {   

        // Accept a connection
        if (new_socket < 0) {
            std::ostringstream iss;
            iss << "Could not accept connection on port " << my_port << 
                " and IP address " << ip_address << std::endl;
        }

        log("Connection accepted. Waiting for message from client");

        // Receive a message from the client
        const int BUFFER_SIZE = 30720;

        char buffer[BUFFER_SIZE] = {0};
        bytes_received = read(new_socket, buffer, BUFFER_SIZE);

        if (bytes_received < 0) {
            error("Could not receive message from client");
        } else if (bytes_received == 0) {
            log("Client disconnected");
            break;
        }

        log("Message received from client");
        log("Message: " + std::string(buffer)); // Print the message

        std::string client_message = "";
        if (std::string(buffer) == "fetch") {
            client_message = FETCH;
        } else if (std::string(buffer) == "buy") {
            client_message = BUY;
        } else if (std::string(buffer) == "sell") {
            client_message = SELL;
        } else {
            client_message = "Invalid command";
        } 

        // Send a message back to the client
        int send_status = write(new_socket, client_message.c_str(), client_message.size());
        if (send_status < 0) {
            error("Could not send back message to client");
        }
        // close (new_socket);
    }

    close(new_socket);
    return;

}

void Server::accept_connection(int new_socket) {

}

void Server::close_server() {
    close(my_socket);
    close(new_socket);
    exit(0);
}
