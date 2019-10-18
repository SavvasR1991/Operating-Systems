#include "BasicFunctions.h"


void printVector(vector<int> values){
	cout<<"\n";
	int i = 0;
	for (std::vector<int>::iterator it=values.begin(), end = values.end(); it!= end; ++it)
	{
		std::cout << "Vector element ["<<i<<"]: " << *it << std::endl;
		i++;
	}
}

void printVector(vector<double> values){
	cout<<"\n";
	int i = 0;
	for (std::vector<double>::iterator it=values.begin(), end = values.end(); it!= end; ++it)
	{
		std::cout << "Vector element ["<<i<<"]: " << *it << std::endl;
		i++;
	}
}

void printVector(vector<string> values){
	cout<<"\n";
	int i = 0;
	for (std::vector<string>::iterator it=values.begin(), end = values.end(); it!= end; ++it)
	{
		std::cout << "Vector element ["<<i<<"]: " << *it << std::endl;
		i++;
	}
}

string MaxValueString(string first , string second){

	string maxValue;
    int firstStringLen = first.length();
    int secondStringLen = second.length();
    int smallestFirstSecond = MinValue(firstStringLen,secondStringLen);
    int count = 0;
    while(count <smallestFirstSecond){
        if(first[count]!=second[count]){
            if(first[count] == MaxValue(first[count],second[count])){
                maxValue = first;
            }
			else{
				maxValue = second;
			}
            break;
        }
        count++;
    }   
    return maxValue;
}

int FindMax(int first , int second){

    if(first<second){
        return first;
    }
    return second;
}

double FindMax(double first , double second){

    if(first<second){
        return first;
    }
    return second;
}

string FindMax(string first , string second){

    return MaxValueString(first,second);
}

int isNumberOrFloat( string myString ) {
    int i = 0;
    char ch;
    
    int checkIfFloat = 0;
    
    if(!isdigit(myString[0]) && myString[0]!='-'){
        return 0;
    }
    for(i=1;i< myString.size();i++){
        ch = myString[i];
        if (!isdigit(ch)) {
            if(ch=='.'){
                checkIfFloat++;
                if(checkIfFloat>1){
                    return 0;
                }  
            }
            else{
                return 0;
            }
        }
    }
    if(checkIfFloat == 0){
        return 1;
    }
    else{
        return 2;
    }
}
