cmake_minimum_required(VERSION 3.0)
project(mavlink_raw_comm)

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

include_directories(
	include
	tests
)

# Compile and link libraries

add_library(mavlink_encoder STATIC src/mavlink_encoder/MavlinkEncoder.cpp)
add_library(status_text_encoder STATIC src/status_text/StatusTextEncoder.cpp)

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

add_executable(statustext_encoder_test 
	tests/status_text/statustext_encoder_test.cpp)
target_link_libraries(statustext_encoder_test 
	status_text_encoder)

add_executable(mavlink_encoder_test 
	tests/mavlink_encoder/mavlink_encoder_test.cpp)
target_link_libraries(mavlink_encoder_test 
mavlink_encoder)

# Run the test
add_test(trial_test trial_test)
add_test(statustext_encoder_test statustext_encoder_test)
add_test(mavlink_encoder_test statustext_encoder_test)
enable_testing()