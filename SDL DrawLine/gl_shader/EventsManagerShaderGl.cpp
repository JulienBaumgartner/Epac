#include "EventsManagerShaderGl.h"
#include <stdio.h>

bool EventsManagerShaderGl::manageEvents(SDL_Event event)
{
	switch (event.type)
	{
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym) {
		case SDLK_ESCAPE:
			return false;
		case SDLK_DOLLAR:
			showConsole = !showConsole;

			break;
		}
		break;
	case SDL_QUIT:
		printf("quit\n");
		return false;
		break;
	}

	return true;
}
