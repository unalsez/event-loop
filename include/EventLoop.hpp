#pragma once

#include <memory>
#include <queue>

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

   private:
    std::queue<std::shared_ptr<EventSource>> event_queue;
};
}  // namespace event_handler
