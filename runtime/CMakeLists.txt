cmake_minimum_required(VERSION 3.10)
project(FlanerRuntime)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)
add_subdirectory(numeric)
add_subdirectory(concurrency)
