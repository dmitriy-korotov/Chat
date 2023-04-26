#pragma once
#ifndef SERVER_H
#define SERVER_H

#include "Socket.h"

#include <vector>
#include <mutex>
#include <string>



namespace Chat
{
	class Server
	{
	public:

		Server() = delete;
		~Server() = delete;

		static bool run() noexcept;
		static void finish() noexcept;

		static const std::string& getIPAddress() noexcept;
		static uint16_t getPort() noexcept;

	private:

		static bool socketsInitialization() noexcept;
		static bool initServerSocket() noexcept;
		static bool bindServerSocket() noexcept;
		static bool startLinstenigOtherSockets() noexcept;
		static void acceptClientsHandler() noexcept;
		static void clientsMessagesHandler(size_t _index) noexcept;
		static void closeServerHandler() noexcept;
		static void logSuccessfulyRecivedMessage(uint16_t _port) noexcept;



		static Chat::Socket m_socket;

		static const Chat::EAddressFamily _ADDRESS_FAMILY_;
		static const std::string _IP_ADDRESS_;
		static const uint16_t _PORT_;



		static std::vector<std::string> m_all_messages;	
		static std::mutex m_message_mutex;
		static bool m_is_finish_server;
		static std::vector<std::pair<Chat::Socket, std::thread>> m_clients;	
		static std::mutex m_clients_mutex;

	};
}

#endif // !SERVER_H
