//
//	raster.cpp
//	Raster
//
//	Created by Matthew Dillard on 2/7/16.
//

#include "raster.h"

raster::raster() {
	m_eyePos = 0;
	m_eyeDir = 0;
}

raster::~raster() {
	
}

bool raster::initialize(const FLOAT3& p, const FLOAT3& d) {
	m_eyePos = new FLOAT3(p);
	m_eyeDir = new FLOAT3(d);
	
	return true;
}

void raster::shutdown() {
	delete m_eyePos;
	m_eyePos = 0;
	
	delete m_eyeDir;
	m_eyeDir = 0;
}

void raster::setEyePos(const FLOAT3& p) {
	m_eyePos = new FLOAT3(p);
}

void raster::setLookDir(const FLOAT3& d) {
	m_eyeDir = new FLOAT3(d);
}

FLOAT3 raster::getEyePos() const {
	return *m_eyePos;
}

FLOAT3 raster::getLookDir() const {
	return *m_eyeDir;
}
