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
#include "Texture.h"
#include "../DrawLine/Mesh.h"
#include "../DrawLine/Camera.h"
#include "Program.h"

class WindowShaderGl
{
public:
	WindowShaderGl(int width, int height);
	~WindowShaderGl();

	void init();
	void run();
	void imguiWindow();
	void setIndices(char* str_indices);
	void addPoint();
	void removePoint(int index);
	static void GLAPIENTRY debugMessage(GLenum source,
		GLenum type,
		GLuint id,
		GLenum severity,
		GLsizei length,
		const GLchar *message,
		const void *userParam) {
		if (severity != GL_DEBUG_SEVERITY_NOTIFICATION)
		{
			std::cout << message << "\n";
		}
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
	
	EventsManagerShaderGl eventsManager;

	// Color texture.
	std::shared_ptr<Texture> texture1_ = nullptr;

	Mesh mesh_;
	std::shared_ptr<Program> program_ = nullptr;
	Camera camera_;
};


