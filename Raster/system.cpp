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
	std::map<std::string, colordata*> colors;
	std::map<std::string, std::function<void (std::istream&)>> args;
	
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
			RGBA ambient{};
			float offset{};
			
			args["ambient"] = [&](std::istream& is){ is >> ambient; m_scene->setAmbientLight(ambient); };
			args["offset"] = [&](std::istream& is){ is >> offset; m_scene->setDiffuseOffset(offset); };
			
			takeObject(file, args, token);
		}
		
		else if (token == "camera") {
			unsigned int xRes, yRes, antialiasing(16);
			FLOAT3 position, direction, up{0,1,0};
			float xFOV, nearClip, farClip;
			bool res(false), pos(false), dir(false), fov(false), cli(false);
			
			args["resolution"] = args["res"] = [&](std::istream& is){ is >> xRes >> yRes; res = true; };
			args["antialiasing"] = args["supersampling"] = [&](std::istream& is){ is >> antialiasing; };
			args["position"] = [&](std::istream& is){ is >> position; pos = true; };
			args["direction"] = [&](std::istream& is){ is >> direction; dir = true; };
			args["fov"] = args["xfov"] = [&](std::istream& is){ is >> xFOV; fov = true; };
			args["clipping"] = args["clip"] = [&](std::istream& is){ is >> nearClip >> farClip; cli = true; };
			args["up"] = args["updirection"] = [&](std::istream& is){ is >> up; };
			
			takeObject(file, args, token);
			
			if (!res || !pos || !dir || !fov || !cli) {
				throw incompleteType(token);
			}
			
			m_scene->setCamera(new camera(xRes, yRes, position, direction,xFOV, nearClip, farClip, m_scene->getShapes(), m_scene->getLights(), antialiasing, up));
		}
		
		// Define a color
		else if (token == "color") {
			RGBA ambient{}, diffuse{}, specular{}, glow{};
			float shininess{};
			bool dif(false);
			
			args["ambient"] = [&](std::istream& is){ is >> ambient; };
			args["diffuse"] = [&](std::istream& is){ is >> diffuse; dif = true; };
			args["specular"] = [&](std::istream& is){ is >> specular; };
			args["shininess"] = args["shine"] = [&](std::istream& is){ is >> shininess; };
			args["glow"] = [&](std::istream& is){ is >> glow; };
			
			takeObject(file, args, token);
			
			if (!dif || name.length() < 1) {
				throw incompleteType(token);
			}
			
			colors[name] = new colordata(ambient, diffuse, specular, shininess, glow);
		}
		
		// add a new plane
		else if (token == "plane") {
			std::string colorname{};
			FLOAT3 position{}, normal{};
			bool clr(false), pos(false), nor(false);
			
			args["color"] = [&](std::istream& is){
				getline(is, colorname);
				clr = true;
				if (colors.find(colorname) == colors.end())
					throw unrecognizedSymbol(colorname, token);
			};
			args["position"] = [&](std::istream& is){ is >> position; pos = true; };
			args["normal"] = [&](std::istream& is){ is >> normal; nor = true; };
			
			takeObject(file, args, token);
			
			if (!clr || !pos || !nor) {
				throw incompleteType(token);
			}
			
			m_scene->addShape(new plane(*colors[colorname], position, normal));
		}
		
		// add a new sphere
		else if (token == "sphere") {
			std::string colorname{};
			FLOAT3 position{};
			float radius{};
			bool clr(false), pos(false), rad(false);
			
			args["color"] = [&](std::istream& is){
				getline(is, colorname);
				clr = true;
				if (colors.find(colorname) == colors.end())
					throw unrecognizedSymbol(colorname, token);
			};
			args["position"] = [&](std::istream& is){ is >> position; pos = true; };
			args["radius"] = [&](std::istream& is){ is >> radius; rad = true; };
			
			takeObject(file, args, token);
			
			if (!clr || !pos || !rad) {
				throw incompleteType(token);
			}
			
			m_scene->addShape(new sphere(*colors[colorname], position, radius));
		}
		
		// add a new cylinder
		else if (token == "cylinder") {
			std::string colorname{};
			FLOAT3 position{};
			float radius{};
			bool clr(false), pos(false), rad(false);
			
			args["color"] = [&](std::istream& is){
				getline(is, colorname);
				clr = true;
				if (colors.find(colorname) == colors.end())
					throw unrecognizedSymbol(colorname, token);
			};
			args["position"] = [&](std::istream& is){ is >> position; pos = true; };
			args["radius"] = [&](std::istream& is){ is >> radius; rad = true; };
			
			takeObject(file, args, token);
			
			if (!clr || !pos || !rad) {
				throw incompleteType(token);
			}
			
			m_scene->addShape(new cylinder(*colors[colorname], position, radius));
		}
		
		// add a new quadric
		else if (token == "quadric") {
			std::string colorname{};
			FLOAT3 position{};
			quadric::equation quadratic;
			bool clr(false), pos(false), equ(false);
			
			args["color"] = [&](std::istream& is){
				getline(is, colorname);
				clr = true;
				if (colors.find(colorname) == colors.end())
					throw unrecognizedSymbol(colorname, token);
			};
			args["position"] = [&](std::istream& is){ is >> position; pos = true; };
			args["equation"] = [&](std::istream& is){ is >> quadratic; equ = true; };
			
			takeObject(file, args, token);
			
			if (!clr || !pos || !equ) {
				throw incompleteType(token);
			}
			
			m_scene->addShape(new quadric(*colors[colorname], position, quadratic));
		}
		
		// add point light
		else if (token == "pointlight") {
			RGBA color{};
			FLOAT3 position{};
			bool clr(false), pos(false);
			
			args["color"] = [&](std::istream& is){ is >> color; clr = true; };
			args["position"] = [&](std::istream& is){ is >> position; pos = true; };
			
			takeObject(file, args, token);
			
			if (!clr || !pos) {
				throw incompleteType(token);
			}
			
			m_scene->addLight(new pointlight(color, position));
		}
		
		// add directional light
		else if (token == "directlight") {
			RGBA color{};
			FLOAT3 direction{};
			bool clr(false), dir(false);
			
			args["color"] = [&](std::istream& is){ is >> color; clr = true; };
			args["direction"] = [&](std::istream& is){ is >> direction; dir = true; };
			
			takeObject(file, args, token);
			
			if (!clr || !dir) {
				throw incompleteType(token);
			}
			
			m_scene->addLight(new directionlight(color, direction));
		}
		
		// add spotlight
		else if (token == "spotlight") {
			RGBA color{};
			FLOAT3 position{}, direction{};
			float angle{};
			bool clr(false), pos(false), dir(false), ang(false);
			
			args["color"] = [&](std::istream& is){ is >> color; clr = true; };
			args["position"] = [&](std::istream& is){ is >> position; pos = true; };
			args["direction"] = [&](std::istream& is){ is >> direction; dir = true; };
			args["angle"] = [&](std::istream& is){ is >> angle; ang = true; };
			
			takeObject(file, args, token);
			
			if (!clr || !pos || !dir || !ang) {
				throw incompleteType(token);
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
		args.clear();
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

std::vector<RGBA> system::capture() {
	return m_scene->capture();
}

void system::takeObject(std::istream& is, std::map<std::string, std::function<void (std::istream&)>> args, std::string& object) {
	std::string token;
	std::stringstream linestream;
	
	getline(is, token);
	
	while (token != "") {
		linestream.clear();
		linestream << token;
		token.clear();
		
		linestream >> token >> std::ws;
		
		if (token[0] == '#')
			getline(linestream, token);
		else {
			auto itr(args.find(token));
			
			if (itr == args.end())
				throw unrecognizedSymbol(token, object);
			else
				itr->second(linestream);
		}
		
		if (!linestream.eof()) {
			token.clear();
			getline(linestream, token);
			throw unrecognizedSymbol(token, object);
		}
		
		token.clear();
		getline(is, token);
	}
}
