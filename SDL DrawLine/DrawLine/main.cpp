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

	algebra::Vec3<float> v_look_at = { 0,0,1 };
	algebra::Vec3<float> v_up = { 0,1,0 };
	algebra::Vec3<float> v_position = { 0,0,-5 };
	algebra::Vec3<float> v_target = v_position + v_look_at;
	Camera cam;
	cam.position = v_position;
	cam.target = v_target;
	cam.up = v_up;

	auto a = cam.View() * cam.ViewInv();

	Image image(width, height);
	Window window(image, cam, std::make_shared<EventsManagerExample>());

	Mesh cube;

	cube.ExtractObj("torus.obj");



	window.addMesh(cube);

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
	drawLine();

	return 0;
}

