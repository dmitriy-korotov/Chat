#pragma once
#ifndef USER_H
#define USER_H

#include "Socket.h"

#include <string>



namespace Chat
{
	class User
	{
	public:

		User(const User&) = delete;
		User& operator=(const User&) = delete;

		User(const std::string& _username, Socket&& _socket) noexcept;
		User(User&& _other) noexcept;
		User& operator=(User&& _right) noexcept;

		const std::string& getUsername() const noexcept;
		uint16_t getPortInfo() const noexcept;
		EAddressFamily getAddressFamityInfo() const noexcept;

		void swap(User& _other) noexcept;

		bool reciveMessage(const std::string& _username, const std::string& _message) const noexcept;
		bool reciveMessage(const std::string& _message) const noexcept;
		std::string reciveMessage() const noexcept;
		void unplug() noexcept;
		bool isConnected() const noexcept;

	private:

		bool sendData(const std::string _data) const noexcept;
		bool sendMessage(const std::string& _message) const noexcept;



		std::string m_username = "None";
		Socket m_socket;

		bool m_is_connecting = true;

	};
}

#endif // !USER_H
