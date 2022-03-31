cmake_minimum_required(VERSION 3.0)
project(mavlink_sender)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_library(mavlink_sender STATIC src/mavlink_sender/MavlinkSender.cpp)

add_executable(main src/main.cpp)

target_compile_options(main PRIVATE -Wall -Wshadow)

target_link_libraries(main mavlink_sender)

install(TARGETS main DESTINATION ${PROJECT_SOURCE_DIR}/bin)