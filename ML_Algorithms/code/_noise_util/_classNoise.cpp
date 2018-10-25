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

struct mySorter
{
    inline bool operator() (const string& s1, const string& s2)
    {
    	// if(s1.length() == s2.length())
    	// 	return s1.compare(s2);
    	return s1.length() < s2.length();
    }
};

struct dataPoint
{
    int x1;
    int y;
};

/* Driver program to test above function */
int main(void) 
{ 
	string input1 = "digit_images.txt";
	string input2 = "digit_classes.txt";
	string ds_clases = 
	"C:/Users/Swastik/Desktop/MastersDegree_CS/Semester_1/MachineLearning/GroupAssingment/noisyDataSets/ML_Algorithms/data_set/logistic_regression/ds_1/" + input2;
	string ds_images = 
	"C:/Users/Swastik/Desktop/MastersDegree_CS/Semester_1/MachineLearning/GroupAssingment/noisyDataSets/ML_Algorithms/data_set/logistic_regression/ds_1/" + input1;
	string ns_ds1 = 
	"C:/Users/Swastik/Desktop/MastersDegree_CS/Semester_1/MachineLearning/GroupAssingment/noisyDataSets/ML_Algorithms/data_set/logistic_regression/ds_1/ns_ds1_7/";
	string desc_file = ns_ds1 + "description.txt";
 
	string str = "";
	int lineNumber = 0;
	float NOISE_PERCENT = 0.50f;
	vector<dataPoint> noisyDataSets =  vector<dataPoint>();
	vector<dataPoint> originalDataSet =  vector<dataPoint>(); 

	string fPath = ds_images;
	fstream file(fPath);
    while(std::getline(file, str))
    {
    	if(str.length() == 0)
    		continue; 

    	replaceAll( str, "\n", "");
    	replaceAll( str, "\t", "");
    	dataPoint objData = {  stoi(str),  // x1  
    		 					0  // y
    		 				};
		originalDataSet.push_back(objData);
		lineNumber++;
    }

	fPath = ds_clases;
	fstream file2(fPath);
	lineNumber = 0;
    while(std::getline(file2, str))
    {
    	if(str.length() == 0)
    		continue; 

    	replaceAll( str, "\n", "");
    	replaceAll( str, "\t", "");
		originalDataSet[lineNumber].y = stoi(str);
		lineNumber++;
    }
	// sort(originalDataSet.begin(), originalDataSet.end());
	// cout<<originalDataSet.size()<<endl;

	//testing:
	// for(int i=0; i<20; i++)
	// 	cout<<originalDataSet[i].x1<<"\t"<<originalDataSet[i].y<<endl;
	// for(dataPoint x : originalDataSet)
	//  	cout<<x.x1<<"\t"<<x.y<<endl;
	
	
	/*Random noise to x% of data*/
	//random seed
    std::mt19937 rng;
    rng.seed(std::random_device()());
    std::uniform_int_distribution<std::mt19937::result_type> dist9(0,9); // distribution in range [0, 9]

    //shuffle the array 
	random_shuffle(&originalDataSet[0], &originalDataSet[lineNumber-1]);

	int finalNoiseCount =0;
	int SUBSET_SIZE = lineNumber * NOISE_PERCENT;
	for(int i =0; i<SUBSET_SIZE; i++)
	{
		int x = dist9(rng);
		if(originalDataSet[i].y != x)
			finalNoiseCount++;
		originalDataSet[i].y = x;		
	}

	string featureSet = "";
	string outputClass = ""; 
	for(int i =0; i<lineNumber; i++)
	{
		featureSet += originalDataSet[i].x1 + "\n";
		outputClass += originalDataSet[i].y + "\n";
	}

   	std::ofstream out(ns_ds1 + input1);
    out << featureSet;
	out.close();

   	std::ofstream out2(ns_ds1 + input2);
    out2 << outputClass;
	out2.close();


	string desc = "->> " + to_string((int)(NOISE_PERCENT * 100)) + "% of the class value were changed randomly\n->> Rows were selected randomly\n->> Value was changed to a randomly picked value between [0,9]\n\nExpected noisy rows = " + to_string((int)(NOISE_PERCENT * 100)) + "%\nFinal results:\nNumber of rows: " + to_string(lineNumber) + "\nNoisy rows    : " + to_string(finalNoiseCount);

   	std::ofstream out3(desc_file);
    out3 << desc;
	out3.close();

	cout<<finalNoiseCount<<"/"<<lineNumber<<endl;

   return 0; 
} 
