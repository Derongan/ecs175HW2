#include "graphics.h"

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
		int test = (int)ceil((fmin(points[i * 2 + 1], points[(i + 1) * 2 + 1]) - .5));
		edgeTable[(int)ceil((fmin(points[i * 2 + 1], points[(i + 1) * 2 + 1])-.5))].add(ceil(ymax-.5), xmin, minv, dx, dy);
	}

	/*for (int i = 0; i < height; i++) {
		edgeTable[i].print();
	}*/

	list activeEdgeList = list();

	bool parity = false;
	Bucket* bucket;

	float last;

	int counterL = 0;
	int counterR = 0;

	for (i = 0; i < this->height; i++) {
		activeEdgeList.removeObsolete(i);
		activeEdgeList.prepend(&edgeTable[i]);
		activeEdgeList.sort();

		bucket = activeEdgeList.head;
		while(bucket) {
			if (parity) {
				//int r truncates the int. This means the left side is drawn if the edge is directly on the halfway
				//r<bucket->xmin + 1 will never draw on bucket->xmin if it is passed the .5
				for (int r = ceilf(last - .5); r+.5 < bucket->xmin; r++) {
					setPixel(r, i);
				}
			}
			last = bucket->xmin;
			parity = !parity;

			bucket->xmin += bucket->minv;

			//counterL += dx;
			bucket = bucket->next;
		}
	}

	delete[] edgeTable;
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