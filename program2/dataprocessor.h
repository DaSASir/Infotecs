#ifndef MAIN_DATA_PROCESSOR_H
#define MAIN_DATA_PROCESSOR_H

#include "idataprocessor.h"

class DataProcessor : public IDataProcessor {
public:
    void process(const std::string& data) const override;
};

#endif // MAIN_DATA_PROCESSOR_H