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
#include "Mesh.h"
#include "Camera.h"

//#if defined(_WIN32) || defined(_WIN64)
#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "opengl32.lib")

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
	Window window(image, cam, std::make_shared<EventsManagerExample>());

	Mesh cube;

	cube.ExtractObj("torus.obj");

	window.addMesh(cube);

	window.run();
}

int main(int argc, char* argv[])
{
	drawLine();

	return 0;
}

