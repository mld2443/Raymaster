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
	cylinder(const FLOAT3& color, const FLOAT3& position, const FLOAT3& direction, const float& radius);
	~cylinder();
	
	shapetype getType() const;
	
	float intersectRay(const FLOAT3& cam_pos, const FLOAT3& ray) const;
	
private:
};

#endif /* cylinder_h */
