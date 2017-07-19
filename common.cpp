#include "common.h"
#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

void checkFile(ofstream &ofs, string filename){
	if(!ofs.is_open()){
		cout<<"can not open file "<<filename<<endl;
		exit(1);
	}
}

void resetFStream(ofstream &ofs){
	ofs.close();
	ofs.clear();
}
