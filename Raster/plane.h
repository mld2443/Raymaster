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
	plane(const colordata& colors, const FLOAT3& position, const FLOAT3& normal);
	~plane();

	shapetype getType() const;
	
	FLOAT3 getNormal(const FLOAT3&) const;
	
	float intersectRay(const FLOAT3&, const FLOAT3&) const;
	
private:
	FLOAT3 *m_norm;
	float *m_d;
};

#endif /* plane_h */
