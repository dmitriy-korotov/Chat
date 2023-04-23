#include "ConsoleLogFunctions.h"

#include "Console.h"
#include "ConsoleOutputFunctions.h"

#include <chrono>



void consoleLogError(const std::string& _error_message, bool _move_to_next_line) noexcept
{
	Chat::Console::setConsoleColor(Chat::Console::EColor::Red);
	std::cerr << " => ERROR: "; 
	Chat::Console::setConsoleColor(Chat::Console::EColor::White);
	if (_move_to_next_line)
	{
		std::cerr << _error_message << "\n\n";
	}
	else
	{
		std::cerr << _error_message;
	}
}

void consoleLogSuccess(const std::string& _success_message, bool _move_to_next_line) noexcept
{
	Chat::Console::setConsoleColor(Chat::Console::EColor::Green);
	std::cout << " => SUCCESS: ";
	Chat::Console::setConsoleColor(Chat::Console::EColor::White);
	if (_move_to_next_line)
	{
		std::cerr << _success_message << "\n\n";
	}
	else
	{
		std::cerr << _success_message;
	}
}

void consoleLogSocketAddress(const std::string& _ip_address, uint16_t _port) noexcept
{
	Chat::Console::setConsoleColor(Chat::Console::EColor::LightBlue);
	std::cout << "\t\tIP Address: " << _ip_address << "\n\t\tPort: " << _port << "\n\n";
	Chat::Console::setConsoleColor(Chat::Console::EColor::White);
}

void consoleLogTime(Chat::Console::EColor _time_color, Chat::Console::EColor _bgc) noexcept
{
	auto time_point_now = std::chrono::system_clock::now();
	time_t time = std::chrono::system_clock::to_time_t(time_point_now);

	std::string time_str =  std::ctime(&time);
	std::string formated_time_str = "- - - " + time_str.substr(0, time_str.length() - 1) + " - - -";

	Chat::Console::setConsoleColor(_time_color, _bgc);
	Chat::printCenteringMessage(formated_time_str);
}
