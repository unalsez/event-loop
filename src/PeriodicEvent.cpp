#include "PeriodicEvent.hpp"

namespace event_handler
{
PeriodicEvent::PeriodicEvent(event_callback callback) : EventSource(callback) { resume(); };

void PeriodicEvent::resume()
{
    std::lock_guard<std::mutex> guard(mtx);
    src_type = source_type::PERIODIC_EVENT;
}
}  // namespace event_handler
