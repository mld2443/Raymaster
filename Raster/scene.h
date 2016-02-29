//
//  scene.h
//  Raster
//
//  Created by Matthew Dillard on 2/28/16.
//

#ifndef scene_h
#define scene_h

#include <exception>
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
	class fileNotFound: public std::exception {
		virtual const char* what() const throw() {
			return "Could not open file";
		}
	};
	
	class unrecognizedType: public std::exception {
	public:
		unrecognizedType(const std::string t): type(t) {}
		
	private:
		virtual const char* what() const throw() {
			return ("Unrecognized type \"" + type + "\"").c_str();
		}
		
		std::string type;
	};
	
	class unrecognizedSymbol: public std::exception {
	public:
		unrecognizedSymbol(const std::string s, const std::string t): symbol(s) {}
		
	private:
		virtual const char* what() const throw() {
			return ("Unrecognized symbol \"" + symbol + "\" while defining type \"" + type + "\"").c_str();
		}
		
		std::string symbol, type;
	};
	
	class multipleScenes: public std::exception {
		virtual const char* what() const throw() {
			return "More than one scene defined";
		}
	};
	
	class incompleteType: public std::exception {
	public:
		incompleteType(const std::string t): type(t) {}
		
	private:
		virtual const char* what() const throw() {
			return ("Object of type \"" + type + "\" not properly defined").c_str();
		}
		
		std::string type;
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
