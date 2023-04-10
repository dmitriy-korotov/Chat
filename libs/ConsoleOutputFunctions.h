#pragma once

#include "ConsoleCoords.h"

#include <iostream>



namespace Chat
{
	void printHorizontalLine(char _symbol_fill, uint16_t _width, bool _move_to_next_line = true) noexcept;

	void moveConsoleCursor(const ConsoleCoords& _coords, int _handle = STD_OUTPUT_HANDLE) noexcept;
}