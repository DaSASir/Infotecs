#ifndef I_DATA_PROCESSOR_H
#define I_DATA_PROCESSOR_H

#include <string>

class IDataProcessor {
public:
    virtual ~IDataProcessor() = default;

    virtual void process(const std::string& data) const = 0;
};

#endif // I_DATA_PROCESSOR_H