#include <iostream>
#include <windows.h>
#include <stdio.h>
#include "vec3.h"
#include <vector>
#include "clip.h"



typedef struct _Bline
{
	int startX;
	int startY;
	int endX;
	int endY;
} BresenhamLine;


BresenhamLine myLine;


int getOctant(BresenhamLine line)
{
	int dy = (line.endY - line.startY);
	int dx = (line.endX - line.startX);
	//Slope		
	float m = abs(dy) / (float)abs(dx);

	if (m < 1 && dx>0 && dy <= 0) return 1;
	if (m >= 1 && dx >= 0 && dy < 0) return 2;

	if (m > 1 && dx<0 && dy <= 0) return 3;
	if (m <= 1 && dx<0 && dy <= 0) return 4;

	if (m < 1 && dx <= 0 && dy > 0) return 5;
	if (m >= 1 && dx<=0 && dy >= 0) return 6;

	if (m > 1 && dx >= 0 && dy > 0) return 7;
	if (m <= 1 && dx>0 && dy >= 0) return 8;
		return 8;

	return 0;
}

//Draws a new raster line using Bresenham's algorithm
void BresenhamDraw(BresenhamLine line)
{
	int t_startX, t_endX, t_startY, t_endY, t_currX, t_currY;
	int d, dx, dy, inc1, inc2;
	dx = abs(line.endX - line.startX);
	dy = abs(line.endY - line.startY);

	


	switch (getOctant(line)) {
	case 1:
		t_startX = line.startX;
		t_endX = line.endX;
		t_startY = line.startY;
		t_endY = line.endY;
		t_currX = line.startX;
		t_currY = line.startY;
		d = dy - 2 * dx;
		inc1 = 2 * dy;
		inc2 = 2 * dy - 2 * dx;
		while (t_currX <= t_endX)
		{
			SDL_RenderDrawPoint(renderer, t_currX, t_currY);
			t_currX++;
			if (d < 0) d += inc1;
			else {
				d += inc2;
				t_currY--;
			}
		}
		break;
	case 2:
		t_startX = line.startX;
		t_endX = line.endX;
		t_startY = line.startY;
		t_endY = line.endY;
		t_currX = line.startX;
		t_currY = line.startY;
		d = dx - 2 * dy;
		inc1 = 2 * dx;
		inc2 = 2 * dx - 2 * dy;
		while (t_currY >= t_endY)
		{
			SDL_RenderDrawPoint(renderer, t_currX, t_currY);
			t_currY--;
			if (d < 0) d += inc1;
			else {
				d += inc2;
				t_currX++;
			}
		}
		break;
	case 3:
		t_startX = line.startX;
		t_endX = line.endX;
		t_startY = line.startY;
		t_endY = line.endY;
		t_currX = line.startX;
		t_currY = line.startY;
		d = dx - 2 * dy;
		inc1 = 2 * dx;
		inc2 = 2 * dx - 2 * dy;
		while (t_currY >= t_endY)
		{
			SDL_RenderDrawPoint(renderer, t_currX, t_currY);
			t_currY--;
			if (d < 0) d += inc1;
			else {
				d += inc2;
				t_currX--;
			}
		}
		break;
	case 4:
		t_startX = line.startX;
		t_endX = line.endX;
		t_startY = line.startY;
		t_endY = line.endY;
		t_currX = line.startX;
		t_currY = line.startY;
		d = dy - 2 * dx;
		inc1 = 2 * dy;
		inc2 = 2 * dy - 2 * dx;
		while (t_currX >= t_endX)
		{
			SDL_RenderDrawPoint(renderer, t_currX, t_currY);
			t_currX--;
			if (d < 0) d += inc1;
			else {
				d += inc2;
				t_currY--;
			}
		}
		break;
	case 5:
		t_startX = line.endX;
		t_endX = line.startX;
		t_startY = line.endY;
		t_endY = line.startY;
		t_currX = line.endX;
		t_currY = line.endY;
		d = dy - 2 * dx;
		inc1 = 2 * dy;
		inc2 = 2 * dy - 2 * dx;
		while (t_currX <= t_endX)
		{
			SDL_RenderDrawPoint(renderer, t_currX, t_currY);
			t_currX++;
			if (d < 0) d += inc1;
			else {
				d += inc2;
				t_currY--;
			}
		}
		break;
	case 6:
		t_endX = line.startX;
		t_startX = line.endX;
		t_endY = line.startY;
		t_startY = line.endY;
		t_currX = line.endX;
		t_currY = line.endY;
		d = dx - 2 * dy;
		inc1 = 2 * dx;
		inc2 = 2 * dx - 2 * dy;
		while (t_currY >= t_endY)
		{
			SDL_RenderDrawPoint(renderer, t_currX, t_currY);
			t_currY--;
			if (d < 0) d += inc1;
			else {
				d += inc2;
				t_currX++;
			}
		}
		break;
	case 7:
		t_endX = line.startX;
		t_startX = line.endX;
		t_endY = line.startY;
		t_startY = line.endY;
		t_currX = line.endX;
		t_currY = line.endY;
		d = dx - 2 * dy;
		inc1 = 2 * dx;
		inc2 = 2 * dx - 2 * dy;
		while (t_currY >= t_endY)
		{
			SDL_RenderDrawPoint(renderer, t_currX, t_currY);
			t_currY--;
			if (d < 0) d += inc1;
			else {
				d += inc2;
				t_currX--;
			}
		}
		break;
	case 8:
		t_startX = line.endX;
		t_endX = line.startX;
		t_startY = line.endY;
		t_endY = line.startY;
		t_currX = line.endX;
		t_currY = line.endY;
		d = dy - 2 * dx;
		inc1 = 2 * dy;
		inc2 = 2 * dy - 2 * dx;
		while (t_currX >= t_endX)
		{
			SDL_RenderDrawPoint(renderer, t_currX, t_currY);
			t_currX--;
			if (d < 0) d += inc1;
			else {
				d += inc2;
				t_currY--;
			}
		}
		break;

	}
}


int main(int argc, char * argv[]) {

	//some demo here....

	return 0;
}