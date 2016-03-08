//
//  directionlight.cpp
//  Raster
//
//  Created by Matthew Dillard on 2/22/16.
//

#include "directionlight.h"

directionlight::directionlight(const RGBA& c, const FLOAT3& n) {
	m_color = new RGBA(c);
	m_normal = new FLOAT3(n.normalize());
}

directionlight::~directionlight() {
	delete m_color;
	m_color = 0;
	
	delete m_normal;
	m_normal = 0;
}


light::lighttype directionlight::getType() const {
	return directional;
}


FLOAT3 directionlight::normalToLight(const FLOAT3& p) const {
	return -(*m_normal);
}

bool directionlight::illuminated(const FLOAT3&) const {
	return true;
}

float directionlight::distance(const FLOAT3& point) const {
	return FLT_MAX;
}
