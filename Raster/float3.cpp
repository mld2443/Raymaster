//
//  float3.cpp
//  Raster
//
//  Created by Matthew Dillard on 2/22/16.
//

#include <sstream>

#include "float3.h"

FLOAT3 operator*(const float& f, const FLOAT3& f3) {
	return {f * f3.x, f * f3.y, f * f3.z};
}


std::istream& operator>>(std::istream& is, FLOAT3& f) {
	std::string s;
	std::stringstream ss;
	
	is >> s;
	
	for (char &c : s) {
		if (c == '(' || c == ',' || c == ')')
			c = ' ';
	}
	
	ss << s;
	
	ss >> f.x >> f.y >> f.z;
	
	return is;
}

std::ostream& operator<<(std::ostream& os, const FLOAT3& f) {
	os << '(' << f.x << ',' << f.y << ',' << f.z << ')';
	return os;
}
