//
//	plane.h
//	Raster
//
//	Created by Matthew Dillard on 2/7/16.
//

#ifndef plane_h
#define plane_h

#include "shape.h"

class plane : shape {
public:
	plane();
	~plane();

	bool initialize(const FLOAT3&, const FLOAT3&);
	void shutdown();
	
	void setNormal(const FLOAT3&);

	shapetype getType() const;
	FLOAT3 getNormal() const;
	
private:
	FLOAT3 *m_normal;
};

#endif /* plane_h */
