#ifndef CLIENT_H
#define CLIENT_H

#include <cstring> 
#include <iostream> 
#include <netinet/in.h> 
#include <sys/socket.h> 
#include <unistd.h> 
  
class Client { 
    private:
        std::string m_ip;
        int m_port;
        int m_socket;
        struct sockaddr_in server_addr;
        bool m_connected;

    public:
        Client(std::string ip, int port);
        void start_client();
        void close_client();
        void connect_to_server(std::string ip, int port);
        void send_message(std::string message);
        void receive_message();
        bool is_connected();
        ~Client(); 

};

#endif