#include "Graphics.hpp"

void graphics::MultiplyMatrixVector(const structs::mat4x4 &m, const structs::vec3d &i, structs::vec3d &o)
{
	o.x = i.x * m.m[0][0] + i.y * m.m[1][0] + i.z * m.m[2][0] + m.m[3][0];
	o.y = i.x * m.m[0][1] + i.y * m.m[1][1] + i.z * m.m[2][1] + m.m[3][1];
	o.z = i.x * m.m[0][2] + i.y * m.m[1][2] + i.z * m.m[2][2] + m.m[3][2];
	float w = i.x * m.m[0][3] + i.y * m.m[1][3] + i.z * m.m[2][3] + m.m[3][3];
	if (w)
	{
		o.x /= w;
		o.y /= w;
		o.z /= w;
	}
}

void graphics::ComputePointAtMatrix(const structs::vec3d &pos, const structs::vec3d &target, const structs::vec3d &up, structs::mat4x4 &o)
{
	structs::vec3d newForward, newUp, newRight;
	//calculate a forward vector between our two points

	newForward = target - pos;
	NormalizeVector(newForward);

	//recalculate our up vector by projecting it onto our new forward and minusing it from our old up
	newUp = up - newForward * CalculateDotProduct(up, newForward);
	NormalizeVector(newUp);

	newRight = CrossProduct(newForward, newUp);
	NormalizeVector(newRight);

	o.m[0][0] = newRight.x;		o.m[0][1] = newRight.y;		o.m[0][2] = newRight.z;		o.m[0][3] = 0.0f;
	o.m[1][0] = newUp.x;		o.m[1][1] = newUp.y;		o.m[1][2] = newUp.z;		o.m[1][3] = 0.0f;
	o.m[2][0] = newForward.x;	o.m[2][1] = newForward.y;	o.m[2][2] = newForward.z;	o.m[2][3] = 0.0f;
	o.m[3][0] = pos.x;			o.m[3][1] = pos.y;			o.m[3][2] = pos.z;			o.m[3][3] = 1.0f;
}

structs::mat4x4 graphics::ComputePointAtMatrix(const structs::vec3d &pos, const structs::vec3d &target, const structs::vec3d &up)
{
	structs::vec3d newForward, newUp, newRight;
	//calculate a forward vector between our two points

	newForward = target - pos;
	NormalizeVector(newForward);

	//recalculate our up vector by projecting it onto our new forward and minusing it from our old up
	newUp = up - newForward * CalculateDotProduct(up, newForward);
	NormalizeVector(newUp);

	newRight = CrossProduct(newForward, newUp);
	NormalizeVector(newRight);

	structs::mat4x4 o;
	o.m[0][0] = newRight.x;		o.m[0][1] = newRight.y;		o.m[0][2] = newRight.z;		o.m[0][3] = 0.0f;
	o.m[1][0] = newUp.x;		o.m[1][1] = newUp.y;		o.m[1][2] = newUp.z;		o.m[1][3] = 0.0f;
	o.m[2][0] = newForward.x;	o.m[2][1] = newForward.y;	o.m[2][2] = newForward.z;	o.m[2][3] = 0.0f;
	o.m[3][0] = pos.x;			o.m[3][1] = pos.y;			o.m[3][2] = pos.z;			o.m[3][3] = 1.0f;
	return o;
}

void graphics::QuickInverseMatrix(const structs::mat4x4 &m, structs::mat4x4 &o)
{
	o.m[0][0] = m.m[0][0]; o.m[0][1] = m.m[1][0]; o.m[0][2] = m.m[2][0]; o.m[0][3] = 0.0f;
	o.m[1][0] = m.m[0][1]; o.m[1][1] = m.m[1][1]; o.m[1][2] = m.m[2][1]; o.m[1][3] = 0.0f;
	o.m[2][0] = m.m[0][2]; o.m[2][1] = m.m[1][2]; o.m[2][2] = m.m[2][2]; o.m[2][3] = 0.0f;
	o.m[3][0] = -(m.m[3][0] * o.m[0][0] + m.m[3][1] * o.m[1][0] + m.m[3][2] * o.m[2][0]);
	o.m[3][1] = -(m.m[3][0] * o.m[0][1] + m.m[3][1] * o.m[1][1] + m.m[3][2] * o.m[2][1]);
	o.m[3][2] = -(m.m[3][0] * o.m[0][2] + m.m[3][1] * o.m[1][2] + m.m[3][2] * o.m[2][2]);
	o.m[3][3] = 1.0f;
}

structs::mat4x4 graphics::QuickInverseMatrix(const structs::mat4x4 &m)
{
	structs::mat4x4 matrix;
	matrix.m[0][0] = m.m[0][0]; matrix.m[0][1] = m.m[1][0]; matrix.m[0][2] = m.m[2][0]; matrix.m[0][3] = 0.0f;
	matrix.m[1][0] = m.m[0][1]; matrix.m[1][1] = m.m[1][1]; matrix.m[1][2] = m.m[2][1]; matrix.m[1][3] = 0.0f;
	matrix.m[2][0] = m.m[0][2]; matrix.m[2][1] = m.m[1][2]; matrix.m[2][2] = m.m[2][2]; matrix.m[2][3] = 0.0f;
	matrix.m[3][0] = -(m.m[3][0] * matrix.m[0][0] + m.m[3][1] * matrix.m[1][0] + m.m[3][2] * matrix.m[2][0]);
	matrix.m[3][1] = -(m.m[3][0] * matrix.m[0][1] + m.m[3][1] * matrix.m[1][1] + m.m[3][2] * matrix.m[2][1]);
	matrix.m[3][2] = -(m.m[3][0] * matrix.m[0][2] + m.m[3][1] * matrix.m[1][2] + m.m[3][2] * matrix.m[2][2]);
	matrix.m[3][3] = 1.0f;
	return matrix;
}

//void graphics::DrawTriangle(sf::RenderWindow &window, const structs::tri &t)
//{
//	sf::Vertex vArr[3];
//	DrawTriangle(window, t, vArr);
//}

//void graphics::DrawTriangle(sf::RenderWindow &window, const structs::tri &t, sf::Vertex * vArr)
//{
//	if (constants::DebugVariables::GetInstance()->wireframe)
//	{
//		vArr[0].color = sf::Color::White;
//		vArr[1].color = sf::Color::White;
//		vArr[0].position = sf::Vector2f(t.p[0].x, constants::screenHeight - t.p[0].y);
//		vArr[1].position = sf::Vector2f(t.p[1].x, constants::screenHeight - t.p[1].y);
//		window.draw(&vArr[0], 2, sf::Lines);
//		vArr[0].position = sf::Vector2f(t.p[1].x, constants::screenHeight - t.p[1].y);
//		vArr[1].position = sf::Vector2f(t.p[2].x, constants::screenHeight - t.p[2].y);
//		window.draw(&vArr[0], 2, sf::Lines);
//		vArr[0].position = sf::Vector2f(t.p[0].x, constants::screenHeight - t.p[0].y);
//		vArr[1].position = sf::Vector2f(t.p[2].x, constants::screenHeight - t.p[2].y);
//		window.draw(&vArr[0], 2, sf::Lines);
//	}
//	else
//	{
//		vArr[0].color = t.c;
//		vArr[1].color = t.c;
//		vArr[2].color = t.c;
//		vArr[0].position = sf::Vector2f(t.p[0].x, constants::screenHeight - t.p[0].y);
//		vArr[1].position = sf::Vector2f(t.p[1].x, constants::screenHeight - t.p[1].y);
//		vArr[2].position = sf::Vector2f(t.p[2].x, constants::screenHeight - t.p[2].y);
//		window.draw(&vArr[0], 3, sf::Triangles);
//
//		vArr[0].color = sf::Color::Black;
//		vArr[1].color = sf::Color::Black;
//		vArr[0].position = sf::Vector2f(t.p[0].x, constants::screenHeight - t.p[0].y);
//		vArr[1].position = sf::Vector2f(t.p[1].x, constants::screenHeight - t.p[1].y);
//		window.draw(&vArr[0], 2, sf::Lines);
//		vArr[0].position = sf::Vector2f(t.p[1].x, constants::screenHeight - t.p[1].y);
//		vArr[1].position = sf::Vector2f(t.p[2].x, constants::screenHeight - t.p[2].y);
//		window.draw(&vArr[0], 2, sf::Lines);
//		vArr[0].position = sf::Vector2f(t.p[0].x, constants::screenHeight - t.p[0].y);
//		vArr[1].position = sf::Vector2f(t.p[2].x, constants::screenHeight - t.p[2].y);
//		window.draw(&vArr[0], 2, sf::Lines);
//	}
//}

void graphics::ProjectOntoScreenSpace(const structs::tri &i, structs::tri &o)
{
	ApplyMatrixToTriangle(i, o, constants::matrices::projectionMatrix);

	//Move it onto the screen
	o.p[0].x += 1.0f; o.p[0].y += 1.0f;
	o.p[1].x += 1.0f; o.p[1].y += 1.0f;
	o.p[2].x += 1.0f; o.p[2].y += 1.0f;
	o.p[0].x *= 0.5f * constants::screenWidth; o.p[0].y *= 0.5f * constants::screenHeight;
	o.p[1].x *= 0.5f * constants::screenWidth; o.p[1].y *= 0.5f * constants::screenHeight;
	o.p[2].x *= 0.5f * constants::screenWidth; o.p[2].y *= 0.5f * constants::screenHeight;
}

inline void graphics::CalculateNormal(const structs::tri &tri, structs::vec3d &o)
{
	structs::vec3d l1;
	structs::vec3d l2;
	CalculateNormal(tri, l1, l2, o);
}

void graphics::CalculateNormal(const structs::tri &tri, structs::vec3d &line1, structs::vec3d &line2, structs::vec3d &o)
{
	line1.x = tri.p[0].x - tri.p[2].x;
	line1.y = tri.p[0].y - tri.p[2].y;
	line1.z = tri.p[0].z - tri.p[2].z;

	line2.x = tri.p[0].x - tri.p[1].x;
	line2.y = tri.p[0].y - tri.p[1].y;
	line2.z = tri.p[0].z - tri.p[1].z;

	CalculateNormal(line1, line2, o);
}

inline void graphics::CalculateNormal(const structs::vec3d &line1, const structs::vec3d &line2, structs::vec3d &o)
{
	o.x = line1.y * line2.z - line1.z * line2.y;
	o.y = line1.z * line2.x - line1.x * line2.z;
	o.z = line1.x * line2.y - line1.y * line2.x;
	NormalizeVector(o);
}

//void graphics::DrawMesh(sf::RenderWindow &window, const structs::mesh &m, const structs::vec3d &cameraPos, const structs::vec3d &cameraDirection)
//{
//	//local vars allocated once
//	std::vector<structs::tri> trisToDraw;
//	structs::tri triTransformed, triProjected, triViewed;
//	structs::vec3d line1, line2, normal, vUp;
//	structs::vec3d cameraRay[3];
//	structs::mat4x4 rotX, rotY, rotZ, cameraMat;
//	sf::Vertex vArr[3];
//	float lightingRatio;
//
//	structs::vec3d lightDirection = { 0.0f, 0.0f, -1.0f };
//	NormalizeVector(lightDirection);
//
//	ComputeXRotationMatrix(m.rot.x, rotX);
//	ComputeYRotationMatrix(m.rot.y, rotY);
//	ComputeZRotationMatrix(m.rot.z, rotZ);
//
//	vUp = { 0, 1, 0 };
//	ComputePointAtMatrix(cameraPos, cameraPos + cameraDirection, vUp, cameraMat);
//	QuickInverseMatrix(cameraMat);
//
//
//	for (const structs::tri &tri : m.tris)
//	{
//		//Rotate our cube in X, Y, then Z, may gimble lock because not quaternions
//		ApplyMatrixToTriangle(tri, triTransformed, rotX);
//		ApplyMatrixToTriangle(triTransformed, triTransformed, rotY);
//		ApplyMatrixToTriangle(triTransformed, triTransformed, rotZ);
//
//		//Translate
//		triTransformed.Translate(m.pos.x, m.pos.y, m.pos.z);
//
//		//Determine if we need to cull the triangle
//		cameraRay[0] = GetVectorBetween(triTransformed.p[0], cameraPos);
//		cameraRay[1] = GetVectorBetween(triTransformed.p[1], cameraPos);
//		cameraRay[2] = GetVectorBetween(triTransformed.p[2], cameraPos);
//		NormalizeVector(cameraRay[0]);
//		NormalizeVector(cameraRay[1]);
//		NormalizeVector(cameraRay[2]);
//		CalculateNormal(triTransformed, line1, line2, normal);
//		float d[3];
//		d[0] = CalculateDotProduct(normal, cameraRay[0]);
//		d[1] = CalculateDotProduct(normal, cameraRay[1]);
//		d[2] = CalculateDotProduct(normal, cameraRay[2]);
//
//		//Culling calculations
//		if (CalculateDotProduct(normal, cameraRay[0]) <= 0.0f || 
//			CalculateDotProduct(normal, cameraRay[1]) <= 0.0f || 
//			CalculateDotProduct(normal, cameraRay[2]) <= 0.0f)
//		{
//			//Perform lighting calculation
//			CalculateDotProduct(normal, lightDirection, lightingRatio);
//			//SetTriangleColor(triProjected, lightingRatio);
//			SetTriangleColor(triProjected, 1);
//
//			//Convert from world space to our camera space
//			ApplyMatrixToTriangle(triTransformed, triViewed, cameraMat);
//
//			//Project onto the screen
//			ProjectOntoScreenSpace(triViewed, triProjected);
//			triProjected.label.assign(tri.label);
//			trisToDraw.push_back(triProjected);
//		}
//		else if(tri.label.compare("top") == 0)
//		{
//			std::cout << "top culled " << Time::GetInstance()->GetCurrentTime() << std::endl;
//		}
//	}
//	std::sort(trisToDraw.begin(), trisToDraw.end());
//	for (const structs::tri &tri : trisToDraw)
//	{
//		DrawTriangle(window, tri, vArr);	
//	}
//
//}