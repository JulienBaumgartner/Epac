#pragma once
#include "Image.h"
#include "SDL.h"
class EventsManagerInterface
{
public:
	virtual bool manage_events(Image& image , SDL_Event event) = 0;
};

