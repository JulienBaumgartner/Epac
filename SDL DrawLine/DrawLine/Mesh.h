#pragma once
#include <vector>
#include "Algebra.h"

class Mesh
{
public:
	Mesh();
	~Mesh();

	std::vector<algebra::Vec3<float>> project(const std::vector<algebra::Vec3<float>>& points, int w, int h, const algebra::Matrix4<float>& m_view) const;
	bool ExtractObj(const std::string& path);

	std::vector<algebra::Vec3<float>> points;
	std::vector<int> indices;
	std::vector<algebra::Vec4<float>> colors;

};

