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



	std::vector<std::string> Server::m_all_messages;
	std::mutex Server::m_message_mutex;
	bool Server::m_is_finish_server = false;
	std::vector<std::pair<Chat::Socket, std::thread>> Server::m_clients;
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
			std::string packet = m_clients[_index].first.reciveData();
			if (packet == "")
			{
				break;
			}
			m_message_mutex.lock();
			m_all_messages.push_back(packet);
			m_message_mutex.unlock();

			logSuccessfulyRecivedMessage(m_clients[_index].first.getPort());
			
			std::lock_guard<std::mutex> client_guard(m_clients_mutex);
			for (const auto& client : m_clients)
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

				m_message_mutex.lock();
				for (const std::string& packet : m_all_messages)
				{
					m_socket.sendData(packet.c_str(), packet.size());
				}
				m_message_mutex.unlock();

				std::thread messages_handler(clientsMessagesHandler, m_clients.size());
				messages_handler.detach();

				m_clients.emplace_back(std::move(client_socket), std::move(messages_handler));
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



	void Server::closeServerHandler() noexcept
	{
		while (!m_is_finish_server)
		{
			m_is_finish_server = (_getch() == Chat::KeyBoard::Escape);
		}
	}



	bool Server::run() noexcept
	{
		Chat::Console::setConsoleColor(Chat::Console::EColor::White, Chat::Console::EColor::Purpule);
		std::cout << " => RUNNING SERVER...\n\n";

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


		// Threads
		std::thread client_accepting_handler(acceptClientsHandler);
		
		std::thread close_server_handler(closeServerHandler);

		close_server_handler.join();
		client_accepting_handler.detach();


		Chat::Socket::closeAllSockets();


		Chat::Console::setConsoleColor(Chat::Console::EColor::White, Chat::Console::EColor::Purpule);
		std::cout << " => SERVER FINISHES WORK...\n\n";

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
}