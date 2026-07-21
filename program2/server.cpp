#include "Server.h"
#include "../library/library.h"

#include <iostream>
#include <thread>
#include <chrono>

Server::Server(uint16_t port)
    : m_port(port), 
    m_listenSocket(INVALID_SOCKET_VAL), 
    m_clientSocket(INVALID_SOCKET_VAL) {
#ifdef _WIN32
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);
#endif
}

Server::~Server() {
    stop();
#ifdef _WIN32
    WSACleanup();
#endif
}

bool Server::init() {
    m_listenSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (m_listenSocket == INVALID_SOCKET_VAL) 
        return false;

    int opt = 1;

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

    if (listen(m_listenSocket, 3) < 0) 
        return false;

    return true;
}

bool Server::acceptConnection() {
    closeClient();
    sockaddr_in clientAddr{};

#ifdef _WIN32
    int addrLen = sizeof(clientAddr);
    m_clientSocket = accept(m_listenSocket, reinterpret_cast<struct sockaddr*>(&clientAddr), &addrLen);
#else
    socklen_t linuxAddrLen = sizeof(clientAddr);
    m_clientSocket = accept(m_listenSocket, reinterpret_cast<struct sockaddr*>(&clientAddr), &linuxAddrLen);
#endif

    return m_clientSocket != INVALID_SOCKET_VAL;
}

bool Server::receiveMessage(std::string& outMessage) {
    outMessage.clear();
    char buffer[1];
    while (true) {
        int bytesRead = recv(m_clientSocket, buffer, 1, 0);
        if (bytesRead <= 0) return false;
        if (buffer[0] == '\n') break;
        if (buffer[0] != '\r') outMessage += buffer[0];
    }
    return true;
}

void Server::operator()() {
    if (!init()) 
        return;

    while (true) {
        std::cout << "Waiting program1..." << std::endl;

        if (!acceptConnection()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            continue;
        }

        std::cout << "Program1 connected" << std::endl;
        std::string receivedData;

        while (receiveMessage(receivedData))
            if (analyseOfSymbols(receivedData))
                std::cout << "Good function3:" << receivedData << std::endl;
            else
                std::cout << "Error function3:" << receivedData << std::endl;

        std::cout << "Disconnected. Wait..." << std::endl;
        closeClient();
    }
}

void Server::closeClient() {
    if (m_clientSocket != INVALID_SOCKET_VAL) {
        close_socket(m_clientSocket);
        m_clientSocket = INVALID_SOCKET_VAL;
    }
}

void Server::stop() {
    closeClient();
    if (m_listenSocket != INVALID_SOCKET_VAL) {
        close_socket(m_listenSocket);
        m_listenSocket = INVALID_SOCKET_VAL;
    }
}