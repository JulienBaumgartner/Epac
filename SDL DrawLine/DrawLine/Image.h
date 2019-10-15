#pragma once
#include <vector>
#include "Mesh.h"
#include "Pixel.h"
#include "Camera.h"
#include "Vertex.h"

class Image
{
public:
	Image(int width, int height);
	~Image();

	int image_width;
	int image_height;
	std::vector<Pixel> current_image;

	void drawPoint(Pixel color, int x, int y);
	void drawLine(Pixel color1, Pixel color2, int x1, int y1, int x2, int y2);
	void drawTriangle(Camera& camera, Pixel color1, const algebra::Vec3<float>& vec1, Pixel color2, const algebra::Vec3<float>& vec2, Pixel color3, const algebra::Vec3<float>& vec3);
	void drawMesh(const Mesh& mesh, const algebra::Matrix4<float>& m_view, Camera& camera);
	void fillTriangle(Vertex a, Vertex b, Vertex c);
};

