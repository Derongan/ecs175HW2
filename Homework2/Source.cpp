#include <GL/glut.h>
#include "graphics.h"
#include "list.h"

void display();

graphics* g;

int main(int argc, char *argv[])
{
	//Setup graphics object;

	g = new graphics(800, 600);

	//allocate new pixel buffer, need initialization!!
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE);
	//set window size to 200*200
	glutInitWindowSize(g->width, g->height);
	//set window position
	glutInitWindowPosition(100, 100);

	//create and set main window title
	int MainWindow = glutCreateWindow("Landscape");
	glClearColor(0, 0, 0, 0); //clears the buffer of OpenGL
	glutDisplayFunc(display); //sets display function


	glutMainLoop();//main display loop, will display until terminate
	return 0;
}

void display()
{
	//Misc.
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	//Mountains
	g->setColor(.01, .01, .08);
	float mountain1[] = {150,400,g->width,400,600,580,150,400};
	g->fillPolygon(mountain1, 4);

	g->setColor(.1, .1, .15);
	float mountain2[] = { 0,400,g->width,300,400,580,0,400 };
	g->fillPolygon(mountain2, 4);

	//Ground
	float ground[] = { 0,0,g->width,0,g->width,400,0,400,0,0 };
	g->setColor(0.54, 0.27, 0.07);
	g->fillPolygon(ground, 5);

	//First rock
	float rockshadow[] = { 110,100,425,100,320,80,300,80,110,100 };
	g->setColor(.2, .2, .2);
	//g->fillPolygon(rockshadow, 5);

	float rock1[] = { 100,100,200,70,175,150,100,100 };
	g->setColor(.6, .6, .6);
	g->fillPolygon(rock1, 4);

	float rock3d[] = { 400,100,200,70,175,150,400,100 };
	g->setColor(.7, .7, .7);
	g->fillPolygon(rock3d, 4);


	//Second rock
	float rockshadow2[] = { 500,350,800,330,700,325,500,350 };
	g->setColor(.2, .2, .2);
	//g->fillPolygon(rockshadow2, 4);

	float rock2[] = { 500,350,700,330,575,420,500,350 };
	g->setColor(.6, .6, .6);
	g->fillPolygon(rock2, 4);

	float rock23d[] = { 800,350,700,330,575,420,800,350 };
	g->setColor(.7, .7, .7);
	g->fillPolygon(rock23d, 4);

	//Road
	float hash[10];
	g->setColor(.6, .54, .44);
	for (int i = 0; i < g->width - 40; i += 80) {
		hash[0] = hash[8] = hash[6] = i;
		hash[2] = hash[4] = i + 40;
		hash[1] = hash[3] = hash[9] = 282;
		hash[5] = hash[7] = 302;
		g->fillPolygon(hash, 5);
	}

	float road[] = { 0,185, 175, 205, g->width,210,g->width,290,0,290,0,185 };
	g->setColor(.76, .7, .5);
	g->fillPolygon(road, 6);

	g->setColor(0, 0, 0);

	g->setColor(.6, .54, .44);
	for (int i = 0; i < 160; i += 80) {
		hash[0] = hash[8] = hash[6] = i;
		hash[2] = hash[4] = i + 40;
		hash[1] = hash[9] = 180+i/10;
		hash[3] = 180 + i / 10 + 4;
		hash[7] = 200+i/10;
		hash[5] = 200 + i / 10 + 4;
		g->fillPolygon(hash, 5);
	}
	for (int i = 160; i < g->width - 40; i += 80) {
		hash[0] = hash[8] = hash[6] = i;
		hash[2] = hash[4] = i+40;
		hash[1] = hash[3] = hash[9] = 200;
		hash[5] = hash[7] = 220;
		g->fillPolygon(hash, 5);
	}


	glDrawPixels(g->width, g->height, GL_RGB, GL_FLOAT, g->getCurrentBuffer());

	//window refresh
	glFlush();
}