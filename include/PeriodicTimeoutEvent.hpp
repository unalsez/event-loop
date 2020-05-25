#pragma once

#include "TimeoutEvent.hpp"

namespace event_handler
{
class PeriodicTimeoutEvent : public TimeoutEvent
{
   public:
    PeriodicTimeoutEvent(const int64_t timeout_ms, event_callback callback);
    virtual ~PeriodicTimeoutEvent() = default;

    void resume() override;
};
}  // namespace event_handler
