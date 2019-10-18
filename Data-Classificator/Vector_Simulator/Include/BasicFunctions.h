#ifndef BASIC_FUNCTIONS_H   
#define BASIC_FUNCTIONS_H  

#include <iostream>
#include <string>
#include <math.h>
#include <sstream>

using namespace std;

template<typename T>
T MaxValue(T first , T second){

    if(first>second){
        return first;
    }
    return second;
}

template<typename T1>
T1 MinValue(T1 first , T1 second){

    if(first<second){
        return first;
    }
    return second;
}

template<class T2>
void setArrayToZero(T2 &arrayInput,size_t size){

    for(int i=0;i<size;i++){
        arrayInput[i]=0;
    }

}

template<class T3>
void printArray(const T3 arrayInput[],size_t size){

    for(int i=0;i<size;i++){
        std::cout<<arrayInput[i]<<std::endl;
    }

}

template<class T4> 
T4 maxArray(const T4* data, int size) {
    T4 result = data[0];
    for(int i = 1 ; i < size ; i++)
        if(result < data[i])
        result = data[i];
    return result;
}

template<class T7> 
T7 maxArrayPossition(const T7* data, int size) {
    T7 result = data[0];
    int possition = 0;
    for(int i = 1 ; i < size ; i++)
        if(result < data[i]){
            result = data[i];
            possition = i;
        }
    return possition;
}

template<class T5> 
T5 minArray(const T5* data, int size) {
    T5 result = data[0];
    for(int i = 1 ; i < size ; i++)
        if(result > data[i])
        result = data[i];
    return result;
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

int HexToDecimalConverter(string input);

string longDivision(string number, int divisor);

int longMod(string number, int divisor);

int moduloHexCalculation(string input,int divisor);

int isNumberOrFloat( string myString );


#endif
