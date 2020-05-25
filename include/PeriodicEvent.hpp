#pragma once

#include "EventSource.hpp"

namespace event_handler
{
class PeriodicEvent : public EventSource
{
   public:
    PeriodicEvent(event_callback callback);
    virtual ~PeriodicEvent() = default;

    void resume() override;
};
}  // namespace event_handler
