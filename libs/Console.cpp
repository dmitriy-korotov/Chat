#include "Console.h"



static constexpr uint8_t _SYMBOL_WIDTH_ = 8;
static constexpr uint8_t _SYMBOL_HEIGHT_ = 18;
static constexpr uint16_t _SCROLLBAR_WIDTH_ = 0; // 60



namespace Chat
{
	HANDLE Console::m_handle = GetStdHandle(STD_OUTPUT_HANDLE);



	void Console::setConsoleColor(EColor _color, EColor _background_color) noexcept
	{
		SetConsoleTextAttribute(m_handle, (((static_cast<uint8_t>(_background_color) << 4) | static_cast<uint8_t>(_color))));
	}



	HANDLE Console::getStdOutputHandle() noexcept
	{
		return m_handle;
	}



	void Console::setConsoleSize(const ConsoleCoords& _size) noexcept
	{
		SetConsoleScreenBufferSize(m_handle, static_cast<COORD>(_size));
		HWND console_window = GetConsoleWindow();
		RECT rect;
		GetWindowRect(console_window, &rect);
		MoveWindow(console_window, rect.left, rect.top, _size.getX() * _SYMBOL_WIDTH_ - _SCROLLBAR_WIDTH_, _size.getY() * _SYMBOL_HEIGHT_, TRUE);
	}



	void Console::moveConsoleCursor(const ConsoleCoords& _coords, int _handle) noexcept
	{
		SetConsoleCursorPosition(GetStdHandle(_handle), static_cast<COORD>(_coords));
	}



	ConsoleCoords Console::getConsoleCursorPosition() noexcept
	{
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		if (GetConsoleScreenBufferInfo(m_handle, &csbi))
		{
			return ConsoleCoords(csbi.dwCursorPosition);
		}
		else
		{
			return ConsoleCoords();
		}
	}



	ConsoleCoords Console::getConsoleSize() noexcept
	{
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		if (GetConsoleScreenBufferInfo(m_handle, &csbi))
		{
			return ConsoleCoords(csbi.dwSize);
		}
		else
		{
			return ConsoleCoords();
		}
	}



	void Console::clear() noexcept
	{
		system("CLS");
	}



	void Console::clearStdInBuffer() noexcept
	{
		rewind(stdin);
	}
}