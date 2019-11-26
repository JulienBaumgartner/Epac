#pragma once
#include "SDL.h"
#include <GL/glew.h>
#include "EventsManagerShaderGl.h"
#include <memory>
#include <vector>
#include <iostream>
#include <chrono>
#include <ctime>
#include <string>

class WindowShaderGl
{
public:
	WindowShaderGl(int width, int height, std::shared_ptr<EventsManagerShaderGl> events_manager);
	~WindowShaderGl();

	void render();
	void init();
	void run();
	static void GLAPIENTRY debugMessage(GLenum source,
		GLenum type,
		GLuint id,
		GLenum severity,
		GLsizei length,
		const GLchar *message,
		const void *userParam) {
		std::cout << message << "\n";
	}

	int GetWidth() { return screenWidth; }
	int GetHeight() { return screenHeight; }
protected:
	int screenWidth;
	int screenHeight;
	GLuint ibo = 0;
	
	std::vector<std::chrono::system_clock::time_point> framesTime;
	std::chrono::system_clock::time_point lastUpdateTitle;
	
	SDL_Window* window;
	
	std::shared_ptr<EventsManagerShaderGl> eventsManager;
};


