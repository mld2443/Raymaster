//
//	plane.cpp
//	Raster
//
//	Created by Matthew Dillard on 2/7/16.
//

#include "plane.h"

plane::plane(const FLOAT3& c, const FLOAT3& p, const FLOAT3& n) {
	m_color = new FLOAT3(c);
	m_pos = new FLOAT3(p);
	m_dir = new FLOAT3(n.normalize());
	m_radius = new float(n.dot(p));
}

plane::~plane() {
	delete m_color;
	m_color = 0;
	
	delete m_pos;
	m_pos = 0;
	
	delete m_dir;
	m_dir = 0;
	
	delete m_radius;
	m_radius = 0;
}


shape::shapetype plane::getType() const {
	return shape::shapetype::plane;
}


float plane::intersectRay(const FLOAT3& eye, const FLOAT3& ray) const {
	return (*m_radius - m_dir->dot(eye)) / (m_dir->dot(ray));
}
