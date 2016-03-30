cmake_minimum_required(VERSION 2.8)
project(multicast_ip_serverd)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(multicast_ip_serverd ${SOURCE_FILES})