#include "Triangle.h"
#include <iostream>

Triangle::Triangle(int a, int b) : Polygon(a, b)
{
}

Triangle::~Triangle()
{
	std::cout << "Triangle destructeur\n";
}

int Triangle::area()
{
	return h * w / 2;
}
