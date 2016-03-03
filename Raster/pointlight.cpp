//
//  pointlight.cpp
//  Raster
//
//  Created by Matthew Dillard on 2/22/16.
//

#include "pointlight.h"

pointlight::pointlight(const FLOAT3& color, const FLOAT3& position) {
	m_color = new FLOAT3(color);
	m_position = new FLOAT3(position);
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

bool pointlight::illuminated(const FLOAT3 &) const{
	return true;
}

float pointlight::distance(const FLOAT3& point) const {
	return (*m_position - point).len();
}
