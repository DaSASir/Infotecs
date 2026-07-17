#include "Buffer.h"
#include "Producer.h"
#include "Consumer.h"

int main() {

    Buffer buffer;
    Consumer consumer(buffer);
    Producer producer(buffer);

    std::thread producerThread(std::ref(producer));
    std::thread consumerThread(std::ref(consumer));

    producerThread.join();
    consumerThread.join();

    return 0;
}