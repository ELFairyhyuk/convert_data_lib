#ifndef DAY_0_H
#define DAY_0_H
#include "convertData.h"
using namespace std;
class Criteo : public convertData{
public:
    virtual ~Criteo(){};

    void writeInBinary(ifstream &fs, int Dim);
protected:
    virtual void processData(ifstream &ifs,ofstream &ofs);

};

#endif
