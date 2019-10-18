#include "FileFunctions.h"
#include "BasicFunctions.h"

void FileAnalysis(vector<int> &theVectorInt,vector<double> &theVectorDouble,vector<string> &theVectorString,ifstream &myfile){

    string word;

    if (myfile.is_open())
    {
        while (myfile >> word)
        {

            if(isNumberOrFloat(word) == 1){
                theVectorInt.push_back(fromString<int>(word));
            }
            else if(isNumberOrFloat(word) == 2){
                theVectorDouble.push_back(fromString<double>(word));
            }
            else{
                theVectorString.push_back(word);
            }
        }
        myfile.close();
    }
    else{
        cout << "Unable to open file\n"; 
    }
        
}
