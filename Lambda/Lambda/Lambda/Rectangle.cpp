#include "Rectangle.h"
#include <iostream>



Rectangle::Rectangle(int a, int b) : Polygon(a,b)
{
}

Rectangle::~Rectangle()
{
	std::cout << "Rectangle destructeur\n";
}

int Rectangle::area() 
{
	return h * w;
}
