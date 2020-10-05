
cmake_minimum_required(VERSION 3.14)
project(os_lab_06)

set(CMAKE_CXX_STANDARD 17)

add_executable(terminal main.cpp)
add_executable(child child.cpp)
add_library(functions server.cpp server.h)

target_link_libraries(functions zmq)
target_link_libraries(terminal zmq functions)
target_link_libraries(child zmq functions)