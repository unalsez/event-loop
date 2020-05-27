#include <gtest/gtest.h>

#include <mutex>
#include <thread>

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

TEST(eventloop, suspend_resume_remove)
{
    const int64_t timeout_ms = 50;
    std::mutex _mutex;

    std::chrono::system_clock::time_point event_time;
    auto periodic_timeout_source = std::make_shared<event_handler::PeriodicTimeoutEvent>(timeout_ms, [&]() {
        std::lock_guard<std::mutex> guard(_mutex);
        event_time = std::chrono::system_clock::now();
    });

    event_handler::EventLoop loop;
    ASSERT_TRUE(loop.add_event_source(periodic_timeout_source));

    std::thread loop_run(&event_handler::EventLoop::run, std::ref(loop), 0);

    for (auto i = 0; i < 5; ++i)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(timeout_ms * 3));
        std::lock_guard<std::mutex> guard(_mutex);
        auto elapsed_time =
            std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - event_time)
                .count();
        ASSERT_LE(elapsed_time, timeout_ms);
    }

    {
        periodic_timeout_source->suspend();
        std::this_thread::sleep_for(std::chrono::milliseconds(timeout_ms * 3));
        std::lock_guard<std::mutex> guard(_mutex);
        auto elapsed_time =
            std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - event_time)
                .count();
        ASSERT_GE(elapsed_time, timeout_ms * 3);
    }

    periodic_timeout_source->resume();
    for (auto i = 0; i < 5; ++i)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(timeout_ms * 3));
        std::lock_guard<std::mutex> guard(_mutex);
        auto elapsed_time =
            std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - event_time)
                .count();
        ASSERT_LE(elapsed_time, timeout_ms);
    }

    periodic_timeout_source->remove();

    loop_run.join();
}

TEST(eventloop, stop_loop)
{
    const int64_t timeout_ms = 100;
    std::mutex _mutex;
    uint32_t counter = 0;

    auto periodic_timeout_source = std::make_shared<event_handler::PeriodicTimeoutEvent>(timeout_ms, [&]() {
        std::lock_guard<std::mutex> guard(_mutex);
        std::cout << "From periodic_timeout_source: " << ++counter << std::endl;
    });

    event_handler::EventLoop loop;
    ASSERT_TRUE(loop.add_event_source(periodic_timeout_source));

    std::thread loop_run(&event_handler::EventLoop::run, std::ref(loop), 0);

    while (true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
        std::lock_guard<std::mutex> guard(_mutex);
        if (counter >= 5)
        {
            loop.stop();
            break;
        }
    }

    ASSERT_LE(counter, 6);
    loop_run.join();
}