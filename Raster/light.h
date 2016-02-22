//
//  light.h
//  Raster
//
//  Created by Matthew Dillard on 2/22/16.
//

#ifndef light_h
#define light_h

#include "float3.h"

class light {
public:
	enum lighttype { point, directional };
	
	virtual lighttype getType() const =0;
	FLOAT3 getColor() const;
	
protected:
	FLOAT3 *m_color, *m_pos;
};

#endif /* light_h */
