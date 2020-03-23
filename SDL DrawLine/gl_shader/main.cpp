#include "SDL.h"
#include <stdio.h>
#include <GL/glew.h>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <fstream>
#include <string>
#include "WindowShaderGl.h"
#include <functional>
#include "../DrawLine/Algebra.h";
#include "../DrawLine/Mesh.h"
#include "../DrawLine/Camera.h"
#include "EventsManagerShaderGl.h"
#include <imgui.h>

void shaderGl()
{
	int width = 720;
	int height = 720;

	WindowShaderGl window(width, height);

	window.run();
}

int main(int argc, char* argv[])
{
	shaderGl();

	return 0;
}

