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

//#if defined(_WIN32) || defined(_WIN64)
#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "opengl32.lib")


int main(int argc, char* argv[])
{
	int width = 1280;
	int height = 720;

	Image image(width, height);
	Window window(image, std::make_shared<EventsManagerExample>());

	window.run();

	return 0;
}

