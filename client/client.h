#include <cstring> 
#include <iostream> 
#include <netinet/in.h> 
#include <sys/socket.h> 
#include <unistd.h> 
  
class TCPClient { 
    private:
        std::string m_ip;
        int m_port;
        int m_socket;
        struct sockaddr_in server_addr;
        bool m_connected;

    public:
        TCPClient(std::string ip, int port);
        void startClient();
        void closeClient();
        void connectToServer(std::string ip, int port);
        void sendMessage(std::string message);
        void receiveMessage();
        bool isConnected();
        ~TCPClient(); 

};
