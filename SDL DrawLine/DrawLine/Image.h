#pragma once
#include <vector>
#include "Mesh.h"
#include "Camera.h"
#include "Vertex.h"

class Image
{
public:
	Image(int width, int height, Camera& camera);
	~Image();

	int imageWidth;
	int imageHeight;
	std::vector<algebra::Vec4<float>> currentImage;
	std::vector<float> zBuffer;

	void drawPoint(algebra::Vec4<float> color, int x, int y, float z);
	void drawLine(algebra::Vec4<float> color1, algebra::Vec4<float> color2, int x1, int y1, float z1, int x2, int y2, float z2);
	void drawTriangle(Camera& camera, algebra::Vec4<float> color1, const algebra::Vec3<float>& vec1, algebra::Vec4<float> color2,
		const algebra::Vec3<float>& vec2, algebra::Vec4<float> color3, const algebra::Vec3<float>& vec3);
	void drawMesh(const Mesh& mesh, const algebra::Matrix4<float>& m_view, Camera& camera, float rotation);
	void fillTriangle(Vertex a, Vertex b, Vertex c, algebra::Vec3<float> pos1,
		algebra::Vec3<float> pos2, algebra::Vec3<float> pos3, const Mesh& mesh);
protected:
	bool isVisible(Camera& camera, const algebra::Vec3<float>& vec1, const algebra::Vec3<float>& vec2,
		const algebra::Vec3<float>& vec3, const algebra::Vec3<float>& pos);
	bool isOutOfScreen(const algebra::Vec3<float>& vec1, const algebra::Vec3<float>& vec2, const algebra::Vec3<float>& vec3);
	Camera camera;

};

