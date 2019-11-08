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

	int GetWidth() { return screenWidth; }
	int GetHeight() { return screenHeight; }
protected:
	int screenWidth;
	int screenHeight;
	GLuint textureId = 0;
	SDL_Window* window;
	Image& image;
	Camera& camera;
	std::shared_ptr<EventsManagerInterface> eventsManager;
	std::vector<Mesh> meshes;
};


