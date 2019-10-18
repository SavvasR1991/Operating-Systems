#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include "Statistics.h"
#include "FileFunctions.h"


using namespace std;

int main(){

    vector<int> theVectorInt;
    vector<string> theVectorString;
    vector<double> theVectorDouble;
    
    ifstream myfile ("../Tests/test2");
    
    FileAnalysis(theVectorInt,theVectorDouble,theVectorString,myfile);

    statistics(theVectorInt);
    
    statistics(theVectorDouble);
    
    statistics(theVectorString);
    
    return 0;
  
}
