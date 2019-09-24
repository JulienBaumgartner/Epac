#pragma once
#include "SDL.h"
#include <GL/glew.h>
#include "Image.h"
#include "EventsManagerInterface.h"
#include <memory>

class Window
{
public:
	Window(Image& image, std::shared_ptr<EventsManagerInterface> events_manager);
	~Window();

	void render();
	void init();
	void run();
protected:
	int screen_width_;
	int screen_height_;
	GLuint texture_id_ = 0;
	SDL_Window* window_;
	Image& image_;
	std::shared_ptr<EventsManagerInterface> events_manager_;
};


