//
//	shape.h
//	Raster
//
//	Created by Matthew Dillard on 2/7/16.
//

#ifndef shape_h
#define shape_h

#include "float3.h"

class shape {
public:
	enum shapetype { plane, sphere, cylinder };

	virtual bool initialize(const FLOAT3&, const FLOAT3&, const FLOAT3&, const float&) =0;
	virtual void shutdown() =0;
	
	virtual shapetype getType() const =0;
	FLOAT3 getPos() const;
	FLOAT3 getColor() const;
	FLOAT3 getNormal() const;
	float getRadius() const;
	
	virtual float intersectRay(const FLOAT3&, const FLOAT3&) const =0;

protected:
	FLOAT3 *m_pos, *m_color, *m_normal;
	float *m_radius;
};

#endif /* shape_h */
