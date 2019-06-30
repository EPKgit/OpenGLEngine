#include "Library.hpp"

#define _USE_MATH_DEFINES

#include <math.h>
#include <vector>

#include "MeshComponent.hpp"
#include "TransformComponent.hpp"
#include "EntityManager.hpp"
#include "CameraComponent.hpp"

inline float lib::DegToRadf(float degreeMeasure)
{
	return degreeMeasure * (float)M_PI / 180.0f;
}
inline float lib::RadToDegf(float radMeasure)
{
	return radMeasure / (float)M_PI * 180.0f;
}

std::shared_ptr<Entity> lib::CreateCubeEntity()
{
	std::vector<float> vertices =
	{

		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};
	std::shared_ptr <MeshComponent> mesh = std::make_shared<MeshComponent>(&vertices, false, true);
	Texture t1("container.jpg");
	Texture t2("awesomeface.png", GL_RGBA, GL_RGBA, true);
	Shader s("BaseVertex.vert", "BaseFragment.frag");
	mesh->textures.push_back(t1);
	mesh->textures.push_back(t2);
	mesh->s = s;
	mesh->s.Use();
	mesh->s.SetInt("texture1", 0);
	mesh->s.SetInt("texture2", 1);

	std::shared_ptr<Entity> e = EntityManager::GetInstance()->createEntity();
	e->addComp<MeshComponent>(mesh);
	e->addComp<TransformComponent>();
	return e;
}

std::shared_ptr<Entity> lib::CreateCameraEntityFPS()
{
	std::shared_ptr<Entity> e = EntityManager::GetInstance()->createEntity();
	e->addComp<TransformComponent>();
	e->addComp<CameraComponent, glm::vec3>({ 0, 0, 3 });
	return e;
}

std::shared_ptr<Entity> lib::CreateCameraEntityThirdPerson()
{
	std::shared_ptr<Entity> e = lib::CreateCubeEntity();
	e->addComp<CameraComponent, glm::vec3>({ 0, 1.2, 1.2 });
	e->getComp<TransformComponent>()->scale = { 0.2, 0.2, 0.2 };
	return e;
}