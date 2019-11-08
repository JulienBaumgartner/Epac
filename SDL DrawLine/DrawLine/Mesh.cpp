#include "Mesh.h"
#include <fstream>
#include <iostream>
#include <string>



Mesh::Mesh()
{
}


Mesh::~Mesh()
{
}


std::vector<algebra::Vec3<float>> Mesh::project(const std::vector<algebra::Vec3<float>>& points, int w, int h, const algebra::Matrix4<float>& m_view) const{
	algebra::Matrix4<float> projection = algebra::Matrix4<float>::projectionMatrix(w, h, 0.1, 100000, 90 *M_PI /180);
	std::vector<algebra::Vec3<float>> projectedPoints;

	for (int i = 0; i < points.size(); i++) {
		algebra::Vec4<float> v4(points[i]);

		v4 = v4 * m_view;
		v4 = v4 * projection;

		algebra::Vec3<float> v3(points[i]);
		if (v4.w != 0) 
		{
		 v3.x = v4.x / v4.w;
		 v3.y = v4.y / v4.w;
		 v3.z = v4.z / v4.w;
		}
		
		projectedPoints.push_back(v3);
	}

	return projectedPoints;
}

bool Mesh::ExtractObj(const std::string & path)
{
	std::ifstream file(path);
	std::string str;
	if (file.is_open()) {
		while (!std::getline(file, str).eof())
		{
			//char firstChar = str[0];
			std::string delimiter = " ";
			size_t pos = 0;
			std::string token;

			std::vector<std::string> splitStr;

			while ((pos = str.find(delimiter)) != std::string::npos) {
				token = str.substr(0, pos);
				splitStr.push_back(token);
				str.erase(0, pos + delimiter.length());
			}
			splitStr.push_back(str);

			algebra::Vec4<float> p;
			switch (splitStr[0][0])
			{
			case 'v':

				points.push_back(algebra::Vec3<float>(std::stof(splitStr[1]),
					std::stof(splitStr[2]), std::stof(splitStr[3]))); 
				p.w = 1;
				p.x = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
				p.y = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
				p.z = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
				colors.push_back(p);

				break;
			case 'f':

				indices.push_back(std::stoi(splitStr[1])-1);
				indices.push_back(std::stoi(splitStr[2])-1);
				indices.push_back(std::stoi(splitStr[3])-1);
				break;
			}
		}

		return true;
	}
	else {
		return false;
	}

}
