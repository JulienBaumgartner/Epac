#pragma once
#include "SDL.h"

class EventsManagerShaderGl
{
public:
	bool manageEvents(SDL_Event event);
	bool showConsole = false;
	int type = 0;
};

