#include "NetworkSystem.hpp"

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
	network::PopulateAddrinfo(nptr->addr, AF_UNSPEC, SOCK_STREAM, IPPROTO_TCP);
	network::ResolveAddrinfo(nptr->addr, &nptr->result);
	nptr->runMethod = &NetworkSystem::HandleConnecting;//we start by trying to connect a few times
										//if that fails then we become the host
}

void NetworkSystem::Run(float deltaTime)
{
	
	std::shared_ptr<NetworkComponent> nptr = em->getSingletonEntity()->getComp<NetworkComponent>();
	while (nptr->lastNetworkTick < Time::GetInstance()->GetCurrentTotalTime())
	{
		printf("____________________________\nNetwork Run at %f vs %f\n\n", nptr->lastNetworkTick, Time::GetInstance()->GetCurrentTotalTime());
		nptr->lastNetworkTick += constants::timePerNetworkTick;
		(*this.*nptr->runMethod)(nptr);
	}
}


void NetworkSystem::CreateLobby(std::shared_ptr<NetworkComponent> nptr)
{
	network::FreeAddrinfo(nptr->result);
	network::CloseSocket(nptr->socket);;
	network::PopulateAddrinfo(nptr->addr); //default values are host
	network::ResolveAddrinfo(nptr->addr, &nptr->result, NULL);
	network::CreateSocket(nptr->socket, nptr->result);
	network::SetSocketNonblocking(nptr->socket);
	network::BindSocket(nptr->socket, *nptr->result);
	network::FreeAddrinfo(nptr->result);
	network::ListenSocket(nptr->socket);
	nptr->connectedSockets.push_back(nptr->socket); //we need to monitor our own socket for clients trying to connect
}

void NetworkSystem::HandleConnecting(std::shared_ptr<NetworkComponent> nptr)
{
	int result = network::AttemptConnection(nptr->socket, nptr->result, nptr->connectionAttempts++);
	switch (result)
	{
	case network::ConnectionReturn::Success:
		nptr->isConnecting = false;
		nptr->runMethod = &NetworkSystem::HandleClient;
		break;
	case network::ConnectionReturn::Failure:
		break;
	case network::ConnectionReturn::Timeout:
		nptr->isHost = true;
		CreateLobby(nptr);
		nptr->isConnecting = false;
		nptr->runMethod = &NetworkSystem::HandleHost;
		break;
	}
}

void NetworkSystem::HandleHost(std::shared_ptr<NetworkComponent> nptr)
{
	RecieveData(nptr);
	SendData(nptr);
}

void NetworkSystem::RecieveData(std::shared_ptr<NetworkComponent> nptr)
{
	FD_ZERO(&nptr->fds);
	for (SOCKET s : nptr->connectedSockets)
	{
		FD_SET(s, &nptr->fds);
	}
	struct timeval timeout;
	timeout.tv_sec = 0;
	int retval = select(nptr->fds.fd_count, &nptr->fds, NULL, NULL, &timeout);
	if (retval == -1)
	{
		printf("Select Error\n");
		return;
	}
	if (retval == 0)
	{
		printf("No input this frame\n");
		return;
	}
	for (int x = 0; x < nptr->fds.fd_count; ++x)
	{
		if (FD_ISSET(x, &nptr->fds))
		{
			if (x == nptr->socket)
			{
				AcceptConnection(nptr);
			}
			else
			{
				printf("would be reading data on %d\n", x);
			}
		}
	}
}

void NetworkSystem::SendData(std::shared_ptr<NetworkComponent> nptr)
{
	for (int x = 0; x < nptr->connectedSockets.size(); ++x)
	{
		if (x == nptr->socket) //don't send data to ourselves
		{
			continue;
		}
		printf("would be sending data to socket %d\n", nptr->connectedSockets[x]);
	}
}

void NetworkSystem::AcceptConnection(std::shared_ptr<NetworkComponent> nptr)
{
	printf("would accept connection here\n");
}

void NetworkSystem::HandleClient(std::shared_ptr<NetworkComponent> nptr)
{

}
