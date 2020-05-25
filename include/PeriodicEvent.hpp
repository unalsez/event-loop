#pragma once

#include "EventSource.hpp"

namespace event_handler
{
class PeriodicEvent : public EventSource
{
   public:
    PeriodicEvent(event_callback callback) : EventSource(callback){};
    virtual ~PeriodicEvent() = default;

    const source_type get_source_type() const override;
};
}  // namespace event_handler
