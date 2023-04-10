#include "ConsoleOutputFunctions.h"



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



	void moveConsoleCursor(const ConsoleCoords& _coords, int _handle) noexcept
	{
		SetConsoleCursorPosition(GetStdHandle(_handle), static_cast<COORD>(_coords));
	}
}