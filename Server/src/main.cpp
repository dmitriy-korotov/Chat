#include "Server/Server.h"

#include <conio.h>


int main(int argc, char** argv)
{
	if (!Chat::Server::run())
	{
		return 1;
	}

	char get = _getch();

	return 0;
}