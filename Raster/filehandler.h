//
//  filehandler.h
//  Raster
//
//  Created by Matthew Dillard on 2/22/16.
//

#ifndef filehandler_h
#define filehandler_h

#include <iostream>
#include <fstream>

#include "raster.h"

class filehandler {
public:
	filehandler();
	~filehandler();
	
	raster* loadfile(const char*);
};

#endif /* filehandler_h */
