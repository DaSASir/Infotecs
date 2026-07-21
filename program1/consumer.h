#ifndef CONSUMER_H
#define CONSUMER_H

#include "IBuffer.h"

#ifdef _WIN32
    #include <winsock2.h>
    using socket_t = SOCKET;
#else
    using socket_t = int;
#endif

class Consumer {
public:
    Consumer(IBuffer& buffer);
    ~Consumer();
    void operator()();

private:
    bool connectToServer();

private:
    IBuffer& m_buffer;
    socket_t m_serverSocket;
};

#endif // CONSUMER_H