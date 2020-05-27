#include "EventSource.hpp"

namespace event_handler
{
const EventSource::source_type EventSource::get_source_type()
{
    std::lock_guard<std::mutex> guard(mtx);
    return src_type;
}

void EventSource::resume()
{
    std::lock_guard<std::mutex> guard(mtx);
    src_type = source_type::UKNOWN_EVENT;
}

void EventSource::suspend()
{
    std::lock_guard<std::mutex> guard(mtx);
    src_type = source_type::STOPPED_EVENT;
}

void EventSource::remove()
{
    std::lock_guard<std::mutex> guard(mtx);
    src_type = source_type::REMOVED_EVENT;
}
}  // namespace event_handler
