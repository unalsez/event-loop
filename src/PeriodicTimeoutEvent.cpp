#include "PeriodicTimeoutEvent.hpp"

namespace event_handler
{
PeriodicTimeoutEvent::PeriodicTimeoutEvent(const int64_t timeout_ms, event_callback callback)
    : TimeoutEvent(timeout_ms, callback)
{
    resume();
}

void PeriodicTimeoutEvent::resume()
{
    std::lock_guard<std::mutex> guard(mtx);
    src_type = source_type::PERIODIC_TIMEOUT_EVENT;
}

}  // namespace event_handler
