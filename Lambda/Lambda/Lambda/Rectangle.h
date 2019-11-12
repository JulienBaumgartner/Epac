#pragma once
#include "Polygon.h"

class Rectangle : public Polygon
{
public:
	Rectangle(int a, int b);
	~Rectangle();

	int area() override;
};


