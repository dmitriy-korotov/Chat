#include <iostream>
//#include <Winsock2.h>
//#include <WS2tcpip.h>
//#include <vector>
//#include <chrono>
//#include <Windows.h>
//
//#pragma comment(lib, "ws2_32.lib")

#include "/Users/User/MyProjects/Chat/libs/Socket.h"

int main(int argc, char** argv)
{
	/*WSADATA wsData;

	if (WSAStartup(MAKEWORD(2, 2), &wsData))
	{
		std::cout << "Error WinSock version initialisation # " << WSAGetLastError() << std::endl;
		return 1;
	}

	SOCKET server_socket = socket(AF_INET, SOCK_STREAM, 0);

	if (server_socket == INVALID_SOCKET)	
	{
		std::cout << "Error initialisation socket # " << WSAGetLastError() << std::endl;
		closesocket(server_socket);
		WSACleanup();
		return 1;
	}
	else
	{
		std::cout << "Access server socket initialization" << std::endl;
	}

	in_addr ip_to_num;
	std::memset(&ip_to_num, 0, sizeof(ip_to_num));
	
	if (inet_pton(AF_INET, "127.0.0.1", &ip_to_num) <= 0)
	{
		std::cout << "Error in IP translation to special numeric format" << std::endl;
		return 1;
	}

	sockaddr_in server_info;
	ZeroMemory(&server_info, sizeof(server_info));

	server_info.sin_family = AF_INET;
	server_info.sin_addr = ip_to_num;
	server_info.sin_port = htons(2000);

	if (bind(server_socket, reinterpret_cast<sockaddr*>(&server_info), sizeof(server_info)))
	{
		std::cout << "Error Socket binding to server info. Error # " << WSAGetLastError() << std::endl;
		closesocket(server_socket);
		WSACleanup();
		return 1; 
	}
	else
	{
		std::cout << "Access binding socket" << std::endl;
	}

	if (listen(server_socket, SOMAXCONN))
	{
		std::cout << "Can't start to listen to. Error # " << WSAGetLastError() << std::endl;
		closesocket(server_socket);
		WSACleanup();
		return 1;
	}
	else
	{
		std::cout << "Listening..." << std::endl;
	}

	sockaddr_in client_info;
	std::memset(&client_info, 0, sizeof(client_info));

	int size_client_info = sizeof(client_info);

	SOCKET client_connect = accept(server_socket, reinterpret_cast<sockaddr*>(&client_info), &size_client_info);

	if (client_connect == INVALID_SOCKET)
	{
		std::cout << "Error connecting to a client" << std::endl;
		closesocket(server_socket);
		closesocket(client_connect);
		WSACleanup();
		return 1;
	}

	std::vector<char> server_buffer(1024, '\0');
	std::vector<char> client_buffer(1024, '\0');

	short packet_size = 0;

	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

	

	while (true)
	{
		SetConsoleTextAttribute(h, 2);
		packet_size = recv(client_connect, client_buffer.data(), client_buffer.capacity(), 0);
		std::cout << "\nClient's message: " << client_buffer.data() << std::endl;
		SetConsoleTextAttribute(h, 3);

		std::cout << "Your (host) message: ";
		fgets(server_buffer.data(), server_buffer.capacity(), stdin);


		if (server_buffer[0] == 'x' && server_buffer[1] == 'x' && server_buffer[2] == 'x') {
			shutdown(server_socket, SD_BOTH);
			closesocket(server_socket);
			closesocket(client_connect);
			WSACleanup();
			SetConsoleTextAttribute(h, 4);
			return 0;
		}

		packet_size = send(client_connect, server_buffer.data(), server_buffer.size(), 0);

		if (packet_size == SOCKET_ERROR)
		{
			std::cout << "Can't send message to Client. Error # " << WSAGetLastError() << std::endl;
			closesocket(server_socket);
			closesocket(client_connect);
			WSACleanup();
			return 1;
		}
	}*/

	Web::Socket::initSockets();

	Web::Socket socket(Web::EAddressFamily::AF_Inet, Web::ESocketType::SocketStream);

	socket.bindSocket(Web::EAddressFamily::AF_Inet, "127.0.0.1", 2000);

	socket.listenOtherSockets();

	Web::Socket client_socket = socket.acceptOtherSocket();

	std::string message;

	while (true)
	{
		std::string message = client_socket.reciveData();

		std::cout << message << std::endl;

		std::cin >> message;

		if (message == "end")
		{
			break;
		}

		client_socket.sendData("message");

	}

	Web::Socket::closeAllSockets();

	return 0;
}

