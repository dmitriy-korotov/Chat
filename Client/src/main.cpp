#include "Socket.h"
#include "ConsoleColor.h"
#include "ConsoleLogFunctions.h"

#include <conio.h>
#include <thread>



// server data
static const Web::EAddressFamily _SERVER_ADDRESS_FAMILY_ = Web::EAddressFamily::AF_Inet;
static const std::string _SERVER_IP_ADDRESS_ = "127.0.0.1";
static const uint16_t _SERVER_PORT_ = 2000u;


// client
int main(int argc, char** argv)
{
	srand(time(0));


	// client data
	static const Web::EAddressFamily _ADDRESS_FAMILY_ = Web::EAddressFamily::AF_Inet;
	static const std::string _IP_ADDRESS_ = "127.0.0.1";
	static const uint16_t _PORT_ = 2001 + std::rand() % 2000;


	std::cout << " => Client application running...\n\n";

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


	// connecting to other socket
	if (!socket.connectToOtherSocket(_SERVER_IP_ADDRESS_, _SERVER_PORT_))
	{
		consoleLogError("Can't connect to other socket:");
		consoleLogSocketAddress(_SERVER_IP_ADDRESS_, _SERVER_PORT_);
		char get = _getch();
		return 1;
	}
	else
	{
		consoleLogSuccess("Successfully connect to other socket:");
		consoleLogSocketAddress(_SERVER_IP_ADDRESS_, _SERVER_PORT_);
	}


	// buffer messages
	std::string message;



	std::thread thread1([&]()
		{
			// client loop
			while (true)
			{
				// inputing message
				ConsoleColor::setConsoleColor(ConsoleColor::EColor::Purpule);
				std::cout << " => Input your message:   ";
				ConsoleColor::setConsoleColor(ConsoleColor::EColor::White);
				std::cin >> message;			std::cout << "\n";

				if (message == "end" || message == "END")
				{
					socket.close();
					break;
				}


				// sending message
				if (!socket.sendData(message))
				{
					consoleLogError("Can't send message.");
				}
			}
		});

	std::thread thread2([&]()
		{
			// client loop
			while (true)
			{
				// reciving message
				std::string message = socket.reciveData();
				if (message != "")
				{
					ConsoleColor::setConsoleColor(ConsoleColor::EColor::Blue);
					std::cout << " => Server message:   ";
					ConsoleColor::setConsoleColor(ConsoleColor::EColor::White);
					std::cout << message << "\n\n";
				}
				else
				{
					socket.close();
					break;
				}
			}
		});

	thread2.join();
	thread1.detach();

	// closing all sockets
	Web::Socket::closeAllSockets();

	std::cout << " => Client finishes work...\n\n";				char get = _getch();

	return 0;
}

