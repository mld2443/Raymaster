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
	plane();
	~plane();

	bool initialize(const FLOAT3&, const FLOAT3&, const FLOAT3&, const float&);
	void shutdown();
	
	shapetype getType() const;
	
	float intersectRay(const FLOAT3&, const FLOAT3&) const;
	
private:
};

#endif /* plane_h */
