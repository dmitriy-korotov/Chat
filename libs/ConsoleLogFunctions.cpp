#include "ConsoleLogFunctions.h"
#include "Console.h"



void consoleLogError(const std::string& _error_message)
{
	Chat::Console::setConsoleColor(Chat::Console::EColor::Red);
	std::cerr << " => ERROR: "; 
	Chat::Console::setConsoleColor(Chat::Console::EColor::White);
	std::cerr << _error_message << "\n\n";
}

void consoleLogSuccess(const std::string& _success_message)
{
	Chat::Console::setConsoleColor(Chat::Console::EColor::Green);
	std::cout << " => SUCCESS: ";
	Chat::Console::setConsoleColor(Chat::Console::EColor::White);
	std::cerr << _success_message << "\n\n";
}

void consoleLogSocketAddress(const std::string& _ip_address, uint16_t _port)
{
	Chat::Console::setConsoleColor(Chat::Console::EColor::LightBlue);
	std::cout << "\t\tIP Address: " << _ip_address << "\n\t\tPort: " << _port << "\n\n";
	Chat::Console::setConsoleColor(Chat::Console::EColor::White);
}
