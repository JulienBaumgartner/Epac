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
	algebra::Vec4<float> lineColor1;
	algebra::Vec4<float> lineColor2;
	bool draw = false;
	int pos_x = 0;
	int pos_y = 0;
};

