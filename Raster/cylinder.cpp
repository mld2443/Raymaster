//
//  cylinder.cpp
//  Raster
//
//  Created by Matthew Dillard on 2/8/16.
//

#include "cylinder.h"

cylinder::cylinder(const colordata& colors,
				   const FLOAT3& pos,
				   const float& radius) : quadric(colors, pos, {1,0,1,0,0,0,0,0,0,-(radius*radius)}) {}

cylinder::~cylinder() {
	delete m_colors;
	delete m_pos;
	delete m_eq;
	
	m_colors = 0;
	m_eq = 0;
	m_pos = 0;
}


shape::shapetype cylinder::getType() const {
	return shape::shapetype::cylinder;
}
