#ifndef _INPUTCOMPONENT_HPP
#define _INPUTCOMPONENT_HPP

#include <bitset>

#include "Component.hpp"

enum InputMaps
{
	W = 0,
	A,
	S,
	D,
	SPACE,
	COUNT
};

class InputComponent : public Component
{
public:
	InputComponent(std::weak_ptr<Entity> e) : Component(e)
	{
		type = constants::ComponentType::InputComponent;
		mouseAxis = { 0, 0 };
		moveAxis = { 0, 0 };
	}
	std::bitset<InputMaps::COUNT> heldBits; //whether the button is down on this frame
	std::bitset<InputMaps::COUNT> downBits; //buttons that were pressed this frame
	std::bitset<InputMaps::COUNT> upBits; //buttons that were resleased this frame
	double mousePosition[6];//0/1 for fresh input, 2/3 for old input, 4/5 for diff
	glm::vec2 mouseAxis;
	glm::vec2 moveAxis;
private:
};
#endif // !_INPUTCOMPONENT_HPP
