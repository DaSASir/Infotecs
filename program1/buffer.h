#ifndef BUFFER_H
#define BUFFER_H

#include "ibuffer.h"

#include <queue>
#include <mutex>
#include <condition_variable>

class Buffer : public IBuffer {
public:
    Buffer() = default;

    void push(std::string& data) override;
    std::string pop() override;

private:
    std::queue<std::string> m_bufferQueue;
    std::mutex m_mutex;
    std::condition_variable m_cv;
};

#endif // BUFFER_H