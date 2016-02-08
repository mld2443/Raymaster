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
}

plane::~plane() {
	
}

bool plane::initialize(const FLOAT3& p, const FLOAT3& c){
	m_pos = new FLOAT3(p);
	m_color = new FLOAT3(c);
	
	return true;
}

void plane::shutdown() {
	delete m_pos;
	m_pos = 0;
	
	delete m_color;
	m_color = 0;
	
	delete m_normal;
	m_normal = 0;
}

void plane::setNormal(const FLOAT3& n) {
	m_normal = new FLOAT3(n);
}

shape::shapetype plane::getType() const {
	return shape::shapetype::plane;
}

FLOAT3 plane::getNormal() const {
	return *m_normal;
}
