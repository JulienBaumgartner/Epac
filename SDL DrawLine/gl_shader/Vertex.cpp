#include "Vertex.h"

bool Vertex::operator==(const Vertex& v) const
{
	return v.positions_ == this->positions_ &&
		   v.normal_ == this->normal_ &&
		   v.textures_ == this->textures_;
}

bool Vertex::operator<(const Vertex& v) const
{
	return this->positions_ < v.positions_ &&
		   this->normal_ < v.normal_ &&
		   this->textures_ < v.textures_;
}
