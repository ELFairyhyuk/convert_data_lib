#include "spatialNetwork.h"
#include <fstream>
#include <sstream>
#include <cstring>

void spatialNetwork::processData(ifstream &ifs, ofstream &ofs){	
	string line,value;
	stringstream strs;
	while(getline(ifs,line)){//read a line from data file
		strs<<line;
		getline(strs,value,',');//split the line stream with comma (char  ',')
		ofs<<value;//output label
		int i=1;
		while(getline(strs,value,','))
		{
			ofs<<" "<<i<<":"<<value;//ouput all diemnsions
			i++;
		}
		ofs<<endl;
		//strs.str("");//clean the string in stream to reuse strs
		strs.clear();//clean wrong flag to reuse strs 
	}
}
