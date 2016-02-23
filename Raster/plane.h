//
//	plane.h
//	Raster
//
//	Created by Matthew Dillard on 2/7/16.
//

#ifndef plane_h
#define plane_h

#include "shape.h"

class plane : public shape {
public:
	plane(const FLOAT3& glowColor, const FLOAT3& ambientColor, const FLOAT3& diffuseColor, const FLOAT3& specularColor, const float& shininess, const FLOAT3& position, const FLOAT3& normal);
	~plane();

	shapetype getType() const;
	
	FLOAT3 getNormal(const FLOAT3& point) const;
	
	float intersectRay(const FLOAT3& cam_pos, const FLOAT3& ray) const;
};

#endif /* plane_h */
