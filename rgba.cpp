//
//  rgba.cpp
//  Raster
//
//  Created by Matthew Dillard on 3/7/16.
//

#include "rgba.h"

RGBA RGBA::operator+(const RGBA& c) const {
/*	float alpha = A + c.A * (1 - A);
	
	float red = (R * A + c.R * c.A * (1 - A)) / alpha;
	float green = (G * A + c.G * c.A * (1 - A)) / alpha;
	float blue = (B * A + c.B * c.A * (1 - A)) / alpha;*/
	
	return {R + c.R, G + c.G, B + c.B};
}

RGBA RGBA::operator*(const float& f) const {
	return {R * f, G * f, B * f};
}

RGBA RGBA::operator/(const float& f) const {
	return {R / f, G / f, B / f};
}

RGBA RGBA::operator*(const RGBA& c) const {
	return {R * c.R, G * c.G, B * c.B};
}


RGBA& RGBA::operator+=(const RGBA& c) {
/*	float alpha = A + c.A * (1 - A);
	
	R = (R * A + c.R * c.A * (1 - A)) / alpha;
	G = (G * A + c.G * c.A * (1 - A)) / alpha;
	B = (B * A + c.B * c.A * (1 - A)) / alpha;
	A = alpha;*/
	R += c.R;
	G += c.G;
	B += c.B;
	
	return *this;
}

RGBA& RGBA::operator*=(const float& f) {
	R *= f;
	G *= f;
	B *= f;
//	A *= f;
	return *this;
}

RGBA& RGBA::operator=(const RGBA& c) {
	R = c.R;
	G = c.G;
	B = c.B;
//	A = c.A;
	return *this;
}


bool RGBA::operator==(const RGBA& c) const {
	return (R == c.R && G == c.G && B == c.B);
}

bool RGBA::operator!=(const RGBA& c) const {
	return (R != c.R || G != c.G || B != c.B);
}


RGBA operator*(const float& f, const RGBA& color) {
	return {color.R * f, color.G * f, color.B * f};
}


std::istream& operator>>(std::istream& is, RGBA& color) {
	std::string s;
	std::stringstream ss;
	
	is >> s;
	
	for (char &c : s) {
		if (c == '(' || c == ',' || c == ')')
			c = ' ';
	}
	
	ss << s;
	
	ss >> color.R >> color.G >> color.B;
	
	return is;
}

std::ostream& operator<<(std::ostream& os, const RGBA& color) {
	os << '(' << color.R << ',' << color.G << ',' << color.B << ')';
	return os;
}
