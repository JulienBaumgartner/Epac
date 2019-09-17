#pragma once
#include <vector>

struct Pixel {
	uint8_t r, g, b, a;
};

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
};

