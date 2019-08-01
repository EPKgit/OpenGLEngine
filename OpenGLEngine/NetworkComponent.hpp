#ifndef _NETWORKCOMPONENT_HPP
#define _NETWORKCOMPONENT_HPP

#include <vector>
#define NOMINMAX
#include <winsock2.h>
#undef NOMINMAX
#include "Component.hpp"
#include "Time.hpp"

class NetworkSystem;

class NetworkComponent : public Component
{
public:
	NetworkComponent(std::weak_ptr<Entity> e) : Component(e)
	{
		type = constants::ComponentType::NetworkComponent;
		isConnecting = true;
		isHost = false;
		startedConnectionTime = lastNetworkTick = Time::GetInstance()->GetCurrentTotalTime();
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
	float startedConnectionTime;
	float lastNetworkTick;
	
private:
};
#endif // !_NETWORKCOMPONENT_HPP
