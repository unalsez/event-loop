#include "TimeoutEvent.hpp"

namespace event_handler
{
TimeoutEvent::TimeoutEvent(const int64_t timeout_ms, event_callback callback)
    : EventSource(callback), timeout(timeout_ms)
{
    sync();
};

const TimeoutEvent::source_type TimeoutEvent::get_source_type() const { return source_type::TIMEOUT_EVENT; }

void TimeoutEvent::sync() { last_sync = std::chrono::system_clock::now(); }

const bool TimeoutEvent::is_timeout_reached()
{
    auto elapsed_time =
        std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - last_sync).count();

    return elapsed_time > timeout;
}
}  // namespace event_handler
