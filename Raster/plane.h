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
	plane(const FLOAT3& color, const FLOAT3& position, const FLOAT3& normal);
	~plane();

	shapetype getType() const;
	
	float intersectRay(const FLOAT3& cam_pos, const FLOAT3& ray) const;
	
private:
};

#endif /* plane_h */
