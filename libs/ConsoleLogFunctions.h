#pragma once
#ifndef CONSOLE_LOG_FUNCTION
#define CONSOLE_LOG_FUNCTION

#include "Console.h"

#include <iostream>



void consoleLogError(const std::string& _error_message);
void consoleLogSuccess(const std::string& _success_message);
void consoleLogSocketAddress(const std::string& _ip_address, uint16_t _port);

#endif // !CONSOLE_LOG_FUNCTION
