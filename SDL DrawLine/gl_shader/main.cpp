#include "SDL.h"
#include <stdio.h>
#include <GL/glew.h>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <fstream>
#include <string>
#include "../DrawLine/Window.h"
#include <functional>
#include "../DrawLine/Algebra.h";
#include "../DrawLine/Mesh.h"
#include "../DrawLine/Camera.h"
#include "EventsManagerShaderGl.h"

void drawLine()
{
	int width = 1080;
	int height = 720;

	algebra::Vec3<float> vLookAt = { 0,0,1 };
	algebra::Vec3<float> vUp = { 0,1,0 };
	algebra::Vec3<float> vPosition = { 0,0,-5 };
	algebra::Vec3<float> vTarget = vPosition + vLookAt;
	Camera cam;
	cam.position = vPosition;
	cam.target = vTarget;
	cam.up = vUp;

	Image image(width, height, cam);
	Window window(image, cam, std::make_shared<EventsManagerShaderGl>());

	window.run();
}

int main(int argc, char* argv[])
{
	drawLine();

	return 0;
}

