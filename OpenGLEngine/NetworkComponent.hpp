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
		startedConnectionTime = lastNetworkTick = Time::GetInstance()->GetCurrentTotalTime();
	}
	WSADATA wsaData = WSADATA();
	SOCKET socket = SOCKET();
	ADDRINFOA addr = ADDRINFOA();
	ADDRINFOA *result = nullptr;
	fd_set fds = fd_set();
	std::vector<SOCKET> connectedSockets;
	bool isHost = false;
	bool isConnecting = true;
	void(NetworkSystem::*runMethod)(std::shared_ptr<NetworkComponent> nptr) = nullptr;
	float startedConnectionTime;
	float lastNetworkTick;
	
private:
};
#endif // !_NETWORKCOMPONENT_HPP
