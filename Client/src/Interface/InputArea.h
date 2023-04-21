#pragma once
#ifndef INPUT_AREA_H
#define INPUT_AREA_H

#include "Console.h"
#include "ConsoleCoords.h"

#include "InterfaceSync.h"

#include <iostream>
#include <Windows.h>



namespace Chat
{
	class InputArea : protected InterfaceSync
	{
	public:

		explicit InputArea(uint16_t _area_height, uint16_t _input_area_position_x = 0, uint16_t _input_area_position_y = 0);

		std::string inputMessage() const noexcept;

		void setCursorOnInput() const noexcept;
		void setColor(Chat::Console::EColor _color) noexcept;
		void setBorder(char _border_symbol) noexcept;

	private:

		void clearInputArea() const noexcept;



		uint16_t m_console_width = Console::getConsoleSize().getX();
		uint16_t m_console_height = Console::getConsoleSize().getY() - 1;

		ConsoleCoords m_console_coords = ConsoleCoords();

		uint16_t m_input_area_position_x = 0;
		uint16_t m_input_area_position_y = 0;

		Console::EColor m_color = Console::EColor::SkyBlue;
		char m_border_symbol = '#';

		uint16_t m_area_height = 0;

	};
}

#endif // !INPUT_AREA_H
