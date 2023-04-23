#include "ConsoleOutputFunctions.h"

#include "Console.h"



namespace Chat
{
	void printHorizontalLine(char _symbol_fill, uint16_t _width, bool _move_to_next_line) noexcept
	{
		for (uint16_t i = 0; i < _width; ++i)
		{
			std::cout << _symbol_fill;
		}
		if (_move_to_next_line)
		{
			std::cout << std::endl;
		}
	}



	void printCenteringMessage(const std::string& _message) noexcept
	{
		uint16_t console_width = Chat::Console::getConsoleSize().getX();

		Console::moveConsoleCursor(Chat::ConsoleCoords((console_width - _message.length()) / 2, Chat::Console::getConsoleCursorPosition().getY()));
		
		std::cout << _message << std::endl;
	}
}