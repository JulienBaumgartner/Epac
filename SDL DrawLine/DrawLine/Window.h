#pragma once
#include "SDL.h"
#include <GL/glew.h>
#include "Image.h"
#include "EventsManagerInterface.h"
#include <memory>
#include "Mesh.h"
#include <vector>
#include "Camera.h"

class Window
{
public:
	Window(Image& image, Camera& camera, std::shared_ptr<EventsManagerInterface> events_manager);
	~Window();

	void render();
	void init();
	void run();
	void addMesh(const Mesh& mesh);

	int GetWidth() { return screen_width_; }
	int GetHeight() { return screen_height_; }
protected:
	int screen_width_;
	int screen_height_;
	GLuint texture_id_ = 0;
	SDL_Window* window_;
	Image& image_;
	Camera& camera_;
	std::shared_ptr<EventsManagerInterface> events_manager_;
	std::vector<Mesh> meshes_;
};


