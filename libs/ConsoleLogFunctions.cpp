#include "ConsoleLogFunctions.h"
#include "ConsoleColor.h"



void consoleLogError(const std::string& _error_message)
{
	ConsoleColor::setConsoleColor(ConsoleColor::EColor::Red);
	std::cerr << " => ERROR: "; 
	ConsoleColor::setConsoleColor(ConsoleColor::EColor::White);
	std::cerr << _error_message << "\n\n";
}

void consoleLogSuccess(const std::string& _success_message)
{
	ConsoleColor::setConsoleColor(ConsoleColor::EColor::Green);
	std::cout << " => SUCCESS: ";
	ConsoleColor::setConsoleColor(ConsoleColor::EColor::White);
	std::cerr << _success_message << "\n\n";
}

void consoleLogSocketAddress(const std::string& _ip_address, uint16_t _port)
{
	ConsoleColor::setConsoleColor(ConsoleColor::EColor::LightBlue);
	std::cout << "\t\tIP Address: " << _ip_address << "\n\t\tPort: " << _port << "\n\n";
	ConsoleColor::setConsoleColor(ConsoleColor::EColor::White);
}
