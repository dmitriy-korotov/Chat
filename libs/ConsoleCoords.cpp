#include "ConsoleCoords.h"



namespace Chat
{
	ConsoleCoords::ConsoleCoords(uint16_t _x, uint16_t _y)
			: m_console_coords { static_cast<SHORT>(_x), static_cast<SHORT>(_y) }
	{ }



	ConsoleCoords::operator COORD() const noexcept
	{
		return m_console_coords;
	}



	ConsoleCoords ConsoleCoords::operator+(const ConsoleCoords& _right) const noexcept
	{
		return ConsoleCoords(m_console_coords.X + _right.getX(), m_console_coords.Y + _right.getY());
	}



	ConsoleCoords ConsoleCoords::operator-(const ConsoleCoords& _right) const noexcept
	{
		return ConsoleCoords(m_console_coords.X - _right.getX(), m_console_coords.Y - _right.getY());
	}



	ConsoleCoords& ConsoleCoords::operator+=(const ConsoleCoords& _right) noexcept
	{
		m_console_coords.X += _right.getX();
		m_console_coords.Y += _right.getY();
		return *this;
	}



	ConsoleCoords& ConsoleCoords::operator-=(const ConsoleCoords& _right) noexcept
	{
		m_console_coords.X -= _right.getX();
		m_console_coords.Y -= _right.getY();
		return *this;
	}



	void ConsoleCoords::setCoords(uint16_t _x, uint16_t _y) noexcept
	{
		m_console_coords.X = _x;
		m_console_coords.Y = _y;
	}



	void ConsoleCoords::setX(uint16_t _value) noexcept
	{
		m_console_coords.X = _value;
	}



	void ConsoleCoords::setY(uint16_t _value) noexcept
	{
		m_console_coords.Y = _value;
	}



	uint16_t ConsoleCoords::getX() const noexcept
	{
		return m_console_coords.X;
	}



	uint16_t ConsoleCoords::getY() const noexcept
	{
		return m_console_coords.Y;
	}
}