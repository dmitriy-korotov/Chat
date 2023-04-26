#pragma once
#ifndef CLIENT_H
#define CLIENT_H

#include "Socket.h"
#include "../Interface/InputArea.h"



namespace Chat
{
	class ClientChat
	{
	public:

		ClientChat() = delete;
		~ClientChat() = delete;

		static bool run() noexcept;
		static void finish() noexcept;

		static void setChatSize(uint16_t _console_width, uint16_t _console_height) noexcept;

		static const std::string& getServerIPAddress() noexcept;
		static uint16_t getServerPort() noexcept;

	private:

		static bool socketsInitialization() noexcept;
		static bool initClientSocket() noexcept;
		static bool connectToServer() noexcept;
		static void inputUsername() noexcept;
		static void inputMessagesHandler() noexcept;
		static void reciveMessagesHandler() noexcept;


		static uint16_t m_console_width;
		static uint16_t m_console_height;

		static Chat::Socket m_socket;

		static const EAddressFamily _SERVER_ADDRESS_FAMILY_;
		static const std::string _SERVER_IP_ADDRESS_;
		static const uint16_t _SERVER_PORT_;

		static bool is_finish;
		
		static Chat::InputArea m_input_area;

		static std::string m_client_username;

	};
}

#endif // !CLIENT_H
