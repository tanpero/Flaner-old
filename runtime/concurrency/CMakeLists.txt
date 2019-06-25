cmake_minimum_required(VERSION 3.10)
project(flaner.concurrency)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)
include_directories(..)
include_directories(./detail)
include_directories(../../global)

#add_library(flaner.concurrency STATIC bigint.cc rational.cc)
add_executable(test-flaner.concurrency test-concurrency.cc)

