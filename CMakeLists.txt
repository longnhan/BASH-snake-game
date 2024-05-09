cmake_minimum_required(VERSION 3.10)
project(snake C)

# Add the executable terget
add_executable(snake snake.c)

# Include the header files directory
target_include_directories(snake PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})