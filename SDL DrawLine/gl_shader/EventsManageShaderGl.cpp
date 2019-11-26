#include "EventsManagerShaderGl.h"
#include <stdio.h>

bool EventsManagerShaderGl::manageEvents(Image& image, SDL_Event event, Camera& camera)
{
	switch (event.type)
	{
	case SDL_KEYDOWN:
		printf("key pressed: %s\n", SDL_GetKeyName(event.key.keysym.sym));
		switch (event.key.keysym.sym) {
		case SDLK_ESCAPE:
			return false;
		}

		break;
	case SDL_QUIT:
		printf("quit\n");
		return false;
		break;
	}

	return true;
}
