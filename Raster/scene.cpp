//
//  scene.cpp
//  Raster
//
//  Created by Matthew Dillard on 2/28/16.
//

#include "scene.h"

scene::scene(const char *filename) {
	m_shapes = new std::list<shape*>();
	m_lights = new std::list<light*>();
	m_ambientLight = new FLOAT3(0,0,0);
	m_diffuseOffset = new float(0);
	
	std::ifstream file(filename);
	std::string token, name;
	std::stringstream linestream;
	std::map<std::string,colordata*> colors;
	
	// If we can't open the file, there's a problem!
	if (!file.is_open()) {
		throw fileNotFound();
	}
	
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
				}
				else if (token == "ambient") {
					linestream >> ambient;
				}
				else if (token == "offset") {
					linestream >> offset;
				}
				else {
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
			
			*m_ambientLight = ambient;
			*m_diffuseOffset = offset;
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
				}
				else if (token == "ambient") {
					linestream >> ambient;
				}
				else if (token == "diffuse") {
					linestream >> diffuse;
					dif = true;
				}
				else if (token == "specular") {
					linestream >> specular;
				}
				else if (token == "shininess" || token == "shine") {
					linestream >> shininess;
				}
				else if (token == "glow") {
					linestream >> glow;
				}
				else {
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
				
				linestream >> token;
				
				if (token[0] == '#') {
					getline(linestream, token);
				}
				else if (token == "color") {
					linestream >> colorname;
					
					if (colors.find(colorname) == colors.end())
						throw unrecognizedSymbol(colorname, "plane");
					
					clr = true;
				}
				else if (token == "position" || token == "pos") {
					linestream >> position;
					pos = true;
				}
				else if (token == "normal") {
					linestream >> normal;
					nor = true;
				}
				else {
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
			
			m_shapes->push_back(new plane(*colors[colorname], position, normal));
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
				
				linestream >> token;
				
				if (token[0] == '#') {
					getline(linestream, token);
				}
				else if (token == "color") {
					linestream >> colorname;
					
					if (colors.find(colorname) == colors.end())
						throw unrecognizedSymbol(colorname, "sphere");
					
					clr = true;
				}
				else if (token == "position" || token == "pos") {
					linestream >> position;
					pos = true;
				}
				else if (token == "radius") {
					linestream >> radius;
					rad = true;
				}
				else {
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
			
			m_shapes->push_back(new sphere(*colors[colorname], position, radius));
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
				
				linestream >> token;
				
				if (token[0] == '#') {
					getline(linestream, token);
				}
				else if (token == "color") {
					linestream >> colorname;
					
					if (colors.find(colorname) == colors.end())
						throw unrecognizedSymbol(colorname, "cylinder");
					
					clr = true;
				}
				else if (token == "position" || token == "pos") {
					linestream >> position;
					pos = true;
				}
				else if (token == "radius") {
					linestream >> radius;
					rad = true;
				}
				else {
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
			
			m_shapes->push_back(new cylinder(*colors[colorname], position, radius));
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
				
				linestream >> token;
				
				if (token[0] == '#') {
					getline(linestream, token);
				}
				else if (token == "color") {
					linestream >> colorname;
					
					if (colors.find(colorname) == colors.end())
						throw unrecognizedSymbol(colorname, "quadric");
					
					clr = true;
				}
				else if (token == "position" || token == "pos") {
					linestream >> position;
					pos = true;
				}
				else if (token == "equation") {
					linestream >> quadratic;
					equ = true;
				}
				else {
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
			
			m_shapes->push_back(new quadric(*colors[colorname], position, quadratic));
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
				}
				else if (token == "color") {
					linestream >> color;
					clr = true;
				}
				else if (token == "position" || token == "pos") {
					linestream >> position;
					pos = true;
				}
				else {
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
			
			m_lights->push_back(new pointlight(color, position));
		}
		
		// add directional light
		else if (token == "directlight") {
			FLOAT3 color{}, normal{};
			bool clr(false), nor(false);
			
			token.clear();
			getline(file, token);
			
			while (token != "") {
				linestream.clear();
				linestream << token;
				token.clear();
				
				linestream >> token;
				
				if (token[0] == '#') {
					getline(linestream, token);
				}
				else if (token == "color") {
					linestream >> color;
					clr = true;
				}
				else if (token == "normal") {
					linestream >> normal;
					nor = true;
				}
				else {
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
			
			if (!clr || !nor) {
				throw incompleteType("directlight");
			}
			
			m_lights->push_back(new directionlight(color, normal));
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
	
	for (auto &pair : colors)
		pair.second->~colordata();
}

scene::~scene() {
	for (shape *s : *m_shapes) {
		switch (s->getType()) {
			case shape::plane:
				delete (plane*)s;
				break;
				
			case shape::sphere:
				delete (sphere*)s;
				break;
				
			case shape::cylinder:
				delete (cylinder*)s;
				break;
				
			case shape::quadric:
				delete (quadric*)s;
				break;
				
			default:
				break;
		}
		s = 0;
	}
	
	m_shapes->clear();
	delete m_shapes;
	m_shapes = 0;
	
	for (light *l : *m_lights) {
		switch (l->getType()) {
			case light::point:
				delete (pointlight*)l;
				break;
				
			case light::directional:
				delete (directionlight*)l;
				break;
				
			default:
				break;
		}
		l = 0;
	}
	
	m_lights->clear();
	delete m_lights;
	m_lights = 0;
}

FLOAT3 scene::getAmbientLight() const {
	return *m_ambientLight;
}

float scene::getDiffuseOffset() const {
	return *m_diffuseOffset;
}

const std::list<shape*> scene::getShapes() const {
	return *m_shapes;
}

const std::list<light*> scene::getLights() const {
	return *m_lights;
}
