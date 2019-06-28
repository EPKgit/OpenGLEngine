#ifndef _STRUCTS_HPP
#define _STRUCTS_HPP

namespace structs
{
		/*bool ImportFromFile(std::string fileName)
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
		}*/
};

#endif