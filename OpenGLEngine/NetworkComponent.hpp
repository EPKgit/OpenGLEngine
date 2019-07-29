#ifndef _NETWORKCOMPONENT_HPP
#define _NETWORKCOMPONENT_HPP

#include <vector>
#include <winsock2.h>

#include "Component.hpp"

class NetworkSystem;

class NetworkComponent : public Component
{
public:
	NetworkComponent(std::weak_ptr<Entity> e) : Component(e)
	{
		type = constants::ComponentType::Network;
		connectionAttempts = 0;
		isConnecting = true;
		isHost = false;
	}
	WSADATA wsaData;
	SOCKET socket;
	ADDRINFOA addr;
	ADDRINFOA *result;
	fd_set fds;
	std::vector<SOCKET> connectedSockets;
	bool isHost;
	bool isConnecting;
	void(NetworkSystem::*runMethod)(std::shared_ptr<NetworkComponent> nptr);
	int connectionAttempts;
	float lastNetworkTick;
	
private:
};
#endif // !_NETWORKCOMPONENT_HPP
