#include "Socket.h"

#include <vector>

namespace Web
{
	WSADATA Socket::m_ws_data;



	Socket::Socket(EAddressFamily _address_family, ESocketType _socket_type, EProtocolType _protocol_type)
		: m_address_family(_address_family)
	{
		m_socket = socket(static_cast<int>(_address_family), static_cast<int>(_socket_type), static_cast<int>(_protocol_type));
	}



	Socket::Socket(const SOCKET& _socket, EAddressFamily _address_family, Port _port)
		: m_socket(_socket)
		, m_address_family(_address_family)
		, m_port(_port)
	{ }



	Socket::Socket(Socket&& _other_socket) noexcept
		: m_address_family(_other_socket.m_address_family)
		, m_port(_other_socket.m_port)
		, m_socket(_other_socket.m_socket)
	{
		_other_socket.m_socket = 0;
		_other_socket.m_port = 0;
		_other_socket.m_address_family = EAddressFamily::AF_Inet;
	}



	Socket& Socket::operator=(Socket&& _other_socket) noexcept
	{
		if (this != &_other_socket)
		{
			Socket socket = std::move(_other_socket);
			swap(socket);
		}
		return *this;
	}



	Socket::~Socket()
	{
		close();
	}



	EAddressFamily Socket::getAddressFamity() const noexcept
	{
		return m_address_family;
	}



	uint16_t Socket::getPort() const noexcept
	{
		return m_port;
	}



	void Socket::swap(Socket& _other_socket)
	{
		std::swap(m_address_family, _other_socket.m_address_family);
		std::swap(m_port, _other_socket.m_port);
		std::swap(m_socket, _other_socket.m_socket);
	}



	bool Socket::isValid() const noexcept
	{
		return !(m_socket == INVALID_SOCKET);
	}



	bool Socket::bindSocket(EAddressFamily _address_family, const std::string& _ip_address, Port _port)
	{
		in_addr numeric_address;
		std::memset(&numeric_address, 0, sizeof(numeric_address));
		numeric_address = transformToNumericFormat(_ip_address);

		sockaddr_in socket_address = createSocketAddress(numeric_address, _port);

		if (bind(m_socket, reinterpret_cast<sockaddr*>(&socket_address), sizeof(socket_address)) == BINDED)
		{
			m_port = _port;
			return true;
		}
		else
		{
			return false;
		}
	}



	bool Socket::connectToOtherSocket(const std::string& _ip_address, Port _port) const noexcept
	{
		in_addr numeric_ip_address;
		std::memset(&numeric_ip_address, 0, sizeof(numeric_ip_address));
		sockaddr_in socket_info;
		std::memset(&socket_info, 0, sizeof(socket_info));

		try
		{
			numeric_ip_address = transformToNumericFormat(_ip_address);
			socket_info = createSocketAddress(numeric_ip_address, _port);
		}
		catch (...)
		{
			return false;
		}

		return !connect(m_socket, reinterpret_cast<sockaddr*>(&socket_info), sizeof(socket_info));
	}



	in_addr Socket::transformToNumericFormat(const std::string& _ip_address) const
	{
		in_addr address;
		std::memset(&address, 0, sizeof(address));

		if (inet_pton(static_cast<int>(m_address_family), _ip_address.c_str(), &address) > 0)
		{
			return address;
		}
		else
		{
			throw std::exception("Error in IP translation to special numeric format.");
		}
	}



	sockaddr_in Socket::createSocketAddress(const in_addr& _address, Port _port) const noexcept
	{
		sockaddr_in socket_info = { static_cast<unsigned short>(m_address_family), htons(_port), _address };
		return socket_info;
	}



	bool Socket::listenOtherSockets(unsigned int _max_listened_sockets) const noexcept
	{
		return !listen(m_socket, static_cast<int>(_max_listened_sockets));
	}



	Socket Socket::acceptOtherSocket() const
	{
		sockaddr_in socket_info;
		std::memset(&socket_info, 0, sizeof(socket_info));
		int size_socket_info = sizeof(socket_info);

		SOCKET socket = accept(m_socket, reinterpret_cast<sockaddr*>(&socket_info), &size_socket_info);
		
		if (socket == INVALID_SOCKET)
		{
			closesocket(socket);
			throw std::exception("Error connecting to socket.");
		}
		else
		{
			Port port = 0;

			try
			{
				port = getSocketPort(socket);
			}
			catch (...)
			{
				closesocket(socket);
				throw;
			}

			Socket connected_socket(socket, m_address_family, port);
			return connected_socket;
		}

	}



	Socket::Port Socket::getSocketPort(const SOCKET& _socket)
	{
		sockaddr_in socket_info;
		std::memset(&socket_info, 0, sizeof(socket_info));
		int size_socket_info = sizeof(socket_info);

		if (getpeername(_socket, reinterpret_cast<sockaddr*>(&socket_info), &size_socket_info))
		{
			throw std::exception("Can't get socket port.");
		}
		else
		{
			return socket_info.sin_port;
		}
	}



	std::string Socket::reciveData(size_t _buffer_size) const noexcept
	{
		std::vector<char> buff(_buffer_size);

		if (recv(m_socket, buff.data(), static_cast<int>(_buffer_size), 0) > 0)
		{
			return std::string(buff.data());
		}
		else
		{
			return std::string();
		}
	}



	bool Socket::sendData(const std::string& _message) const noexcept
	{
		return send(m_socket, _message.c_str(), _message.length(), 0) != SOCKET_ERROR;
	}



	void Socket::close() noexcept
	{
		if (m_socket != 0)
		{
			closesocket(m_socket);
			m_port = 0;
			m_socket = 0;
		}
	}



	bool Socket::initSockets() noexcept
	{
		return !WSAStartup(MAKEWORD(SOCKET_VERSION_1, SOCKET_VERSION_2), &m_ws_data);
	}



	void Socket::closeAllSockets() noexcept
	{
		WSACleanup();
	}



	int Socket::getLastError() noexcept
	{
		return WSAGetLastError();
	}
}