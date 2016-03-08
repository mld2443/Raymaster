//
//  light.h
//  Raster
//
//  Created by Matthew Dillard on 2/22/16.
//

#ifndef light_h
#define light_h

#include "float3.h"
#include "rgba.h"

class light {
public:
	enum lighttype { point, directional, spot };
	
	virtual lighttype getType() const =0;
	RGBA getColor() const;
	
	virtual FLOAT3 normalToLight(const FLOAT3&) const =0;
	virtual bool illuminated(const FLOAT3&) const =0;
	virtual float distance(const FLOAT3&) const =0;
	
protected:
	RGBA *m_color;
};

#endif /* light_h */
