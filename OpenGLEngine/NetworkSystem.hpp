#ifndef _NETWORKSYSTEM_HPP
#define _NETWORKSYSTEM_HPP

#include "System.hpp"

class NetworkComponent;

class NetworkSystem : public System
{
public:
	NetworkSystem();
	void Run(float deltaTime);
private:
	void CreateLobby(std::shared_ptr<NetworkComponent> nptr);
	void HandleConnecting(std::shared_ptr<NetworkComponent> nptr);

	void HandleHost(std::shared_ptr<NetworkComponent> nptr);
	
		void RecieveData(std::shared_ptr<NetworkComponent> nptr);

		void SendData(std::shared_ptr<NetworkComponent> nptr);

		void AcceptConnection(std::shared_ptr<NetworkComponent> nptr);

	void HandleClient(std::shared_ptr<NetworkComponent> nptr);
	
};
#endif // !_NETWORKSYSTEM_HPP
