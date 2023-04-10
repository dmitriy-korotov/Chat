cmake_minimum_required(VERSION 3.26 FATAL_ERROR)

set(PROJECT_NAME Client)

project(${PROJECT_NAME})

add_executable(${PROJECT_NAME}

		src/main.cpp
		
		src/Interface/InputArea.h
		src/Interface/InputArea.cpp

		../libs/Socket.h
		../libs/Socket.cpp
		../libs/SocketFunctions.h
		../libs/SocketFunctions.cpp
		
		../libs/ConsoleColor.h
		../libs/ConsoleColor.cpp
		../libs/ConsoleLogFunctions.h
		../libs/ConsoleLogFunctions.cpp
		../libs/ConsoleOutputFunctions.h
		../libs/ConsoleOutputFunctions.cpp
		../libs/ConsoleCoords.h
		../libs/ConsoleCoords.cpp
)

include_directories(../libs)
