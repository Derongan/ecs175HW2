#include <GL/glut.h>
#include "graphics.h"
#include "list.h"

graphics* g;
void display();

int main(int argc, char *argv[])
{
	//Setup graphics object;

	g = new graphics(200, 200);

	//allocate new pixel buffer, need initialization!!
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE);
	//set window size to 200*200
	glutInitWindowSize(g->width, g->height);
	//set window position
	glutInitWindowPosition(100, 100);

	//create and set main window title
	int MainWindow = glutCreateWindow("Hello Graphics!!");
	glClearColor(0, 0, 0, 0); //clears the buffer of OpenGL
							  //sets display function
	glutDisplayFunc(display);

	glutMainLoop();//main display loop, will display until terminate
	return 0;
}

void display()
{
	//Misc.
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();


	g->setColor(1.0, 0, 0);

	float A[] = { 0,100.5,100,100.5,50,150,0,100.5 };

	g->fillPolygon(A, 4);

	g->setColor(0, 1.0, 0);

	//g->strokePolygon(A, 4);

	float B[] = { 50,100.5,150,100.5,100,50,50,100.5 };

	//g->fillPolygon(B, 4);

	g->setColor(1.0, 0, 0);

	//g->strokePolygon(B, 4);

	glDrawPixels(g->width, g->height, GL_RGB, GL_FLOAT, g->getCurrentBuffer());

	//window refresh
	glFlush();
}