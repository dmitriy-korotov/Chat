#pragma once
#ifndef SOCKET_H
#define SOCKET_H

#include <iostream>
#include <Winsock2.h>
#include <WS2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")



static constexpr uint8_t BINDED = 0;
static constexpr uint8_t ZERO_PORT = 0;
static constexpr uint8_t SOCKET_VERSION_1 = 2;
static constexpr uint8_t SOCKET_VERSION_2 = 2;



namespace Web
{
	enum class EAddressFamily : uint8_t
	{
		AF_Inet = AF_INET,
		AF_Unix = AF_UNIX,
		AF_Inet6 = AF_INET6,
		AF_Ipx = AF_IPX
	};

	enum class ESocketType : uint8_t
	{
		SocketStream = SOCK_STREAM,
		SocketDGRAM = SOCK_DGRAM,
		SocketSEQPacket = SOCK_SEQPACKET,
		SocketRaw = SOCK_RAW,
		SocketRDM = SOCK_RDM
	};

	enum class EProtocolType : uint8_t
	{
		Default = 0
	};



	class Socket
	{
	private:

		using Port = uint16_t;

	public:

		Socket(const Socket&) = delete;
		Socket& operator=(const Socket&) = delete;



		Socket() = default;
		Socket(EAddressFamily _address_family, ESocketType _socket_type, EProtocolType _protocol_type = EProtocolType::Default);
		Socket(Socket&& _other_socket) noexcept;
		Socket& operator=(Socket&& _other_socket) noexcept;
		~Socket();



		EAddressFamily getAddressFamity() const noexcept;
		Port getPort() const noexcept;

		void swap(Socket& _other_socket);

		bool isValid() const noexcept;
		bool bindSocket(EAddressFamily _address_family, const std::string& _ip_address, Port _port);
		bool connectToOtherSocket(const std::string& _ip_address, Port _port) const noexcept;
		bool listenOtherSockets(unsigned int _max_listened_sockets = SOMAXCONN) const noexcept;
		Socket acceptOtherSocket() const;
		std::string reciveData(size_t _buffer_size = 1024) const noexcept;
		bool sendData(const std::string& _message) const noexcept;
		void close() noexcept;

		static bool initSockets() noexcept;
		static int getLastError() noexcept;
		static void closeAllSockets() noexcept;

	private:

		Socket(const SOCKET& _socket, EAddressFamily _address_family, Port _port);

		in_addr transformToNumericFormat(const std::string& _ip_address) const;
		sockaddr_in createSocketAddress(const in_addr& _address, Port _port) const noexcept;

		static Port getSocketPort(const SOCKET& _socket);

		
		static WSADATA m_ws_data;

		SOCKET m_socket = INVALID_SOCKET;
		EAddressFamily m_address_family = EAddressFamily::AF_Inet;
		Port m_port = 0;
	};
}

#endif // SOCKET_H
