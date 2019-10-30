#include "Image.h"
#include <algorithm>
#include <iostream>
#include <string>


Image::Image(int width, int height)
{
	image_width = width;
	image_height = height;

	current_image.assign(image_width*image_height, { 40, 0, 40, 255 });
}


Image::~Image()
{
}


void Image::drawPoint(Pixel color, int x, int y)
{
	if (x >= image_width) {
		x = image_width-1;
	}
	if (y >= image_height) {
		y = image_height - 1;
	}
	int index = x + y * image_width;
	if (x >= 0 && x < image_width && y >= 0 && y < image_height)
	{
		current_image.at(index) = color;
	}
}

void Image::drawLine(Pixel color1, Pixel color2, int x1, int y1, int x2, int y2)
{
	int dx = x2 - x1;
	int dy = y2 - y1;

	if (abs(dx) < abs(dy))
	{
		Pixel col = color1;
		if (y1 > y2)
		{
			std::swap(x1, x2);
			std::swap(y1, y2);
			col = color2;
		}

		int dr = color2.r - color1.r;
		int dg = color2.g - color1.g;
		int db = color2.b - color1.b;

		for (int y = y1; y <= y2; y++)
		{
			int x = x1 + dx * (y - y1) / dy;
			Pixel color;
			color.r = col.r + dr * (y - y1) / dy;
			color.g = col.g + dg * (y - y1) / dy;
			color.b = col.b + db * (y - y1) / dy;
			color.a = 255;

			drawPoint(color, x, y);
		}
	}
	else if (abs(dx) > abs(dy) || dx != 0)
	{
		Pixel col = color1;
		if (x1 > x2)
		{
			std::swap(x1, x2);
			std::swap(y1, y2);
			col = color2;
		}

		int dr = color2.r - color1.r;
		int dg = color2.g - color1.g;
		int db = color2.b - color1.b;

		for (int x = x1; x <= x2; x++)
		{
			int y = y1 + dy * (x - x1) / dx;
			Pixel color;
			color.r = col.r + dr * (x - x1) / dx;
			color.g = col.g + dg * (x - x1) / dx;
			color.b = col.b + db * (x - x1) / dx;
			color.a = 255;

			drawPoint(color, x, y);
		}
	}
	else
	{
		drawPoint(color1, x1, y1);
	}
}



static float t = 287.98f;
void Image::drawTriangle(Camera& cam, Pixel color1, const algebra::Vec3<float>& vec1, Pixel color2, const algebra::Vec3<float>& vec2, Pixel color3, const algebra::Vec3<float>& vec3)
{
	drawLine(color1, color2, vec1.x_, vec1.y_, vec2.x_, vec2.y_);
	drawLine(color2, color3, vec2.x_, vec2.y_, vec3.x_, vec3.y_);
	drawLine(color1, color3, vec1.x_, vec1.y_, vec3.x_, vec3.y_);
}


void Image::drawMesh(const Mesh& mesh, const algebra::Matrix4<float>& m_view, Camera& camera)
{
	std::vector<algebra::Vec3<float>> points;
	for (const algebra::Vec3<float>& f : mesh.points_) {
		auto vec = f;

		vec = vec * algebra::Matrix3<float>::rotateMatrixX(t * 0.3f);
		vec = vec * algebra::Matrix3<float>::rotateMatrixY(t * 0.5f);
		vec = vec * algebra::Matrix3<float>::rotateMatrixZ(t);
		//t += 0.03f;


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

		if (isVisible(camera, projectedPoints[mesh.indices_[i]], projectedPoints[mesh.indices_[i + 1]], projectedPoints[mesh.indices_[i + 2]], points[mesh.indices_[i]])) {

			fillTriangle(a, b, c);


			drawTriangle(camera, Pixel{ 0,0,0,255 }, projectedPoints[mesh.indices_[i]],
				Pixel{ 0,0,0,255 }, projectedPoints[mesh.indices_[i + 1]],
				Pixel{ 0,0,0,255 }, projectedPoints[mesh.indices_[i + 2]]);


			/*drawTriangle(camera, mesh.colors_[mesh.indices_[i]], projectedPoints[mesh.indices_[i]],
				mesh.colors_[mesh.indices_[i + 1]], projectedPoints[mesh.indices_[i + 1]],
				mesh.colors_[mesh.indices_[i + 2]], projectedPoints[mesh.indices_[i + 2]]);*/
		}
	}


}

void Image::fillTriangle(Vertex a, Vertex b, Vertex c)
{
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

		float dx1_3 = lastPoint.screen_position.x_ - firstPoint.screen_position.x_;
		float dy1_3 = lastPoint.screen_position.y_ - firstPoint.screen_position.y_;

		float dx2_3 = lastPoint.screen_position.x_ - secondPoint.screen_position.x_;
		float dy2_3 = lastPoint.screen_position.y_ - secondPoint.screen_position.y_;

		float minX = std::min({firstPoint.screen_position.x_, secondPoint.screen_position.x_, lastPoint.screen_position.x_});
		float maxX = std::max({firstPoint.screen_position.x_, secondPoint.screen_position.x_, lastPoint.screen_position.x_});


		int dr1_2 = secondPoint.color.r - firstPoint.color.r;
		int dg1_2 = secondPoint.color.g - firstPoint.color.g;
		int db1_2 = secondPoint.color.b - firstPoint.color.b;

		int dr1_3 = lastPoint.color.r - firstPoint.color.r;
		int dg1_3 = lastPoint.color.g - firstPoint.color.g;
		int db1_3 = lastPoint.color.b - firstPoint.color.b;

		int dr2_3 = lastPoint.color.r - secondPoint.color.r;
		int dg2_3 = lastPoint.color.g - secondPoint.color.g;
		int db2_3 = lastPoint.color.b - secondPoint.color.b;


		for (int y = firstPoint.screen_position.y_; y <= lastPoint.screen_position.y_; y++)
		{

			float x1_2 = firstPoint.screen_position.x_;
			float x1_3 = firstPoint.screen_position.x_;
			float x2_3 = secondPoint.screen_position.x_;
			if (dy1_2 != 0)
			{
				//x1_2 += dx1_2 * (y - firstPoint.y_) / dy1_2;
			}
			if (dy1_3 != 0)
			{
				///x1_3 += dx1_3 * (y - firstPoint.y_) / dy1_3;
			}
			if (dy2_3 != 0)
			{
				//x2_3 += dx2_3 * (y - firstPoint.y_) / dy2_3;
			}

			float x_line1;
			Pixel color1;

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

			float x_line2 = x1_3 + dx1_3 * coef1_3;
			Pixel color2;
			color2.r = firstPoint.color.r + dr1_3 * coef1_3;
			color2.g = firstPoint.color.g + dg1_3 * coef1_3;
			color2.b = firstPoint.color.b + db1_3 * coef1_3;

			if (y > secondPoint.screen_position.y_) {
				x_line1 = x2_3 + dx2_3 * coef2_3;
				color1.r = secondPoint.color.r + (dr2_3 * coef2_3);
				color1.g = secondPoint.color.g + (dg2_3 * coef2_3);
				color1.b = secondPoint.color.b + (db2_3 * coef2_3);
			}
			else {
				x_line1 = x1_2 + dx1_2 * coef1_2;
				color1.r = firstPoint.color.r + (dr1_2 * coef1_2);
				color1.g = firstPoint.color.g + (dg1_2 * coef1_2);
				color1.b = firstPoint.color.b + (db1_2 * coef1_2);
			}


			int dr = color2.r - color1.r;
			int dg = color2.g - color1.g;
			int db = color2.b - color1.b;

			Pixel col = color1;
			Pixel col2 = color2;
			if (x_line1 > x_line2)
			{
				std::swap(x_line1, x_line2);
				col = color2;
				col2 = color1;
				dr *= -1;
				dg *= -1;
				db *= -1;
			}

			for (int x = minX+1; x < maxX; x++)
			{
				if (x > x_line1 && x < x_line2) {

					int dx = x_line2 - x_line1;
					Pixel color;
					color.a = 255;

					if (dx == 0)
					{
						color.r = col.r;
						color.g = col.g;
						color.b = col.b;
					}
					else
					{
						color.r = col.r + dr * (int)(x - x_line1) / dx;
						color.g = col.g + dg * (int)(x - x_line1) / dx;
						color.b = col.b + db * (int)(x - x_line1) / dx;
					}

					drawPoint(color, x, y);
				}
			}
			
		}
	
}

bool Image::isVisible(Camera& cam, const algebra::Vec3<float>& vec1, const algebra::Vec3<float>& vec2, const algebra::Vec3<float>& vec3, const algebra::Vec3<float>& pos)
{
	algebra::Vec3<float> n = (vec2 - vec1) ^ (vec3 - vec1);
	n = n.normalize();

	//algebra::Vec3<float> camera(0, 0, 0);
	algebra::Matrix4<float> projection = algebra::Matrix4<float>::projectionMatrix(image_width, image_height, 0.1, 10000, 120 * M_PI / 180);
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
	//return n * (vec1 - v3) < 0.0f;
}
