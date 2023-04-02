#include "ConsoleColor.h"

HANDLE ConsoleColor::handle = GetStdHandle(STD_OUTPUT_HANDLE);



void ConsoleColor::setConsoleColor(EColor _color, EColor _background_color) noexcept
{
	SetConsoleTextAttribute(handle, (((static_cast<uint8_t>(_background_color) << 4) | static_cast<uint8_t>(_color))));
}