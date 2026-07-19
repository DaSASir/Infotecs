#include "Buffer.h"

void Buffer::push(const std::string& data) {
    std::unique_lock<std::mutex> lock(m_mutex);
    m_bufferQueue.push(data);
    m_cv.notify_one();
}

std::string Buffer::pop() {
    std::unique_lock<std::mutex> lock(m_mutex);
    m_cv.wait(lock, 
        [this]() { 
            return !m_bufferQueue.empty(); 
        });

    std::string data = m_bufferQueue.front();
    m_bufferQueue.pop();
    return data;
}