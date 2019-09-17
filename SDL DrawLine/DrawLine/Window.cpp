#include "Window.h"
#include <stdio.h>
#include <algorithm>
#include <stdlib.h>


Window::Window(int width, int height)
{
	screen_width = width;
	screen_height = height;

	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screen_width, screen_height, SDL_WINDOW_OPENGL);
	init();
}


Window::~Window()
{
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Window::render(Image image)
{
	glTexImage2D(GL_TEXTURE_2D,
		0, GL_RGBA, screen_width, screen_height,
		0, GL_RGBA, GL_UNSIGNED_BYTE, &image.current_image[0]);

	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture_id);
	{
		glPushMatrix();
		glBegin(GL_QUADS);
		{
			glTexCoord2f(0, 0);
			glVertex2f(-1, 1);
			glTexCoord2f(1, 0);
			glVertex2f(1, 1);
			glTexCoord2f(1, 1);
			glVertex2f(1, -1);
			glTexCoord2f(0, 1);
			glVertex2f(-1, -1);
		}
		glEnd();
		glPopMatrix();
	}
	glDisable(GL_TEXTURE_2D);
	glFlush();

	SDL_GL_SwapWindow(window);
}

void Window::init()
{

	auto sdl_gl_context = SDL_GL_CreateContext(window);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);


	glGenTextures(1, &texture_id);

	glBindTexture(GL_TEXTURE_2D, texture_id);
	glTexParameteri(GL_TEXTURE_2D,
		GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,
		GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}
