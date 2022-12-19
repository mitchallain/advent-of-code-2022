cmake_minimum_required(VERSION 3.10)
project(Day10)

set(CMAKE_BUILD_TYPE RelWithDebInfo)
set(CMAKE_CXX_FLAGS
    "${CMAKE_CXX_FLAGS} -Wfatal-errors -Wall -Wshadow -Wextra -Wpedantic -fPIC"
    CACHE STRING "Set C++ Compiler Flags" FORCE)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(${PROJECT_NAME} main.cc)
set_target_properties(
  ${PROJECT_NAME}
  PROPERTIES CXX_STANDARD 17
             CXX_STANDARD_REQUIRED TRUE
             CXX_EXTENSIONS FALSE)

# target_compile_definitions(${PROJECT_NAME} PRIVATE)
