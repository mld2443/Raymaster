//
//	sphere.h
//	Raster
//
//	Created by Matthew Dillard on 2/7/16.
//

#ifndef sphere_h
#define sphere_h

#include <math.h>

#include "quadric.h"

class sphere : public quadric {
public:
	sphere(const colordata& colors,
		   const FLOAT3& position,
		   const float& radius);
	~sphere();

	shapetype getType() const;
};

#endif /* sphere_h */
