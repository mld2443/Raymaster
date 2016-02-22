//
//  light.cpp
//  Raster
//
//  Created by Matthew Dillard on 2/22/16.
//

#include "light.h"

FLOAT3 light::getColor() const {
	return *m_color;
}
