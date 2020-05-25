#pragma once

#include <functional>

namespace event_handler
{
using event_callback = std::function<void(void)>;

class EventSource
{
   public:
    enum class source_type
    {
        UKNOWN_EVENT,
        PERIODIC_EVENT,
        PERIODIC_TIMEOUT_EVENT,
        TIMEOUT_EVENT,
    };

    EventSource(event_callback callback) : callback(callback){};
    virtual ~EventSource() = default;

    virtual const source_type get_source_type() const;

    event_callback callback;
};
}  // namespace event_handler
