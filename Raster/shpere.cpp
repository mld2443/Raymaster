//
//	shpere.cpp
//	Raster
//
//	Created by Matthew Dillard on 2/7/16.
//

#include "shpere.h"

sphere::sphere() {
	m_pos = 0;
	m_color = 0;
	m_radius = 0;
}

sphere::~sphere() {
	
}

bool sphere::initialize(const FLOAT3& p, const FLOAT3& c){
	m_pos = new FLOAT3(p);
	m_color = new FLOAT3(c);
	
	return true;
}

void sphere::shutdown() {
	delete m_pos;
	m_pos = 0;
	
	delete m_color;
	m_color = 0;
	
	delete m_radius;
	m_radius = 0;
}

void sphere::setRadius(const float& r) {
	m_radius = new float(r);
}

shape::shapetype sphere::getType() const {
	return shape::shapetype::sphere;
}

float sphere::getRadius() const {
	return *m_radius;
}
