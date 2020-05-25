#pragma once

#include "TimeoutEvent.hpp"

namespace event_handler
{
class PeriodicTimeoutEvent : public TimeoutEvent
{
   public:
    PeriodicTimeoutEvent(const int64_t timeout_ms, event_callback callback) : TimeoutEvent(timeout_ms, callback){};
    virtual ~PeriodicTimeoutEvent() = default;

    const source_type get_source_type() const override;
};
}  // namespace event_handler
