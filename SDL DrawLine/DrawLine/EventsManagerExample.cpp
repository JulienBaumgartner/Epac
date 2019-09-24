#include "EventsManagerExample.h"
#include <stdio.h>

bool EventsManagerExample::manage_events(Image& image, SDL_Event event)
{
	switch (event.type)
	{
	case SDL_KEYDOWN:
		printf("key pressed: %s\n", SDL_GetKeyName(event.key.keysym.sym));
		if (event.key.keysym.sym == SDLK_ESCAPE)
		{
			return false;
		}
		draw = !draw;
		break;
	case SDL_MOUSEMOTION:
		if (draw)
		{
			x2 = event.motion.x;
			y2 = event.motion.y;
			image.drawLine(lineColor1, lineColor2, x1, y1, x2, y2);
		}
		break;
	case SDL_QUIT:
		printf("quit\n");
		return false;
		break;
	case SDL_MOUSEBUTTONDOWN:
		if (event.button.button == SDL_BUTTON_LEFT) {
			printf("left click\n");
			x1 = event.motion.x;
			y1 = event.motion.y;
			printf("%i %i\n", x1, y1);
		}
		if (event.button.button == SDL_BUTTON_RIGHT) {
			printf("right click\n");
			x2 = event.motion.x;
			y2 = event.motion.y;
			printf("%i %i\n", x2, y2);
		}

		if (x1 != -1 && x2 != -1) {
			image.drawLine(lineColor1, lineColor2, x1, y1, x2, y2);
		}
		break;
	}

	return true;
}
