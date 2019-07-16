#ifndef _NETWORK_HPP
#define _NETWORK_HPP

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <stdio.h>
#include <iostream>

#include "Constants.hpp"

#pragma comment(lib, "Ws2_32.lib")

namespace network
{

	enum class NetworkError
	{
		NetworkStartup = 1,
		ResolveAddrInfo,
		CreateSocket,
		BindSocket,
		ListenSocket,
		AcceptConnection,
		ShutdownSendingSide
	};

	void StartWindowsSockets(WSAData &wsaData)
	{
		int err = WSAStartup(MAKEWORD(2, 2), &wsaData);
		if (err)
		{
			printf("WSAStartup failed with err\"%d\"\n", err);
			throw NetworkError::NetworkStartup;
		}
		printf("WSA started succesfully\n");
	}

	void PopulateAddrinfo(	ADDRINFO &hints, int family = AF_INET, int sockType = SOCK_STREAM,
							int protocol = IPPROTO_TCP, int flags = AI_PASSIVE) noexcept
	{
		memset(&hints, 0, sizeof(hints));
		hints.ai_family = family;
		hints.ai_socktype = sockType;
		hints.ai_protocol = protocol;
		hints.ai_flags = flags;
		printf("Succesfully populated the addrinfo struct\n");
	}

	void ResolveAddrinfo(	ADDRINFO &hints, ADDRINFOA **result, 
							const PCSTR hostName = constants::defaultHostName, 
							const PCSTR portNum = constants::defaultPort)
	{
		int err = getaddrinfo(hostName, portNum, &hints, result);
		if (err)
		{
			printf("getaddrinfo failed: \"%d\"\n", err);
			WSACleanup();
			throw NetworkError::ResolveAddrInfo;
		}
		printf("Succesfully got address info\n");
	}

	void CreateSocket(SOCKET &newSocket, ADDRINFOA &result)
	{
		newSocket = socket(result.ai_family, result.ai_socktype, result.ai_protocol);
		if (newSocket == INVALID_SOCKET) 
		{
			printf("Error at socket(): %ld\n", WSAGetLastError());
			freeaddrinfo(&result);
			WSACleanup();
			throw NetworkError::CreateSocket;
		}
		printf("Succesfully created socket\n");
	}

	void BindSocket(SOCKET &listeningSocket, ADDRINFOA &result)
	{
		int err = bind(listeningSocket, result.ai_addr, result.ai_addrlen);
		if (err == SOCKET_ERROR)
		{
			printf("bind failed with error: %d\n", WSAGetLastError());
			freeaddrinfo(&result);
			closesocket(listeningSocket);
			WSACleanup();
			throw NetworkError::BindSocket;
		}
		printf("Succesfully bound socket to \"%s\"\n", result.ai_addr->sa_data);
	}

	void ListenSocket(SOCKET &listeningSocket)
	{
		int err = listen(listeningSocket, SOMAXCONN);
		if (err == SOCKET_ERROR)
		{
			printf("Listen failed with error: %ld\n", WSAGetLastError());
			closesocket(listeningSocket);
			WSACleanup();
			throw NetworkError::ListenSocket;
		}
		printf("Succesfully listened on port\n");
	}

	void AcceptConnection(SOCKET &listeningSocket, SOCKET &clientSocket, ADDRINFO *address, int *len)
	{
		clientSocket = accept(listeningSocket, address, len);
		if (clientSocket == INVALID_SOCKET) 
		{
			printf("accept failed: %d\n", WSAGetLastError());
			closesocket(listeningSocket);
			WSACleanup();
			throw NetworkError::AcceptConnection;
		}
		printf("Succesfully accepted connection\n");
	}

	void ShutdownClient(SOCKET &socket)
	{
		int err = shutdown(socket, SD_SEND);
		if (err == SOCKET_ERROR)
		{
			printf("shutdown failed with error: %d\n", WSAGetLastError());
			closesocket(socket);
			WSACleanup();
			throw NetworkError::ShutdownSendingSide;
		}
		printf("Succesfully closed sending side of socket\n");
	}
}
#endif // !_NETWORK_HPP
