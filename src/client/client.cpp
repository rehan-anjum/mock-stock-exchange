#include <iostream>
#include <sys/socket.h>
#include <string>
#include <cstring>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "client.h"


TCPClient::TCPClient(std::string ip, int port) : m_ip(ip), m_port(port) {

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(m_port);
    server_addr.sin_addr.s_addr = inet_addr(ip.c_str());

    std::cout << "Client created with IP: " << m_ip << " and port: " << m_port << std::endl;

}

void TCPClient::startClient() {
    m_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (m_socket < 0) {
        std::cerr << "Error creating socket" << std::endl;
        return;
    }

    int socket_connect = connect(m_socket, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if (socket_connect < 0) {
        std::cerr << "Error connecting to socket" << std::endl;
        return;
    }

    m_connected = true;
    std::cout << "Created socket successfully!" << std::endl;

}

void TCPClient::closeClient() {
    close(m_socket);
    std::cout << "Socket closed successfully!" << std::endl;
    exit(0);
}

void TCPClient::sendMessage(std::string message) {
    if (!m_connected) {
        std::cerr << "Client not connected" << std::endl;
        return;
    }

    int send_status = write(m_socket, message.c_str(), message.size());
    if (send_status < 0) {
        std::cerr << "Error sending message" << std::endl;
        return;
    }

    std::cout << "Message sent successfully!" << std::endl;

}

void TCPClient::receiveMessage() {
    if (!m_connected) {
        std::cerr << "Client not connected" << std::endl;
        return;
    }

    char buffer[1024] = {0};
    int read_status = read(m_socket, buffer, 1024);
    if (read_status < 0) {
        std::cerr << "Error reading message" << std::endl;
        return;
    }

    std::cout << "Message received: " << buffer << std::endl;

}

void TCPClient::connectToServer(std::string ip, int port) {
    int connection_status = connect(m_socket, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if (connection_status < 0) {
        std::cerr << "Error connecting to server" << std::endl;
        return;
    }

    m_connected = true;
    std::cout << "Connected to server successfully!" << std::endl;
}

bool TCPClient::isConnected() {
    return m_connected;
}

TCPClient::~TCPClient() {
    closeClient();
}


        
