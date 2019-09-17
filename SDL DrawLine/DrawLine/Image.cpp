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
	current_image.at(x + y * image_width) = color;
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
