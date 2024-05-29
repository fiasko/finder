cmake_minimum_required(VERSION 3.10)

# Set the project name
project(finder)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set the source files
file(GLOB SOURCES "src/*.cpp" "src/*.h")

# Add the executable
add_executable(finder ${SOURCES})

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/305e5a238b3c8d11266fbafd85520fb6b3184851.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  test_finder
  "test/test_argument_parser.cpp"
  "test/test_path_crawler.cpp"
  "src/PathCrawler.cpp"
  "test/test_content_finder.cpp")

target_link_libraries(
  test_finder
  GTest::gtest_main
  GTest::gmock_main
)

include(GoogleTest)
gtest_discover_tests(test_finder)

file(COPY "test/testdata" DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
