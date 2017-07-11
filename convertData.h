//#include <>
#ifndef CONVERTDATA_H
#define CONVERTDATA_H
#include <fstream>
#include <iostream>
using namespace std;

class convertData{
public:
	convertData(){}
	virtual ~convertData(){}
	void convData2Lib(ifstream &ifs, ofstream &ofs){
		getFirstLine(ifs, ofs);
		processData(ifs, ofs);
	}
protected:
	virtual void getFirstLine(ifstream &ifs,ofstream &ofs){

	}
	
	virtual void processData(ifstream &ifs,ofstream &ofs)=0;

};
#endif
