//
//  system.h
//  Raster
//
//  Created by Matthew Dillard on 3/2/16.
//

#ifndef system_h
#define system_h

#include <functional>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

#include "camera.h"
#include "scene.h"
#include "rgba.h"

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
	
	std::vector<RGBA> capture();
	
private:
	static void takeObject(std::istream&, std::map<std::string, std::function<void (std::istream&)>>, std::string&);
	
	scene *m_scene;
};

#endif /* system_h */
