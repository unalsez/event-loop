#include "PeriodicEvent.hpp"

namespace event_handler
{
const PeriodicEvent::source_type PeriodicEvent::get_source_type() const { return source_type::PERIODIC_EVENT; }
}  // namespace event_handler
