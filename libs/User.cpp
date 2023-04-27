#include "User.h"



namespace Chat
{
	User::User(const std::string& _username, Socket&& _socket) noexcept
			: m_username(_username)
			, m_socket(std::move(_socket))
	{ }



	User::User(User&& _other) noexcept
			: m_username(std::move(_other.m_username))
			, m_socket(std::move(_other.m_socket))
			, m_is_connecting(_other.m_is_connecting)
	{ }



	User& User::operator=(User&& _right) noexcept
	{
		if (this != &_right)
		{
			User tmp = std::move(_right);
			swap(tmp);
		}
		return* this;
	}



	const std::string& User::getUsername() const noexcept
	{
		return m_username;
	}



	uint16_t User::getPortInfo() const noexcept
	{
		return m_socket.getPort();
	}



	EAddressFamily User::getAddressFamityInfo() const noexcept
	{
		return m_socket.getAddressFamity();
	}



	void User::swap(User& _other) noexcept
	{
		std::swap(m_username, _other.m_username);
		std::swap(m_socket, _other.m_socket);
		std::swap(m_is_connecting, _other.m_is_connecting);
	}



	bool User::sendData(const std::string _data) const noexcept
	{
		return m_socket.sendData(_data.c_str(), _data.size());
	}



	bool User::sendMessage(const std::string& _message) const noexcept
	{
		return m_socket.sendMessage(m_username, _message);
	}



	bool User::reciveMessage(const std::string& _username, const std::string& _message) const noexcept
	{
		return sendData((_username + '|' + _message));
	}



	std::string User::reciveMessage() const noexcept
	{
		return m_socket.reciveData();
	}



	void User::unplug() noexcept
	{
		m_is_connecting = false;
	}



	bool User::isConnected() const noexcept
	{
		return m_is_connecting;
	}
}