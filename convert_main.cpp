#include <iostream>
#include <cstring>
//#include "data2lib.h"
#include "convertData.h"
#include "carInsurance.h"
#include "spatialNetwork.h"
/*bool checkFile(fstream &fs,string filename){
	if(!fs.is_open()){
		cout<<"can not open file "<<filename<<endl;
		return false;
	}
	else
		return true;
}*/


int main(int argc,char** argv){
	string ifile=argv[1];//filename of input data
	string ofile=argv[2];//filename of output libsvm data
	ifstream ifs(ifile.c_str());
	//check if file open
	if(!ifs.is_open()){
		cout<<"can not open file "<<ifile<<endl;
		return 1;
	}
	ofstream ofs(ofile.c_str());
	if(!ofs.is_open()){
		cout<<"can not open file "<<ofile<<endl;
		return 1;
	}
    //transfer UCI data to libsvm data
	
	//convertData *cd=new spatialNetwork();
	convertData *cd=new carInsurance();
	cd->getFirstLine(ifs,ofs);
	cd->processData(ifs,ofs);
	ifs.close();
	ofs.close();
    return 0;

}
