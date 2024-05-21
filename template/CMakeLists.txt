cmake_minimum_required(VERSION 3.10)

# Find the source file in the src directory
file(GLOB SRC_FILES src/*)
get_filename_component(PROJECT_NAME ${SRC_FILES} NAME_WE)

# Set the project name
project(${PROJECT_NAME})

# Add the executable
add_executable(${PROJECT_NAME} ${SRC_FILES})