#pragma once
#ifndef CONSOLE_COLOR_H
#define CONSOLE_COLOR_H

#include <Windows.h>
#include <iostream>

class ConsoleColor
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

	ConsoleColor() = delete;
	~ConsoleColor() = default;

	static void setConsoleColor(EColor _text_color, EColor _background_color = EColor::Black) noexcept;

private:

	static HANDLE handle;

};

#endif // !CONSOLE_COLOR_H
