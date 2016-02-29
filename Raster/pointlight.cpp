//
//  pointlight.cpp
//  Raster
//
//  Created by Matthew Dillard on 2/22/16.
//

#include "pointlight.h"

pointlight::pointlight(const FLOAT3& c, const FLOAT3& p) {
	m_color = new FLOAT3(c);
	m_position = new FLOAT3(p);
}

pointlight::~pointlight() {
	delete m_color;
	delete m_position;
	
	m_color = 0;
	m_position = 0;
}


light::lighttype pointlight::getType() const {
	return point;
}


FLOAT3 pointlight::normalToLight(const FLOAT3& p) const {
	return (*m_position - p).normalize();
}
