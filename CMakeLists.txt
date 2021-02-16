cmake_minimum_required(VERSION 3.0)

project(keeft)

add_executable(keeft main.cpp net.cpp io.cpp config.cpp net_receive.cpp net_send.cpp)

install(TARGETS keeft RUNTIME DESTINATION bin)
