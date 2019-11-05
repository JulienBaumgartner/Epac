#include "Image.h"
#include <algorithm>
#include <iostream>
#include <string>


Image::Image(int width, int height, Camera& camera) : camera_(camera)
{
	image_width = width;
	image_height = height;

	current_image.assign(image_width*image_height, { 40, 0, 40, 255 });
	z_buffer.assign(image_width*image_height, { -10000 });
}


Image::~Image()
{
}


void Image::drawPoint(algebra::Vec4<float> color, int x, int y, float z)
{
	if (x >= image_width) {
		x = image_width-1;
	}
	if (y >= image_height) {
		y = image_height - 1;
	}
	int index = x + y * image_width;
	if (x >= 0 && x < image_width && y >= 0 && y < image_height
		&& z_buffer.at(index) < z)
	{
		current_image.at(index) = color;
		z_buffer.at(index) = z;
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

		float dr = color2.x_ - color1.x_;
		float dg = color2.y_ - color1.y_;
		float db = color2.z_ - color1.z_;

		for (int y = y1; y <= y2; y++)
		{
			int x = x1 + dx * (y - y1) / dy;
			float z = z1 + dz * (y - y1) / dy;
			algebra::Vec4<float> color(0,0,0,0);
			color.x_ = col.x_ + dr * (y - y1) / dy;
			color.y_ = col.y_ + dg * (y - y1) / dy;
			color.z_ = col.z_ + db * (y - y1) / dy;
			color.w_ = 255;

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

		float dr = color2.x_ - color1.x_;
		float dg = color2.y_ - color1.y_;
		float db = color2.z_ - color1.z_;

		for (int x = x1; x <= x2; x++)
		{
			int y = y1 + dy * (x - x1) / dx;
			float z = z1 + dz * (x - x1) / dx;
			algebra::Vec4<float> color(0,0,0,0);
			color.x_ = col.x_ + dr * (x - x1) / dx;
			color.y_ = col.y_ + dg * (x - x1) / dx;
			color.z_ = col.z_ + db * (x - x1) / dx;
			color.w_ = 255;

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
	drawLine(color1, color2, vec1.x_, vec1.y_, vec1.z_, vec2.x_, vec2.y_, vec2.z_);
	drawLine(color2, color3, vec2.x_, vec2.y_, vec2.z_, vec3.x_, vec3.y_, vec3.z_);
	drawLine(color1, color3, vec1.x_, vec1.y_, vec1.z_, vec3.x_, vec3.y_, vec3.z_);
}


void Image::drawMesh(const Mesh& mesh, const algebra::Matrix4<float>& m_view, Camera& camera, float rotation)
{
	std::vector<algebra::Vec3<float>> points;
	for (const algebra::Vec3<float>& f : mesh.points_) {
		auto vec = f;

		vec = vec * algebra::Matrix3<float>::rotateMatrixX(rotation * 0.3f);
		vec = vec * algebra::Matrix3<float>::rotateMatrixY(rotation * 0.5f);
		vec = vec * algebra::Matrix3<float>::rotateMatrixZ(rotation);


		points.push_back(vec);
	}


	std::vector<algebra::Vec3<float>> projectedPoints = mesh.project(points, image_width, image_height, m_view);

	for (algebra::Vec3<float>& f : projectedPoints) {
		f = (f + 1) / 2;

		f.x_ *= image_width;
		f.y_ *= image_height;
	}

	for (int i = 0; i < mesh.indices_.size(); i += 3) {

		Vertex a;
		a.color = mesh.colors_[mesh.indices_[i]];
		a.screen_position = projectedPoints[mesh.indices_[i]];

		Vertex b;
		b.color = mesh.colors_[mesh.indices_[i+1]];
		b.screen_position = projectedPoints[mesh.indices_[i+1]];

		Vertex c;
		c.color = mesh.colors_[mesh.indices_[i+2]];
		c.screen_position = projectedPoints[mesh.indices_[i+2]];

		if (isVisible(camera, projectedPoints[mesh.indices_[i]], projectedPoints[mesh.indices_[i + 1]],
			projectedPoints[mesh.indices_[i + 2]], points[mesh.indices_[i]])) {

			fillTriangle(a, b, c, points[mesh.indices_[i]], points[mesh.indices_[i+1]], points[mesh.indices_[i+2]]);


			/*drawTriangle(camera, algebra::Vec4<float>{ 0,0,0,255 }, projectedPoints[mesh.indices_[i]],
				algebra::Vec4<float>{ 0,0,0,255 }, projectedPoints[mesh.indices_[i + 1]],
				algebra::Vec4<float>{ 0,0,0,255 }, projectedPoints[mesh.indices_[i + 2]]);*/


			/*drawTriangle(camera, mesh.colors_[mesh.indices_[i]], projectedPoints[mesh.indices_[i]],
				mesh.colors_[mesh.indices_[i + 1]], projectedPoints[mesh.indices_[i + 1]],
				mesh.colors_[mesh.indices_[i + 2]], projectedPoints[mesh.indices_[i + 2]]);*/
		}
	}


}

void Image::fillTriangle(Vertex a, Vertex b, Vertex c, algebra::Vec3<float> pos1, algebra::Vec3<float> pos2, algebra::Vec3<float> pos3)
{
	algebra::Vec3<float> n = (pos2 - pos1) ^ (pos3 - pos1);
	n = n.normalize();

	algebra::Vec3<float> light_pos(0, 0, 1);
	algebra::Vec4<float> light_color(0, 0, 0.5, 1);
	light_pos = light_pos.normalize();
	float shade = light_pos * n;

	Vertex firstPoint(a);
	Vertex secondPoint(a);
	Vertex lastPoint(a);

	if (b.screen_position.y_ < firstPoint.screen_position.y_)
	{
		firstPoint = b;
	}
	else if (b.screen_position.y_ > lastPoint.screen_position.y_)
	{
		lastPoint = b;
	}
	else if (b.screen_position.y_ == firstPoint.screen_position.y_ && b.screen_position.x_ < firstPoint.screen_position.x_)
	{
		firstPoint = b;
	}
	else if (b.screen_position.y_ == lastPoint.screen_position.y_ && b.screen_position.x_ > lastPoint.screen_position.x_)
	{
		lastPoint = b;
	}


	if (c.screen_position.y_ < firstPoint.screen_position.y_)
	{
		firstPoint = c;
	}
	else if (c.screen_position.y_ > lastPoint.screen_position.y_)
	{
		lastPoint = c;
	}
	else if (c.screen_position.y_ == firstPoint.screen_position.y_ && c.screen_position.x_ < firstPoint.screen_position.x_)
	{
		firstPoint = c;
	}
	else if (c.screen_position.y_ == lastPoint.screen_position.y_ && c.screen_position.x_ > lastPoint.screen_position.x_)
	{
		lastPoint = c;
	}

	if (firstPoint.screen_position != b.screen_position && lastPoint.screen_position != b.screen_position)
	{
		secondPoint = b;
	}
	else if (firstPoint.screen_position != c.screen_position && lastPoint.screen_position != c.screen_position)
	{
		secondPoint = c;
	}



	float dx1_2 = secondPoint.screen_position.x_ - firstPoint.screen_position.x_;
	float dy1_2 = secondPoint.screen_position.y_ - firstPoint.screen_position.y_;
	float dz1_2 = secondPoint.screen_position.z_ - firstPoint.screen_position.z_;

	float dx1_3 = lastPoint.screen_position.x_ - firstPoint.screen_position.x_;
	float dy1_3 = lastPoint.screen_position.y_ - firstPoint.screen_position.y_;
	float dz1_3 = lastPoint.screen_position.z_ - firstPoint.screen_position.z_;

	float dx2_3 = lastPoint.screen_position.x_ - secondPoint.screen_position.x_;
	float dy2_3 = lastPoint.screen_position.y_ - secondPoint.screen_position.y_;
	float dz2_3 = lastPoint.screen_position.z_ - secondPoint.screen_position.z_;

	float minX = std::min({firstPoint.screen_position.x_, secondPoint.screen_position.x_, lastPoint.screen_position.x_});
	float maxX = std::max({firstPoint.screen_position.x_, secondPoint.screen_position.x_, lastPoint.screen_position.x_});


	float dr1_2 = secondPoint.color.x_ - firstPoint.color.x_;
	float dg1_2 = secondPoint.color.y_ - firstPoint.color.y_;
	float db1_2 = secondPoint.color.z_ - firstPoint.color.z_;

	float dr1_3 = lastPoint.color.x_ - firstPoint.color.x_;
	float dg1_3 = lastPoint.color.y_ - firstPoint.color.y_;
	float db1_3 = lastPoint.color.z_ - firstPoint.color.z_;

	float dr2_3 = lastPoint.color.x_ - secondPoint.color.x_;
	float dg2_3 = lastPoint.color.y_ - secondPoint.color.y_;
	float db2_3 = lastPoint.color.z_ - secondPoint.color.z_;


	for (int y = firstPoint.screen_position.y_; y <= lastPoint.screen_position.y_; y++)
	{

		float coef1_2 = 1;
		float coef1_3 = 1;
		float coef2_3 = 1;

		if (dy1_2 != 0) {
			coef1_2 = (int)(y - firstPoint.screen_position.y_) / dy1_2;
		}
		if (dy1_3 != 0) {
			coef1_3 = (int)(y - firstPoint.screen_position.y_) / dy1_3;
		}
		if (dy2_3 != 0) {
			coef2_3 = (int)(y - secondPoint.screen_position.y_) / dy2_3;
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

		float x_line1;
		float z_line1;
		algebra::Vec4<float> color1;
		float x_line2 = firstPoint.screen_position.x_ + dx1_3 * coef1_3;
		float z_line2 = firstPoint.screen_position.z_ + dz1_3 * coef1_3;
		algebra::Vec4<float> color2;
		color2.x_ = firstPoint.color.x_ + dr1_3 * coef1_3;
		color2.y_ = firstPoint.color.y_ + dg1_3 * coef1_3;
		color2.z_ = firstPoint.color.z_ + db1_3 * coef1_3;

		if (y > secondPoint.screen_position.y_) {
			x_line1 = secondPoint.screen_position.x_ + dx2_3 * coef2_3;
			z_line1 = secondPoint.screen_position.z_ + dz2_3 * coef2_3;
			color1.x_ = secondPoint.color.x_ + (dr2_3 * coef2_3);
			color1.y_ = secondPoint.color.y_ + (dg2_3 * coef2_3);
			color1.z_ = secondPoint.color.z_ + (db2_3 * coef2_3);
		}
		else {
			x_line1 = firstPoint.screen_position.x_ + dx1_2 * coef1_2;
			z_line1 = firstPoint.screen_position.z_ + dz1_2 * coef1_2;
			color1.x_ = firstPoint.color.x_ + (dr1_2 * coef1_2);
			color1.y_ = firstPoint.color.y_ + (dg1_2 * coef1_2);
			color1.z_ = firstPoint.color.z_ + (db1_2 * coef1_2);
		}


		float dr = color2.x_ - color1.x_;
		float dg = color2.y_ - color1.y_;
		float db = color2.z_ - color1.z_;

		algebra::Vec4<float> col = color1;
		algebra::Vec4<float> col2 = color2;
		if (x_line1 > x_line2)
		{
			std::swap(x_line1, x_line2);
			std::swap(z_line1, z_line2);
			col = color2;
			col2 = color1;
			dr *= -1;
			dg *= -1;
			db *= -1;
		}

		for (int x = minX + 1; x < maxX; x++)
		{
			if (x > x_line1 && x < x_line2) {

				int dx = x_line2 - x_line1;
				algebra::Vec4<float> color;
				color.w_ = 255;

				if (dx == 0)
				{
					color.x_ = col.x_;
					color.y_ = col.y_;
					color.z_ = col.z_;
				}
				else
				{
					color.x_ = col.x_ + dr * (int)(x - x_line1) / dx;
					color.y_ = col.y_ + dg * (int)(x - x_line1) / dx;
					color.z_ = col.z_ + db * (int)(x - x_line1) / dx;
				}

				color.x_ = (color.x_ + light_color.x_) / 2 * shade;
				color.y_ = (color.y_ + light_color.y_) / 2 * shade;
				color.z_ = (color.z_ + light_color.z_) / 2 * shade;
				

				drawPoint(algebra::Vec4<float>(color.x_, color.y_, color.z_, 1), x, y, a.screen_position.z_);
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
	algebra::Matrix4<float> projection = algebra::Matrix4<float>::projectionMatrix(image_width, image_height, 0.1, 100000, 90 * M_PI / 180);
	algebra::Vec3<float> camera(cam.position);

	algebra::Vec3<float> v3 = pos - camera;

	algebra::Vec4<float> v4(v3);

	v4 = v4 * projection;

	if (v4.w_ != 0) {
		v3.x_ = v4.x_ / v4.w_;
		v3.y_ = v4.y_ / v4.w_;
		v3.z_ = v4.z_ / v4.w_;
	}


	v3 = (v3 + 1) / 2;
	v3.x_ *= image_width;
	v3.y_ *= image_height;

	return n * v3 < 0.0f;
}

bool Image::isOutOfScreen(const algebra::Vec3<float>& vec1, const algebra::Vec3<float>& vec2, const algebra::Vec3<float>& vec3)
{
	if ((vec1.x_ < 0 || vec1.x_ > image_width || vec1.y_ < 0 || vec1.y_ > image_height) &&
		(vec2.x_ < 0 || vec2.x_ > image_width || vec2.y_ < 0 || vec2.y_ > image_height) && 
		(vec3.x_ < 0 || vec3.x_ > image_width || vec3.y_ < 0 || vec3.y_ > image_height))
	{
		return true;
	}
	return false;
}
