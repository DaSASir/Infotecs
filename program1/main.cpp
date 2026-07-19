#include "Buffer.h"
#include "Producer.h"
#include "Consumer.h"

#include <thread>   

int main() {

    Buffer buffer;
    Consumer consumer(buffer);
    Producer producer(buffer);

    std::thread consumerThread(std::ref(consumer));

    producer();
    consumerThread.join();

    return 0;
}