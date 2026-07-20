#ifndef SERVER_H
#define SERVER_H

#include <string>
#include <cstdint>

#ifdef _WIN32
    #include <winsock2.h>
    #include <ws2tcpip.h>
    #pragma comment(lib, "Ws2_32.lib")
    #define close_socket closesocket
    #define INVALID_SOCKET_VAL INVALID_SOCKET
    using socket_t = SOCKET;
#else
    #include <sys/socket.h>
    #include <arpa/inet.h>
    #include <unistd.h>
    #define close_socket ::close
    #define INVALID_SOCKET_VAL -1
    using socket_t = int;
#endif

class Server {
public:
    explicit Server(uint16_t port);
    ~Server();

    void operator()();

private:
    uint16_t m_port;
    socket_t m_listenSocket;
    socket_t m_clientSocket;

    bool init();
    bool acceptConnection();
    bool receiveMessage(std::string& outMessage);
    void closeClient();
    void stop();
};

#endif // SERVER_H