//
//	plane.cpp
//	Raster
//
//	Created by Matthew Dillard on 2/7/16.
//

#include "plane.h"

plane::plane(const colordata& colors,
			 const FLOAT3& pos,
			 const FLOAT3& normal) {
	m_colors = new colordata(colors);
	m_pos = new FLOAT3(pos);
	m_norm = new FLOAT3(normal.normalize());
	m_d = new float(normal.dot(pos));
}

plane::~plane() {
	delete m_colors;
	delete m_pos;
	delete m_norm;
	delete m_d;
	
	m_colors = 0;
	m_pos = 0;
	m_norm = 0;
	m_d = 0;
}


shape::shapetype plane::getType() const {
	return shape::shapetype::plane;
}


FLOAT3 plane::getNormal(const FLOAT3&) const {
	return *m_norm;
}


float plane::intersectRay(const FLOAT3& eye, const FLOAT3& ray) const {
	return (*m_d - m_norm->dot(eye)) / (m_norm->dot(ray));
}
