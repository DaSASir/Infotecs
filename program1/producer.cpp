#include "Producer.h"
#include "../library/library.h"

#include <iostream>
#include <algorithm>

Producer::Producer(IBuffer& buffer) 
    : m_buffer(buffer) {}

bool Producer::isValidInput(const std::string& str) {
    if (str.empty() || str.length() > 64)
        return false;

    return std::all_of(str.begin(), str.end(), ::isdigit);
}

void Producer::operator()() {
    std::string input;
    std::cout << "Write ur string: ";
    while (true) {
        if (!std::getline(std::cin, input)) 
            break;

        if (input == "-") {
            m_buffer.push("-");
            break;
        }

        if (!isValidInput(input)) {
            std::cout << "ERROR." << std::endl;
            std::cout << "Write ur string: ";
            continue;
        }

        sortAndReplace(input);
        m_buffer.push(input);
    }
}