#include <iostream>
#include <cstring>
//#include "data2lib.h"
#include "convertData.h"
#include "carInsurance.h"
#include "spatialNetwork.h"
#include "day_0.h"
<<<<<<< HEAD
#include "common.h"
=======
/*bool checkFile(fstream &fs,string filename){
	if(!fs.is_open()){
		cout<<"can not open file "<<filename<<endl;
		return false;
	}
	else
		return true;
}*/
>>>>>>> origin/master


int main(int argc,char** argv){
	string ifile=argv[1];//filename of input data
	string ofile=argv[2];//filename of output libsvm data
	ifstream ifs(ifile.c_str());
	//check if file open
	if(!ifs.is_open()){
		cout<<"can not open file "<<ifile<<endl;
		return 1;
	}
	ofstream ofs(ofile.c_str(),ofstream::binary);
    checkFile(ofs,ofile);
	
<<<<<<< HEAD
    //convertData *cd=new carInsurance();
	//convertData *cd=new spatialNetwork();
	convertData *cd=new day();
	//cd->convData2Lib(ifs,ofs);
	int num_feature=40;
	day dd;
	dd.readFeature(ifs,num_feature);
=======
<<<<<<< HEAD
    //convertData *cd=new carInsurance();
	//convertData *cd=new spatialNetwork();
    convertData *cd=new day();
=======
	convertData *cd=new carInsurance();
	//convertData *cd=new spatialNetwork();
>>>>>>> origin/master
	cd->convData2Lib(ifs,ofs);
>>>>>>> origin/master
	delete cd;
	cd=NULL;
	ifs.close();
	ofs.close();
    return 0;

}
