#include <iostream>
#include <vector>
#include <string>
#include "MultiSortingEvaluation.h"
#include "FileFunctions.h"

using namespace std;


int main(){

    vector<int> theVectorInt;
    vector<string> theVectorString;
    vector<double> theVectorDouble;
    
    ifstream myfile ("../Tests/test2");
    
    FileAnalysis(theVectorInt,theVectorDouble,theVectorString,myfile);

    cout<<"------------------Integers sorting------------------"<<endl;
    multiSortingEvaluation(theVectorInt);
    cout<<endl;
        
    cout<<"-------------------Doubles sorting------------------"<<endl;
    multiSortingEvaluation(theVectorDouble);
    cout<<endl;
    
    cout<<"-------------------Strings sorting------------------"<<endl;
    multiSortingEvaluation(theVectorString);
    cout<<endl;

}
