#include "SDL.h"
#include <stdio.h>
#include <GL/glew.h>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <fstream>
#include <string>
#include "Window.h"
#include <functional>
#include "EventsManagerExample.h"
#include "Algebra.h";

//#if defined(_WIN32) || defined(_WIN64)
#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "opengl32.lib")

void drawLine() 
{
	int width = 1280;
	int height = 720;

	Image image(width, height);
	Window window(image, std::make_shared<EventsManagerExample>());

	window.run();
}

void math() 
{
	algebra::Vec3<float> v(0, M_PI/2, 0);
	algebra::Vec3<float> v2(1, 0, 0);
	algebra::Quaternion<float> q(v);

	std::cout << q.rotate(v2);
}

int main(int argc, char* argv[])
{
	math();

	return 0;
}

