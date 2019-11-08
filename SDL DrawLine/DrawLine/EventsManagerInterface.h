#pragma once
#include "Image.h"
#include "SDL.h"
#include "Camera.h"
class EventsManagerInterface
{
public:
	virtual bool manageEvents(Image& image , SDL_Event event, Camera& camera) = 0;
};

