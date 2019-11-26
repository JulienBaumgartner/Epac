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


std::vector<algebra::Vec4<float>> Mesh::project(const std::vector<algebra::Vec4<float>>& points, int w, int h, const algebra::Matrix4<float>& m_view) const{
	algebra::Matrix4<float> projection = algebra::Matrix4<float>::projectionMatrix(w, h, 0.1, 100000, 90 *M_PI /180);
	std::vector<algebra::Vec4<float>> projectedPoints;

	for (int i = 0; i < points.size(); i++) {
		algebra::Vec4<float> v4(points[i]);

		v4 = v4 * m_view;
		v4 = v4 * projection;

		if (v4.w != 0) 
		{
		 v4 /= v4.w;
		}
		
		projectedPoints.push_back(v4);
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
			std::string identifier;
			identifier.push_back(splitStr[0][0]);
			if (splitStr[0][1] != '\0') {
				identifier.push_back(splitStr[0][1]);
			}
			
			if (identifier == "v") 
			{
				points.push_back(algebra::Vec4<float>(std::stof(splitStr[1]),
					std::stof(splitStr[2]), std::stof(splitStr[3]), 1));
				p.w = 1;
				p.x = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
				p.y = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
				p.z = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
				colors.push_back(p);
			}
			else if(identifier == "f")
			{
				importF(splitStr);
			}
			else if (identifier == "vt")
			{
				uv.push_back(algebra::Vec2<float>(std::stof(splitStr[1]),
					std::stof(splitStr[2])));
			}
			else if (identifier == "vn")
			{
				normals.push_back(algebra::Vec3<float>(std::stof(splitStr[1]),
					std::stof(splitStr[2]), std::stof(splitStr[3])));
			}
		}

		return true;
	}
	else {
		return false;
	}

}

void Mesh::loadTexture(const char* path)
{
	int i;
	FILE* f = fopen(path, "rb");
	unsigned char info[54];
	fread(info, sizeof(unsigned char), 54, f); // read the 54-byte header

	// extract image height and width from header
	textureWidth = *(int*)&info[18];
	textureHeight = *(int*)&info[22];

	int size = 3 * textureWidth * textureHeight;
	unsigned char* data = new unsigned char[size]; // allocate 3 bytes per pixel
	fread(data, sizeof(unsigned char), size, f); // read the rest of the data at once
	fclose(f);

	for (i = 0; i < size; i += 3)
	{
		algebra::Vec4<float> color(0, 0, 0, 1);
		color.x = data[i + 2] / 255.0f;
		color.y = data[i + 1] / 255.0f;
		color.z = data[i] / 255.0f;
		textureColors.push_back(color);
	}


}

void Mesh::importF(std::vector<std::string> str)
{
	for (int i = 1; i <= 3; i++) 
	{
		std::string delimiter = "/";
		size_t pos = 0;
		std::string token;

		std::vector<std::string> splitStr;

		while ((pos = str[i].find(delimiter)) != std::string::npos) {
			token = str[i].substr(0, pos);
			splitStr.push_back(token);
			str[i].erase(0, pos + delimiter.length());
		}
		splitStr.push_back(str[i]);


		indices.push_back(std::stoi(splitStr[0]) - 1);
		if (splitStr.size() > 1) 
		{
			indicesUv.push_back(std::stoi(splitStr[1]) - 1);
			indicesNormals.push_back(std::stoi(splitStr[2]) - 1);
		}
	}
}