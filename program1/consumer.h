#ifndef CONSUMER_H
#define CONSUMER_H

#include "ibuffer.h"
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

class Consumer {
public:
    explicit Consumer(IBuffer& buffer, uint16_t port = 8080);
    ~Consumer();

    void operator()();

private:
    bool m_connectToServer();
    void m_closeSocket();

private:
    IBuffer& m_buffer;
    const uint16_t m_port;
    socket_t m_serverSocket;
};

#endif // CONSUMER_H