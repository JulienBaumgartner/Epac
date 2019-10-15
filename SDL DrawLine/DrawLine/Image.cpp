#include "Image.h"



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



static float t = 0;
void Image::drawTriangle(Camera& cam, Pixel color1, const algebra::Vec3<float>& vec1, Pixel color2, const algebra::Vec3<float>& vec2, Pixel color3, const algebra::Vec3<float>& vec3)
{
	algebra::Vec3<float> n = (vec2 - vec1) ^ (vec3 - vec1);
	n = n.normalize();

	algebra::Vec3<float> camera(0,0,0);
	//algebra::Vec3<float> camera(cam.position);


	algebra::Vec4<float> v4(camera);
	v4 = v4 * algebra::Matrix4<float>::projectionMatrix(image_width, image_height, 0.1, 10000, 90 * M_PI / 180);

	if (v4.w_ != 0) {
		camera.x_ = v4.x_ / v4.w_;
		camera.y_ = v4.y_ / v4.w_;
		camera.z_ = v4.z_ / v4.w_;
	}

	camera = (camera + 1) / 2;
	camera.x_ *= image_width;
	camera.y_ *= image_height;


	if (n * (vec1 - camera) < 0.0f)
	{
		drawLine(color1, color2, vec1.x_, vec1.y_, vec2.x_, vec2.y_);
		drawLine(color2, color3, vec2.x_, vec2.y_, vec3.x_, vec3.y_);
		drawLine(color1, color3, vec1.x_, vec1.y_, vec3.x_, vec3.y_);
	}
}


void Image::drawMesh(const Mesh& mesh, const algebra::Matrix4<float>& m_view, Camera& camera)
{
	std::vector<algebra::Vec3<float>> points;
	for (const algebra::Vec3<float>& f : mesh.points_) {
		auto vec = f;

		vec = vec * algebra::Matrix3<float>::rotateMatrixX(t * 0.3f);
		vec = vec * algebra::Matrix3<float>::rotateMatrixY(t * 0.5f);
		vec = vec * algebra::Matrix3<float>::rotateMatrixZ(t);
		//t += 0.001f;


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

		fillTriangle(a, b, c);


		drawTriangle(camera, Pixel{0,0,0,255}, projectedPoints[mesh.indices_[i]],
			Pixel{ 0,0,0,255 }, projectedPoints[mesh.indices_[i + 1]],
			Pixel{ 0,0,0,255 }, projectedPoints[mesh.indices_[i + 2]]);
	}

}

void Image::fillTriangle(Vertex a, Vertex b, Vertex c)
{
	algebra::Vec3<float> firstPoint(a.screen_position);
	algebra::Vec3<float> secondPoint(a.screen_position);
	algebra::Vec3<float> lastPoint(a.screen_position);

	if (b.screen_position.y_ < firstPoint.y_)
	{
		firstPoint = b.screen_position;
	}
	else if (b.screen_position.y_ > lastPoint.y_)
	{
		lastPoint = b.screen_position;
	}
	else if(b.screen_position.y_ == firstPoint.y_ && b.screen_position.x_ < firstPoint.x_)
	{
		firstPoint = b.screen_position;
	}
	else if (b.screen_position.y_ == lastPoint.y_ && b.screen_position.x_ > lastPoint.x_)
	{
		lastPoint = b.screen_position;
	}


	if (c.screen_position.y_ < firstPoint.y_)
	{
		firstPoint = c.screen_position;
	}
	else if (c.screen_position.y_ > lastPoint.y_)
	{
		lastPoint = c.screen_position;
	}
	else if (c.screen_position.y_ == firstPoint.y_ && c.screen_position.x_ < firstPoint.x_)
	{
		firstPoint = c.screen_position;
	}
	else if (c.screen_position.y_ == lastPoint.y_ && c.screen_position.x_ > lastPoint.x_)
	{
		lastPoint = c.screen_position;
	}

	if (firstPoint != b.screen_position && lastPoint != b.screen_position)
	{
		secondPoint = b.screen_position;
	}
	else if (firstPoint != c.screen_position && lastPoint != c.screen_position)
	{
		secondPoint = c.screen_position;
	}



	int dx1_2 = secondPoint.x_ - firstPoint.x_;
	int dy1_2 = secondPoint.y_ - firstPoint.y_;

	int dx1_3 = lastPoint.x_ - firstPoint.x_;
	int dy1_3 = lastPoint.y_ - firstPoint.y_;

	int dx2_3 = lastPoint.x_ - secondPoint.x_;
	int dy2_3 = lastPoint.y_ - secondPoint.y_;



	for (int y = firstPoint.y_; y <= lastPoint.y_; y++)
	{
		/*int dr = color2.r - color1.r;
		int dg = color2.g - color1.g;
		int db = color2.b - color1.b;*/

			int x1_2 = firstPoint.x_;
			int x1_3 = firstPoint.x_; 
			int x2_3 = secondPoint.x_; 
			if (dy1_2 != 0) 
			{
				x1_2 += dx1_2 * (y - firstPoint.y_) / dy1_2;
			}
			if (dy1_3 != 0)
			{
				x1_3 += dx1_3 * (y - firstPoint.y_) / dy1_3;
			}
			if (dy2_3 != 0)
			{
				x2_3 += dx2_3 * (y - secondPoint.y_) / dy2_3;
			}

			int x1 = y > secondPoint.y_ ? x1_2 : x2_3;
			int x2 = x1_3;

			if (x1 > x2)
			{
				std::swap(x1, x2);
			}

			Pixel color;
			/*color.r = col.r + dr * (y - y1) / dy;
			color.g = col.g + dg * (y - y1) / dy;
			color.b = col.b + db * (y - y1) / dy;
			color.a = 255;*/
			for (int x = x1; x <= x2; x++) 
			{
				drawPoint(a.color, x, y);
			}
		
	}
	


}
