#pragma once

#include <functional>
#include <mutex>

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

    const source_type get_source_type();
    virtual void resume();
    void suspend();
    void remove();

    event_callback callback;
    source_type src_type{source_type::UKNOWN_EVENT};
    std::mutex mtx;
};
}  // namespace event_handler
