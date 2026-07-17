#include "Consumer.h"

Consumer::Consumer(IBuffer& buffer) : m_buffer(buffer) {}

void Consumer::operator()() {
    while (true) {
        std::string data = m_buffer.pop();

        if (data == "exit") {
            break;
        }

        std::cout << "From buffer: " << data << std::endl;
    }
}