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
	regex_t reg1,reg2,reg3;
	regcomp(&reg1,"[A-Z]+",REG_EXTENDED);//pattern for manufactury
	regcomp(&reg2,"[A-Z]+\\.",REG_EXTENDED);//pattern for model
	regcomp(&reg3,"[A-Z]+\\.[0-9]+\\.",REG_EXTENDED);//pattern for submodel
	regmatch_t pmatch[1];
	const size_t nmatch=1;
	//get map
    map<string, int> model;
	map<string, int> submodel;
	int counts=0;
	int countm=0;
	int countt=0;
	while(countt<3){
	//while(getline(ifs,line)){
		countt++;
		getline(ifs,line);
		int i=1;
    	int ind=line.find_last_of(",");
		strs2<<line.substr(ind+1,line.length());//output label:the last term in riginal data is label
		strs2>>value;
		ofs<<value;
		strs2.clear();
		//substr from 0 to ind is feature value
		strs<<line.substr(0,ind);
	    while(getline(strs,value,',')){	
			//skip missing data
			//categorical data
			if(regexec(&reg3,value.c_str(),nmatch,pmatch,0)==0){
				if(submodel.find(value)==submodel.end()){
					submodel[value]=counts;
					//cate.insert(make_pair(value,count));
					counts++;
				}
				ofs<<" "<<i<<":"<<submodel[value];
			}
			else if(regexec(&reg2,value.c_str(),nmatch,pmatch,0)==0){
				if(model.find(value)==model.end()){
					model[value]=countm;
					//cate.insert(make_pair(value,count));
					countm++;
				}
				ofs<<" "<<i<<":"<<model[value];
				/*strs2<<value;
				char c;
				string rest;
				while(strs2>>c){
					if(c!='.')
						ofs<<(int)(c-'A')<<0;//ASC2 of 'A' is 65
					else{
						strs2>>rest;
						ofs<<rest;
					}
				}
				strs2.clear();*/
			}
			
			//single letter
			else if(regexec(&reg1,value.c_str(),nmatch,pmatch,0)==0){
				char c;
				int i=0;
				int num=0;
				strs2<<value;
				while(strs2>>c){
					num+=(int)(c-'A')+26*i;
					i++;
				}
				ofs<<" "<<i<<":"<<num;
				strs2.clear();
			}
			//numerical data
			else if(value!="?") 
				ofs<<" "<<i<<":"<<value;
			i++;
		}
	
		ofs<<endl;
		strs.clear();
		strs.str();
	}
	regfree(&reg1);
	regfree(&reg2);
}
