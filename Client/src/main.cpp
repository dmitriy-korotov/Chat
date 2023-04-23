#include "Socket.h"

#include "Console.h"
#include "ConsoleLogFunctions.h"
#include "ConsoleOutputFunctions.h"

#include "ClientApp/Interface/Message.h"
#include "ClientApp/Interface/InputArea.h"

#include "MessagePacket.h"

#include <conio.h>
#include <thread>



// server data
static const Chat::EAddressFamily _SERVER_ADDRESS_FAMILY_ = Chat::EAddressFamily::AF_Inet;
static const std::string _SERVER_IP_ADDRESS_ = "127.0.0.1";
static const uint16_t _SERVER_PORT_ = 2000u;


// console settings
static constexpr uint16_t _CONSOLE_WIDTH_ = 120;
static constexpr uint16_t _CONSOLE_HEIGHT_ = 30;


// client
int main(int argc, char** argv)
{
	// set console size
	Chat::Console::setConsoleSize(Chat::ConsoleCoords(_CONSOLE_WIDTH_, _CONSOLE_HEIGHT_));



	// initializing sockets
	if (!Chat::Socket::initSockets())
	{
		consoleLogError("Can't initialiezed sockets.");
		char get = _getch();
		return 1;
	}


	// creating socket
	Chat::Socket socket(Chat::EAddressFamily::AF_Inet, Chat::ESocketType::SocketStream);
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
	std::string buffer_to_input_messages;

	// username
	std::string client_username;

	// Input area object
	Chat::InputArea input_area(3);


	std::string label_for_input_username = "INPUT YOUR NAME:";
	Chat::Console::moveConsoleCursor(Chat::ConsoleCoords(_CONSOLE_WIDTH_ / 2 - label_for_input_username.length() / 2, _CONSOLE_HEIGHT_ / 2));
	Chat::Console::setConsoleColor(Chat::Console::EColor::Purpule);
	std::cout << "INPUT YOUR NAME: ";				
	Chat::Console::setConsoleColor(Chat::Console::EColor::White);
	std::cin >> client_username;
	Chat::Console::clearStdInBuffer();
	Chat::Console::clear();



	std::thread input_message_thread([&]()
		{
			// client loop
			while (true)
			{
				buffer_to_input_messages = input_area.inputMessage();

				if (buffer_to_input_messages == "end\n" || buffer_to_input_messages == "END\n")
				{
					socket.close();
					break;
				}

				
				if (buffer_to_input_messages != "" && buffer_to_input_messages != "\n")
				{
					// sending message
					if (!socket.sendMessage(client_username, buffer_to_input_messages))
					{
						consoleLogError("Can't send message.");
					}
				}
			}
		});

	std::thread recive_message_thread([&]()
		{
			// client loop
			while (true)
			{
				// reciving message
				Chat::MessagePacket msg_packet(socket.reciveData());

				if (msg_packet.getMessage() != "")
				{
					if (msg_packet.getSender() == client_username)
					{
						Chat::Message::printMessage("You", msg_packet.getMessage());
					}
					else
					{
						Chat::Message::printMessage(msg_packet.getSender(), msg_packet.getMessage());
					}

					input_area.setCursorOnInput();
				}
				else
				{
					socket.close();
					break;
				}
			}
		});

	recive_message_thread.join();
	input_message_thread.join();

	// closing all sockets
	Chat::Socket::closeAllSockets();
		
	char get = _getch();

	return 0;
}

