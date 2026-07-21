#include "dataprocessor.h"
#include "../library/library.h"

#include <iostream>

void DataProcessor::process(const std::string& data) const {
    const bool isValid = analyseOfSymbols(data);

    if (isValid)
        std::cout << "(SUCCESS) Sum: " << data << std::endl;
    else
        std::cout << "(ERROR) Sum: " << data << std::endl;
}