#pragma once
#include "Algebra.h"
#include "Pixel.h"

struct Vertex {
	algebra::Vec3<float> screen_position;
	algebra::Vec4<float> color;
};