//
//	shape.cpp
//	Raster
//
//	Created by Matthew Dillard on 2/7/16.
//

#include "shape.h"

// all the getters
RGBA shape::getAmbient() const {
	return m_colors->getAmbient();
}

RGBA shape::getDiffuse() const {
	return m_colors->getDiffuse();
}

RGBA shape::getSpecular() const {
	return m_colors->getSpecular();
}

float shape::getShininess() const {
	return m_colors->getShininess();
}

RGBA shape::getGlow() const {
	return m_colors->getGlow();
}

FLOAT3 shape::getPos() const {
	return *m_pos;
}
