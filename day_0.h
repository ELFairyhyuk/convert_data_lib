#ifndef DAY_0_H
#define DAY_0_H
#include "convertData.h"
using namespace std;
class day : public convertData{
public:
<<<<<<< HEAD
    virtual ~day(){};
    void readFeature(ifstream &fs, int num_feature);
protected:
    virtual void processData(ifstream &ifs,ofstream &ofs);
=======
virtual ~day(){};
protected:
virtual void processData(ifstream &ifs,ofstream &ofs);
>>>>>>> origin/master
};

#endif
