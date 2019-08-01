#include "RigidbodyComponent.hpp"

#include <assert.h>

#include "Time.hpp"
#include "Entity.hpp"

RigidbodyComponent::RigidbodyComponent(std::weak_ptr<Entity> e, float f, glm::vec3 v, glm::vec3 a) 
	: Component(e), mass(f), velocity(v), constantAcceleration(a)
{
	type = constants::ComponentType::RigidbodyComponent;
	currentFrameForce = { 0, 0, 0 };
	inverseMass = 1.0f / f;
	SetDampingCoeff(0.8f);
	dragCoefficient1 = 0.4f;
	dragCoefficient2 = 0.4f;
	tptr = entity.lock()->getComp<TransformComponent>();
	assert(!tptr.expired());
}

void RigidbodyComponent::ApplyForce(glm::vec3 direction, float amount, float duration)
{
	direction = glm::normalize(direction);
	if (duration > 0)
	{
		forces.push_back(std::make_pair((amount / mass) * direction, (Time::GetInstance()->GetCurrentTotalTime() + duration)));
	}
	else
	{
		currentFrameForce += (amount / mass) * direction;
	}
	//velocity += (amount / mass) * direction;
}

void RigidbodyComponent::SetInfiniteMass()
{
	inverseMass = 0;
	mass = std::numeric_limits<float>::max();
}

void RigidbodyComponent::SetMass(float f)
{
	mass = f;
	inverseMass = 1.0f / f;
}
void RigidbodyComponent::SetDampingCoeff(float f)
{
	dampingCoeff = f;
	scaledDampingCoeff = powf(dampingCoeff, constants::fixedTimeStep);
}