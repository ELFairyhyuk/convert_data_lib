//#include <>
#ifndef CONVERTDATA_H
#define CONVERTDATA_H
#include <fstream>
using namespace std;

class convertData{
public:
	//convertData(){}
	//~convertData(){}
	virtual void getFirstLine(ifstream &ifs,ofstream &ofs)=0;
	
	virtual void processData(ifstream &ifs,ofstream &ofs)=0;

};
#endif
