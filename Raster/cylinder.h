//
//  cylinder.h
//  Raster
//
//  Created by Matthew Dillard on 2/8/16.
//

#ifndef cylinder_h
#define cylinder_h

#include <math.h>

#include "quadric.h"

class cylinder : public quadric {
public:
	cylinder(const colordata& colors,
			 const FLOAT3& pos,
			 const float& radius);
	~cylinder();
	
	shapetype getType() const;
};

#endif /* cylinder_h */
