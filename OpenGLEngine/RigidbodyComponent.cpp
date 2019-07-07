#include "RigidbodyComponent.hpp"

#include "Time.hpp"

RigidbodyComponent::RigidbodyComponent(float f, glm::vec3 v, glm::vec3 a) : mass(f), velocity(v), acceleration(a)
{
	type = constants::ComponentType::RigidbodyComponent;
	inverseMass = 1.0f / f;
	dampingCoeff = 0.95f;
	scaledDampingCoeff = 0.99948719858f;
}

void RigidbodyComponent::ApplyForce(glm::vec3 direction, float amount, float duration)
{
	direction = glm::normalize(direction);
	if (duration > 0)
	{
		forces.push_back(std::make_pair((amount / mass) * direction, (Time::GetInstance()->GetCurrentTime() + duration)));
	}
	else
	{
		acceleration += (amount / mass) * direction;
	}
	//velocity += (amount / mass) * direction;
}