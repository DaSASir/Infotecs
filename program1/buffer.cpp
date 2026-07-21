#include "Buffer.h"

void Buffer::push(std::string& data) {
    std::unique_lock<std::mutex> lock(m_mutex);
    m_bufferQueue.push(std::move(data));
    m_cv.notify_one();
}

std::string Buffer::pop() {
    std::unique_lock<std::mutex> lock(m_mutex);
    m_cv.wait(lock, 
        [this]() { 
            return !m_bufferQueue.empty(); 
        });

    std::string data = std::move(m_bufferQueue.front());
    m_bufferQueue.pop();
    return data;
}