#pragma once
class Polygon
{
protected:
	int w;
	int h;
public:
	Polygon(int a, int b);
	virtual ~Polygon() {}
	virtual int area() = 0;
};

