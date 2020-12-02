project(cmake_template)
cmake_minimum_required(VERSION 3.1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(EXECUTABLE_OUTPUT_PATH "/app/bin")

enable_testing()

add_subdirectory(src)
