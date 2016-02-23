//
//  filehandler.cpp
//  Raster
//
//  Created by Matthew Dillard on 2/22/16.
//

#include "filehandler.h"

filehandler::filehandler() {
	
}

filehandler::~filehandler() {
	
}


raster* filehandler::loadfile(const char *filename, const unsigned int& width, const unsigned int& height) {
	raster *input = 0;
	camera *cam = 0;
	std::ifstream file(filename);
	std::string token;
	
	if (!file.is_open()) {
		std::cout << "ERROR: file not found" << std::endl;
		return 0;
	}
	
	// iterate through the file and add in vertices and faces
	while (!file.eof()) {
		// get the token
		file >> token;
		
		// comment lines
		if (token[0] == '#') {
			getline(file, token);
		}
		
		else if (token == "") {
			//do nothing
		}
		
		// define a camera
		else if (token == "c") {
			if (cam) {
				delete cam;
				std::cout << "ERROR: camera defined more than once" << std::endl;
				return 0;
			}
			
			FLOAT3 pos, look, up = {0,1,0};
			float fov, low, high;
			
			file >> pos >> look >> fov >> low >> high >> std::ws;
			
			// optionally rotate the camera
			if (file.peek() == '(')
				file >> up;
			
			cam = new camera(pos, look, fov, low, high, up);
		}
		
		else if (!cam) {
			std::cout << "ERROR: camera must be defined first" << std::endl;
			return 0;
		}
		
		else if (token == "r") {
			if (input) {
				delete input;
				std::cout << "ERROR: scene defined more than once" << std::endl;
				return 0;
			}
			
			FLOAT3 ambient;
			float offset = 0.0;
			
			file >> ambient >> std::ws;
			
			// offset between 0 and 1, higher numbers mean brighter diffuse shading
			if (std::isdigit(file.peek()))
				file >> offset;
			
			input = new raster(width, height, cam, ambient, offset);
		}
		
		else if (!input) {
			std::cout << "ERROR: scene undefined before adding objects to it" << std::endl;
			return 0;
		}
		
		// add a new plane
		else if (token == "p") {
			FLOAT3 glow, ambient, diffuse, specular, pos, normal;
			float shininess;
			
			file >> glow >> ambient >> diffuse >> specular >> shininess >> pos >> normal;
			
			input->addShape(new plane(glow, ambient, diffuse, specular, shininess, pos, normal));
		}
		
		// add a new sphere
		else if (token == "s") {
			FLOAT3 glow, ambient, diffuse, specular, pos;
			float radius, shininess;
			
			file >> glow >> ambient >> diffuse >> specular >> shininess >> pos >> radius;
			
			input->addShape(new sphere(glow, ambient, diffuse, specular, shininess, pos, radius));
		}
		
		// add a new sphere
		else if (token == "q") {
			FLOAT3 glow, ambient, diffuse, specular, pos, normal;
			float radius, shininess;
			
			file >> glow >> ambient >> diffuse >> specular >> shininess >> pos >> normal >> radius;
			
			input->addShape(new cylinder(glow, ambient, diffuse, specular, shininess, pos, normal, radius));
		}
		
		// add point light
		else if (token == "pl") {
			FLOAT3 color, pos;
			
			file >> color >> pos;
			
			input->addLight(new pointlight(color, pos));
		}
		
		// add directional light
		else if (token == "dl") {
			FLOAT3 color, dir;
			
			file >> color >> dir;
			
			input->addLight(new directionlight(color, dir));
		}
		
		else {
			// token is unrecognized
			if (cam)
				delete cam;
			
			if (input)
				delete input;
			
			std::cout << "ERROR: unrecognized symbol: " << token << std::endl;
			return 0;
		}
		
		token.clear();
	}
	
	return input;
}
