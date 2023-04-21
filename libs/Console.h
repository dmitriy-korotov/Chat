#pragma once
#ifndef CONSOLE_COLOR_H
#define CONSOLE_COLOR_H

#include "ConsoleCoords.h"

#include <Windows.h>
#include <iostream>



namespace Chat
{
	class Console
	{
	public:

		enum class EColor : uint8_t
		{
			Black = 0,
			Blue,
			Green,
			SkyBlue,
			Red,
			Purpule,
			Yellow,
			White,
			Grey,
			LightBlue,
			LightGreen,
			LightSkyBlue,
			LightRed,
			LightYellow,
			LightWhite
		};

		Console() = delete;
		~Console() = default;

		static void setConsoleColor(EColor _text_color, EColor _background_color = EColor::Black) noexcept;
		static void setConsoleSize(const ConsoleCoords& _size) noexcept;
		static HANDLE getStdOutputHandle() noexcept;
		static void moveConsoleCursor(const ConsoleCoords& _coords, int _handle = STD_OUTPUT_HANDLE) noexcept;
		static ConsoleCoords getConsoleCursorPosition() noexcept;
		static ConsoleCoords getConsoleSize() noexcept;
		static void clear() noexcept;
		static void clearStdInBuffer() noexcept;

	private:

		static HANDLE m_handle;

	};
}

#endif // !CONSOLE_COLOR_H
