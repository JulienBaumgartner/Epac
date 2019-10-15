#pragma once
#include "Algebra.h"

class Camera
{
public:
	Camera();
	~Camera();

	algebra::Matrix4<float> View() const;
	algebra::Matrix4<float> ViewInv() const;

	algebra::Vec3<float> position;
	algebra::Vec3<float> target;
	algebra::Vec3<float> up;
};

