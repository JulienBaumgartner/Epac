#pragma once
#include <vector>
#include "Algebra.h"

class Mesh
{
public:
	Mesh();
	~Mesh();

	std::vector<algebra::Vec4<float>> project(const std::vector<algebra::Vec4<float>>& points, int w, int h, const algebra::Matrix4<float>& m_view) const;
	bool ExtractObj(const std::string& path);
	void loadTexture(const char* path);
	void ComputeFlat();
	const std::vector<float>& GetFlatPositions() const;
	const std::vector<float>& GetFlatNormals() const;
	const std::vector<float>& GetFlatTextures() const;
	const std::vector<unsigned int>& GetFlatIndices() const;

	std::vector<algebra::Vec4<float>> points;
	std::vector<algebra::Vec4<float>> colors;
	std::vector<algebra::Vec2<float>> uv;
	std::vector<algebra::Vec3<float>> normals;
	std::vector<int> indices;
	std::vector<int> indicesUv;
	std::vector<int> indicesNormals;

	std::vector<algebra::Vec4<float>> textureColors;
	int textureWidth;
	int textureHeight;

protected:
	void importF(std::vector<std::string> str);

	std::vector<float> flatPositions_ = {};
	std::vector<float> flatNormals_ = {};
	std::vector<float> flatTextures_ = {};
	std::vector<unsigned int> flatIndices_ = {};

	
};

