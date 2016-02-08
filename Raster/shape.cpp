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
