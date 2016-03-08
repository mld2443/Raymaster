//
//  rgba.h
//  Raster
//
//  Created by Matthew Dillard on 3/7/16.
//

#ifndef rgba_h
#define rgba_h

#include <iostream>
#include <sstream>

struct RGBA {
	float R, G, B;
	
	RGBA(const float& r = 0.0f, const float& g = 0.0f, const float& b = 0.0f): R(r), G(g), B(b) {}
	RGBA(const RGBA& copy): R(copy.R), G(copy.G), B(copy.B) {}
	
	RGBA operator+(const RGBA&) const;
	RGBA operator*(const float&) const;
	RGBA operator/(const float&) const;
	RGBA operator*(const RGBA&) const;
	
	RGBA& operator+=(const RGBA&);
	RGBA& operator*=(const float&);
	RGBA& operator=(const RGBA&);
	
	bool operator==(const RGBA&) const;
	bool operator!=(const RGBA&) const;
	
	friend RGBA operator*(const float&, const RGBA&);
	
	friend std::istream& operator>>(std::istream&, RGBA&);
	friend std::ostream& operator<<(std::ostream&, const RGBA&);
};
#endif /* rgba_h */
