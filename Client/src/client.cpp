#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <vector>

#pragma comment(lib, "Ws2_32.lib")

int main(int argc, char** argv)
{
	WSADATA ws_data;

	if (WSAStartup(MAKEWORD(2, 2), &ws_data))
	{
		std::cout << "Error WinSock version initialisation # " << WSAGetLastError() << std::endl;
		return 1;
	}

	SOCKET client_socket = socket(AF_INET, SOCK_STREAM, 0);

	if (client_socket == INVALID_SOCKET)
	{
		std::cout << "Error initialisation socket # " << WSAGetLastError() << std::endl;
		closesocket(client_socket);
		WSACleanup();
		return 1;
	}
	else
	{
		std::cout << "Access client socket initialization" << std::endl;
	}

	in_addr ip_to_num;
	std::memset(&ip_to_num, 0, sizeof(ip_to_num));

	if (inet_pton(AF_INET, "127.0.0.1", &ip_to_num) <= 0)
	{
		std::cout << "Error in IP translation to special numeric format" << std::endl;
		return 1;
	}

	sockaddr_in server_info;
	std::memset(&server_info, 0, sizeof(server_info));

	server_info.sin_family = AF_INET;
	server_info.sin_addr = ip_to_num;
	server_info.sin_port = htons(2000);

	if (connect(client_socket, reinterpret_cast<sockaddr*>(&server_info), sizeof(server_info)))
	{
		std::cout << "Error Socket binding to server info. Error # " << WSAGetLastError() << std::endl;
		closesocket(client_socket);
		WSACleanup();
		return 1;
	}
	else
	{
		std::cout << "Access connecting to server\n" << std::endl;
	}

	std::vector<char> server_buffer(1024, '\n');
	std::vector<char> client_buffer(1024, '\n');

	short packet_size = 0;

	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

	while (true)
	{
		SetConsoleTextAttribute(h, 2);
		std::cout << "Your message: ";
		fgets(client_buffer.data(), client_buffer.capacity(), stdin);
		SetConsoleTextAttribute(h, 3);

		if (client_buffer[0] == 'x' && client_buffer[1] == 'x' && client_buffer[2] == 'x') {
			shutdown(client_socket, SD_BOTH);
			closesocket(client_socket);
			closesocket(client_socket);
			WSACleanup();
			SetConsoleTextAttribute(h, 4);
			return 0;
		}

		packet_size = send(client_socket, client_buffer.data(), client_buffer.size(), 0);

		if (packet_size == SOCKET_ERROR)
		{
			std::cout << "Can't send message to Server. Error # " << WSAGetLastError() << std::endl;
			closesocket(client_socket);
			closesocket(client_socket);
			WSACleanup();
			return 1;
		}

		packet_size = recv(client_socket, server_buffer.data(), server_buffer.capacity(), 0);

		std::cout << "\nServer's message: " << server_buffer.data() << std::endl;
	}

	return 0;
}
