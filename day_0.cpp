#include "day_0.h"
#include <iostream>
#include <sstream>
#include <cstring>
#include <string>
#include <regex.h>
#include <map>
#include <limits>
#include <cstdlib>
#include <vector>
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


void day::readFeature(ifstream &fs, int Dim){
	//string suffixName;
	string line,value;
	regex_t reg;
	regcomp(&reg,"[a-z]+",REG_EXTENDED);//pattern for categorical data
	regmatch_t pmatch[1];
	const size_t nmatch=1;

	float count=0;
	int featureId=0;
	stringstream sstr;
	map<string, float> categorical;
	string fileName;
	ofstream streamForFea;
	ofstream streamForId;
	ofstream streamForStartPos;
	ofstream streamForLen;

	fileName="feature.bin";
	streamForFea.open(fileName.c_str(),ofstream::app|ofstream::binary);
	checkFile(streamForFea,fileName);
		
	fileName="instanceId.bin";
	streamForId.open(fileName.c_str(),ofstream::app|ofstream::binary);
	checkFile(streamForFea,fileName);
		
	fileName="startPos.bin";
	streamForStartPos.open(fileName.c_str(),ofstream::app|ofstream::binary);
	checkFile(streamForFea,fileName);
		
	fileName="length.bin";
	streamForLen.open(fileName.c_str(),ofstream::app|ofstream::binary);
	checkFile(streamForFea,fileName);
	int total_num=0;//total num of value of each feature that were visited
	while(featureId<Dim){
		if(featureId>3)
			break;
		int id=0;//id of instance
		int num_feature=0;
		vector <float> valueTemp;
		vector <float> idTemp;
		while(getline(fs,line)){
			if(id>3)
				break;
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
				valueTemp.push_back(categorical[value]);
				//streamForFea.write((char *)&categorical[value],sizeof(categorical[value]));//write in binary
				num_feature+=1;
				idTemp.push_back(id);
				//streamForId.write((char *)&id,sizeof(id));

					
			}
		    //numerical data
			//skip missing data
			else if(value!=""){
				float val=stof(value);
				valueTemp.push_back(val);
				//streamForFea.write((char *)&val,sizeof(val));
				num_feature+=1;
				idTemp.push_back(id);
				//streamForId.write((char *)&id,sizeof(id));
				cout<<featureId<<" "<<val<<endl;		
			}
			id++;
			
		}//end getline while
		
		streamForFea.write((char *)&valueTemp[0],valueTemp.size()*sizeof(valueTemp[0]));//write in binary
		streamForId.write((char *)&idTemp[0],idTemp.size()*sizeof(idTemp[0]));
		streamForLen.write((char *)&num_feature,sizeof(num_feature));
		//streamForStartPos<<total_num<<" ";
		//streamForLen<<num_feature<<" ";
		streamForStartPos.write((char*)&total_num,sizeof(total_num));
		total_num+=num_feature;
		
		featureId++;
		sstr.clear();
		sstr.str();
		fs.clear();
		fs.seekg(0);//reset the pointer to the head of file
	}
    streamForFea.close();
	streamForId.close();
	streamForStartPos.close();
	streamForLen.close();

}
