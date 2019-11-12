#include "Image.h"
#include <algorithm>
#include <iostream>
#include <string>


Image::Image(int width, int height, Camera& camera) : camera(camera)
{
	imageWidth = width;
	imageHeight = height;

	currentImage.assign(imageWidth*imageHeight, { 40, 0, 40, 255 });
	zBuffer.assign(imageWidth*imageHeight, { -10000 });
}


Image::~Image()
{
}


void Image::drawPoint(algebra::Vec4<float> color, int x, int y, float z)
{
	if (x >= imageWidth) {
		x = imageWidth-1;
	}
	if (y >= imageHeight) {
		y = imageHeight - 1;
	}
	int index = x + y * imageWidth;
	if (x >= 0 && x < imageWidth && y >= 0 && y < imageHeight
		&& zBuffer.at(index) < z)
	{
		currentImage.at(index) = color;
		zBuffer.at(index) = z;
	}
}

void Image::drawLine(algebra::Vec4<float> color1, algebra::Vec4<float> color2, int x1, int y1, float z1, int x2, int y2, float z2)
{
	int dx = x2 - x1;
	int dy = y2 - y1;
	float dz = z2 - z1;

	if (abs(dx) < abs(dy))
	{
		algebra::Vec4<float> col = color1;
		if (y1 > y2)
		{
			std::swap(x1, x2);
			std::swap(y1, y2);
			std::swap(z1, z2);
			col = color2;
		}

		float dr = color2.x - color1.x;
		float dg = color2.y - color1.y;
		float db = color2.z - color1.z;

		for (int y = y1; y <= y2; y++)
		{
			int x = x1 + dx * (y - y1) / dy;
			float z = z1 + dz * (y - y1) / dy;
			algebra::Vec4<float> color(0,0,0,0);
			color.x = col.x + dr * (y - y1) / dy;
			color.y = col.y + dg * (y - y1) / dy;
			color.z = col.z + db * (y - y1) / dy;
			color.w = 255;

			drawPoint(color, x, y, z);
		}
	}
	else if (abs(dx) > abs(dy) || dx != 0)
	{
		algebra::Vec4<float> col = color1;
		if (x1 > x2)
		{
			std::swap(x1, x2);
			std::swap(y1, y2);
			std::swap(z1, z2);
			col = color2;
		}

		float dr = color2.x - color1.x;
		float dg = color2.y - color1.y;
		float db = color2.z - color1.z;

		for (int x = x1; x <= x2; x++)
		{
			int y = y1 + dy * (x - x1) / dx;
			float z = z1 + dz * (x - x1) / dx;
			algebra::Vec4<float> color(0,0,0,0);
			color.x = col.x + dr * (x - x1) / dx;
			color.y = col.y + dg * (x - x1) / dx;
			color.z = col.z + db * (x - x1) / dx;
			color.w = 255;

			drawPoint(color, x, y, z);
		}
	}
	else
	{
		drawPoint(color1, x1, y1, 0);
	}
}



void Image::drawTriangle(Camera& cam, algebra::Vec4<float> color1, const algebra::Vec3<float>& vec1, algebra::Vec4<float> color2, const algebra::Vec3<float>& vec2, algebra::Vec4<float> color3, const algebra::Vec3<float>& vec3)
{
	drawLine(color1, color2, vec1.x, vec1.y, vec1.z, vec2.x, vec2.y, vec2.z);
	drawLine(color2, color3, vec2.x, vec2.y, vec2.z, vec3.x, vec3.y, vec3.z);
	drawLine(color1, color3, vec1.x, vec1.y, vec1.z, vec3.x, vec3.y, vec3.z);
}


void Image::drawMesh(const Mesh& mesh, const algebra::Matrix4<float>& m_view, Camera& camera, float rotation)
{
	std::vector<algebra::Vec4<float>> points;
	for (const algebra::Vec4<float>& f : mesh.points) {
		algebra::Vec3<float> v3(f);

		v3 = v3 * algebra::Matrix3<float>::rotateMatrixX(rotation * 0.3f);
		v3 = v3 * algebra::Matrix3<float>::rotateMatrixY(rotation * 0.5f);
		v3 = v3 * algebra::Matrix3<float>::rotateMatrixZ(rotation);


		points.push_back(algebra::Vec4<float>(v3.x, v3.y, v3.z, f.w));
	}


	std::vector<algebra::Vec4<float>> projectedPoints = mesh.project(points, imageWidth, imageHeight, m_view);

	for (algebra::Vec4<float>& f : projectedPoints) {
		f = (f + 1) / 2;

		f.x *= imageWidth;
		f.y *= imageHeight;
	}

	for (int i = 0; i < mesh.indices.size(); i += 3) {

		Vertex a;
		a.screenPosition = projectedPoints[mesh.indices[i]];

		Vertex b;
		b.screenPosition = projectedPoints[mesh.indices[i+1]];

		Vertex c;
		c.screenPosition = projectedPoints[mesh.indices[i+2]];

		if (mesh.uv.size() == 0) 
		{
			a.color = mesh.colors[mesh.indices[i]];
			b.color = mesh.colors[mesh.indices[i + 1]];
			c.color = mesh.colors[mesh.indices[i + 2]];
		}
		else
		{
			a.color = algebra::Vec4<float>(mesh.uv[mesh.indicesUv[i]].x, mesh.uv[mesh.indicesUv[i]].y,0,1);
			b.color = algebra::Vec4<float>(mesh.uv[mesh.indicesUv[i+1]].x, mesh.uv[mesh.indicesUv[i+1]].y,0,1);
			c.color = algebra::Vec4<float>(mesh.uv[mesh.indicesUv[i+2]].x, mesh.uv[mesh.indicesUv[i+2]].y,0,1);
		}

		if (isVisible(camera, projectedPoints[mesh.indices[i]], projectedPoints[mesh.indices[i + 1]],
			projectedPoints[mesh.indices[i + 2]], points[mesh.indices[i]])) {

			fillTriangle(a, b, c, points[mesh.indices[i]], points[mesh.indices[i+1]], points[mesh.indices[i+2]], mesh);

			
			/*drawTriangle(camera, algebra::Vec4<float>{ 0,0,0,255 }, projectedPoints[mesh.indices_[i]],
				algebra::Vec4<float>{ 0,0,0,255 }, projectedPoints[mesh.indices_[i + 1]],
				algebra::Vec4<float>{ 0,0,0,255 }, projectedPoints[mesh.indices_[i + 2]]);*/
		}
	}


}

void Image::fillTriangle(Vertex a, Vertex b, Vertex c, algebra::Vec3<float> pos1,
	algebra::Vec3<float> pos2, algebra::Vec3<float> pos3, const Mesh& mesh)
{
	algebra::Vec3<float> n;
	n = (pos2 - pos1) ^ (pos3 - pos1);
	n = n.normalize();

	algebra::Vec3<float> lightPos(0, 0, 1);
	algebra::Vec4<float> lightColor(0, 0, 0, 1);
	lightPos = lightPos.normalize();
	float shade = lightPos * n;

	Vertex firstPoint(a);
	Vertex secondPoint(a);
	Vertex lastPoint(a);

	if (b.screenPosition.y < firstPoint.screenPosition.y)
	{
		firstPoint = b;
	}
	else if (b.screenPosition.y > lastPoint.screenPosition.y)
	{
		lastPoint = b;
	}
	else if (b.screenPosition.y == firstPoint.screenPosition.y && b.screenPosition.x < firstPoint.screenPosition.x)
	{
		firstPoint = b;
	}
	else if (b.screenPosition.y == lastPoint.screenPosition.y && b.screenPosition.x > lastPoint.screenPosition.x)
	{
		lastPoint = b;
	}


	if (c.screenPosition.y < firstPoint.screenPosition.y)
	{
		firstPoint = c;
	}
	else if (c.screenPosition.y > lastPoint.screenPosition.y)
	{
		lastPoint = c;
	}
	else if (c.screenPosition.y == firstPoint.screenPosition.y && c.screenPosition.x < firstPoint.screenPosition.x)
	{
		firstPoint = c;
	}
	else if (c.screenPosition.y == lastPoint.screenPosition.y && c.screenPosition.x > lastPoint.screenPosition.x)
	{
		lastPoint = c;
	}

	if (firstPoint.screenPosition != b.screenPosition && lastPoint.screenPosition != b.screenPosition)
	{
		secondPoint = b;
	}
	else if (firstPoint.screenPosition != c.screenPosition && lastPoint.screenPosition != c.screenPosition)
	{
		secondPoint = c;
	}



	float dx1_2 = secondPoint.screenPosition.x - firstPoint.screenPosition.x;
	float dy1_2 = secondPoint.screenPosition.y - firstPoint.screenPosition.y;
	float dz1_2 = secondPoint.screenPosition.z - firstPoint.screenPosition.z;
	float dw1_2 = secondPoint.screenPosition.w - firstPoint.screenPosition.w;

	float dx1_3 = lastPoint.screenPosition.x - firstPoint.screenPosition.x;
	float dy1_3 = lastPoint.screenPosition.y - firstPoint.screenPosition.y;
	float dz1_3 = lastPoint.screenPosition.z - firstPoint.screenPosition.z;
	float dw1_3 = lastPoint.screenPosition.w - firstPoint.screenPosition.w;

	float dx2_3 = lastPoint.screenPosition.x - secondPoint.screenPosition.x;
	float dy2_3 = lastPoint.screenPosition.y - secondPoint.screenPosition.y;
	float dz2_3 = lastPoint.screenPosition.z - secondPoint.screenPosition.z;
	float dw2_3 = lastPoint.screenPosition.w - secondPoint.screenPosition.w;

	float minX = std::min({firstPoint.screenPosition.x, secondPoint.screenPosition.x, lastPoint.screenPosition.x});
	float maxX = std::max({firstPoint.screenPosition.x, secondPoint.screenPosition.x, lastPoint.screenPosition.x});


	float dr1_2 = secondPoint.color.x - firstPoint.color.x;
	float dg1_2 = secondPoint.color.y - firstPoint.color.y;
	float db1_2 = secondPoint.color.z - firstPoint.color.z;

	float dr1_3 = lastPoint.color.x - firstPoint.color.x;
	float dg1_3 = lastPoint.color.y - firstPoint.color.y;
	float db1_3 = lastPoint.color.z - firstPoint.color.z;

	float dr2_3 = lastPoint.color.x - secondPoint.color.x;
	float dg2_3 = lastPoint.color.y - secondPoint.color.y;
	float db2_3 = lastPoint.color.z - secondPoint.color.z;

	for (int y = firstPoint.screenPosition.y; y <= lastPoint.screenPosition.y; y++)
	{

		float coef1_2 = 1;
		float coef1_3 = 1;
		float coef2_3 = 1;

		if (dy1_2 != 0) {
			coef1_2 = (int)(y - firstPoint.screenPosition.y) / dy1_2;
		}
		if (dy1_3 != 0) {
			coef1_3 = (int)(y - firstPoint.screenPosition.y) / dy1_3;
		}
		if (dy2_3 != 0) {
			coef2_3 = (int)(y - secondPoint.screenPosition.y) / dy2_3;
		}
		if (coef1_2 < 0) {
			coef1_2 = 0;
		}
		if (coef1_3 < 0) {
			coef1_3 = 0;
		}
		if (coef2_3 < 0) {
			coef2_3 = 0;
		}

		float xLine1;
		float zLine1;
		float wLine1;
		algebra::Vec4<float> color1;
		float xLine2 = firstPoint.screenPosition.x + dx1_3 * coef1_3;
		float zLine2 = firstPoint.screenPosition.z + dz1_3 * coef1_3;
		float wLine2 = firstPoint.screenPosition.w + dw1_3 * coef1_3;
		algebra::Vec4<float> color2;
		color2.x = firstPoint.color.x + dr1_3 * coef1_3;
		color2.y = firstPoint.color.y + dg1_3 * coef1_3;
		color2.z = firstPoint.color.z + db1_3 * coef1_3;

		if (y > secondPoint.screenPosition.y) {
			xLine1 = secondPoint.screenPosition.x + dx2_3 * coef2_3;
			zLine1 = secondPoint.screenPosition.z + dz2_3 * coef2_3;
			wLine1 = secondPoint.screenPosition.w + dw2_3 * coef2_3;
			color1.x = secondPoint.color.x + (dr2_3 * coef2_3);
			color1.y = secondPoint.color.y + (dg2_3 * coef2_3);
			color1.z = secondPoint.color.z + (db2_3 * coef2_3);
		}
		else {
			xLine1 = firstPoint.screenPosition.x + dx1_2 * coef1_2;
			zLine1 = firstPoint.screenPosition.z + dz1_2 * coef1_2;
			wLine1 = firstPoint.screenPosition.w + dw1_2 * coef1_2;
			color1.x = firstPoint.color.x + (dr1_2 * coef1_2);
			color1.y = firstPoint.color.y + (dg1_2 * coef1_2);
			color1.z = firstPoint.color.z + (db1_2 * coef1_2);
		}


		float dr = color2.x - color1.x;
		float dg = color2.y - color1.y;
		float db = color2.z - color1.z;

		algebra::Vec4<float> col = color1;
		algebra::Vec4<float> col2 = color2;
		if (xLine1 > xLine2)
		{
			std::swap(xLine1, xLine2);
			std::swap(zLine1, zLine2);
			std::swap(wLine1, wLine2);
			col = color2;
			col2 = color1;
			dr *= -1;
			dg *= -1;
			db *= -1;
		}

		for (int x = minX; x < maxX; x++)
		{
			if (x > xLine1 && x < xLine2) {

				int dx = xLine2 - xLine1;


				int dw = wLine2 - wLine1;
				float w = wLine1 + dw * (int)(x - xLine1);
				float alpha = (int)(x - xLine1);
				if (dx != 0) {
					alpha /= dx;
					w /= dx;
				}
				float b = alpha * wLine1 / ((1 - alpha)*wLine2 + alpha * wLine1);
				float fx = ((1 - b)*xLine1 + b * xLine2) / ((1 - b)*wLine1 + b*wLine2);
				float u = ((1 - b)*col.x + b * col2.x) / ((1 - b)*wLine1 + b*wLine2);
				float v = ((1 - b)*col.y + b * col2.y) / ((1 - b)*wLine1 + b*wLine2);

				algebra::Vec4<float> color;
				color.w = 255;

				if (dx == 0)
				{
					color.x = col.x;
					color.y = col.y;
					color.z = col.z;
				}
				else
				{
					color.x = col.x + dr * (int)(x - xLine1) / wLine1 * w;
					color.y = col.y + dg * (int)(x - xLine1) / wLine1 * w;
					//color.x = col.x + dr * (int)(x - xLine1) / dx;
					//color.y = col.y + dg * (int)(x - xLine1) / dx;
					color.z = col.z + db * (int)(x - xLine1) / dx;
				}

				if (mesh.textureColors.size() != 0 && mesh.uv.size() > 0) 
				{
					float pxWidthF = std::max(0.0f, std::min(color.x * mesh.textureWidth, mesh.textureWidth - 1.0f));
					float pxHeightF = std::max(0.0f, std::min(color.y * mesh.textureHeight, mesh.textureHeight - 1.0f));

					int pxWidth = pxWidthF;
					int pxHeight = pxHeightF;

					if (pxHeight+1 < mesh.textureHeight && pxWidth+1 < mesh.textureWidth) {
						algebra::Vec4<float> c1 = mesh.textureColors[pxWidth + mesh.textureWidth*pxHeight];
						algebra::Vec4<float> c2 = mesh.textureColors[pxWidth + 1 + mesh.textureWidth*pxHeight];
						algebra::Vec4<float> c3 = mesh.textureColors[pxWidth + mesh.textureWidth*(pxHeight + 1)];
						algebra::Vec4<float> c4 = mesh.textureColors[pxWidth + 1 + mesh.textureWidth*(pxHeight + 1)];

						float dWidth = pxWidthF - pxWidth;
						float dHeight = pxHeightF - pxHeight;

						color.x = (1 - dHeight)*((1 - dWidth)*c1.x + dWidth * c2.x) + dHeight * ((1 - dWidth)*c3.x + dWidth * c4.x);
						color.y = (1 - dHeight)*((1 - dWidth)*c1.y + dWidth * c2.y) + dHeight * ((1 - dWidth)*c3.y + dWidth * c4.y);
						color.z = (1 - dHeight)*((1 - dWidth)*c1.z + dWidth * c2.z) + dHeight * ((1 - dWidth)*c3.z + dWidth * c4.z);
					}
					else 
					{
						color = mesh.textureColors[pxWidth + mesh.textureWidth*pxHeight];
					}

					

					//color = mesh.textureColors[pxWidth + mesh.textureWidth*pxHeight];
				}

				color.x = (color.x + lightColor.x) / 2 * shade;
				color.y = (color.y + lightColor.y) / 2 * shade;
				color.z = (color.z + lightColor.z) / 2 * shade;
				

				drawPoint(algebra::Vec4<float>(color.x, color.y, color.z, 1), x, y, a.screenPosition.z);
			}
		}
	}
}

bool Image::isVisible(Camera& cam, const algebra::Vec3<float>& vec1,
	const algebra::Vec3<float>& vec2, const algebra::Vec3<float>& vec3,
	const algebra::Vec3<float>& pos)
{
	if (isOutOfScreen(vec1, vec2, vec3)) 
	{
		return false;
	}

	algebra::Vec3<float> n = (vec2 - vec1) ^ (vec3 - vec1);
	n = n.normalize();

	//algebra::Vec3<float> camera(0, 0, 0);
	algebra::Matrix4<float> projection = algebra::Matrix4<float>::projectionMatrix(imageWidth, imageHeight, 0.1, 100000, 90 * M_PI / 180);
	algebra::Vec3<float> camera(cam.position);

	algebra::Vec3<float> v3 = pos - camera;

	algebra::Vec4<float> v4(v3);

	v4 = v4 * projection;

	if (v4.w != 0) {
		v3.x = v4.x / v4.w;
		v3.y = v4.y / v4.w;
		v3.z = v4.z / v4.w;
	}


	v3 = (v3 + 1) / 2;
	v3.x *= imageWidth;
	v3.y *= imageHeight;

	return n * v3 < 0.0f;
}

bool Image::isOutOfScreen(const algebra::Vec3<float>& vec1, const algebra::Vec3<float>& vec2, const algebra::Vec3<float>& vec3)
{
	if ((vec1.x < 0 || vec1.x > imageWidth || vec1.y < 0 || vec1.y > imageHeight) &&
		(vec2.x < 0 || vec2.x > imageWidth || vec2.y < 0 || vec2.y > imageHeight) && 
		(vec3.x < 0 || vec3.x > imageWidth || vec3.y < 0 || vec3.y > imageHeight))
	{
		return true;
	}
	return false;
}
