cmake_minimum_required(VERSION 3.0)
project(mavlink_sender)

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

include_directories(include)

add_library(mavlink_encoder STATIC src/mavlink_encoder/MavlinkEncoder.cpp)
add_library(status_text_encoder STATIC src/status_text/StatusTextEncoder.cpp)

add_dependencies(mavlink_encoder status_text_encoder)

target_link_libraries(mavlink_encoder status_text_encoder)

add_executable(main src/main.cpp)

target_compile_options(main PRIVATE -Wall -Wshadow)

target_link_libraries(main mavlink_encoder)

install(TARGETS main DESTINATION ${PROJECT_SOURCE_DIR}/bin)