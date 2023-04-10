#include "Socket.h"
#include "ConsoleColor.h"
#include "ConsoleLogFunctions.h"
#include "ConsoleOutputFunctions.h"
#include "Interface/Message.h"
#include "Interface/InputArea.h"

#include <conio.h>
#include <thread>



// server data
static const Web::EAddressFamily _SERVER_ADDRESS_FAMILY_ = Web::EAddressFamily::AF_Inet;
static const std::string _SERVER_IP_ADDRESS_ = "127.0.0.1";
static const uint16_t _SERVER_PORT_ = 2000u;


// console settings
static constexpr uint16_t _CONSOLE_WDITH_ = 120;
static constexpr uint16_t _CONSOLE_HEIGHT_ = 30;


// client
int main(int argc, char** argv)
{
	// initializing sockets
	if (!Web::Socket::initSockets())
	{
		consoleLogError("Can't initialiezed sockets.");
		char get = _getch();
		return 1;
	}


	// creating socket
	Web::Socket socket(Web::EAddressFamily::AF_Inet, Web::ESocketType::SocketStream);
	if (!socket.isValid())
	{
		consoleLogError("Can't creating clinet socket");
		char get = _getch();
		return 1;
	}


	// connecting to server
	if (!socket.connectToOtherSocket(_SERVER_IP_ADDRESS_, _SERVER_PORT_))
	{
		consoleLogError("Can't connect to server:");
		consoleLogSocketAddress(_SERVER_IP_ADDRESS_, _SERVER_PORT_);
		char get = _getch();
		return 1;
	}



	// buffer messages
	std::string message;

	// Input area object
	Chat::InputArea input_area(_CONSOLE_WDITH_, _CONSOLE_HEIGHT_, 3);



	std::thread thread1([&]()
		{
			// client loop
			while (true)
			{
				// inputing message
				message = input_area.inputMessage();

				if (message == "end\n" || message == "END\n")
				{
					socket.close();
					break;
				}

				
				if (message != "")
				{
					Chat::Message::printMessage("You", message, ConsoleColor::EColor::Purpule);


					// sending message
					if (!socket.sendData(message))
					{
						consoleLogError("Can't send message.");
					}
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
					Chat::Message::printMessage("Other user", message);

					input_area.setCursorOnInput();
				}
				else
				{
					socket.close();
					break;
				}
			}
		});

	thread2.join();
	thread1.join();

	// closing all sockets
	Web::Socket::closeAllSockets();

	//std::cout << " => Client finishes work...\n\n";				
	char get = _getch();

	return 0;
}

