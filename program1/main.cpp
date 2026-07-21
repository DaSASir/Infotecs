#include "buffer.h"
#include "producer.h"
#include "consumer.h"

int main() {

    Buffer buffer;
    Consumer consumer(buffer);
    Producer producer(buffer);

    std::thread consumerThread(std::ref(consumer));

    producer();
    consumerThread.join();

    return 0;
}