#pragma once
#include "../DrawLine/Algebra.h"


class Vertex
{
public:
	Vertex(algebra::Vec4<float> positions, algebra::Vec3<float> normal, algebra::Vec2<float> textures) :
		positions_(positions), normal_(normal), textures_(textures) {}

	const algebra::Vec4<float>& GetPositions() const{ return positions_; }
	const algebra::Vec3<float>& GetNormal() const{ return normal_; }
	const algebra::Vec2<float>& GetTextures() const { return textures_; }

	bool operator==(const Vertex& v) const;
	bool operator<(const Vertex& v) const;

private:
	algebra::Vec4<float> positions_;
	algebra::Vec3<float> normal_;
	algebra::Vec2<float> textures_;
};
