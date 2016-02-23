//
//  cylinder.h
//  Raster
//
//  Created by Matthew Dillard on 2/8/16.
//

#ifndef cylinder_h
#define cylinder_h

#include <math.h>

#include "shape.h"

class cylinder : public shape {
public:
	cylinder(const FLOAT3& glowColor, const FLOAT3& ambientColor, const FLOAT3& diffuseColor, const FLOAT3& specularColor, const float& shininess, const FLOAT3& position, const FLOAT3& direction, const float& radius);
	~cylinder();
	
	shapetype getType() const;
	
	FLOAT3 getNormal(const FLOAT3& point) const;
	
	float intersectRay(const FLOAT3& cam_pos, const FLOAT3& ray) const;
};

#endif /* cylinder_h */
