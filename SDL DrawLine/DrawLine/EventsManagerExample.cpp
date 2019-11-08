#include "EventsManagerExample.h"
#include <stdio.h>

bool EventsManagerExample::manageEvents(Image& image, SDL_Event event, Camera& camera)
{
	algebra::Vec3<float> vLookDir;
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
			vLookDir = (camera.target - camera.position) * algebra::Matrix3<float>::rotateMatrixY(1);
			camera.target = camera.position + vLookDir;
			break;
		case SDLK_d:
			vLookDir = (camera.target - camera.position) * algebra::Matrix3<float>::rotateMatrixY(-1);
			camera.target = camera.position + vLookDir;
			break;
		case SDLK_o:
			camera.position.z += 0.1f;
			break;
		case SDLK_p:
			camera.position.z -= 0.1f;
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

		break;
	case SDL_MOUSEMOTION:
		if (SDL_GetRelativeMouseMode() == SDL_TRUE)
		{
			printf("look at: {%f, %f, %f}\n", camera.target.x - camera.position.x,
				camera.target.y - camera.position.y, camera.target.z - camera.position.z);

			vLookDir = (camera.target - camera.position)
				* algebra::Matrix3<float>::rotateMatrixY(-event.motion.xrel*0.1f)
				* algebra::Matrix3<float>::rotateMatrixX(-event.motion.yrel*0.1f);
			camera.target = camera.position + vLookDir;
		}
		break;
	case SDL_QUIT:
		printf("quit\n");
		return false;
		break;
	}

	return true;
}
