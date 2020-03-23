#pragma once
#include <utility>
#include <string>
#include <GL/glew.h>
#include "Image.h"

class Texture
{
public:
	Texture(const std::string& file);
	~Texture();

	 void Bind(const unsigned int slot = 0) const;
	 void UnBind() const;
	 unsigned int GetId() const { return textureId_;  }
private:
	unsigned int textureId_;
	std::pair<size_t, size_t> size_ = { 0,0 };
	std::vector<algebra::Vec4<float>> textureColors_;
};