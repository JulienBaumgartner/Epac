#include "Window.h"
#include <stdio.h>
#include <algorithm>
#include <stdlib.h>
#include "Image.h"
#include <iostream>
#include <chrono>
#include <ctime>  


Window::Window(Image& image, Camera& camera, std::shared_ptr<EventsManagerInterface> events_manager) : image(image), camera(camera)
{
	screenWidth = image.imageWidth;
	screenHeight = image.imageHeight;
	eventsManager = events_manager;
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_OPENGL);
	init();
}


Window::~Window()
{
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Window::render()
{
	glTexImage2D(GL_TEXTURE_2D,
		0, GL_RGBA, screenWidth, screenHeight,
		0, GL_RGBA, GL_FLOAT, &image.currentImage[0]);

	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureId);
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

static float t = 0;
static std::chrono::system_clock::time_point startTime = std::chrono::system_clock::now();
void Window::run()
{
	SDL_Event event;
	bool loop = true;
	while (loop)
	{
		auto currentTime = std::chrono::system_clock::now();
		std::chrono::duration<float> elapsed_seconds = currentTime - startTime;
		t = elapsed_seconds.count()*20;
		std::fill(image.currentImage.begin(), image.currentImage.end(), algebra::Vec4<float>(0.2f,0,0.2f,1));
		std::fill(image.zBuffer.begin(), image.zBuffer.end(), -10000);

		algebra::Matrix4<float> m_view = camera.View().inv();

		while (SDL_PollEvent(&event))
		{
			loop = eventsManager->manageEvents(image, event, camera);
		}

		for (Mesh m : meshes) 
		{
			image.drawMesh(m, m_view, camera, t);
		}
		render();
	}

}

void Window::init()
{

	auto sdl_gl_context = SDL_GL_CreateContext(window);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);


	glGenTextures(1, &textureId);

	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexParameteri(GL_TEXTURE_2D,
		GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,
		GL_TEXTURE_MAG_FILTER, GL_LINEAR);

}


void Window::addMesh(const Mesh& mesh) 
{
	meshes.push_back(mesh);
}
