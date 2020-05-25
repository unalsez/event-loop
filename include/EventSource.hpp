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
        STOPPED_EVENT,
        REMOVED_EVENT,
        PERIODIC_EVENT,
        PERIODIC_TIMEOUT_EVENT,
        TIMEOUT_EVENT,
    };

    EventSource(event_callback callback) : callback(callback){};
    virtual ~EventSource() = default;

    virtual const source_type get_source_type() const;
    virtual void resume();
    void suspend();
    void remove();

    event_callback callback;
    source_type _type{source_type::UKNOWN_EVENT};
};
}  // namespace event_handler
