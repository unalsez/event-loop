#include "PeriodicEvent.hpp"

namespace event_handler
{
PeriodicEvent::PeriodicEvent(event_callback callback) : EventSource(callback) { resume(); };

void PeriodicEvent::resume() { _type = source_type::PERIODIC_EVENT; }
}  // namespace event_handler
