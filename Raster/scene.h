//
//  scene.h
//  Raster
//
//  Created by Matthew Dillard on 2/28/16.
//

#ifndef scene_h
#define scene_h

#include <stdexcept>
#include <iostream>
#include <cstdarg>
#include <fstream>
#include <sstream>
#include <list>
#include <map>

#include "plane.h"
#include "sphere.h"
#include "cylinder.h"
#include "pointlight.h"
#include "directionlight.h"

class scene {
public:
	struct fileNotFound: public std::runtime_error {
        fileNotFound(const std::string file): runtime_error("File \"" + file + "\" not found") {}
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
	
	scene(const char *filename);
	~scene();
	
	FLOAT3 getAmbientLight() const;
	float getDiffuseOffset() const;
	const std::list<shape*> getShapes() const;
	const std::list<light*> getLights() const;
	
private:
	FLOAT3 *m_ambientLight;
	float *m_diffuseOffset;
	std::list<shape*> *m_shapes;
	std::list<light*> *m_lights;
};

#endif /* scene_h */
