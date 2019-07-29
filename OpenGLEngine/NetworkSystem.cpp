#include "NetworkSystem.hpp"

//#include <windows.h>
//#include <winsock2.h>
//#include <ws2tcpip.h>
//#include <iphlpapi.h>
//#include <stdio.h>
//#include <iostream>

#include "EntityManager.hpp"
#include "NetworkComponent.hpp"
#include "Time.hpp"
#include "Network.hpp"

//#pragma push_macro("GetCurrentTime()")
//#undef GetCurrentTime()
//#undef GetCurrentTotalTime()
NetworkSystem::NetworkSystem()
{
	std::shared_ptr<NetworkComponent> nptr = em->getSingletonEntity()->addComp<NetworkComponent>();
	network::StartWindowsSockets(nptr->wsaData);
	network::CreateSocket(nptr->socket, nptr->addr);
	network::PopulateAddrinfo(nptr->addr, AF_INET, SOCK_STREAM, IPPROTO_TCP);
	network::ResolveAddrinfo(nptr->addr, &nptr->result);
	nptr->runMethod = &HandleConnecting;
}

void NetworkSystem::Run(float deltaTime)
{
	std::shared_ptr<NetworkComponent> nptr = em->getSingletonEntity()->getComp<NetworkComponent>();
	while (nptr->lastNetworkTick < Time::GetInstance()->GetCurrentTotalTime())
	{
		nptr->lastNetworkTick += constants::timePerNetworkTick;
		(*this.*nptr->runMethod)(nptr);
	}
}


void NetworkSystem::CreateLobby(std::shared_ptr<NetworkComponent> nptr)
{
	network::FreeAddrinfo(nptr->result);
	network::ResolveAddrinfo(nptr->addr, &nptr->result, NULL);
	network::BindSocket(nptr->socket, *nptr->result);
	network::FreeAddrinfo(nptr->result);
	network::ListenSocket(nptr->socket);
}

void NetworkSystem::HandleConnecting(std::shared_ptr<NetworkComponent> nptr)
{
	int result = network::AttemptConnection(nptr->socket, nptr->result, nptr->connectionAttempts++);
	switch (result)
	{
	case network::ConnectionReturn::Success:
		nptr->isConnecting = false;
		nptr->runMethod = &HandleClient;
		break;
	case network::ConnectionReturn::Failure:
		break;
	case network::ConnectionReturn::Timeout:
		nptr->isHost = true;
		CreateLobby(nptr);
		nptr->isConnecting = false;
		nptr->runMethod = &HandleHost;
		break;
	}
}

void NetworkSystem::HandleHost(std::shared_ptr<NetworkComponent> nptr)
{
	FD_ZERO(&nptr->fds);
	for (SOCKET s : nptr->connectedSockets)
	{
		FD_SET(s, &nptr->fds);
	}
	int retval = select(nptr->fds.fd_count, &nptr->fds, NULL, NULL, NULL);
	for (int x = 0; x < nptr->fds.fd_count; ++x)
	{

	}

}

void NetworkSystem::HandleClient(std::shared_ptr<NetworkComponent> nptr)
{
}
