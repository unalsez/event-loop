#pragma once

#include <chrono>

#include "EventSource.hpp"

namespace event_handler
{
class TimeoutEvent : public EventSource
{
   public:
    TimeoutEvent(const int64_t timeout_ms, event_callback callback);
    virtual ~TimeoutEvent() = default;

    const source_type get_source_type() const override;
    void sync();
    const bool is_timeout_reached();

   private:
    std::chrono::milliseconds::rep timeout;
    std::chrono::system_clock::time_point last_sync;
};
}  // namespace event_handler
