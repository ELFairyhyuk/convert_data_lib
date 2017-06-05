#include <iostream>
#include <sstream>
#include <cstring>
#include <regex.h>
#include "data2lib.h"

/*convert uci data to libsvm format*/
void uci2Lib( ifstream &ifs,ofstream &ofs){
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

/*convert data(include categorical data) from kaggle to libsvm format*/
void kaggle2Lib( ifstream &ifs, ofstream &ofs){
	string line,value;
	stringstream strs;
	stringstream strs2;
	regex_t reg;
	regcomp(&reg,"[A-Z]+.*",REG_EXTENDED);
	regmatch_t pmatch[1];
	const size_t nmatch=1;
	//skip first line of atrributes name 
	getline(ifs,line);
	while(getline(ifs,line)){
		int i=1;
    	int ind=line.find_last_of(",");
		strs2<<line.substr(ind+1,line.length());//output label:the last term in riginal data is label
		strs2>>value;
		ofs<<value;
		strs2.clear();
		//substr from 0 to ind is feature value
		strs<<line.substr(0,ind);
	    while(getline(strs,value,',')){	
			//missing data
			if(value=="?"){
				ofs<<" "<<i<<":"<<NULL;
			}
			//categorical data
			else if(regexec(&reg,value.c_str(),nmatch,pmatch,0)==0){
				ofs<<" "<<i<<":";
				strs2<<value;
				char c;
				string model;
				while(strs2>>c){
					if(c!='.')
						ofs<<((int)c-64)<<0;//ASC2 of 'A' is 65
					else{
						strs2>>model;
						ofs<<model;
					}
				}
				strs2.clear();
			}
			//numerical data
			else 
				ofs<<" "<<i<<":"<<value;
			i++;
		}
	
		ofs<<endl;
		strs.clear();
	}
	regfree(&reg);
}
