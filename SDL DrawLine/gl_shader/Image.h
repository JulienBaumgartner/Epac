#pragma once
#include <vector>
#include <utility>
#include "../DrawLine/Algebra.h"

class Image
{
public:
	std::vector<algebra::Vec4<float>> loadTexture(const char* path, std::pair<size_t, size_t>& size);
};