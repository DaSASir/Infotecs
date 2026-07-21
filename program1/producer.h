#ifndef PRODUCER_H
#define PRODUCER_H

#include "ibuffer.h"

class Producer {
public:
	Producer(IBuffer& buffer);
	void operator()();

private:
	bool isValidInput(const std::string& str) const;

private:
	IBuffer& m_buffer;
};

#endif // PRODUCER_H