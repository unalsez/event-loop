cmake_minimum_required(VERSION 3.7.2)

set(PROJECT_NAME "C++ Simple Event Loop")
set(PROJECT_TARGET "event_loop")
set(PROJECT_DESCRIPTION "C++ Simple Event Loop")
set(PROJECT_VERSION 0.0.1)

project(${PROJECT_TARGET}
        VERSION ${PROJECT_VERSION}
        LANGUAGES CXX)

add_library(${PROJECT_TARGET} SHARED
        src/EventLoop.cpp
        src/EventSource.cpp
        src/PeriodicEvent.cpp
        src/PeriodicTimeoutEvent.cpp
        src/TimeoutEvent.cpp
)

set_target_properties(
  ${PROJECT_TARGET}
PROPERTIES
  FRAMEWORK ON
  SOVERSION ${PROJECT_VERSION_MAJOR}
  VERSION ${PROJECT_VERSION}
  PUBLIC_HEADER "${HEADER_FILES}"
  PRIVATE_HEADER "${PRIVATE_HEADER_FILES}"
  ARCHIVE_OUTPUT_DIRECTORY "lib"
  LIBRARY_OUTPUT_DIRECTORY "lib"
)

option(BUILD_TESTS "Specify whether tests will be compiled" ON)

target_compile_options(${PROJECT_TARGET} PRIVATE -Wall -Werror)

if(NOT (CMAKE_VERSION LESS 3.8))
    target_compile_features(${PROJECT_TARGET} PRIVATE cxx_std_14)
else()
    set_target_properties(${PROJECT_TARGET} PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
    )
endif()

target_include_directories(${PROJECT_TARGET}
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
)


target_link_libraries(${PROJECT_TARGET}
    PUBLIC
        ""
    PRIVATE
        ""
)

set(CMAKE_INSTALL_PREFIX "/usr/")
install(TARGETS ${PROJECT_TARGET}
    LIBRARY DESTINATION lib)

install(
    DIRECTORY ${CMAKE_SOURCE_DIR}/include/
    DESTINATION include/EventLoop
    FILES_MATCHING PATTERN "*.h*")

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
