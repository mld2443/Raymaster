//
//	shape.cpp
//	Raster
//
//	Created by Matthew Dillard on 2/7/16.
//

#include "shape.h"

// all the getters
FLOAT3 shape::getAmbient() const {
	return m_colors->getAmbient();
}

FLOAT3 shape::getDiffuse() const {
	return m_colors->getDiffuse();
}

FLOAT3 shape::getSpecular() const {
	return m_colors->getSpecular();
}

float shape::getShininess() const {
	return m_colors->getShininess();
}

FLOAT3 shape::getGlow() const {
	return m_colors->getGlow();
}

FLOAT3 shape::getPos() const {
	return *m_pos;
}
