#include "Network.hpp"

namespace network
{
	
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

	void PopulateAddrinfo(ADDRINFO &hints, int family, int sockType, int protocol, int flags) noexcept
	{
		memset(&hints, 0, sizeof(hints));
		hints.ai_family = family;
		hints.ai_socktype = sockType;
		hints.ai_protocol = protocol;
		hints.ai_flags = flags;
		printf("Succesfully populated the addrinfo struct\n");
	}

	void ResolveAddrinfo(ADDRINFO &hints, ADDRINFOA **result, const PCSTR hostName, const PCSTR portNum)
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

	void FreeAddrinfo(ADDRINFO *addr)
	{
		freeaddrinfo(addr);
	}

	void CreateSocket(SOCKET &newSocket, ADDRINFOA *result)
	{
		newSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
		if (newSocket == INVALID_SOCKET)
		{
			printf("Error at socket(): %ld\n", WSAGetLastError());
			freeaddrinfo(result);
			WSACleanup();
			throw NetworkError::CreateSocket;
		}
		printf("Succesfully created socket\n");
	}

	void SetSocketNonblocking(SOCKET &socket)
	{
		u_long mode = 1; //nonblocking mode
		int err = ioctlsocket(socket, FIONBIO, &mode);
		if (err != NO_ERROR)
		{
			printf("Error setting the socket to be nonblocking\n");
			throw NetworkError::Nonblocking;
		}
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

	void AcceptConnection(SOCKET &listeningSocket, SOCKET &clientSocket, sockaddr * address, int * len)
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

	namespace //anonymous namespace so that attempting to connect won't use our internal function
	{
		bool ConnectToServer(SOCKET &connectionSocket, ADDRINFOA *result)
		{
			int err = connect(connectionSocket, result->ai_addr, result->ai_addrlen);
			if (err == SOCKET_ERROR)
			{
				closesocket(connectionSocket);
				//WSACleanup();
				connectionSocket = INVALID_SOCKET;
				printf("Unable to connect to server with err:%d!\n", WSAGetLastError());
				return false;
			}
			printf("Succesfully connected to the server\n");
			return true;
		}
	}

	int AttemptConnection(SOCKET &connectionSocket, ADDRINFOA *result, int attemptNo)
	{
		if (attemptNo < constants::NUMBER_OF_ATTEMPTS)
		{
			int x = 0;
			for (PADDRINFOA ptr = result; ptr != NULL; ptr = ptr->ai_next)
			{
				CreateSocket(connectionSocket, ptr);
				SetSocketNonblocking(connectionSocket);
				printf("Attemping to connect #%d-%d\n", attemptNo, ++x);
				if (ConnectToServer(connectionSocket, ptr))
				{
					freeaddrinfo(result);//successful connection
					return ConnectionReturn::Success;
				}
			}
			return ConnectionReturn::Failure;
		}
		return ConnectionReturn::Timeout;
	}

	void ShutdownSocket(SOCKET &socket, int closeType)
	{
		int err = shutdown(socket, closeType);
		if (err == SOCKET_ERROR)
		{
			printf("shutdown failed with error: %d\n", WSAGetLastError());
			closesocket(socket);
			WSACleanup();
			throw NetworkError::ShutdownSendingSide;
		}
		printf("Succesfully closed sending side of socket\n");
	}

	void CloseSocket(SOCKET &socket)
	{
		closesocket(socket);
	}
}