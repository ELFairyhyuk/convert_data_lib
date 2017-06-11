#include "carInsurance.h"
#include <fstream>
#include <sstream>
#include <map>
#include <cstring>
#include <regex.h>

void carInsurance::getFirstLine(ifstream &ifs, ofstream &ofs){
	//skip first line of atrributes name 
	string line;
	getline(ifs,line);
}
void carInsurance::processData(ifstream &ifs, ofstream &ofs){
	string line,value;
	stringstream strs;
	stringstream strs2;
	regex_t reg;
	regcomp(&reg,"[A-Z]+.*",REG_EXTENDED);
	regmatch_t pmatch[1];
	const size_t nmatch=1;
	//get map
    map<char,int> cate;
	for(int i=0;i<26;i++){
		cate[(char)('A'+i)]=i;
	}
	while(getline(ifs,line)){
	//while(getline(ifs,line)){
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
			//if(value=="?"){
			//	ofs<<" "<<i<<":"<<NULL;
			//}
			//categorical data
			if(regexec(&reg,value.c_str(),nmatch,pmatch,0)==0){
				ofs<<" "<<i<<":";
				strs2<<value;
				char c;
				string rest;
				while(strs2>>c){
					if(c!='.')
						ofs<<cate[c]<<0;//ASC2 of 'A' is 65
					else{
						strs2>>rest;
						ofs<<rest;
					}
				}
				strs2.clear();
			}
			//numerical data
			else if(value!="?") 
				ofs<<" "<<i<<":"<<value;
			i++;
		}
	
		ofs<<endl;
		strs.clear();
	}
	regfree(&reg);
}
