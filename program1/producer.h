#ifndef PRODUCER_H
#define PRODUCER_H

#include "IBuffer.h"
#include "../../../library/library.h"

class Producer {
public:
	Producer(IBuffer& buffer);
	void operator()();

private:
	IBuffer& m_buffer;

	bool isValidInput(const std::string& str);
};

#endif // PRODUCER_H