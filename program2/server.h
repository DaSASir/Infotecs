#ifndef SERVER_H
#define SERVER_H

#include "idataprocessor.h"

#include <string>
#include <cstdint>

#ifdef _WIN32
    #include <winsock2.h>
    #include <ws2tcpip.h>
    #pragma comment(lib, "Ws2_32.lib")
    using socket_t = SOCKET;
#else
    #include <sys/socket.h>
    #include <arpa/inet.h>
    #include <unistd.h>
    using socket_t = int;
#endif

class Server {
public:
    explicit Server(uint16_t port, IDataProcessor& processor);
    ~Server();

    void operator()();

private:
    bool m_initServer();
    bool m_acceptClient();
    bool m_readLine(std::string& outMessage);
    void m_closeClientSocket();
    void m_cleanupSockets();

private:
    const uint16_t m_port;
    socket_t m_listenSocket;
    socket_t m_clientSocket;
    IDataProcessor& m_processor;
};

#endif // SERVER_H