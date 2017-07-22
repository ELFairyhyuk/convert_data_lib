#include <iostream>
#include <cstring>

//#include "data2lib.h"
#include "convertData.h"
#include "carInsurance.h"
#include "spatialNetwork.h"
#include "criteo.h"
#include "common.h"

int main(int argc, char** argv) {
	string inputFile = argv[1]; //filename of input data
	string outputFile = argv[2]; //filename of output libsvm data
	ifstream inFileStream(inputFile.c_str());
	//check if file open
	if (!inFileStream.is_open()) {
		cout << "can not open file " << inputFile << endl;
		return 1;
	}
	ofstream outFileStream(outputFile.c_str(), ofstream::binary);
	checkFile(outFileStream, outputFile);

	//convertData *cd=new carInsurance();
	//convertData *cd=new spatialNetwork();
	convertData *cd = new Criteo();
	//cd->convData2Lib(ifs,ofs);
	int num_feature = 40;
	Criteo dd;
	dd.writeInBinary(inFileStream, num_feature);

	delete cd;
	cd = NULL;
	inFileStream.close();
	outFileStream.close();
	return 0;
}
