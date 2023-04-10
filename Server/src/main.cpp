#include "Socket.h"
#include "ConsoleColor.h"
#include "ConsoleLogFunctions.h"

#include <conio.h>
#include <thread>


static const Web::EAddressFamily _ADDRESS_FAMILY_ = Web::EAddressFamily::AF_Inet;
static const std::string _IP_ADDRESS_ = "127.0.0.1";
static const uint16_t _PORT_ = 2000u;


// server
int main(int argc, char** argv)
{
	std::cout << " => Runing server...\n\n";


	// initializing sockets
	if (!Web::Socket::initSockets())
	{
		consoleLogError("Can't initialiezed sockets.");
		char get = _getch();
		return 1;
	}
	else
	{
		consoleLogSuccess("Sockets successfully initialiezed.");
	}
	

	// creating socket
	Web::Socket socket(Web::EAddressFamily::AF_Inet, Web::ESocketType::SocketStream);
	if (!socket.isValid())
	{
		consoleLogError("Can't creating socket:");
		consoleLogSocketAddress(_IP_ADDRESS_, _PORT_);
		char get = _getch();
		return 1;
	}
	else
	{
		consoleLogSuccess("Socket successfully creating:");
		consoleLogSocketAddress(_IP_ADDRESS_, _PORT_);
	}


	// binding socket
	if (!socket.bindSocket(_ADDRESS_FAMILY_, _IP_ADDRESS_, _PORT_))
	{
		consoleLogError("Can't binding socket:");
		consoleLogSocketAddress(_IP_ADDRESS_, _PORT_);
		char get = _getch();
		return 1;
	}
	else
	{
		consoleLogSuccess("Socket successfully binded:");
		consoleLogSocketAddress(_IP_ADDRESS_, _PORT_);
	}


	// start listening other sockets
	if (!socket.listenOtherSockets())
	{
		consoleLogError("Can't listen other sockets.");
		char get = _getch();
		return 1;
	}
	else
	{
		consoleLogSuccess("Successfuly listening other sockets...");
	}


	// buffer messages
	std::string message;

	Web::Socket client_socket1;
	Web::Socket client_socket2;

	std::thread thread1([&]()
		{
			// accepting other socket
			try
			{
				client_socket1 = socket.acceptOtherSocket();
			}
			catch (...)
			{
				consoleLogError("Can't accept other socket.");
				char get = _getch();
			}


			// server loop
			while (true)
			{
				// reciving message
				std::string message = client_socket1.reciveData();
				if (message != "")
				{
					ConsoleColor::setConsoleColor(ConsoleColor::EColor::Blue);
					std::cout << " => Client message:   ";
					ConsoleColor::setConsoleColor(ConsoleColor::EColor::White);
					std::cout << message << "\n\n";
				}
				else
				{
					break;
				}


				if (client_socket2.isValid())
				{
					// sending message
					if (!client_socket2.sendData(message))
					{
						consoleLogError("Can't send message.");
					}
				}
			}
		});

	std::thread thread2([&]()
		{
			// accepting other socket
			try
			{
				client_socket2 = socket.acceptOtherSocket();
			}
			catch (...)
			{
				consoleLogError("Can't accept other socket.");
				char get = _getch();
			}

			// server loop
			while (true)
			{
				// reciving message
				std::string message = client_socket2.reciveData();
				if (message != "")
				{
					ConsoleColor::setConsoleColor(ConsoleColor::EColor::Blue);
					std::cout << " => Client message:   ";
					ConsoleColor::setConsoleColor(ConsoleColor::EColor::White);
					std::cout << message << "\n\n";
				}
				else
				{
					break;
				}


				if (client_socket1.isValid())
				{
					// sending message
					if (!client_socket1.sendData(message))
					{
						consoleLogError("Can't send message.");
					}
				}
			}
		});

	thread2.join();
	thread1.join();

	// closing all sockets
	Web::Socket::closeAllSockets();

	std::cout << " => Server finishes work...\n\n";				char get = _getch();

	return 0;
}

