cmake_minimum_required(VERSION 3.17)
project(oskp)

set(CMAKE_CXX_STANDARD 17)


add_library(utility_lib lib.cpp)

add_executable(a a.cpp)
add_executable(b b.cpp)
add_executable(c c.cpp)


target_link_libraries(utility_lib zmq)
target_link_libraries(a zmq utility_lib)
target_link_libraries(b zmq utility_lib)
target_link_libraries(c zmq utility_lib pthread)
