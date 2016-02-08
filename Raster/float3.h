//
//	float3.h
//	Simplify
//
//	Created by Matthew Dillard on 1/19/16.
//

#ifndef float3_h
#define float3_h

#include <math.h>

struct FLOAT3 {
	float x,y,z;

	FLOAT3 operator+(const FLOAT3& v) const { return {x + v.x, y + v.y, z + v.z}; }
	FLOAT3 operator-(const FLOAT3& v) const { return {x - v.x, y - v.y, z - v.z}; }
	FLOAT3 operator*(const float d) const { return {x * d, y * d, z * d}; }
	FLOAT3 operator/(const float d) const { return {x / d, y / d, z / d}; }
	FLOAT3& operator+=(const FLOAT3& v) { x += v.x; y += v.y; z += v.z; return *this; }
	FLOAT3& operator-=(const FLOAT3& v) { x -= v.x; y -= v.y; z -= v.z; return *this; }
	FLOAT3& operator*=(const float d) { x *= d; y *= d; z *= d; return *this; }
	FLOAT3& operator/=(const float d) { x /= d; y /= d; z /= d; return *this; }
	FLOAT3 operator-() const { return {-x, -y, -z}; }
	FLOAT3& operator=(const FLOAT3& v) { x = v.x; y = v.y; z = v.z; return *this; }

	float abs() const { return sqrt(x*x + y*y + z*z); }
	float dot(const FLOAT3& v) const { return x*v.x + y*v.y + z*v.z; }
	FLOAT3 cross(const FLOAT3& v) const { return {y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x}; }
	FLOAT3 normalize() const { float mag = abs(); return {x/mag, y/mag, z/mag}; }
};

#endif /* float3_h */
