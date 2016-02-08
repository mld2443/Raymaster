//
//	plane.cpp
//	Raster
//
//	Created by Matthew Dillard on 2/7/16.
//

#include "plane.h"

plane::plane() {
	m_pos = 0;
	m_color = 0;
	m_normal = 0;
	m_radius = 0;
}

plane::~plane() {
	
}


bool plane::initialize(const FLOAT3& p, const FLOAT3& c, const FLOAT3& n, const float&){
	m_pos = new FLOAT3(p);
	m_color = new FLOAT3(c);
	m_normal = new FLOAT3(n);
	m_radius = new float(n.dot(p));
	
	return true;
}

void plane::shutdown() {
	delete m_pos;
	m_pos = 0;
	
	delete m_color;
	m_color = 0;
	
	delete m_normal;
	m_normal = 0;
	
	delete m_radius;
	m_radius = 0;
}


shape::shapetype plane::getType() const {
	return shape::shapetype::plane;
}


float plane::intersectRay(const FLOAT3& eye, const FLOAT3& ray) const {
	return -(eye.dot(*m_normal) + *m_radius) / (ray.dot(*m_normal));
}
