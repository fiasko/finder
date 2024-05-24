cmake_minimum_required(VERSION 3.10)

# Set the project name
project(finder)


# Set the source files
file(GLOB SOURCES "src/*.cpp")

# Add the executable
add_executable(finder ${SOURCES})