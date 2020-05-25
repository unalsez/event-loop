#include <gtest/gtest.h>

#include "EventLoop.hpp"
#include "PeriodicEvent.hpp"
#include "PeriodicTimeoutEvent.hpp"
#include "TimeoutEvent.hpp"

TEST(eventloop, add_source)
{
    auto base_source = std::make_shared<event_handler::EventSource>([]() {});
    auto periodic_source = std::make_shared<event_handler::PeriodicEvent>([]() {});
    auto periodic_timeout_source = std::make_shared<event_handler::PeriodicTimeoutEvent>(1'000, []() {});
    auto timeout_source = std::make_shared<event_handler::TimeoutEvent>(1'000, []() {});

    event_handler::EventLoop loop;

    ASSERT_FALSE(loop.add_event_source(base_source));
    ASSERT_TRUE(loop.add_event_source(periodic_source));
    ASSERT_TRUE(loop.add_event_source(periodic_timeout_source));
    ASSERT_TRUE(loop.add_event_source(timeout_source));
}

TEST(eventloop, timeout_event)
{
    const int64_t timeout_ms = 2'000;
    const int64_t time_delta_ms = 50;

    std::chrono::system_clock::time_point event_time;
    auto timeout_source = std::make_shared<event_handler::TimeoutEvent>(
        timeout_ms, [&event_time]() { event_time = std::chrono::system_clock::now(); });

    event_handler::EventLoop loop;
    ASSERT_TRUE(loop.add_event_source(timeout_source));

    auto before_run = std::chrono::system_clock::now();
    loop.run();
    auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(event_time - before_run).count();

    ASSERT_LE(elapsed_time, timeout_ms + time_delta_ms);
    ASSERT_GE(elapsed_time, timeout_ms);
}
