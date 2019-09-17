#pragma once
#include "SDL.h"
#include <GL/glew.h>
#include "Image.h"

class Window
{
public:
	Window(int width, int height);
	~Window();

	int screen_width;
	int screen_height;

	GLuint texture_id = 0;
	SDL_Window* window;

	void render(Image image);
	void init();

};


