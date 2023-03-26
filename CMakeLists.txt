cmake_minimum_required(VERSION 3.26 FATAL_ERROR)

set(PROJECT_NAME WebServer)

project(${PROJECT_NAME})

add_executable(${PROJECT_NAME}
		src/main.cpp
)
