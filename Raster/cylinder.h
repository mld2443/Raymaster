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
	cylinder(const FLOAT3&, const FLOAT3&, const FLOAT3&, const float&);
	~cylinder();
	
	shapetype getType() const;
	
	float intersectRay(const FLOAT3&, const FLOAT3&) const;
	
private:
};

#endif /* cylinder_h */
