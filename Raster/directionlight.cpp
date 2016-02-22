//
//  directionlight.cpp
//  Raster
//
//  Created by Matthew Dillard on 2/22/16.
//

#include "directionlight.h"

directionlight::directionlight(const FLOAT3& c, const FLOAT3& d) {
	m_color = new FLOAT3(c);
	m_pos = new FLOAT3(d);
}

directionlight::~directionlight() {
	delete m_color;
	m_color = 0;
	
	delete m_pos;
	m_pos = 0;
}


light::lighttype directionlight::getType() const {
	return directional;
}
