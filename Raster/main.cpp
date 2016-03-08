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
#include <vector>
#include <chrono>

//#include "lodepng.h"
#include "system.h"


#define WINDOW_OFFX 100
#define WINDOW_OFFY 100


int window = 0;
bool verbose = false;


class system *tracer;


//void encodeOneStep(const char* filename, std::vector<unsigned char>& image, unsigned width, unsigned height)
//{
//	//Encode the image
//	unsigned error = lodepng::encode(filename, image, width, height);
//	
//	//if there's an error, display it
//	if(error)
//		std::cout << "encoder error " << error << ": "<< lodepng_error_text(error) << std::endl;
//}
//
void display() {
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	glFlush();
	
	if (verbose)
		std::cout << "Tracing...";
	auto wcts = std::chrono::system_clock::now();

	GLfloat *pixels = new GLfloat[glutGet(GLUT_WINDOW_WIDTH) * glutGet(GLUT_WINDOW_HEIGHT) * 3];
	
	auto rgba = tracer->capture();
	
	for (int i = 0; i < rgba.size(); ++i) {
		pixels[(3 * i) + 0] = rgba[i].R;
		pixels[(3 * i) + 1] = rgba[i].G;
		pixels[(3 * i) + 2] = rgba[i].B;
	}

	std::chrono::duration<double> wctduration = (std::chrono::system_clock::now() - wcts);
	if (verbose)
		std::cout << '\t' << wctduration.count() << "s" << std::endl;

	glDrawPixels(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT), GL_RGB, GL_FLOAT, pixels);

	glFlush();

//	delete[] pixels;

	glutSwapBuffers();
}

void init() {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glDisable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glDisable(GL_CULL_FACE);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, glutGet(GLUT_WINDOW_WIDTH) - 1, glutGet(GLUT_WINDOW_HEIGHT) - 1, 0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glutPostRedisplay();
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
	if (argc != 2) {
		if (argc != 3 || !(argv[2][0] == '-' && argv[2][1] == 'v' && argv[2][2] == '\0')) {
			std:: cout << "Expected \"" << argv[0] <<  " file.scene\" [-v]" << std::endl;
			return 1;
		}
		
		verbose = true;
	}
	
	try {
		if (verbose)
			std::cout << "Loading...";
		auto wcts(std::chrono::system_clock::now());
		
		tracer = new class system(argv[1]);
		
		std::chrono::duration<double> wctduration(std::chrono::system_clock::now() - wcts);
		if (verbose)
			std::cout << '\t' << wctduration.count() << "s" << std::endl;
	}
	catch(const std::exception& e){
		std::cout << std::endl << "Exception occured: " << e.what() << std::endl;
		return 2;
	}
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
	glutInitWindowSize(tracer->getCamera()->getXRes(), tracer->getCamera()->getYRes());
	glutInitWindowPosition(WINDOW_OFFX, WINDOW_OFFY);
	window = glutCreateWindow("Raymaster 5000");
	
	init();
	
	glutReshapeFunc (reshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(key);
	glutMainLoop();
	return 0;
}
