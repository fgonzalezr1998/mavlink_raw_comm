cmake_minimum_required(VERSION 3.0)
project(mavlink_raw_comm)

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

include_directories(include)

# Compile and link libraries

add_library(mavlink_encoder SHARED src/mavlink_encoder/MavlinkEncoder.cpp)
add_library(status_text_encoder SHARED src/status_text/StatusTextEncoder.cpp)

add_dependencies(mavlink_encoder status_text_encoder)

target_link_libraries(mavlink_encoder status_text_encoder)

# Compile and link main program

add_executable(main src/main.cpp)

target_compile_options(main PRIVATE -Wall -Wshadow)

target_link_libraries(main mavlink_encoder)

# Install main program and libraries

install(TARGETS main DESTINATION ${PROJECT_SOURCE_DIR}/bin)

install(TARGETS mavlink_encoder DESTINATION ${PROJECT_SOURCE_DIR}/lib)
install(TARGETS status_text_encoder DESTINATION ${PROJECT_SOURCE_DIR}/lib)

# Compile test unit

add_executable(trial_test tests/trial_test.cpp)

# Run the test
add_test(trial_test trial_test)
enable_testing()