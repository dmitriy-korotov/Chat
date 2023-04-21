#include "Socket.h"

#include "Console.h"
#include "ConsoleLogFunctions.h"

#include "KeyBoard.h"

#include "MessagePacket.h"

#include <conio.h>
#include <vector>
#include <thread>
#include <mutex>
#include <atomic>


static const Chat::EAddressFamily _ADDRESS_FAMILY_ = Chat::EAddressFamily::AF_Inet;
static const std::string _IP_ADDRESS_ = "127.0.0.1";
static const uint16_t _PORT_ = 2000u;


// server
int main(int argc, char** argv)
{
	std::cout << " => Runing server...\n\n";


	// initializing sockets
	if (!Chat::Socket::initSockets())
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
	Chat::Socket socket(Chat::EAddressFamily::AF_Inet, Chat::ESocketType::SocketStream);
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
	std::vector<std::string> all_messages;

	bool is_finish_server = false;

	std::vector<std::pair<Chat::Socket, std::thread>> clients;
	std::mutex clients_mutex;

	std::thread client_accepting_handler([&]()
		{
			while (!is_finish_server)
			{
				Chat::Socket client_socket;
				try
				{
					client_socket = socket.acceptOtherSocket();
					consoleLogSuccess("Successfully connected new client:");
					consoleLogSocketAddress(_IP_ADDRESS_, client_socket.getPort());

					std::thread messages_handler([&](size_t _index)
						{
							while (clients.size() == _index)
							{ }

							while (!is_finish_server)
							{
								// reciving message
								std::string packet = clients[_index].first.reciveData();
								if (packet == "")
								{
									break;
								}

								consoleLogSuccess("Message successfuly recived from port:\t" + std::to_string(clients[_index].first.getPort()));
								std::lock_guard<std::mutex> client_guard(clients_mutex);
								for (const auto& client : clients)
								{
									if (client.first.isValid())
									{
										if (!client.first.sendData(packet.c_str(), packet.size()))
										{
											consoleLogError("Can't send message to port:\t" + std::to_string(client.first.getPort()));
										}
									}
								}
							}
						}, clients.size());
					messages_handler.detach();

					clients.emplace_back(std::move(client_socket), std::move(messages_handler));
				}
				catch (...)
				{
					consoleLogError("Can't accept other socket.");
					char get = _getch();
				}
			}
		});

	std::thread close_server_handler([&]()
		{
			while (!is_finish_server)
			{
				is_finish_server = (_getch() == Chat::KeyBoard::Escape);
			}
		});

	close_server_handler.join();
	client_accepting_handler.detach();


	// closing all sockets
	Chat::Socket::closeAllSockets();

	std::cout << " => Server finishes work...\n\n";				char get = _getch();

	return 0;
}

