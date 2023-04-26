#include "InputArea.h"

#include "ConsoleOutputFunctions.h"



namespace Chat
{
	InputArea::InputArea(uint16_t _area_height, uint16_t _input_area_position_x, uint16_t _input_area_position_y) noexcept
			: m_console_coords(_input_area_position_x, m_console_height - _input_area_position_y)
			, m_area_height(_area_height)
	{ }



	void InputArea::create(uint16_t _area_height, uint16_t _input_area_position_x, uint16_t _input_area_position_y) noexcept
	{
		m_console_width = Console::getConsoleSize().getX();
		m_console_height = Console::getConsoleSize().getY();

		m_console_coords.setCoords(_input_area_position_x, m_console_height - _input_area_position_y - 1);
		m_area_height = _area_height;
	}



	std::string InputArea::inputMessage() const noexcept
	{
		char buffer[120 * 3] = {};

		captureFunction([&]()	// thread safety output
			{
				Console::moveConsoleCursor(m_console_coords);
				Console::setConsoleColor(m_color);
				printHorizontalLine(m_border_symbol, m_console_width, false);
				Console::moveConsoleCursor(m_console_coords - ConsoleCoords(0, m_area_height + 1));
				printHorizontalLine(m_border_symbol, m_console_width, false);
				Console::moveConsoleCursor(m_console_coords + ConsoleCoords(0, m_area_height / 2));
			});

		Console::setConsoleColor(Console::EColor::White);
		std::fgets(buffer, m_console_width * m_console_height, stdin);
		Console::setConsoleColor(m_color);

		clearInputArea();

		return buffer;
	}



	void InputArea::setCursorOnInput() const noexcept
	{
		Console::moveConsoleCursor(m_console_coords + ConsoleCoords(0, m_area_height / 2));
	}



	void InputArea::setColor(Chat::Console::EColor _color) noexcept
	{
		m_color = _color;
	}



	void InputArea::setBorder(char _border_symbol) noexcept
	{
		m_border_symbol = _border_symbol;
	}



	void InputArea::clearInputArea() const noexcept
	{	
		captureFunction([&]()
			{
				Console::moveConsoleCursor(m_console_coords - ConsoleCoords(0, m_area_height));
				for (size_t i = 0; i < m_area_height; ++i)
				{
					printHorizontalLine(' ', m_console_width);
				}
			});
	}
}