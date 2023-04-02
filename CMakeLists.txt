cmake_minimum_required(VERSION 3.26 FATAL_ERROR)

set(PROJECT_NAME Chat)

project(${PROJECT_NAME})

add_executable(${PROJECT_NAME} src/main.cpp)

add_subdirectory(Server)
add_subdirectory(Client)
