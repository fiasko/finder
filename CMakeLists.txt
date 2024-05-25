cmake_minimum_required(VERSION 3.10)

# Set the project name
project(finder)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set the source files
file(GLOB SOURCES "src/*.cpp" "src/*.h")

# Add the executable
add_executable(finder ${SOURCES})