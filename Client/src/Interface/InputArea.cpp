#include "InputArea.h"

#include "ConsoleOutputFunctions.h"



namespace Chat
{
	InputArea::InputArea(uint16_t _console_width, uint16_t _console_height, uint16_t _area_height,
						 uint16_t _input_area_position_x, uint16_t _input_area_position_y)
			: m_console_width(_console_width)
			, m_console_height(_console_height)
			, m_input_area_position_x(_input_area_position_x)
			, m_input_area_position_y(_console_height - _input_area_position_y - _area_height - 1)
			, m_console_coords(_input_area_position_x, _console_height - _input_area_position_y - _area_height - 1)
			, m_area_height(_area_height)
	{ }



	std::string InputArea::inputMessage() const noexcept
	{
		char buffer[120] = {};

		moveConsoleCursor(m_console_coords);
		ConsoleColor::setConsoleColor(m_color);
		printHorizontalLine('-', m_console_width);
		moveConsoleCursor(m_console_coords + ConsoleCoords(0, m_area_height));
		printHorizontalLine('-', m_console_width);
		moveConsoleCursor(m_console_coords + ConsoleCoords(0, 2));

		std::fgets(buffer, m_console_width, stdin);
		
		moveConsoleCursor(m_console_coords + ConsoleCoords(0, 2));
		std::cout << "\t\t\t\t\t\t\t\t\t\t\t\t\t\t";

		return buffer;
	}



	void InputArea::setCursorOnInput() const noexcept
	{
		moveConsoleCursor(m_console_coords + ConsoleCoords(0, 2));
	}
}