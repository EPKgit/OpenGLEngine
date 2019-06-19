#ifndef _STRUCTS_HPP
#define _STRUCTS_HPP

#include <iostream>
#include <fstream>
#include <strstream>
#include <sstream>
#include <vector>


namespace structs
{
	struct vec3d
	{
		float x, y, z;

		vec3d operator-(const vec3d &o) const
		{
			vec3d temp;
			temp.x = x - o.x;
			temp.y = y - o.y;
			temp.z = z - o.z;
			return temp;
		}
		vec3d operator+(const vec3d &o) const
		{
			vec3d temp;
			temp.x = x + o.x;
			temp.y = y + o.y;
			temp.z = z + o.z;
			return temp;
		}
		vec3d operator*(float f) const
		{
			vec3d temp;
			temp.x = x * f;
			temp.y = y * f;
			temp.z = z * f;
			return temp;
		}
		vec3d& operator+=(float f)
		{
			x += f;
			y += f;
			z += f;
			return *this;
		}
		vec3d& operator+=(const vec3d& o)
		{
			x += o.x;
			y += o.y;
			z += o.z;
			return *this;
		}
		bool operator==(const float f) const
		{
			return x == f && y == f && z == f;
		}
		bool operator!=(const float f) const
		{
			return !(*this == f);
		}
		friend std::ostream& operator<<(std::ostream& out, const vec3d &v);
	};
	struct tri
	{
		std::string label;
		vec3d p[3];

		void Translate(float _x, float _y, float _z)
		{
			p[0].x += _x;
			p[0].y += _y;
			p[0].z += _z;

			p[1].x += _x;
			p[1].y += _y;
			p[1].z += _z;

			p[2].x += _x;
			p[2].y += _y;
			p[2].z += _z;
		}
		bool operator>(tri &other)
		{
			return (p[0].z + p[1].z + p[2].z) / 3.0f < (other.p[0].z + other.p[1].z + other.p[2].z) / 3.0f;
		}
		bool operator<(tri &other)
		{
			return (p[0].z + p[1].z + p[2].z) / 3.0f > (other.p[0].z + other.p[1].z + other.p[2].z) / 3.0f;
		}
	};
	struct mesh
	{
		std::vector<tri> tris;
		vec3d pos;
		vec3d rot;

		bool ImportFromFile(std::string fileName)
		{
			std::ifstream infile(fileName);
			if (!infile.is_open())
			{
				return false;
			}
			std::vector<vec3d> verts;
			std::string line;
			std::stringstream stream;
			vec3d vTemp;
			tri tTemp;
			int triIndeces[3];
			char junk;
			while (getline(infile, line))
			{
				if (line.length() <= 0 || (line[0] != 'v' && line[0] != 'f'))
				{
					continue;
				}
				stream.str(std::string());
				stream.clear();
				stream << line;
				if (line[0] == 'v')
				{
					stream >> junk >> vTemp.x >> vTemp.y >> vTemp.z;
					verts.push_back(vTemp);
					continue;
				}
				if (line[0] == 'f')
				{
					stream >> junk >> triIndeces[0] >> triIndeces[1] >> triIndeces[2] >> tTemp.label;
					tTemp.p[0] = verts[triIndeces[0] - 1];
					tTemp.p[1] = verts[triIndeces[1] - 1];
					tTemp.p[2] = verts[triIndeces[2] - 1];
					tris.push_back(tTemp);
					continue;
				}
			}
			return true;
		}
	};
	struct mat4x4
	{
		float m[4][4] = { 0 };
	};
};

#endif