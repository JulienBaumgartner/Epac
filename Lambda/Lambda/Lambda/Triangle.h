#pragma once
#include "Polygon.h"

class Triangle : public Polygon
{
public:
	Triangle(int a, int b);
	~Triangle();
	int area() override;
};

