#include "Client.h"

#include "ConsoleLogFunctions.h"

#include "MessagePacket.h"
#include "../Interface/OutputMessagesControler.h"

#include <conio.h>



static constexpr uint8_t INPUT_AREA_HEIGHT = 3;



namespace Chat
{
	uint16_t ClientChat::m_console_width = 120;
	uint16_t ClientChat::m_console_height = 30;

	Chat::Socket ClientChat::m_socket;

	const EAddressFamily ClientChat::_SERVER_ADDRESS_FAMILY_ = Chat::EAddressFamily::AF_Inet;
	const std::string ClientChat::_SERVER_IP_ADDRESS_ = "127.0.0.1";
	const uint16_t ClientChat::_SERVER_PORT_ = 2000u;

	bool ClientChat::is_finish = false;

	Chat::InputArea ClientChat::m_input_area;

	std::string ClientChat::m_client_username;





	bool ClientChat::socketsInitialization() noexcept
	{
		if (!Chat::Socket::initSockets())
		{
			consoleLogError("Can't initialiezed sockets.");
			return false;
		}
		return true;
	}



	bool ClientChat::initClientSocket() noexcept
	{
		m_socket.init(Chat::EAddressFamily::AF_Inet, Chat::ESocketType::SocketStream);
		if (!m_socket.isValid())
		{
			consoleLogError("Can't creating clinet socket");
			return false;
		}
		return true;
	}



	bool ClientChat::connectToServer() noexcept
	{
		if (!m_socket.connectToOtherSocket(_SERVER_IP_ADDRESS_, _SERVER_PORT_))
		{
			consoleLogError("Can't connect to server:");
			consoleLogSocketAddress(_SERVER_IP_ADDRESS_, _SERVER_PORT_);
			return false;
		}
		return true;
	}



	void ClientChat::inputUsername() noexcept
	{
		std::string label_for_input_username = "INPUT YOUR NAME:";
		Chat::Console::moveConsoleCursor(Chat::ConsoleCoords(m_console_width / 2 - label_for_input_username.length() / 2, m_console_height / 2));
		Chat::Console::setConsoleColor(Chat::Console::EColor::Purpule);
		std::cout << "INPUT YOUR NAME: ";
		Chat::Console::setConsoleColor(Chat::Console::EColor::White);
		std::cin >> m_client_username;
		Chat::Console::clearStdInBuffer();
		Chat::Console::clear();
	}



	void ClientChat::inputMessagesHandler() noexcept
	{
		std::string buffer_to_input_messages;

		while (!is_finish)
		{
			buffer_to_input_messages = m_input_area.inputMessage();

			if (buffer_to_input_messages == "end\n" || buffer_to_input_messages == "END\n")
			{
				m_socket.close();
				break;
			}


			if (buffer_to_input_messages != "" && buffer_to_input_messages != "\n")
			{
				if (!m_socket.sendMessage(m_client_username, buffer_to_input_messages))
				{
					consoleLogError("Can't send message.");
				}
			}
		}
	}



	void ClientChat::reciveMessagesHandler() noexcept
	{
		while (!is_finish)
		{
			Chat::MessagePacket msg_packet(m_socket.reciveData());

			if (msg_packet.getMessage() != "")
			{
				if (msg_packet.getSender() == m_client_username)
				{
					Chat::OutputMessagesControler::printMessage("You", msg_packet.getMessage());
				}
				else
				{
					Chat::OutputMessagesControler::printMessage(msg_packet.getSender(), msg_packet.getMessage());
				}
				m_input_area.setCursorOnInput();
			}
			else
			{
				m_socket.close();
				break;
			}
		}
	}



	bool ClientChat::run() noexcept
	{
		if (m_console_width == 0 || m_console_height == 0)
		{
			return false;
		}
		else
		{
			Chat::Console::setConsoleSize(Chat::ConsoleCoords(m_console_width, m_console_height));
		}
		if (!socketsInitialization())
		{
			return false;
		}
		if (!initClientSocket())
		{
			return false;
		}
		if (!connectToServer())
		{
			return false;
		}
		//inputUsername();

		m_input_area.create(INPUT_AREA_HEIGHT);

		std::thread input_message_handler(inputMessagesHandler);

		std::thread recive_message_handler(reciveMessagesHandler);



		recive_message_handler.join();
		input_message_handler.join();



		Chat::Socket::closeAllSockets();

		return true;
	}



	void ClientChat::finish() noexcept
	{
		is_finish = true;
	}



	void ClientChat::setChatSize(uint16_t _console_width, uint16_t _console_height) noexcept
	{
		Chat::Console::setConsoleSize(Chat::ConsoleCoords(_console_width, _console_height));
		m_console_width = _console_width;
		m_console_height = _console_height;
	}



	const std::string& ClientChat::getServerIPAddress() noexcept
	{
		return _SERVER_IP_ADDRESS_;
	}



	uint16_t ClientChat::getServerPort() noexcept
	{
		return _SERVER_PORT_;
	}
}