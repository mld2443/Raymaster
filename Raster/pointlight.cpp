//
//  pointlight.cpp
//  Raster
//
//  Created by Matthew Dillard on 2/22/16.
//

#include "pointlight.h"

pointlight::pointlight(const FLOAT3& c, const FLOAT3& p) {
	m_color = new FLOAT3(c);
	m_pos = new FLOAT3(p);
}

pointlight::~pointlight() {
	delete m_color;
	m_color = 0;
	
	delete m_pos;
	m_pos = 0;
}


light::lighttype pointlight::getType() const {
	return point;
}
