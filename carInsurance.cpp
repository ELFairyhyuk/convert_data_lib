#include "carInsurance.h"
#include <fstream>
#include <sstream>
#include <map>
#include <cstring>
#include <regex.h>
#include <iostream>
#include <stdlib.h>
using namespace std;
void carInsurance::getFirstLine(ifstream &ifs, ofstream &ofs){
	//skip first line of atrributes name 
	string line;
	getline(ifs,line);
}
void carInsurance::processData(ifstream &ifs, ofstream &ofs){
	string line,value;
	stringstream strs;
	regex_t reg1,reg2,reg3;
	regcomp(&reg1,"[A-Z]+",REG_EXTENDED);//pattern for factory
	regcomp(&reg2,"[A-Z]+\\.",REG_EXTENDED);//pattern for model
	regcomp(&reg3,"[A-Z]+\\.[0-9]+\\.",REG_EXTENDED);//pattern for submodel
	regmatch_t pmatch[1];
	const size_t nmatch=1;
	//get map
    map<string, int> model;
	map<string, int> submodel;
	map<string, int> factory;
	int counts=0;//submodel
	int countm=0;//modek
	int countf=0;//factory
	while(getline(ifs,line)){
		int i=1;//id of feature
    	int lastCommaPos=line.find_last_of(",");
		string target = line.substr(lastCommaPos+1, line.length() - lastCommaPos - 1);//output label:the last term in riginal data is label
		float fvalue = atof(target.c_str());
		ofs<<fvalue;
		//substr from 0 to ind is feature value
		strs<<line.substr(0, lastCommaPos);
	    while(getline(strs,value,',')){
			//categorical data
			//submodel
			if(regexec(&reg3,value.c_str(),nmatch,pmatch,0)==0){
				if(submodel.find(value)==submodel.end()){
				    submodel[value]=counts;
					counts++;
				}
				ofs<<" "<<i<<":"<<submodel[value];
			}
			//model
			else if(regexec(&reg2,value.c_str(),nmatch,pmatch,0)==0){
				if(model.find(value)==model.end()){
					model[value]=countm;
					countm++;
				}
				ofs<<" "<<i<<":"<<model[value];
			}
			
			//factory
			else if(regexec(&reg1,value.c_str(),nmatch,pmatch,0)==0){
				if(factory.find(value)==factory.end()){
					factory[value]=countf;
					countf++;
				}
				ofs<<" "<<i<<":"<<factory[value];
			}
			//numerical data
			//skip missing data
			else if(value!="?") {
				ofs<<" "<<i<<":"<<value;
			}
			i++;
		}
	
		ofs<<endl;
		strs.clear();
		strs.str();
	}
	regfree(&reg1);
	regfree(&reg2);
}
