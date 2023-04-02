cmake_minimum_required(VERSION 3.26 FATAL_ERROR)

set(PROJECT_NAME Server)

project(${PROJECT_NAME})

add_executable(${PROJECT_NAME}
		src/main.cpp
		../libs/Socket.h
		../libs/Socket.cpp
		../libs/SocketFunctions.h
		../libs/SocketFunctions.cpp
)
