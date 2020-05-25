#include "EventSource.hpp"

namespace event_handler
{
const EventSource::source_type EventSource::get_source_type() const { return source_type::UKNOWN_EVENT; }
}  // namespace event_handler
