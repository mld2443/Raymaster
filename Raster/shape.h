//
//	shape.h
//	Raster
//
//	Created by Matthew Dillard on 2/7/16.
//

#ifndef shape_h
#define shape_h

#include "float3.h"
#include "colordata.h"

class shape {
public:
	enum shapetype { plane, sphere, cylinder, quadric };

	virtual shapetype getType() const =0;
	RGBA getAmbient() const;
	RGBA getDiffuse() const;
	RGBA getSpecular() const;
	float getShininess() const;
	RGBA getGlow() const;
	FLOAT3 getPos() const;
	
	virtual FLOAT3 getNormal(const FLOAT3& point) const =0;
	
	virtual float intersectRay(const FLOAT3& cam_pos, const FLOAT3& ray) const =0;

protected:
	colordata *m_colors;
	FLOAT3 *m_pos;
};

#endif /* shape_h */
