#ifndef SPATIALNETWORK_H
#define SPATIALNETWORK_H

#include "convertData.h"
class spatialNetwork:public convertData{
public:
	spatialNetwork(){}
	virtual	~spatialNetwork(){}
	virtual void processData(ifstream &ifs,ofstream &ofs);
};
#endif
