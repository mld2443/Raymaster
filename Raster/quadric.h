//
//  quadric.h
//  Raster
//
//  Created by Matthew Dillard on 2/28/16.
//

#ifndef quadric_h
#define quadric_h

#include <sstream>

#include "shape.h"

class quadric : public shape {
public:
	struct equation {
		float A, B, C, D, E, F, G, H, I, J;
		
		FLOAT3 ABC() const { return {A, B, C}; }
		FLOAT3 DEF() const { return {D, E, F}; }
		FLOAT3 GHI() const { return {G, H, I}; }
		
		friend std::istream& operator>>(std::istream&, equation&);
		friend std::ostream& operator<<(std::ostream&, const equation&);
	};
	
	quadric(const colordata& colors,
			const FLOAT3& position,
			const equation& quadratic);
	~quadric();
	
	virtual shapetype getType() const;
	
	FLOAT3 getNormal(const FLOAT3&) const;
	
	float intersectRay(const FLOAT3&, const FLOAT3&) const;
	
protected:
	equation *m_eq;
};

#endif /* quadric_h */
