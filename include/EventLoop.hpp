#pragma once

#include <memory>
#include <queue>
#include <mutex>

#include "EventSource.hpp"

namespace event_handler
{
class EventLoop
{
   public:
    EventLoop() = default;
    ~EventLoop() = default;

    bool add_event_source(std::shared_ptr<EventSource> source);
    void run(const int64_t freq_ms = 0);
    void stop();

   private:
    std::queue<std::shared_ptr<EventSource>> event_queue;
    std::mutex mtx;
};
}  // namespace event_handler
