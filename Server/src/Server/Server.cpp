#include "Server.h"

#include "Console.h"
#include "ConsoleLogFunctions.h"
#include "ConsoleOutputFunctions.h"

#include "KeyBoard.h"

#include <conio.h>



namespace Chat
{
	Chat::Socket Server::m_socket;

	const Chat::EAddressFamily Server::_ADDRESS_FAMILY_ = Chat::EAddressFamily::AF_Inet;
	const std::string Server::_IP_ADDRESS_ = "127.0.0.1";
	const uint16_t Server::_PORT_ = 2000u;



	std::vector<Chat::MessagePacket> Server::m_all_messages;
	std::mutex Server::m_message_mutex;
	bool Server::m_is_finish_server = false;
	std::vector<std::pair<Chat::User, std::thread>> Server::m_clients;
	std::mutex Server::m_clients_mutex;





	bool Server::socketsInitialization() noexcept
	{
		if (!Chat::Socket::initSockets())
		{
			consoleLogError("Can't initialiezed sockets.");
			return false;
		}
		else
		{
			consoleLogSuccess("Sockets successfully initialiezed.");
			return true;
		}
	}



	bool Server::initServerSocket() noexcept
	{
		m_socket.init(Chat::EAddressFamily::AF_Inet, Chat::ESocketType::SocketStream);
		if (!m_socket.isValid())
		{
			consoleLogError("Can't creating socket:");
			consoleLogSocketAddress(_IP_ADDRESS_, _PORT_);
			return false;
		}
		else
		{
			consoleLogSuccess("Socket successfully creating:");
			consoleLogSocketAddress(_IP_ADDRESS_, _PORT_);
			return true;
		}
	}



	bool Server::bindServerSocket() noexcept
	{
		if (!m_socket.bindSocket(_ADDRESS_FAMILY_, _IP_ADDRESS_, _PORT_))
		{
			consoleLogError("Can't binding socket:");
			consoleLogSocketAddress(_IP_ADDRESS_, _PORT_);
			return false;
		}
		else
		{
			consoleLogSuccess("Socket successfully binded:");
			consoleLogSocketAddress(_IP_ADDRESS_, _PORT_);
			return true;
		}
	}



	bool Server::startLinstenigOtherSockets() noexcept
	{
		if (!m_socket.listenOtherSockets())
		{
			consoleLogError("Can't listen other sockets.");
			return false;
		}
		else
		{
			consoleLogSuccess("Successfuly listening other sockets...");
			return true;
		}
	}



	void Server::logSuccessfulyRecivedMessage(uint16_t _port) noexcept
	{
		consoleLogTime(Chat::Console::EColor::White, Chat::Console::EColor::Purpule);
		consoleLogSuccess("Message successfuly recived from port:", false);
		Chat::Console::setConsoleColor(Chat::Console::EColor::Blue);
		Chat::printCenteringMessage(std::to_string(_port));
		std::cout << std::endl;
	}



	void Server::clientsMessagesHandler(size_t _index) noexcept
	{
		while (m_clients.size() == _index)
		{
		}

		while (!m_is_finish_server)
		{
			std::string packet = m_clients[_index].first.reciveMessage();

			Chat::MessagePacket message(std::move(packet));

			if (message.getMessage() == "" || message.getMessage() == "/SERVER: unplug")
			{
				m_clients[_index].first.unplug();
				break;
			}
			m_message_mutex.lock();
			m_all_messages.emplace_back(message);
			m_message_mutex.unlock();

			logSuccessfulyRecivedMessage(m_clients[_index].first.getPortInfo());
			
			std::lock_guard<std::mutex> client_guard(m_clients_mutex);
			for (const auto& client : m_clients)
			{
				if (client.first.isConnected())
				{
					if (!client.first.reciveMessage(message.getSender(), message.getMessage()))
					{
						consoleLogError("Can't send message to port:\t" + std::to_string(client.first.getPortInfo()));
					}
				}
			}
		}
	}



	void Server::acceptClientsHandler() noexcept
	{
		while (!m_is_finish_server)
		{
			Chat::Socket client_socket;
			try
			{
				client_socket = m_socket.acceptOtherSocket();
				consoleLogSuccess("Successfully connected new client:");
				consoleLogSocketAddress(_IP_ADDRESS_, client_socket.getPort());

				std::string client_username = client_socket.reciveData();

				if (!client_username.empty())
				{
					User new_user(client_username, std::move(client_socket));

					sendAllMessagesToUser(new_user);

					std::thread messages_handler(clientsMessagesHandler, m_clients.size());
					messages_handler.detach();

					m_clients.emplace_back(std::move(new_user), std::move(messages_handler));
				}
			}
			catch (...)
			{
				if (!m_is_finish_server)
				{
					consoleLogError("Can't accept other socket.");
				}
				char get = _getch();
			}
		}
	}



	void Server::commandServerHandler() noexcept
	{
		while (!m_is_finish_server)
		{
			char option = _getch();

			switch (option)
			{
			case KeyBoard::Escape:
				m_is_finish_server = true;
				break;
			case KeyBoard::Slesh:
				std::string command;
				printLine(" => Input command:\t", false);
				std::cin >> command;		
				std::cout << std::endl;

				if (command == "users")
				{
					printLine("All Users : \n");
					printAllUsers();
				}
				else
				{
					consoleLogError("Unknowing command");
				}
				break;
			}
		}
	}



	void Server::sendAllMessagesToUser(const User& _user) noexcept
	{
		if (!m_all_messages.empty())
		{
			m_message_mutex.lock();
			std::string big_message_paket;
			for (const Chat::MessagePacket& packet : m_all_messages)
			{
				big_message_paket += packet.getSender() + '|' + packet.getMessage();
			}
			_user.reciveMessage(big_message_paket);
			m_message_mutex.unlock();
		}
		else
		{
			std::string message = "NONE";
			_user.reciveMessage(std::move(message));
		}
	}



	bool Server::run() noexcept
	{
		printLine(" => RUNNING SERVER...\n", true, Chat::Console::EColor::White, Chat::Console::EColor::Purpule);

		if (!socketsInitialization())
		{
			return false;
		}
		if (!initServerSocket())
		{
			return false;
		}
		if (!bindServerSocket())
		{
			return false;
		}
		if (!startLinstenigOtherSockets())
		{
			return false;
		}



		std::thread client_accepting_handler(acceptClientsHandler);
		
		std::thread close_server_handler(commandServerHandler);



		close_server_handler.join();
		client_accepting_handler.detach();


		Chat::Socket::closeAllSockets();


		printLine(" => SERVER FINISHES WORK...\n", true, Chat::Console::EColor::White, Chat::Console::EColor::Purpule);

		return true;
	}



	void Server::finish() noexcept
	{
		m_is_finish_server = true;
	}



	const std::string& Server::getIPAddress() noexcept
	{
		return _IP_ADDRESS_;
	}



	uint16_t Server::getPort() noexcept
	{
		return _PORT_;
	}



	void Server::printAllUsers() noexcept
	{
		if (!m_clients.empty())
		{
			for (const auto& client : m_clients)
			{
				if (client.first.isConnected())
				{
					Console::setConsoleColor(Console::EColor::LightPurple);
					std::cout << ".............." << client.first.getUsername() << "\n\n";
				}
				else
				{
					Console::setConsoleColor(Console::EColor::Red);
					std::cout << ".............." << client.first.getUsername() << " - unplug" << "\n\n";
				}
			}
		}
		else
		{
			consoleLogError("Hasn't connected users.");
		}
	}
}