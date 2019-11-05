#include "EventsManagerExample.h"
#include <stdio.h>

bool EventsManagerExample::manage_events(Image& image, SDL_Event event, Camera& camera)
{
	algebra::Vec3<float> v_look_dir;
	algebra::Vec3<float> forward;
	switch (event.type)
	{
	case SDL_KEYDOWN:
		printf("key pressed: %s\n", SDL_GetKeyName(event.key.keysym.sym));
		switch(event.key.keysym.sym) {
		case SDLK_ESCAPE:
			return false;
		case SDLK_w:
			forward = (camera.position - camera.target).normalize() * 0.1f;
			camera.position = camera.position - forward;
			camera.target = camera.target - forward;
			break;
		case SDLK_s:
			forward = (camera.position - camera.target).normalize() * 0.1f;
			camera.position = camera.position + forward;
			camera.target = camera.target + forward;
			break;
		case SDLK_a:
			v_look_dir = (camera.target - camera.position) * algebra::Matrix3<float>::rotateMatrixY(1);
			camera.target = camera.position + v_look_dir;
			break;
		case SDLK_d:
			v_look_dir = (camera.target - camera.position) * algebra::Matrix3<float>::rotateMatrixY(-1);
			camera.target = camera.position + v_look_dir;
			break;
		case SDLK_o:
			camera.position.z_ += 0.1f;
			//camera.target.z_ += 0.1f;
			break;
		case SDLK_p:
			camera.position.z_ -= 0.1f;
			//camera.target.z_ -= 0.1f;
			break;
		case SDLK_m:
			if (SDL_GetRelativeMouseMode() == SDL_TRUE) 
			{
				SDL_SetRelativeMouseMode(SDL_FALSE);
			}
			else
			{
				SDL_SetRelativeMouseMode(SDL_TRUE);
			}
			break;
		}

		draw = !draw;
		break;
	case SDL_MOUSEMOTION:
		if (draw && x1 != -1)
		{
			x2 = event.motion.x;
			y2 = event.motion.y;
			//image.drawLine(lineColor1, lineColor2, x1, y1, x2, y2);
		}
		if (SDL_GetRelativeMouseMode() == SDL_TRUE)
		{
			printf("look at: {%f, %f, %f}\n", camera.target.x_ - camera.position.x_,
				camera.target.y_ - camera.position.y_, camera.target.z_ - camera.position.z_);

			v_look_dir = (camera.target - camera.position)
				* algebra::Matrix3<float>::rotateMatrixY(-event.motion.xrel*0.1f)
				* algebra::Matrix3<float>::rotateMatrixX(-event.motion.yrel*0.1f);
			camera.target = camera.position + v_look_dir;
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
			//image.drawLine(lineColor1, lineColor2, x1, y1, x2, y2);
		}
		break;
	}

	return true;
}
