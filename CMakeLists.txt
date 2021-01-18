cmake_minimum_required(VERSION 3.17)
project(RRPC)
set(DCMAKE_EXPORT_COMPILE_COMMANDS 1)
add_definitions(-DASIO_STANDALONE)
find_package(Libevent)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_STANDARD 17)
ADD_EXECUTABLE(main basic.cpp basic.h try.cpp call.h)
