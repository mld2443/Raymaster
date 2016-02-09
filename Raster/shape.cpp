//
//	shape.cpp
//	Raster
//
//	Created by Matthew Dillard on 2/7/16.
//

#include "shape.h"

FLOAT3 shape::getPos() const {
	return *m_pos;
}

FLOAT3 shape::getColor() const {
	return *m_color;
}

FLOAT3 shape::getDir() const {
	return *m_dir;
}

float shape::getRadius() const {
	return *m_radius;
}
