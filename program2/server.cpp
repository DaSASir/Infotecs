#include "server.h"

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

Server::Server(uint16_t port, IDataProcessor& processor)
    : m_port(port),
    m_listenSocket(INVALID_SOCKET_VAL),
    m_clientSocket(INVALID_SOCKET_VAL),
    m_processor(processor)
{
#ifdef _WIN32
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif
}

Server::~Server() {
    m_cleanupSockets();
#ifdef _WIN32
    WSACleanup();
#endif
}

bool Server::m_initServer() {
    m_listenSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (m_listenSocket == INVALID_SOCKET_VAL)
        return false;

    const int opt = 1;

#ifdef _WIN32
    setsockopt(m_listenSocket, SOL_SOCKET, SO_REUSEADDR, reinterpret_cast<const char*>(&opt), sizeof(opt));
#else
    setsockopt(m_listenSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
#endif

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(m_port);

    if (bind(m_listenSocket, reinterpret_cast<struct sockaddr*>(&serverAddr), sizeof(serverAddr)) < 0)
        return false;

    if (listen(m_listenSocket, 5) < 0)
        return false;

    return true;
}

bool Server::m_acceptClient() {
    m_closeClientSocket();
    sockaddr_in clientAddr{};

#ifdef _WIN32
    int addrLen = sizeof(clientAddr);
    m_clientSocket = accept(m_listenSocket, reinterpret_cast<struct sockaddr*>(&clientAddr), &addrLen);
#else
    socklen_t addrLen = sizeof(clientAddr);
    m_clientSocket = accept(m_listenSocket, reinterpret_cast<struct sockaddr*>(&clientAddr), &addrLen);
#endif

    return m_clientSocket != INVALID_SOCKET_VAL;
}

bool Server::m_readLine(std::string& outMessage) {
    outMessage.clear();
    char ch;

    while (true) {
        int bytesRead = recv(m_clientSocket, &ch, 1, 0);

        if (bytesRead <= 0)
            return false;
        if (ch == '\n')
            break;
        if (ch != '\r')
            outMessage += ch;
    }
    return true;
}

void Server::operator()() {
    if (!m_initServer())
        return;

    while (true) {
        std::cout << "Wait program1..." << std::endl;

        if (!m_acceptClient()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            continue;
        }

        std::cout << std::endl << "Program1 connected" << std::endl;
        std::string receivedData;

        while (m_readLine(receivedData))
            m_processor.process(receivedData);

        std::cout << std::endl << "Program1 disconnected" << std::endl;
        m_closeClientSocket();
    }
}

void Server::m_closeClientSocket() {
    if (m_clientSocket != INVALID_SOCKET_VAL) {
        close_native_socket(m_clientSocket);
        m_clientSocket = INVALID_SOCKET_VAL;
    }
}

void Server::m_cleanupSockets() {
    m_closeClientSocket();
    if (m_listenSocket != INVALID_SOCKET_VAL) {
        close_native_socket(m_listenSocket);
        m_listenSocket = INVALID_SOCKET_VAL;
    }
}