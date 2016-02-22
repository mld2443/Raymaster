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


raster* filehandler::loadfile(const char *filename) {
	raster *input = 0;
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
		
		// define a camera
		else if (token == "c") {
			if (input) {
				delete input;
				std::cout << "ERROR: camera defined more than once" << std::endl;
				return 0;
			}
			
			FLOAT3 pos, dir;
			float fov, low, high;
			
			file >> pos >> dir >> fov >> low >> high;
			
			input = new raster(pos, dir, fov, low, high);
		}
		
		else if (!input) {
			std::cout << "ERROR: camera undefined before adding plane to scene" << std::endl;
			return 0;
		}
		
		// add a new plane
		else if (token == "p") {
			FLOAT3 color, pos, normal;
			
			file >> color >> pos >> normal;
			
			input->addShape(new plane(color, pos, normal));
		}
		
		// add a new sphere
		else if (token == "s") {
			FLOAT3 color, pos;
			float radius;
			
			file >> color >> pos >> radius;
			
			input->addShape(new sphere(color, pos, radius));
		}
		
		// add a new sphere
		else if (token == "q") {
			FLOAT3 color, pos, normal;
			float radius;
			
			file >> color >> pos >> normal >> radius;
			
			input->addShape(new cylinder(color, pos, normal, radius));
		}
		
		else if (token == "pl") {
			FLOAT3 color, pos;
			
			file >> color >> pos;
			
			input->addLight(new pointlight(color, pos));
		}
		
		else if (token == "dl") {
			FLOAT3 color, dir;
			
			file >> color >> dir;
			
			input->addLight(new directionlight(color, dir));
		}
		
		// token is unrecognized
		else {
			if (input)
				delete input;
			
			std::cout << "ERROR: unrecognized symbol: " << token << std::endl;
			return 0;
		}
	}
	
	return input;
}
