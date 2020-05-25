#include "EventLoop.hpp"

#include <chrono>
#include <memory>
#include <thread>

#include "PeriodicTimeoutEvent.hpp"

namespace event_handler
{
bool EventLoop::add_event_source(std::shared_ptr<EventSource> source)
{
    if (source->get_source_type() != EventSource::source_type::UKNOWN_EVENT)
    {
        event_queue.emplace(source);
        return true;
    }
    else
    {
        return false;
    }
}

void EventLoop::run(const int64_t freq_ms)
{
    while (!event_queue.empty())
    {
        auto source = event_queue.front();
        event_queue.pop();

        switch (source->get_source_type())
        {
            case EventSource::source_type::PERIODIC_EVENT:
            {
                source->callback();
                event_queue.emplace(source);
                break;
            }

            case EventSource::source_type::PERIODIC_TIMEOUT_EVENT:
            {
                auto periodic_timeout_source = std::dynamic_pointer_cast<PeriodicTimeoutEvent>(source);
                if (periodic_timeout_source->is_timeout_reached())
                {
                    periodic_timeout_source->callback();
                    periodic_timeout_source->sync();
                }
                event_queue.emplace(source);
                break;
            }

            case EventSource::source_type::TIMEOUT_EVENT:
            {
                auto timeout_source = std::dynamic_pointer_cast<TimeoutEvent>(source);
                if (timeout_source->is_timeout_reached())
                {
                    timeout_source->callback();
                }
                else
                {
                    event_queue.emplace(source);
                }
                break;
            }

            default:
            {
                break;
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(freq_ms));
    }
}
}  // namespace event_handler
