cmake_minimum_required(VERSION 2.8)
project(multicast_ip_serverd)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(llog/src)
set(SOURCE_FILES main.cpp ip_query.cpp llog/src/llog/llog.cpp llog/src/llog/llog_message.cpp)
add_executable(multicast_ip_serverd ${SOURCE_FILES})