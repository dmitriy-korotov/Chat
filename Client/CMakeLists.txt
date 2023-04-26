cmake_minimum_required(VERSION 3.26 FATAL_ERROR)

set(PROJECT_NAME Client)

project(${PROJECT_NAME} VERSION 1.0 LANGUAGES CXX)

add_executable(${PROJECT_NAME}

		src/main.cpp
		
		src/ClientApp/Client/Client.h
		src/ClientApp/Client/Client.cpp

		src/ClientApp/Interface/InterfaceSync.h
		src/ClientApp/Interface/InterfaceSync.cpp
		src/ClientApp/Interface/OutputMessagesControler.h
		src/ClientApp/Interface/OutputMessagesControler.cpp
		src/ClientApp/Interface/InputArea.h
		src/ClientApp/Interface/InputArea.cpp

		../libs/Socket.h
		../libs/Socket.cpp
		../libs/MessagePacket.h
		../libs/MessagePacket.cpp
		
		../libs/Console.h
		../libs/Console.cpp
		../libs/ConsoleLogFunctions.h
		../libs/ConsoleLogFunctions.cpp
		../libs/ConsoleOutputFunctions.h
		../libs/ConsoleOutputFunctions.cpp
		../libs/ConsoleCoords.h
		../libs/ConsoleCoords.cpp

		../libs/KeyBoard.h
		../libs/KeyBoard.cpp
)

include_directories(../libs)

add_compile_options(
    -Werror

    -Wall
    -Wextra
    -Wpedantic

    -Wcast-align
    -Wcast-qual
    -Wconversion
    -Wctor-dtor-privacy
    -Wenum-compare
    -Wfloat-equal
    -Wnon-virtual-dtor
    -Wold-style-cast
    -Woverloaded-virtual
    -Wredundant-decls
    -Wsign-conversion
    -Wsign-promo
)
