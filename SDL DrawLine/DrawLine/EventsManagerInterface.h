#pragma once
#include "Image.h"
#include "SDL.h"
#include "Camera.h"
class EventsManagerInterface
{
public:
	virtual bool manage_events(Image& image , SDL_Event event, Camera& camera) = 0;
};

