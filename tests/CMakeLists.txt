find_package(GTest REQUIRED)

set(TEST_TARGET "test_event_loop")

add_executable(${TEST_TARGET}
                    test_EventLoop.cpp
)

target_include_directories(${TEST_TARGET}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
    PRIVATE
        ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(${TEST_TARGET}
    PUBLIC
        ""
    PRIVATE
        ${GTEST_LIBRARIES}
        ${GTEST_MAIN_LIBRARIES}
        event_loop
        pthread
)
