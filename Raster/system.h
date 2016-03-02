//
//  system.h
//  Raster
//
//  Created by Matthew Dillard on 3/2/16.
//

#ifndef system_h
#define system_h

#ifdef __APPLE__
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <sstream>

#include "scene.h"
#include "camera.h"

class system {
public:
	struct fileNotFound: public std::runtime_error {
		fileNotFound(const std::string f): runtime_error("File \"" + f + "\" not found") {}
	};
	
	struct unrecognizedType: public std::runtime_error {
		unrecognizedType(const std::string t): runtime_error("Unrecognized type \"" + t + "\"") {}
	};
	
	struct unrecognizedSymbol: public std::runtime_error {
		unrecognizedSymbol(const std::string s, const std::string t):
		runtime_error("Unrecognized symbol \"" + s + "\" while defining type \"" + t + "\"") {}
	};
	
	struct incompleteType: public std::runtime_error {
		incompleteType(const std::string t): runtime_error("Object of type \"" + t + "\" not properly defined") {}
	};
	
	struct incompleteScene: public std::runtime_error {
		incompleteScene(): runtime_error("Missing camera and/or shapes") {}
	};
	
	system(const char *filename);
	~system();
	
	const camera* getCamera() const;
	
	GLfloat* capture();
	
private:
	scene *m_scene;
};

#endif /* system_h */
