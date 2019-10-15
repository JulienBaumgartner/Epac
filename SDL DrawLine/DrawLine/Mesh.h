#pragma once
#include <vector>
#include "Algebra.h"
#include "Pixel.h"

class Mesh
{
public:
	Mesh();
	~Mesh();

	std::vector<algebra::Vec3<float>> project(const std::vector<algebra::Vec3<float>>& points, int w, int h, const algebra::Matrix4<float>& m_view) const;
	bool ExtractObj(const std::string& path);

	std::vector<algebra::Vec3<float>> points_;
	std::vector<int> indices_;
	std::vector<Pixel> colors_;

};

