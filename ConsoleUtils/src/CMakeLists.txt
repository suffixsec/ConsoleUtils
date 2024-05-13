cmake_minimum_required(VERSION 3.10)
project(ConsoleUtils)

set(CMAKE_CXX_STANDARD 11)  # Set the C++ standard for the project

set(SOURCE_FILES console_utils.h)

if(WIN32)
    list(APPEND SOURCE_FILES sys/win.cpp)
else()
    list(APPEND SOURCE_FILES sys/unix.cpp)
endif()

add_library(ConsoleUtils STATIC ${SOURCE_FILES})

set_target_properties(ConsoleUtils PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

target_include_directories(ConsoleUtils PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})