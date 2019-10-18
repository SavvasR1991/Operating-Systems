#ifndef BASIC_FUNCTIONS_H   
#define BASIC_FUNCTIONS_H  

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

template <typename T1>
void swap(T1 *xp, T1 *yp) 
{ 
    T1 temp = *xp; 
    *xp = *yp; 
    *yp = temp; 
} 

template<typename T2>
T2 MaxValue(T2 first , T2 second){

    if(first>second){
        return first;
    }
    return second;
}

template<typename T3>
T3 MinValue(T3 first , T3 second){

    if(first<second){
        return first;
    }
    return second;
}

template <class T > string toString( T value )
{
   stringstream ss;
   ss << value;
   return ss.str();
}


template <class T > T fromString( string s )
{
   T value;
   stringstream ss( s );
   ss >> value;
   return value;
}

int FindMax(int first , int second);

double FindMax(double first , double second);

string FindMax(string first , string second);


void printVector(vector<int> values);

void printVector(vector<double> values);

void printVector(vector<string> values);


string MaxValueString(string,string);

int isNumberOrFloat( string myString );


#endif
