#include "Window.h"
#include <stdio.h>
#include <algorithm>
#include <stdlib.h>
#include "Image.h"


Window::Window(Image& image, Camera& camera, std::shared_ptr<EventsManagerInterface> events_manager) : image_(image), camera_(camera)
{
	screen_width_ = image.image_width;
	screen_height_ = image.image_height;
	events_manager_ = events_manager;
	SDL_Init(SDL_INIT_VIDEO);
	window_ = SDL_CreateWindow("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screen_width_, screen_height_, SDL_WINDOW_OPENGL);
	init();
}


Window::~Window()
{
	SDL_DestroyWindow(window_);
	SDL_Quit();
}

void Window::render()
{
	glTexImage2D(GL_TEXTURE_2D,
		0, GL_RGBA, screen_width_, screen_height_,
		0, GL_RGBA, GL_UNSIGNED_BYTE, &image_.current_image[0]);

	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture_id_);
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

	SDL_GL_SwapWindow(window_);
}

void Window::run()
{
	SDL_Event event;
	bool loop = true;
	while (loop)
	{
		std::fill(image_.current_image.begin(), image_.current_image.end(), Pixel{ 40,0,40,255 });

		algebra::Matrix4<float> m_view = camera_.View().inv();
		//algebra::Matrix4<float> m_view = algebra::Matrix4<float>
		//	(1,0,0,0,
		//	0,1,0,0,
		//	0,0,1,0,
		//	0,0,0,1);

		while (SDL_PollEvent(&event))
		{
			loop = events_manager_->manage_events(image_, event, camera_);
		}

		for (Mesh m : meshes_) 
		{
			image_.drawMesh(m, m_view, camera_);
		}
		render();
	}

}

void Window::init()
{

	auto sdl_gl_context = SDL_GL_CreateContext(window_);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);


	glGenTextures(1, &texture_id_);

	glBindTexture(GL_TEXTURE_2D, texture_id_);
	glTexParameteri(GL_TEXTURE_2D,
		GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,
		GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}


void Window::addMesh(const Mesh& mesh) 
{
	meshes_.push_back(mesh);
}
