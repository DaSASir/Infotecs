#include "Consumer.h"
#include "../../library/library.h"

#include <iostream>
#include <thread>
#include <chrono>

#ifdef _WIN32
    #include <ws2tcpip.h>
    #pragma comment(lib, "Ws2_32.lib")
    #define close_socket closesocket
    #define INVALID_SOCKET_VAL INVALID_SOCKET
#else
    #include <sys/socket.h>
    #include <arpa/inet.h>
    #include <unistd.h>
    #define close_socket ::close
    #define INVALID_SOCKET_VAL -1
#endif

Consumer::Consumer(IBuffer& buffer)
    : m_buffer(buffer), m_serverSocket(INVALID_SOCKET_VAL) {
#ifdef _WIN32
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);
#endif
}

Consumer::~Consumer() {
    if (m_serverSocket != INVALID_SOCKET_VAL) {
        close_socket(m_serverSocket);
    }
#ifdef _WIN32
    WSACleanup();
#endif
}

bool Consumer::connectToServer() {
    if (m_serverSocket != INVALID_SOCKET_VAL) {
        close_socket(m_serverSocket);
        m_serverSocket = INVALID_SOCKET_VAL;
    }

    m_serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (m_serverSocket == INVALID_SOCKET_VAL) {
        return false;
    }

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);

    if (connect(m_serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) >= 0) {
        std::cout << "Connected to Program2" << std::endl;
        return true;
    }

    close_socket(m_serverSocket);
    m_serverSocket = INVALID_SOCKET_VAL;
    return false;
}

void Consumer::operator()() {
    bool isConnected = connectToServer();

    while (true) {
        std::string data = m_buffer.pop();

        if (data == "-") break;

        std::cout << "\nGet from buffer: " << data << std::endl;

        int sum = getSum(data);

        std::string message = std::to_string(sum) + "\n";

        if (!isConnected) {
            isConnected = connectToServer();
        }

        if (isConnected) {
            int bytesSent = send(m_serverSocket, message.c_str(), static_cast<int>(message.length()), 0);

            if (bytesSent <= 0) {
                isConnected = false;
                close_socket(m_serverSocket);
                m_serverSocket = INVALID_SOCKET_VAL;
            }
        }

        std::cout << "Write ur string: ";
    }
}