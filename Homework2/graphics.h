#pragma once
#include <math.h>
#include <algorithm>
#include "list.h"

class graphics
{
private:
	float color[4];
	float *buffer;

public:
	int width;
	int height;

	graphics(int width = 200, int height = 200);
	~graphics();
	void setPixel(int, int);
	void setColor(float, float, float);
	void bLine(int,int,int,int);
	float * getCurrentBuffer();
	void fillTriangle(float, float, float, float, float, float);
	void fillTriangle2(float, float, float, float, float, float);
	void fillTopTriangle(float, float, float, float, float);	// ^
	void fillBottomTriangle(float, float, float, float, float);	// V

	void fillPolygon(float* points, int num);
	void strokePolygon(float* points, int num);

};