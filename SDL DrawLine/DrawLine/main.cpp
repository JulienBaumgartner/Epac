#include "SDL.h"
#include <stdio.h>
#include <GL/glew.h>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <fstream>
#include <string>
#include "Window.h"

//#if defined(_WIN32) || defined(_WIN64)
#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "opengl32.lib")


int main(int argc, char* argv[])
{
	int x1 = -1;
	int x2 = -1;
	int y1 = -1;
	int y2 = -1;
	Pixel lineColor1 = { 0, 100, 100, 255 };
	Pixel lineColor2 = { 100, 0, 0, 255 };
	bool draw = false;
	int width = 1280;
	int height = 720;

	Window window(width, height);
	Image image(width, height);

	SDL_Event event;
	bool loop = true;
	while (loop) 
	{
		while (SDL_PollEvent(&event))
		{
			switch (event.type) 
			{
			case SDL_KEYDOWN:
				printf("key pressed: %s\n", SDL_GetKeyName(event.key.keysym.sym));
				if (event.key.keysym.sym == SDLK_ESCAPE) 
				{
					loop = false;
				}
				draw = !draw;
				break;
			case SDL_MOUSEMOTION:
				if(draw)
				{
					x2 = event.motion.x;
					y2 = event.motion.y;
					image.drawLine(lineColor1, lineColor2, x1, y1, x2, y2);
				}
				break;
			case SDL_QUIT:
				printf("quit\n");
				loop = false;
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
					image.drawLine( lineColor1, lineColor2, x1, y1, x2, y2);
				}

				break;
			}
		}

		window.render(image);
	}

	return 0;
}

