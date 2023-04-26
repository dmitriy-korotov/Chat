#include "ClientApp/Client/Client.h"

#include "ConsoleLogFunctions.h"

#include <conio.h>



int main(int argc, char** argv)
{
	Chat::ClientChat::setChatSize(140, 35);

	if (!Chat::ClientChat::run())
	{
		consoleLogError("Can't running chat to address:");
		consoleLogSocketAddress(Chat::ClientChat::getServerIPAddress(), Chat::ClientChat::getServerPort());
		char end = _getch();
		return 1;
	}

	char end = _getch();

	return 0;
}