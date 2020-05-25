#include "EventSource.hpp"

namespace event_handler
{
const EventSource::source_type EventSource::get_source_type() const { return _type; }

void EventSource::resume() { _type = source_type::UKNOWN_EVENT; }
void EventSource::suspend() { _type = source_type::STOPPED_EVENT; }
void EventSource::remove() { _type = source_type::REMOVED_EVENT; }
}  // namespace event_handler
