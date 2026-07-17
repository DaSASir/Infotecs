#ifndef CONSUMER_H
#define CONSUMER_H

#include "IBuffer.h"

class Consumer {
public:
	Consumer(IBuffer& buffer);
	void operator()();

private:
	IBuffer& m_buffer;
};

#endif // CONSUMER_H