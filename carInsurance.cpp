#include "carInsurance.h"
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <cstring>
#include <regex.h>
#include <iostream>
#include <stdlib.h>
#include <vector>
using namespace std;
void carInsurance::getFirstLine(ifstream &ifs, ofstream &ofs){
	//skip first line of atrributes name 
	string line;
	getline(ifs,line);
}
void carInsurance::processData(ifstream &ifs, ofstream &ofs){
	string line,value;
	stringstream strs;

	vector<unordered_map<string, int> > category;
	for(int c = 0; c < 15; c++)
		category.push_back(unordered_map<string, int>());
	unordered_map<string, int> NVCat;
	while(getline(ifs,line)){
		int i=1;//id of feature
    	int lastCommaPos=line.find_last_of(",");
		string target = line.substr(lastCommaPos+1, line.length() - lastCommaPos - 2);//last term is label; windowns has "\r\n" at the end of line
		ofs<<target;
		//substr from 0 to ind is feature value
		strs<<line.substr(0, lastCommaPos);
		string blindMake, blindModel;
	    while(getline(strs,value,',')){
	    	if(value == "?"){
	    		i++;
	    		continue;
	    	}
	    	//numerical data
	    	if(i < 6 || (i > 20 && i < 30) || i > 30)
	    			ofs<<" "<<i<<":"<< value;
	    	else{//categorical data
	    		if(i == 6){
	    			ofs<<" "<<i<<":"<< value[0] - 'A' + 1;
	    			if(value.size() > 1)
	    				ofs << value[1] - 'A' + 1;
	    			blindMake = value;
	    		}
	    		else if(i == 7){
	    			ofs << " " << i << ":" << value.substr(blindMake.size() + 1);
	    			blindModel = value;
	    		}
	    		else if(i == 8){
	    			ofs << " " << i << ":" << value.substr(blindModel.size() + 1);
	    		}
	    		else if(i > 8 && i <= 20){
//	    			if(category[i - 6].find(value) == category[i - 6].end())
//	    				category[i - 6][value] = category[i - 6].size();
//	    			ofs<<" "<<i<<":"<<category[i - 6][value];
	    			ofs<<" "<<i<<":"<< value[0] - 'A' + 1;
	    		}
	    		else if(i == 30){
//	    			if(NVCat.find(value) == NVCat.end())
//	    				NVCat[value] = NVCat.size();
//	    			ofs<<" "<<i<<":"<<NVCat[value];
	    			ofs<<" "<<i<<":"<< value[0] - 'A' + 1;
	    		}
	    		else{
	    			cerr << "unknown features" << endl;
	    			exit(0);
	    		}
	    	}
			i++;
		}
	
		ofs << "\n";
		strs.clear();
		strs.str();
	}
}
