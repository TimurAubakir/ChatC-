cmake_minimum_required(VERSION 3.10)
project(echo)

set(CMAKE_CXX_STANDARD 11)

add_executable(echo
        client.cpp
        server.cpp)
