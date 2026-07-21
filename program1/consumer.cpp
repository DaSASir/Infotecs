#include "consumer.h"
#include "../library/library.h"

#include <iostream>
#include <thread>
#include <chrono>

namespace {
#ifdef _WIN32
    constexpr socket_t INVALID_SOCKET_VAL = INVALID_SOCKET;
    inline void close_native_socket(socket_t s) { closesocket(s); }
#else
    constexpr socket_t INVALID_SOCKET_VAL = -1;
    inline void close_native_socket(socket_t s) { ::close(s); }
#endif
}

Consumer::Consumer(IBuffer& buffer, uint16_t port)
    : m_buffer(buffer),
    m_port(port),
    m_serverSocket(INVALID_SOCKET_VAL)
{
#ifdef _WIN32
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif
}

Consumer::~Consumer() {
    m_closeSocket();
#ifdef _WIN32
    WSACleanup();
#endif
}

void Consumer::m_closeSocket() {
    if (m_serverSocket != INVALID_SOCKET_VAL) {
        close_native_socket(m_serverSocket);
        m_serverSocket = INVALID_SOCKET_VAL;
    }
}

bool Consumer::m_connectToServer() {
    m_closeSocket();

    m_serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (m_serverSocket == INVALID_SOCKET_VAL) {
        return false;
    }

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(m_port);
    inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);

    if (connect(m_serverSocket, reinterpret_cast<struct sockaddr*>(&serverAddr), sizeof(serverAddr)) >= 0) {
        std::cout << std::endl << "Connected to Program2" << std::endl;
        return true;
    }

    m_closeSocket();
    return false;
}

void Consumer::operator()() {
    bool isConnected = m_connectToServer();

    while (true) {
        std::string data = m_buffer.pop();

        if (data == "-") 
            break;

        std::cout << "Get from buffer: " << data << std::endl;

        int sum = getSum(data);

        std::string message = std::to_string(sum) + "\n";

        if (!isConnected)
            isConnected = m_connectToServer();

        if (isConnected) {
            const int bytesSent = send(m_serverSocket, message.c_str(), static_cast<int>(message.length()), 0);

            if (bytesSent <= 0) {
                std::cerr << "Program2 disconnected" << std::endl;
                isConnected = false;
                m_closeSocket();
            }
            else
                std::cout << "Data go to Program2" << std::endl;
        }

        std::cout << std::endl << "Write ur string: ";
    }
}