cmake_minimum_required(VERSION 3.10)
project(FlanerCompiler)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)
include_directories(../global)

add_executable(FlanerCompiler main.cc exception.hh scanner.hh token.hh token.cc scanner.cc statement.hh statement.cc parser.hh parser.cc)
