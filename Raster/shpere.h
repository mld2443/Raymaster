//
//	shpere.h
//	Raster
//
//	Created by Matthew Dillard on 2/7/16.
//

#ifndef shpere_h
#define shpere_h

#include "shape.h"

class sphere : shape {
public:
	sphere();
	~sphere();

	bool initialize(const FLOAT3&, const FLOAT3&);
	void shutdown();
	
	void setRadius(const float&);

	shapetype getType() const;
	float getRadius() const;
	
private:
	float *m_radius;
};

#endif /* shpere_h */
