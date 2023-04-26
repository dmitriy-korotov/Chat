#include "Server/Server.h"

#include "ConsoleLogFunctions.h"

#include <conio.h>


int main(int argc, char** argv)
{
	if (!Chat::Server::run())
	{
		consoleLogError("Can't running server on address:");
		consoleLogSocketAddress(Chat::Server::getIPAddress(), Chat::Server::getPort());
		return 1;
	}

	char get = _getch();

	return 0;
}