//
//  system.cpp
//  Raster
//
//  Created by Matthew Dillard on 3/2/16.
//

#include "system.h"

system::system(const char *filename): m_scene(new scene()) {
	std::ifstream file(filename);
	std::string token, name;
	std::stringstream linestream;
	std::map<std::string,colordata*> colors;
	
	// If we can't open the file, there's a problem!
	if (!file.is_open())
		throw fileNotFound(filename);
	
	// iterate through the file
	while (!file.eof()) {
		// get the token and put it in our line
		getline(file, token);
		linestream << token;
		token.clear();
		
		// Get the type and the name
		linestream >> token >> std::ws;
		getline(linestream, name);
		
		// Do nothing in case we come across an empty token or a comment
		if (token[0] == '#' || token == "") {}
		
		// Define our scene
		else if (token == "scene") {
			FLOAT3 ambient{};
			float offset{};
			
			token.clear();
			getline(file, token);
			
			while (token != "") {
				linestream.clear();
				linestream << token;
				token.clear();
				
				linestream >> token;
				
				if (token[0] == '#') {
					getline(linestream, token);
				} else if (token == "ambient") {
					linestream >> ambient;
					m_scene->setAmbientLight(ambient);
				} else if (token == "offset") {
					linestream >> offset;
					m_scene->setDiffuseOffset(offset);
				} else {
					throw unrecognizedSymbol(token, "scene");
				}
				
				if (!linestream.eof()) {
					token.clear();
					getline(linestream, token);
					throw unrecognizedSymbol(token, "scene");
				}
				
				token.clear();
				getline(file, token);
			}
		}
		
		else if (token == "camera") {
			unsigned int xRes, yRes, antialiasing(16);
			FLOAT3 position, direction, up{0,1,0};
			float xFOV, nearClip, farClip;
			bool res(false), pos(false), dir(false), fov(false), cli(false);
			
			token.clear();
			getline(file, token);
			
			while (token != "") {
				linestream.clear();
				linestream << token;
				token.clear();
				
				linestream >> token;
				
				if (token[0] == '#') {
					getline(linestream, token);
				} else if (token == "resolution" || token == "res") {
					linestream >> xRes >> yRes;
					res = true;
				} else if (token == "antialiasing" || token == "AA") {
					linestream >> antialiasing;
				} else if (token == "position") {
					linestream >> position;
					pos = true;
				} else if (token == "direction") {
					linestream >> direction;
					dir = true;
				} else if (token == "fov" || token == "xfov") {
					linestream >> xFOV;
					fov = true;
				} else if (token == "clipping" || token == "clip") {
					linestream >> nearClip >> farClip;
					cli = true;
				} else if (token == "up" || token == "updirection") {
					linestream >> up;
				} else {
					throw unrecognizedSymbol(token, "camera");
				}
				
				if (!linestream.eof()) {
					token.clear();
					getline(linestream, token);
					throw unrecognizedSymbol(token, "camera");
				}
				
				token.clear();
				getline(file, token);
			}
			
			if (!res || !pos || !dir || !fov || !cli) {
				throw incompleteType("camera");
			}
			
			m_scene->setCamera(new camera(xRes, yRes, position, direction,xFOV, nearClip, farClip, m_scene->getShapes(), m_scene->getLights(), antialiasing, up));
		}
		
		// Define a color
		else if (token == "color") {
			FLOAT3 ambient{}, diffuse{}, specular{}, glow{};
			float shininess{};
			bool dif(false);
			
			token.clear();
			getline(file, token);
			
			while (token != "") {
				linestream.clear();
				linestream << token;
				token.clear();
				
				linestream >> token;
				
				if (token[0] == '#') {
					getline(linestream, token);
				} else if (token == "ambient") {
					linestream >> ambient;
				} else if (token == "diffuse") {
					linestream >> diffuse;
					dif = true;
				} else if (token == "specular") {
					linestream >> specular;
				} else if (token == "shininess" || token == "shine") {
					linestream >> shininess;
				} else if (token == "glow") {
					linestream >> glow;
				} else {
					throw unrecognizedSymbol(token, "color");
				}
				
				if (!linestream.eof()) {
					token.clear();
					getline(linestream, token);
					throw unrecognizedSymbol(token, "color");
				}
				
				token.clear();
				getline(file, token);
			}
			
			if (!dif || name.length() < 1) {
				throw incompleteType("color");
			}
			
			colors[name] = new colordata(ambient, diffuse, specular, shininess, glow);
		}
		
		// add a new plane
		else if (token == "plane") {
			std::string colorname{};
			FLOAT3 position{}, normal{};
			bool clr(false), pos(false), nor(false);
			
			token.clear();
			getline(file, token);
			
			while (token != "") {
				linestream.clear();
				linestream << token;
				token.clear();
				
				linestream >> token >> std::ws;
				
				if (token[0] == '#') {
					getline(linestream, token);
				} else if (token == "color") {
					getline(linestream, colorname);
					
					if (colors.find(colorname) == colors.end())
						throw unrecognizedSymbol(colorname, "plane");
					
					clr = true;
				} else if (token == "position" || token == "pos") {
					linestream >> position;
					pos = true;
				} else if (token == "normal") {
					linestream >> normal;
					nor = true;
				} else {
					throw unrecognizedSymbol(token, "plane");
				}
				
				if (!linestream.eof()) {
					token.clear();
					getline(linestream, token);
					throw unrecognizedSymbol(token, "plane");
				}
				
				token.clear();
				getline(file, token);
			}
			
			if (!clr || !pos || !nor) {
				throw incompleteType("plane");
			}
			
			m_scene->addShape(new plane(*colors[colorname], position, normal));
		}
		
		// add a new sphere
		else if (token == "sphere") {
			std::string colorname{};
			FLOAT3 position{};
			float radius{};
			bool clr(false), pos(false), rad(false);
			
			token.clear();
			getline(file, token);
			
			while (token != "") {
				linestream.clear();
				linestream << token;
				token.clear();
				
				linestream >> token >> std::ws;
				
				if (token[0] == '#') {
					getline(linestream, token);
				} else if (token == "color") {
					getline(linestream, colorname);
					
					if (colors.find(colorname) == colors.end())
						throw unrecognizedSymbol(colorname, "sphere");
					
					clr = true;
				} else if (token == "position" || token == "pos") {
					linestream >> position;
					pos = true;
				} else if (token == "radius") {
					linestream >> radius;
					rad = true;
				} else {
					throw unrecognizedSymbol(token, "sphere");
				}
				
				if (!linestream.eof()) {
					token.clear();
					getline(linestream, token);
					throw unrecognizedSymbol(token, "sphere");
				}
				
				token.clear();
				getline(file, token);
			}
			
			if (!clr || !pos || !rad) {
				throw incompleteType("sphere");
			}
			
			m_scene->addShape(new sphere(*colors[colorname], position, radius));
		}
		
		// add a new cylinder
		else if (token == "cylinder") {
			std::string colorname{};
			FLOAT3 position{};
			float radius{};
			bool clr(false), pos(false), rad(false);
			
			token.clear();
			getline(file, token);
			
			while (token != "") {
				linestream.clear();
				linestream << token;
				token.clear();
				
				linestream >> token >> std::ws;
				
				if (token[0] == '#') {
					getline(linestream, token);
				}
				else if (token == "color") {
					getline(linestream, colorname);
					
					if (colors.find(colorname) == colors.end())
						throw unrecognizedSymbol(colorname, "cylinder");
					
					clr = true;
				} else if (token == "position" || token == "pos") {
					linestream >> position;
					pos = true;
				} else if (token == "radius") {
					linestream >> radius;
					rad = true;
				} else {
					throw unrecognizedSymbol(token, "cylinder");
				}
				
				if (!linestream.eof()) {
					token.clear();
					getline(linestream, token);
					throw unrecognizedSymbol(token, "cylinder");
				}
				
				token.clear();
				getline(file, token);
			}
			
			if (!clr || !pos || !rad) {
				throw incompleteType("cylinder");
			}
			
			m_scene->addShape(new cylinder(*colors[colorname], position, radius));
		}
		
		// add a new quadric
		else if (token == "quadric") {
			std::string colorname{};
			FLOAT3 position{};
			quadric::equation quadratic;
			bool clr(false), pos(false), equ(false);
			
			token.clear();
			getline(file, token);
			
			while (token != "") {
				linestream.clear();
				linestream << token;
				token.clear();
				
				linestream >> token >> std::ws;
				
				if (token[0] == '#') {
					getline(linestream, token);
				} else if (token == "color") {
					getline(linestream, colorname);
					if (colors.find(colorname) == colors.end())
						throw unrecognizedSymbol(colorname, "quadric");
					clr = true;
				} else if (token == "position" || token == "pos") {
					linestream >> position;
					pos = true;
				} else if (token == "equation") {
					linestream >> quadratic;
					equ = true;
				} else {
					throw unrecognizedSymbol(token, "quadric");
				}
				
				if (!linestream.eof()) {
					token.clear();
					getline(linestream, token);
					throw unrecognizedSymbol(token, "quadric");
				}
				
				token.clear();
				getline(file, token);
			}
			
			if (!clr || !pos || !equ) {
				throw incompleteType("quadric");
			}
			
			m_scene->addShape(new quadric(*colors[colorname], position, quadratic));
		}
		
		// add point light
		else if (token == "pointlight") {
			FLOAT3 color{}, position{};
			bool clr(false), pos(false);
			
			token.clear();
			getline(file, token);
			
			while (token != "") {
				linestream.clear();
				linestream << token;
				token.clear();
				
				linestream >> token;
				
				if (token[0] == '#') {
					getline(linestream, token);
				} else if (token == "color") {
					linestream >> color;
					clr = true;
				} else if (token == "position" || token == "pos") {
					linestream >> position;
					pos = true;
				} else {
					throw unrecognizedSymbol(token, "pointlight");
				}
				
				if (!linestream.eof()) {
					token.clear();
					getline(linestream, token);
					throw unrecognizedSymbol(token, "pointlight");
				}
				
				token.clear();
				getline(file, token);
			}
			
			if (!clr || !pos) {
				throw incompleteType("pointlight");
			}
			
			m_scene->addLight(new pointlight(color, position));
		}
		
		// add directional light
		else if (token == "directlight") {
			FLOAT3 color{}, direction{};
			bool clr(false), dir(false);
			
			token.clear();
			getline(file, token);
			
			while (token != "") {
				linestream.clear();
				linestream << token;
				token.clear();
				
				linestream >> token;
				
				if (token[0] == '#') {
					getline(linestream, token);
				} else if (token == "color") {
					linestream >> color;
					clr = true;
				} else if (token == "direction") {
					linestream >> direction;
					dir = true;
				} else {
					throw unrecognizedSymbol(token, "directlight");
				}
				
				if (!linestream.eof()) {
					token.clear();
					getline(linestream, token);
					throw unrecognizedSymbol(token, "directlight");
				}
				
				token.clear();
				getline(file, token);
			}
			
			if (!clr || !dir) {
				throw incompleteType("directlight");
			}
			
			m_scene->addLight(new directionlight(color, direction));
		}
		
		// add spotlight
		else if (token == "spotlight") {
			FLOAT3 color{}, position{}, direction{};
			float angle{};
			bool clr(false), pos(false), dir(false), ang(false);
			
			token.clear();
			getline(file, token);
			
			while (token != "") {
				linestream.clear();
				linestream << token;
				token.clear();
				
				linestream >> token;
				
				if (token[0] == '#') {
					getline(linestream, token);
				} else if (token == "color") {
					linestream >> color;
					clr = true;
				} else if (token == "position") {
					linestream >> position;
					pos = true;
				} else if (token == "direction") {
					linestream >> direction;
					dir = true;
				} else if (token == "angle") {
					linestream >> angle;
					ang = true;
				} else {
					throw unrecognizedSymbol(token, "spotlight");
				}
				
				if (!linestream.eof()) {
					token.clear();
					getline(linestream, token);
					throw unrecognizedSymbol(token, "spotlight");
				}
				
				token.clear();
				getline(file, token);
			}
			
			if (!clr || !pos || !dir || !ang) {
				throw incompleteType("spotlight");
			}
			
			m_scene->addLight(new spotlight(color, position, direction, angle));
		}
		
		// token is unrecognized
		else {
			throw unrecognizedType(token);
		}
		
		token.clear();
		name.clear();
		linestream.str(std::string());
		linestream.clear();
	}
	
	for (auto& p : colors)
		delete p.second;
	
	if (!*m_scene)
		throw incompleteScene();
}

system::~system() {
	delete m_scene;
	m_scene = 0;
}

const camera* system::getCamera() const {
	return m_scene->getCamera();
}

GLfloat* system::capture() {
	return m_scene->capture();
}
