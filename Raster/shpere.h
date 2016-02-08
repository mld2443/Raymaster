//
//	shpere.h
//	Raster
//
//	Created by Matthew Dillard on 2/7/16.
//

#ifndef shpere_h
#define shpere_h

#include <math.h>

#include "shape.h"

class sphere : shape {
public:
	sphere();
	~sphere();

	bool initialize(const FLOAT3&, const FLOAT3&, const FLOAT3&, const float&);
	void shutdown();
	
	shapetype getType() const;
	
	float intersectRay(const FLOAT3&, const FLOAT3&) const;
	
private:
};

#endif /* shpere_h */
