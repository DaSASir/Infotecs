#include "Producer.h"

Producer::Producer(IBuffer& buffer) : m_buffer(buffer) {}

bool Producer::isValidInput(const std::string& str) {
    if (str.empty() || str.length() > 64) {
        return false;
    }
    return std::all_of(str.begin(), str.end(), ::isdigit);
}

void Producer::operator()() {
    std::string input;
    while (true) {
        std::cout << "Write ur string: ";
        std::cin >> input;

        if (input == "exit") {
            m_buffer.push("exit");
            break;
        }

        if (!isValidInput(input)) {
            std::cout << "ERROR.\n";
            continue;
        }

        sortAndReplace(input);
        m_buffer.push(input);
    }
}