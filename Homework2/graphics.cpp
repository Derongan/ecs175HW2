#include "graphics.h"

void graphics::bubbleSortPoints(float * points, int num)
{
	int newn;
	do {
		int newn = 0;

		for (int i = 1; i < num; i++) {
			if (points[(i - 1) * 2] > points[i * 2]) {
				float temp = points[i * 2];
				points[i * 2] = points[(i - 1) * 2];
				points[(i - 1) * 2] = temp;

				temp = points[i * 2 + 1];
				points[i * 2 + 1] = points[(i - 1) * 2 + 1];
				points[(i - 1) * 2 + 1] = temp;
				newn = i;
			}
		}
		num = newn;
	} while (num != 0);
}

graphics::graphics(int width, int height)
{
	this->width = width;
	this->height = height;
	setColor(1, 1, 1);
	buffer = new float[this->width * this->height * 3];
}

graphics::~graphics()
{
	delete[] this->buffer;
}

void graphics::setPixel(int x, int y)
{
	buffer[x * 3 + y * this->width * 3] = color[0];
	buffer[x * 3 + y * this->width * 3 + 1] = color[1];
	buffer[x * 3 + y * this->width * 3 + 2] = color[2];
}

void graphics::setColor(float r, float g, float b)
{
	this->color[0] = r;
	this->color[1] = g;
	this->color[2] = b;
}

void graphics::bLine(int x0, int y0, int xEnd, int yEnd) {
	int dx = xEnd - x0, dy = yEnd - y0;
	int fdx = fabs(dx), fdy = fabs(dy);
	int px = 2 * fdy - fdx, py = 2 * fdx - fdy;
	int x, y, i;

	//We have eight octants.
	//This can be reduced to four cases. 0 < m < 1.0, m > 1.0, m < -1.0, 0 > m > -1.0

	if (fdy <= fdx) {
		if (xEnd < x0) {
			x = xEnd;
			y = yEnd;
			xEnd = x0;
		}
		else {
			x = x0;
			y = y0;
		}

		this->setPixel(x, y);

		while (x < xEnd) {
			x++;
			if (px < 0) {
				px += 2 * fdy;
			}
			else {
				if ((dx>0 && dy>0) || (dx < 0 && dy < 0)) {
					y++;
				}
				else {
					y--;
				}
				px += 2 * (fdy - fdx);
			}
			this->setPixel(x, y);
		}
	}
	else {
		if (yEnd < y0) {
			x = xEnd;
			y = yEnd;
			yEnd = y0;
		}
		else {
			x = x0;
			y = y0;
		}

		this->setPixel(x, y);

		while (y < yEnd) {
			y++;
			if (py < 0) {
				py += 2 * fdx;
			}
			else {
				if ((dx>0 && dy>0) || (dx < 0 && dy < 0)) {
					x++;
				}
				else {
					x--;
				}
				py += 2 * (fdx - fdy);
			}
			this->setPixel(x, y);
		}
	}
}

float * graphics::getCurrentBuffer()
{
	return this->buffer;
}

void graphics::fillTriangle(float x0, float y0, float x1, float y1 , float x2, float y2)
{

	setColor(1, 0, 0);

	bLine(x0, y0, x1, y1);
	bLine(x0, y0, x2, y2);
	bLine(x1, y1, x2, y2);

	setColor(0, 1, 1);

	int xMax = fmax(x2, fmax(x0, x1));
	int xMin = fmin(x2, fmin(x0, x1));
	int yMax = fmax(y2, fmax(y0, y1));
	int yMin = fmin(y2, fmin(y0, y1));

	float m0 = (y0 - y1) / (x0 - x1);
	float m1 = (y0 - y2) / (x0 - x2);
	float m2 = (y1 - y2) / (x1 - x2);

	float b0 = y0 - m0*x0;
	float b1 = y0 - m1*x0;
	float b2 = y1 - m2*x1;

	for (int i = yMin; i <= yMax; i++) {
		float p1;
		float p2;
		float *current = &p1;
		if (i >= fmin(y0, y1) && i <= fmax(y0, y1)) {
			if (x0 == x1) {
				*current = x0;
			}
			else
				*current = (i - b0) / m0;
			current = &p2;
		}
		if (i >= fmin(y0, y2) && i <= fmax(y0, y2)) {
			if (x0 == x2) {
				*current = x0;
			}
			else
				*current = (i - b1) / m1;
			current = &p2;
		}
		if (i >= fmin(y1, y2) && i <= fmax(y1, y2)) {
			if (x1 == x2) {
				*current = x1;
			}
			else
				*current = (i - b2) / m2;
			current = &p2;
		}

		for (int j = fmin(p1, p2); j <= fmax(p1, p2); j++) {
			setPixel(j, i);
		}
	}
}

void graphics::fillTriangle2(float x0, float y0, float x1, float y1, float x2, float y2)
{
	//First we split the triangle into two triangles, one with a flat top and one with a flat bottom
	//To do this we find the middle point

	int xMax = fmax(x2, fmax(x0, x1));
	int xMin = fmin(x2, fmin(x0, x1));
	int yMax = fmax(y2, fmax(y0, y1));
	int yMin = fmin(y2, fmin(y0, y1));

	if (y0 <= yMax && y0 >= yMin) {
		//this->fillTopTriangle(x0);
	}
	else if (y1 <= yMax && y1 >= yMin) {

	}
	else if (y2 <= yMax && y2 >= yMin) {

	}
}

void graphics::fillTopTriangle(float x0, float y0, float x1, float xT, float yT)
{
	setColor(0, 1, 1);

	float counterL = 0;
	float incrementL = xT - x0;
	float dYL = yT - y0;
	float xIntL = x0;
	int nL = incrementL > 0 ? 1 : -1;

	float counterR = 0;
	float incrementR = xT - x1;
	float dYR = yT - y0;
	float xIntR = x1;
	int nR = incrementR > 0 ? 1 : -1;

	dYL *= nL;
	dYR *= nR;

	for (int j = y0; j < yT; j++) {
		for (int i = xIntL; i < xIntR; i++) {
			setPixel(i, j);
		}

		counterL += incrementL;
		while (fabs(counterL) > fabs(dYL)) {
			xIntL += nL;
			counterL -= dYL;
		}		

		counterR += incrementR;
		while (fabs(counterR) > fabs(dYR)) {
			xIntR += nR;
			counterR -= dYR;
		}
	}

	setColor(1, 0, 0);

	bLine(x0, y0, x1, y0);
	bLine(x0, y0, xT, yT);
	bLine(x1, y0, xT, yT);
}

void graphics::fillBottomTriangle(float x0, float y0, float x1, float xB, float yB)
{
	setColor(0, 1, 1);

	float counterL = 0;
	float incrementL = xB - x0;
	float dYL = y0 - yB;
	float xIntL = xB;
	int nL = incrementL > 0 ? 1 : -1;

	float counterR = 0;
	float incrementR = xB - x1;
	float dYR = y0 - yB;
	float xIntR = xB;
	int nR = incrementR > 0 ? 1 : -1;

	dYL *= nL;
	dYR *= nR;

	for (int j = yB; j < y0; j++) {
		for (int i = xIntL; i < xIntR; i++) {
			setPixel(i, j);
		}

		counterL += incrementL;
		while (fabs(counterL) > fabs(dYL)) {
			xIntL -= nL;
			counterL -= dYL;
		}

		counterR += incrementR;
		while (fabs(counterR) > fabs(dYR)) {
			xIntR -= nR;
			counterR -= dYR;
		}
	}

	setColor(1, 0, 0);

	bLine(x0, y0, x1, y0);
	bLine(x0, y0, xB, yB);
	bLine(x1, y0, xB, yB);
}

void graphics::fillPolygon(float *points, int num)
{
	int i;
	float minv;
	float ymax;
	float xmin;
	float dx;
	float dy;

	list* edgeTable = new list[this->height];
	
	//For every pair of points
	for (i = 0; i < num-1; i++){
		if (points[i * 2 + 1] - points[(i + 1) * 2 + 1] == 0)
			continue;

		dx = points[i * 2] - points[(i + 1) * 2];
		dy = points[i * 2 + 1] - points[(i + 1) * 2 + 1];

		minv = dx / dy;
		ymax = fmax(points[i * 2 + 1], points[(i + 1) * 2 + 1]);
		if (ymax == points[i * 2 + 1])
			xmin = points[(i + 1) * 2];
		else
			xmin = points[i * 2];

		//We add to the correct scanline based on the .5
		//We draw on bottom edge
		//so if .5 draw on 0. Casting to an int will round this properly
		//
		//for ymax if 10.5 instead draw on 10 again a cast to int solves this. This is handled by casting in remove obsolete

		edgeTable[(int)fmin(points[i * 2 + 1], points[(i + 1) * 2 + 1])].add(ymax, xmin, minv, dx, dy);
	}

	list activeEdgeList = list();

	bool parity = false;
	Bucket* bucket;

	int last;

	for (i = 0; i < this->height; i++) {
		activeEdgeList.removeObsolete(i);
		activeEdgeList.prepend(&edgeTable[i]);
		activeEdgeList.sort();
		

		bucket = activeEdgeList.head;
		while(bucket) {
			if (parity) {
				//int r truncates the int. This means the left side is drawn if the edge is directly on the halfway
				//r<bucket->xmin + 1 will never draw on bucket->xmin if it is passed the .5
				for (int r = last; r < bucket->xmin + 1; r++) {
					setPixel(r, i);
				}
			}
			last = bucket->xmin;
			parity = !parity;

			bucket->xmin += bucket->minv;

			bucket = bucket->next;
		}
	}
}

void graphics::strokePolygon(float * points, int num)
{
	for (int i = 0; i < num-1; i++) {
		this->bLine(points[i * 2], points[i * 2 + 1], points[(i + 1) * 2], points[(i + 1) * 2 + 1]);
	}
}

/*procedure bubbleSort( A : list of sortable items )
    n = length(A)
    repeat
       newn = 0
       for i = 1 to n-1 inclusive do
          if A[i-1] > A[i] then
             swap(A[i-1], A[i])
             newn = i
          end if
       end for
       n = newn
    until n = 0
end procedure*/