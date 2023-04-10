#pragma once
#ifndef INPUT_AREA_H
#define INPUT_AREA_H

#include <iostream>
#include <Windows.h>

#include "ConsoleColor.h"
#include "ConsoleCoords.h"



namespace Chat
{
	class InputArea
	{
	public:

		InputArea(uint16_t _console_width, uint16_t _console_height, uint16_t _area_height,
				  uint16_t _input_area_position_x = 0, uint16_t _input_area_position_y = 0);

		std::string inputMessage() const noexcept;

	private:

		mutable ConsoleCoords m_console_coords = ConsoleCoords();

		uint16_t m_console_width = 0;
		uint16_t m_console_height = 0;

		uint16_t m_input_area_position_x = 0;
		uint16_t m_input_area_position_y = 0;

		ConsoleColor::EColor m_color = ConsoleColor::EColor::LightWhite;
		uint16_t m_area_height = 0;

	};
}

#endif // !INPUT_AREA_H
