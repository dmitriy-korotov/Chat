#pragma once
#ifndef CONSOLE_COORDS_H
#define CONSOLE_COORDS_H

#include <iostream>
#include <Windows.h>



namespace Chat
{
	class ConsoleCoords
	{
	public:

		ConsoleCoords(uint16_t _x = 0, uint16_t _y = 0);

		operator COORD() const noexcept;
		ConsoleCoords operator+(const ConsoleCoords& _right) const noexcept;
		ConsoleCoords operator-(const ConsoleCoords& _right) const noexcept;
		ConsoleCoords& operator+=(const ConsoleCoords& _right) noexcept;
		ConsoleCoords& operator-=(const ConsoleCoords& _right) noexcept;

		void setCoords(uint16_t _x, uint16_t _y) noexcept;
		void setX(uint16_t _value) noexcept;
		void setY(uint16_t _value) noexcept;

		uint16_t getX() const noexcept;
		uint16_t getY() const noexcept;

	private:

		COORD m_console_coords = {0, 0};

	};
}

#endif // CONSOLE_COORDS_H

