#ifndef CARINSURANCE_H
#define CARINSURANCE_H
#include "convertData.h"
class carInsurance:public convertData{
public:
	carInsurance(){}
    virtual ~carInsurance(){}
protected:
	virtual void getFirstLine(ifstream &ifs, ofstream &ofs);
	virtual void processData(ifstream &ifs, ofstream &ofs);
};
#endif
