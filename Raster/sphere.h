//
//	sphere.h
//	Raster
//
//	Created by Matthew Dillard on 2/7/16.
//

#ifndef sphere_h
#define sphere_h

#include <math.h>

#include "shape.h"

class sphere : public shape {
public:
	sphere(const FLOAT3& glowColor, const FLOAT3& ambientColor, const FLOAT3& diffuseColor, const FLOAT3& specularColor, const float& shininess, const FLOAT3& position, const float& radius);
	~sphere();

	shapetype getType() const;
	
	FLOAT3 getNormal(const FLOAT3& point) const;
	
	float intersectRay(const FLOAT3& cam_pos, const FLOAT3& ray) const;
};

#endif /* sphere_h */
