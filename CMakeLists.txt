cmake_minimum_required(VERSION 3.0)

project(keeft)

add_executable(keeft main.cpp libkeeft.cpp)

install(TARGETS keeft RUNTIME DESTINATION bin)
