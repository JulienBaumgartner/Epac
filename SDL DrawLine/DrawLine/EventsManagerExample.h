#pragma once
#include "EventsManagerInterface.h"
#include "Camera.h"

class EventsManagerExample : public EventsManagerInterface
{
public:
	bool manage_events(Image& image, SDL_Event event, Camera& camera) override;
private:
	int x1 = -1;
	int x2 = -1;
	int y1 = -1;
	int y2 = -1;
	Pixel lineColor1 = { 0, 100, 100, 255 };
	Pixel lineColor2 = { 100, 0, 0, 255 };
	bool draw = false;
};

