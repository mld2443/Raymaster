//
//	float3.h
//	Simplify
//
//	Created by Matthew Dillard on 1/19/16.
//

#ifndef float3_h
#define float3_h

#include <iostream>
#include <sstream>
#include <math.h>

struct FLOAT3 {
	float x,y,z;
	
	FLOAT3(const float _x=0.0, const float _y=0.0, const float _z=0.0): x(_x), y(_y), z(_z) {}

	FLOAT3 operator+(const FLOAT3& v) const { return {x + v.x, y + v.y, z + v.z}; }
	FLOAT3 operator-(const FLOAT3& v) const { return {x - v.x, y - v.y, z - v.z}; }
	FLOAT3 operator*(const FLOAT3& v) const { return {x * v.x, y * v.y, z * v.z}; }
	FLOAT3 operator/(const FLOAT3& v) const { return {x / v.x, y / v.y, z / v.z}; }
	FLOAT3 operator*(const float f) const { return {x * f, y * f, z * f}; }
	FLOAT3 operator/(const float f) const { return {x / f, y / f, z / f}; }
	FLOAT3 operator-() const { return {-x, -y, -z}; }
	
	FLOAT3& operator+=(const FLOAT3& v) { x += v.x; y += v.y; z += v.z; return *this; }
	FLOAT3& operator-=(const FLOAT3& v) { x -= v.x; y -= v.y; z -= v.z; return *this; }
	FLOAT3& operator*=(const float f) { x *= f; y *= f; z *= f; return *this; }
	FLOAT3& operator/=(const float f) { x /= f; y /= f; z /= f; return *this; }
	FLOAT3& operator=(const FLOAT3& v) { x = v.x; y = v.y; z = v.z; return *this; }
	
	bool operator==(const FLOAT3& c) const { return (x == c.x && y == c.y && z == c.z); }
	bool operator!=(const FLOAT3& c) const { return (x != c.x || y != c.y || z != c.z); }

	float len() const { return sqrt(x*x + y*y + z*z); }
	float dot(const FLOAT3& v) const { return x*v.x + y*v.y + z*v.z; }
	FLOAT3 cross(const FLOAT3& v) const { return {y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x}; }
	FLOAT3 normalize() const { float mag = len(); return {x/mag, y/mag, z/mag}; }
	
	friend FLOAT3 operator*(const float&, const FLOAT3&);
	
	friend std::istream& operator>>(std::istream&, FLOAT3&);
	friend std::ostream& operator<<(std::ostream&, const FLOAT3&);
};

#endif /* float3_h */
