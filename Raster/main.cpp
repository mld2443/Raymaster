//
//	main.cpp
//	Raster
//
//	Created by Matthew Dillard on 2/7/16.
//

#ifdef __APPLE__
	#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
	#include <GLUT/glut.h>
#else
	#include <GL/glut.h>
#endif
#include <iostream>

#include "filehandler.h"

#define WINDOW_OFFX 100
#define WINDOW_OFFY 100

int mouseX = -1, mouseY = -1;
int window_width = 960, window_height = 540;
int window = 0;
bool mouseLeftDown = false, mouseRightDown = false;

filehandler *reader;
raster *tracer;

void display() {
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	glFlush();
	
	unsigned int width = glutGet(GLUT_WINDOW_WIDTH), height = glutGet(GLUT_WINDOW_HEIGHT);

	GLfloat *pixels = tracer->render(width, height, 16);

	glDrawPixels(width, height, GL_RGB, GL_FLOAT, pixels);
	
	glFlush();
	
	delete[] pixels;

	glutSwapBuffers();
}

void init(const char* file) {
	/* select clearing color 	*/
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glDisable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glDisable(GL_CULL_FACE);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, glutGet(GLUT_WINDOW_WIDTH) - 1, glutGet(GLUT_WINDOW_HEIGHT) - 1, 0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	reader = new filehandler();
	tracer = reader->loadfile(file);
	delete reader;
	reader = 0;
	
	glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {
	switch(button)
	{
		case GLUT_LEFT_BUTTON:
			mouseLeftDown = state == GLUT_DOWN;
			break;
		case GLUT_RIGHT_BUTTON:
			mouseRightDown = state == GLUT_DOWN;
			break;
	}

	mouseX = x;
	mouseY = y;
}

void motion(int x, int y) {
	mouseX = x;
	mouseY = y;
}

void reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, glutGet(GLUT_WINDOW_WIDTH) - 1, glutGet(GLUT_WINDOW_HEIGHT) - 1, 0);
	glMatrixMode(GL_MODELVIEW);
}

void key(unsigned char c, int x, int y) {
	switch(c)
	{
		case 9: //tab
			break;
			
		case 13: //return
			break;
			
		case 8: //delete
			break;
			
		case 127: //backspace
			break;
			
		case ' ':
			break;
			
		case 27: //escape
			delete tracer;
			
			glutDestroyWindow(window);
			exit(0);
			break;
			
		default:
			break;
	}
}

int main(int argc, char** argv) {
	if (argc != 2 && argc != 4) {
		printf("expected \"%s file.scene [width height]\"\n", argv[0]);
		return 1;
	}
	
	if (argc == 4) {
		window_width = atoi(argv[2]);
		window_height = atoi(argv[3]);
	}
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
	glutInitWindowSize(window_width, window_height);
	glutInitWindowPosition(WINDOW_OFFX, WINDOW_OFFY);
	window = glutCreateWindow("CPSC 647 HW2");
	
	init(argv[1]);
	
	if (!tracer) {
		printf("ERROR: could not load scene\n");
		return 2;
	}
	
	glutReshapeFunc (reshape);
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutKeyboardFunc(key);
	glutMainLoop();
	return 0;
}
