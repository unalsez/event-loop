#include "PeriodicTimeoutEvent.hpp"

namespace event_handler
{
const PeriodicTimeoutEvent::source_type PeriodicTimeoutEvent::get_source_type() const
{
    return source_type::PERIODIC_TIMEOUT_EVENT;
}
}  // namespace event_handler
