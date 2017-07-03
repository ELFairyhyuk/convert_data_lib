#include "day_0.h"
#include <iostream>
#include<sstream>
#include <cstring>
#include <regex.h>
#include <map>
#include <limits>
#include <cstdlib>
using namespace std;

void day::processData(ifstream &ifs, ofstream &ofs){
	string line,value;
	regex_t reg;
	regcomp(&reg,"[a-z]+",REG_EXTENDED);//pattern for factory
	regmatch_t pmatch[1];
	const size_t nmatch=1;
	long int count=0;
	int countt=0;
	map<string,long int > cate;
	while(getline(ifs,line)){
		//if(countt>3)
			//break;
		cout<<countt++<<endl;
		int i=1;
		//label
		int label=line.find_first_of("\t");
		value=line.substr(0,label);
		ofs<<value;

		line=line.substr(label+1,line.length());
		while(i<40){
			int ind=line.find_first_of("\t");
			string value=line.substr(0,ind);
			line=line.substr(ind+1,line.length());

			if(regexec(&reg,value.c_str(),nmatch,pmatch,0)==0){
				if(cate.find(value)==cate.end()){					
					cate.insert(make_pair(value,count));
					if(count == numeric_limits<long int>::max()){
							cout<<"long int overread!"<<endl;
							exit(1);
						}
				ofs<<" "<<i<<":"<<cate[value];
						count++;
					}
				}
				//ofs<<" "<<i<<"::"<<cate[value];
			//else if(value=="")
				//ofs<<" "<<i<<"::"<<" ";
		
			else if(value!=""){
				ofs<<" "<<i<<":"<<value;
			}
			i++;
			
		}
		/*while(getline(strs,value,'\t')){
			if(regexec(&reg,value.c_str(),nmatch,pmatch,0)==0){
				//if(cate.find(value)==cate.end()){					
					//cate.insert(make_pair(value,count));
					if(count == numeric_limits<long int>::max()){
							cout<<"long int overread!"<<endl;
							exit(1);
						}
				ofs<<" "<<i<<":"<<value;
						count++;
					}
				//ofs<<" "<<i<<"::"<<cate[value];
		
			else if(value=="")
				ofs<<" "<<i<<"::"<<" ";
			else{
				ofs<<" "<<i<<":"<<value;
			}
			i++;
		}*/
		ofs<<endl;
	}
}

