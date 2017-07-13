#include "day_0.h"
#include <iostream>
#include <sstream>
#include <cstring>
#include <regex.h>
#include <map>
#include <limits>
#include <cstdlib>
#include "common.h"

using namespace std;

void day::processData(ifstream &ifs, ofstream &ofs){
	string line,value;
	regex_t reg;
	regcomp(&reg,"[a-z]+",REG_EXTENDED);//pattern for categorical data
	regmatch_t pmatch[1];
	const size_t nmatch=1;

	long unsigned int count=0;
	map<string,long unsigned int > categorical;
	while(getline(ifs,line)){
		int i=1;//id of feature
		int idx=0;
		//label
		int label=line.find_first_of("\t");
		value=line.substr(0,label);
		ofs<<value;
		
		line=line.substr(label+1,line.length());

		while(idx!=-1){
			idx=line.find_first_of("\t");//tab split each feature
			string value=line.substr(0,idx);//substr(0,length())==substr(0,-1)
			line=line.substr(idx+1,line.length());
            //categorical data
			if(regexec(&reg,value.c_str(),nmatch,pmatch,0)==0){
				if(categorical.find(value)==categorical.end()){					
					categorical.insert(make_pair(value,count));


					if(count == numeric_limits<long int>::max()){
							cout<<"long int overread!"<<endl;
							exit(1);
						}

				ofs<<" "<<i<<":"<<categorical[value];
						count++;
					}
				}
		    //numerical data
			//skip missing data
			else if(value!=""){
				ofs<<" "<<i<<":"<<value;
			}
			i++;
			
		}
		ofs<<endl;
	}
}


void day::readFeature(ifstream &fs, int num_feature){
	string suffixName;
	string line,value;
	regex_t reg;
	regcomp(&reg,"[a-z]+",REG_EXTENDED);//pattern for categorical data
	regmatch_t pmatch[1];
	const size_t nmatch=1;
	long unsigned int count=0;
	int featureId=0;
	stringstream sstr;
	map<string,long unsigned int > categorical;
	ofstream streamForFea;
	ofstream streamForId;
	ofstream streamForStartPos;
	ofstream streamForLen;
	while(featureId<num_feature){
		cout<<featureId<<endl;
		sstr<<featureId<<".bin";
		sstr>>suffixName;	//stringstream content to file name
		sstr.clear();
		string fileName;

		fileName="f"+suffixName;
		streamForFea.open(fileName.c_str(),ofstream::app|ofstream::binary);
		checkFile(streamForFea,fileName);
		
		fileName="id"+suffixName;
		streamForId.open(fileName.c_str(),ofstream::app|ofstream::binary);
		checkFile(streamForFea,fileName);
		
		fileName="start"+suffixName;
		streamForStartPos.open(fileName.c_str(),ofstream::app|ofstream::binary);
		checkFile(streamForFea,fileName);
		
		fileName="length"+suffixName;
		streamForLen.open(fileName.c_str(),ofstream::app|ofstream::binary);
		checkFile(streamForFea,fileName);
		int id=0;//id of instance
		int l;//length of each feature
		long unsigned int total_l=0;//total length of features that were visited
		while(getline(fs,line)){
			int idx=-1;
			int j=0;
			while(j<=featureId){
				idx++;
				line=line.substr(idx,line.length());
				j++;
				idx=line.find_first_of("\t");//tab split each feature
			}
		    value=line.substr(0,idx);//substr(0,length())==substr(0,-1)
            //categorical data
			if(regexec(&reg,value.c_str(),nmatch,pmatch,0)==0){
				if(categorical.find(value)==categorical.end()){					
					categorical.insert(make_pair(value,count));
				    count++;
					if(count == numeric_limits<long unsigned int>::max()){
							cout<<"long int overread!"<<endl;
							exit(1);
					}
				}
                //write feature value , start position, feature length into file in binary
				streamForFea.write((char *)&categorical[value],sizeof(categorical[value]));//write in binary
				l=sizeof(categorical[value]);
				streamForLen.write((char *)&l,sizeof(l));
				streamForStartPos.write((char*)&total_l,sizeof(total_l));
				total_l+=l;
					
			}
		    //numerical data
			//skip missing data
			else if(value!=""){
				streamForFea.write((char *)&value,sizeof(value));
				l=sizeof(value);
				streamForLen.write((char *)&l,sizeof(l));
				streamForStartPos.write((char*)&total_l,sizeof(total_l));
				total_l+=l;
					
			}
			//write instance id into file in binary
			streamForId.write((char *)&id,sizeof(id));
			id++;
			
		}//end getline while
		featureId++;
		sstr.clear();
		sstr.str();
		fs.clear();
		fs.seekg(0);//reset the pointer to the head of file
		resetFStream(streamForFea);
		resetFStream(streamForId);
		resetFStream(streamForStartPos);
		resetFStream(streamForLen);

	}
}
