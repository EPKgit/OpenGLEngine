#ifndef _GRAPHICS_HPP
#define _GRAPHICS_HPP

#include <algorithm>


#include "Structs.hpp"
#include "Constants.hpp"
#include "Time.hpp"

namespace graphics
{
	inline float GetMagnititude(const structs::vec3d &line)
	{
		return sqrtf(line.x*line.x + line.y*line.y + line.z*line.z);
	}

	inline structs::vec3d NormalizeVector(structs::vec3d &o)
	{
		float l = GetMagnititude(o);
		o.x /= l;
		o.y /= l;
		o.z /= l;
		return o;
	}

	inline structs::vec3d CrossProduct(const structs::vec3d &line1, const structs::vec3d &line2)
	{
		structs::vec3d v;
		v.x = line1.y * line2.z - line1.z * line2.y;
		v.y = line1.z * line2.x - line1.x * line2.z;
		v.z = line1.x * line2.y - line1.y * line2.x;
		return v;
	}

	inline void CrossProduct(const structs::vec3d &line1, const structs::vec3d &line2, structs::vec3d &o)
	{
		o.x = line1.y * line2.z - line1.z * line2.y;
		o.y = line1.z * line2.x - line1.x * line2.z;
		o.z = line1.x * line2.y - line1.y * line2.x;
	}

	inline void ComputeZRotationMatrix(float fTheta, structs::mat4x4 &matrix)
	{
		matrix.m[0][0] = cosf(fTheta);
		matrix.m[0][1] = sinf(fTheta);
		matrix.m[1][0] = -sinf(fTheta);
		matrix.m[1][1] = cosf(fTheta);
		matrix.m[2][2] = 1;
		matrix.m[3][3] = 1;
	}

	inline void ComputeYRotationMatrix(float fTheta, structs::mat4x4 &matrix)
	{
		matrix.m[0][0] = cosf(fTheta);
		matrix.m[0][2] = sinf(fTheta);
		matrix.m[2][0] = -sinf(fTheta);
		matrix.m[1][1] = 1.0f;
		matrix.m[2][2] = cosf(fTheta);
		matrix.m[3][3] = 1.0f;
	}

	inline void ComputeXRotationMatrix(float fTheta, structs::mat4x4 &matrix)
	{
		matrix.m[0][0] = 1;
		matrix.m[1][1] = cosf(fTheta);
		matrix.m[1][2] = sinf(fTheta);
		matrix.m[2][1] = -sinf(fTheta);
		matrix.m[2][2] = cosf(fTheta);
		matrix.m[3][3] = 1;
	}

	void ComputePointAtMatrix(const structs::vec3d &, const structs::vec3d &, const structs::vec3d &, structs::mat4x4 &);

	structs::mat4x4 ComputePointAtMatrix(const structs::vec3d &, const structs::vec3d &, const structs::vec3d &);

	void QuickInverseMatrix(const structs::mat4x4 &, structs::mat4x4 &);

	structs::mat4x4 QuickInverseMatrix(const structs::mat4x4 &);

	void MultiplyMatrixVector(const structs::mat4x4&, const structs::vec3d&, structs::vec3d&);

	/*void DrawTriangle(sf::RenderWindow&, const structs::tri&);

	void DrawTriangle(sf::RenderWindow &, const structs::tri &, sf::Vertex *);*/

	/*inline void SetTriangleColor(structs::tri &t, float r)
	{
		t.c = sf::Color((sf::Uint8)(255 * r), (sf::Uint8)(255 * r), (sf::Uint8)(255 * r), 255);
	}*/

	void ProjectOntoScreenSpace(const structs::tri &, structs::tri &);

	void CalculateNormal(const structs::tri &, structs::vec3d &);

	void CalculateNormal(const structs::vec3d &, const structs::vec3d &, structs::vec3d &);

	void CalculateNormal(const structs::tri &, structs::vec3d &, structs::vec3d &, structs::vec3d &);

	inline void CalculateDotProduct(const structs::vec3d &line1, const structs::vec3d &line2, float &f)
	{
		f = line1.x * line1.x + line1.y * line2.y + line1.z * line2.z;
	}

	inline float CalculateDotProduct(const structs::vec3d &line1, const structs::vec3d &line2)
	{
		return line1.x * line2.x + line1.y * line2.y + line1.z * line2.z;
	}

	inline float GetAngleBetween_D(const structs::vec3d &line1, const structs::vec3d &line2)
	{
		return lib::RadToDeg(acosf(CalculateDotProduct(line1, line2) / (GetMagnititude(line1) * GetMagnititude(line2))));
	}

	inline structs::vec3d GetVectorBetween(const structs::vec3d &p1, const structs::vec3d &p2)
	{
		return { p1.x - p2.x, p1.y - p2.y, p1.z - p2.z };
	}

	

	inline void ApplyMatrixToTriangle(const structs::tri &i, structs::tri &o, const structs::mat4x4 &m)
	{
		MultiplyMatrixVector(m, i.p[0], o.p[0]);
		MultiplyMatrixVector(m, i.p[1], o.p[1]);
		MultiplyMatrixVector(m, i.p[2], o.p[2]);
	}

	/*void DrawMesh(sf::RenderWindow &, const structs::mesh &, const structs::vec3d &, const structs::vec3d &);*/
};

#endif // !_GRAPHICS_HPP
