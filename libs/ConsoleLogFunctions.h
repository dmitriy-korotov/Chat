#pragma once
#ifndef CONSOLE_LOG_FUNCTION
#define CONSOLE_LOG_FUNCTION

#include "Console.h"

#include <iostream>



void consoleLogError(const std::string& _error_message, bool _move_to_next_line = true) noexcept;
void consoleLogSuccess(const std::string& _success_message, bool _move_to_next_line = true) noexcept;
void consoleLogSocketAddress(const std::string& _ip_address, uint16_t _port) noexcept;
void consoleLogTime(Chat::Console::EColor _time_color, Chat::Console::EColor _bgc = Chat::Console::EColor::Black) noexcept;

#endif // !CONSOLE_LOG_FUNCTION
