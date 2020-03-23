#include "Image.h"

std::vector<algebra::Vec4<float>> Image::loadTexture(const char* path, std::pair<size_t, size_t>& size_)
{
	std::vector<algebra::Vec4<float>> textureColors;
	int i;
	FILE* f = fopen(path, "rb");
	unsigned char info[54];
	fread(info, sizeof(unsigned char), 54, f); // read the 54-byte header

	// extract image height and width from header
	size_.first = *(int*)&info[18];
	size_.second = *(int*)&info[22];

	int size = 3 * size_.first * size_.second;
	unsigned char* data = new unsigned char[size]; // allocate 3 bytes per pixel
	fread(data, sizeof(unsigned char), size, f); // read the rest of the data at once
	fclose(f);

	for (i = 0; i < size; i += 3)
	{
		algebra::Vec4<float> color(0, 0, 0, 1);
		color.x = data[i + 2] / 255.0f;
		color.y = data[i + 1] / 255.0f;
		color.z = data[i] / 255.0f;
		textureColors.push_back(color);
	}

	return textureColors;
}
