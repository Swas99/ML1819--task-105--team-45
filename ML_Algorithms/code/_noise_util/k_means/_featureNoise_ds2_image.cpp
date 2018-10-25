#include <string.h>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <iterator>
#include <iostream>
#include <algorithm>
#include <random>     
#include <cmath>  
using namespace std;

template<typename Out> 

void split(const std::string &s, char delim, Out result) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        *(result++) = item;
    }
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}

void replaceAll(std::string& source, const std::string& from, const std::string& to)
{
    std::string newString;
    newString.reserve(source.length());  // avoids a few memory allocations

    std::string::size_type lastPos = 0;
    std::string::size_type findPos;

    while(std::string::npos != (findPos = source.find(from, lastPos)))
    {
        newString.append(source, lastPos, findPos - lastPos);
        newString += to;
        lastPos = findPos + from.length();
    }

    // Care for the rest after last occurrence
    newString += source.substr(lastPos);

    source.swap(newString);
}

struct dataPoint
{
    int x[32];
    char y;
};

struct mySorter
{
    inline bool operator() (const dataPoint& s1, const dataPoint& s2)
    {
        // if(s1.length() == s2.length())
        //  return s1.compare(s2);
        return s1.y > s2.y;
    }
};

/* Driver program to test above function */
int main(void) 
{ 
	string input1 = "clustering_ds2.txt";
	string input2 = "clustering_ds2.txt";
	string ds_clases = 
	"C:/Users/Swastik/Desktop/MastersDegree_CS/Semester_1/MachineLearning/GroupAssingment/noisyDataSets/ML_Algorithms/data_set/k_means/ds_1/" + input1;
	string ns_ds1 = 
	"C:/Users/Swastik/Desktop/MastersDegree_CS/Semester_1/MachineLearning/GroupAssingment/noisyDataSets/ML_Algorithms/data_set/k_means/ds_1/ns_ds1/";
	string desc_file = ns_ds1 + "description.txt";
 
	string str = "";
	int lineNumber = 0;
    float NOISE_SIZE = 0.3f;
    int NOISE_PERCENT = 5;
	vector<dataPoint> noisyDataSets =  vector<dataPoint>();
	vector<dataPoint> originalDataSet =  vector<dataPoint>(); 

	string fPath = ds_clases;
	fstream file(fPath);
    while(std::getline(file, str))
    {
    	if(str.length() == 0)
    		continue; 

    	replaceAll( str, "\n", "");
    	replaceAll( str, "\t", "");
        vector<string> _row = split(str, ' ');

    	dataPoint objData;
        for(int i = 0; i<3; i++)
            objData.x[i] = stod(_row[i]);

        originalDataSet.push_back(objData);
		lineNumber++;
    }
 

	//testing:
	// for(int i=0; i<30; i++)
	// 	cout<<originalDataSet[i].x[0]<<"\t"<<originalDataSet[i].y<<endl;
	// for(dataPoint x : originalDataSet)
	//  	cout<<x.x1<<"\t"<<x.y<<endl;
	
	
	/*Random noise to x% of data*/
	//random seed
    std::mt19937 rng;
    rng.seed(std::random_device()());
    std::uniform_int_distribution<std::mt19937::result_type> dist9(0,NOISE_PERCENT); // distribution in range [0, 9]

    //shuffle the array 
    random_shuffle(&originalDataSet[0], &originalDataSet[lineNumber-1]);
    for(int i =0; i<9; i++)
    {
        if(dist9(rng) == 0)
            random_shuffle(&originalDataSet[0], &originalDataSet[lineNumber-1]);
    }
	random_shuffle(&originalDataSet[0], &originalDataSet[lineNumber-1]);

	int finalNoiseCount =0;
	int SUBSET_SIZE = lineNumber * NOISE_SIZE;
	for(int i =0; i<SUBSET_SIZE && i<lineNumber; i++)
	{
        int n[] = {dist9(rng), dist9(rng), dist9(rng)};
        if(i<20)
        {
            for(int j=0; j<3 && i<20; j++)
            {
              cout<<originalDataSet[i].x[j]<<"\t";
            }
            cout<<endl;
        }

        for(int j=0; j<3; j++)
        {
            if(i<20)
                cout<<n[j]<<"\t";
            int sign = dist9(rng);
            if(sign<5)
                originalDataSet[i].x[j] = (100+n[j]) * originalDataSet[i].x[j]/100;
            else
                originalDataSet[i].x[j] = (100-n[j]) * originalDataSet[i].x[j]/100;
             originalDataSet[i].x[j]  = std::max(0,  originalDataSet[i].x[j]);
             originalDataSet[i].x[j]  = std::min(255,  originalDataSet[i].x[j]);

        }

        if(i<20)
        {
            cout<<endl;
            for(int j=0; j<3 && i<20; j++)
            {
              cout<<originalDataSet[i].x[j]<<"\t";
            }
            cout<<endl;
            cout<<endl;
        }

        finalNoiseCount++;
	}
    random_shuffle(&originalDataSet[0], &originalDataSet[lineNumber-1]);
	string data = ""; 
    for(int i =0; i<lineNumber; i++)
    {
        for(int j=0; j<3; j++)
            data += to_string(originalDataSet[i].x[j]) + " ";
        data += "\n";
    }
    // cout<<data<<endl;
   	std::ofstream out(ns_ds1 + input1);
    out << data;
	out.close();


	string desc = "->> " + to_string((int)(NOISE_PERCENT * 100)) + "% of the class value were changed randomly\n";
    desc += "->> " + to_string((int)(NOISE_PERCENT * 100)) + " %  of " + " 'M' -> 'B'\n";
    desc += "Final results:\nNumber of rows: " + to_string(lineNumber) + "\nNoisy rows    : " + to_string(finalNoiseCount);

   	std::ofstream out3(desc_file);
    out3 << desc;
	out3.close();

	cout<<finalNoiseCount<<"/"<<lineNumber<<endl;

   return 0; 
} 
