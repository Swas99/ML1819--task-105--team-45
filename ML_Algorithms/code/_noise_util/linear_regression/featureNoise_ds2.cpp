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
#include <cctype>
#include <locale>
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
    string date;
    double x[32];
    double y;
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

    int noiseSeed[] = {0, 10, 20, 30, 40};
    for(int ii = 0; ii<25; ii++)
    {
    	string input1 = "stockprices.csv";
    	string input2 = "stockprices.csv";
    	string ds_clases = 
        "C:/Users/Swastik/Desktop/MastersDegree_CS/Semester_1/MachineLearning/GroupAssingment/noisyDataSets/ML_Algorithms/data_set/linear_regression/ds_2/" + input1;
        string ns_ds1 = 
        "C:/Users/Swastik/Desktop/MastersDegree_CS/Semester_1/MachineLearning/GroupAssingment/noisyDataSets/ML_Algorithms/data_set/linear_regression/ds_2/ns_ds_"
        + to_string(ii+1) + "/";
        string desc_file = ns_ds1 + "description.txt";


    	string str = "";
    	int lineNumber = 0;
        float NOISE_SIZE = 0.1f * (ii%5 + 1);
        int MIN_NOISE_PERCENT = noiseSeed[ii%5];
        int NOISE_PERCENT = MIN_NOISE_PERCENT+5;
    	vector<dataPoint> noisyDataSets =  vector<dataPoint>();
    	vector<dataPoint> originalDataSet =  vector<dataPoint>(); 
    	string fPath = ds_clases;
    	fstream file(fPath);
        std::getline(file, str);
        while(std::getline(file, str))
        { 
        	if(str.length() == 0)
        		continue; 

            replaceAll( str, "\n", "");
            str.erase(0, str.find_first_not_of(' '));       //prefixing spaces
            str.erase(str.find_last_not_of(' ')+1);  
            vector<string> _row = split(str, ',');
            dataPoint objData;
            // if(lineNumber<5)
            //     cout<<str<<endl;
            objData.date = _row[0];
            objData.x[0] = stod(_row[1]);
            objData.x[1] = stod(_row[2]);
            originalDataSet.push_back(objData);
    		lineNumber++;
        } 


    	//testing:
    	// for(int i=0; i<3; i++)
    	// 	cout<<originalDataSet[i].x[0]<<"\t"<<originalDataSet[i].y<<endl;
    	// for(dataPoint x : originalDataSet)
    	//  	cout<<x.x1<<"\t"<<x.y<<endl;
    	 
    	
    	/*Random noise to x% of data*/
    	//random seed
        std::mt19937 rng;
        rng.seed(std::random_device()());
        std::uniform_int_distribution<std::mt19937::result_type> dist9(MIN_NOISE_PERCENT, NOISE_PERCENT); // distribution in range [0, 9]

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
            int n[] = {dist9(rng), dist9(rng) };
            if(i<20)
            {
                for(int j=0; j<2 && i<20; j++)
                {
                  cout<<originalDataSet[i].x[j]<<"\t";
                }
                cout<<endl;
            }

            for(int j=0; j<2; j++)
            {
                if(i<20)
                    cout<<n[j]<<"\t";
                int sign = dist9(rng);
                if(sign<5)
                    originalDataSet[i].x[j] = (100+n[j]) * originalDataSet[i].x[j]/100.0;
                else
                    originalDataSet[i].x[j] = (100-n[j]) * originalDataSet[i].x[j]/100.0;
            }

            if(i<20)
            {
                cout<<endl;
                for(int j=0; j<2 && i<20; j++)
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
        data += data += "#Date,amazon,google\n";
        for(int i =0; i<lineNumber; i++)
        {
            data += originalDataSet[i].date + ",";
            data += to_string(originalDataSet[i].x[0]) + ",";
            data += to_string(originalDataSet[i].x[1]) + "\n";
        }
        // cout<<data<<endl;
       	std::ofstream out(ns_ds1 + input1);
        out << data;
    	out.close();


    	string desc = "->> [" + to_string((int)(MIN_NOISE_PERCENT)) + "," + to_string((int)(NOISE_PERCENT)) + "]% of noise added randomly\n";
        desc += "->> " + to_string((int)(NOISE_SIZE * 100)) + " %  of " + " feature values have noise now\n";
        desc += "Final results:\nNumber of rows: " + to_string(lineNumber) + "\nNoisy rows    : " + to_string(finalNoiseCount);

       	std::ofstream out3(desc_file);
        out3 << desc;
    	out3.close();

    	cout<<finalNoiseCount<<"/"<<lineNumber<<endl<<endl<<endl;
    }

   return 0; 
} 
