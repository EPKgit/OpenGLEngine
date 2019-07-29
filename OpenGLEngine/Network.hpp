#ifndef _NETWORK_HPP
#define _NETWORK_HPP

#include <winsock2.h>
#include <windows.h>
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

	void StartWindowsSockets(WSAData &wsaData);

	void PopulateAddrinfo(	ADDRINFO &hints, int family = AF_INET, int sockType = SOCK_STREAM,
		int protocol = IPPROTO_TCP, int flags = AI_PASSIVE) noexcept;

	void ResolveAddrinfo(	ADDRINFO &hints, ADDRINFOA **result, 
							const PCSTR hostName = constants::defaultHostName, 
							const PCSTR portNum = constants::defaultPort);
	void FreeAddrinfo(ADDRINFO *addr);

	void CreateSocket(SOCKET &newSocket, ADDRINFOA &result);

	void BindSocket(SOCKET &listeningSocket, ADDRINFOA &result);

	void ListenSocket(SOCKET &listeningSocket);

	void AcceptConnection(SOCKET &listeningSocket, SOCKET &clientSocket, sockaddr *address = NULL, int *len = NULL);

	enum ConnectionReturn { Success = 1, Failure = 0, Timeout = -1};
	int AttemptConnection(SOCKET &connectionSocket, ADDRINFOA *result, int attemptNo);

	void ShutdownSocket(SOCKET &socket, int closeType = SD_SEND);
}



#endif // !_NETWORK_HPP
