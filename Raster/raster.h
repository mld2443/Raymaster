//
//	raster.hpp
//	Raster
//
//	Created by Matthew Dillard on 2/7/16.
//

#ifndef raster_h
#define raster_h

#include "shape.h"

class raster {
public:
	raster();
	~raster();

	bool initialize(const FLOAT3&, const FLOAT3&);
	void shutdown();

	void setEyePos(const FLOAT3&);
	void setLookDir(const FLOAT3&);

	FLOAT3 getEyePos() const;
	FLOAT3 getLookDir() const;

private:
	FLOAT3 *m_eyePos, *m_eyeDir;
};

#endif /* raster_h */
