#pragma once

#include "ConsoleCoords.h"
#include "Console.h"

#include <iostream>



namespace Chat
{
	void printHorizontalLine(char _symbol_fill, uint16_t _width, bool _move_to_next_line = true) noexcept;
	void printCenteringMessage(const std::string& _message) noexcept;
	void printLine(const std::string& _text, bool _move_to_next_line = true,
				   Console::EColor _text_color = Console::EColor::White, Console::EColor _bgc = Console::EColor::Black) noexcept;
}