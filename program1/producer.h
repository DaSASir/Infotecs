#ifndef PRODUCER_H
#define PRODUCER_H

#include "IBuffer.h"

class Producer {
public:
	Producer(IBuffer& buffer);
	void operator()();

private:
	bool isValidInput(const std::string& str);

private:
	IBuffer& m_buffer;
};

#endif // PRODUCER_H