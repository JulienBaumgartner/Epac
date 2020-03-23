#include "Texture.h"


Texture::Texture(const std::string& file)
{
	Image im;

	textureColors_ = im.loadTexture(file.c_str(), size_);


	glGenTextures(1, &textureId_);
	glBindTexture(GL_TEXTURE_2D, textureId_);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(
		GL_TEXTURE_2D, // Texture type.
		0, // Mipmap level (default: 0).
		GL_RGBA8, // Internal storage format.
		static_cast<GLsizei>(size_.first), // Width.
		static_cast<GLsizei>(size_.second), // Height.
		0, // This value must be 0.
		GL_RGBA, // Specify the pixel format.
		GL_FLOAT, // Specify the type.
		textureColors_.data()); // Pointer to the array.

	glGenerateMipmap(GL_TEXTURE_2D);
}

Texture::~Texture()
{
	glDeleteTextures(1, &textureId_);
}

void Texture::Bind(const unsigned int slot) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, textureId_);

}

void Texture::UnBind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
