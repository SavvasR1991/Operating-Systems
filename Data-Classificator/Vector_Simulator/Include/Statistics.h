#ifndef STATISTICS_H   
#define STATISTICS_H  

#include <iostream>
#include <vector>
#include <string>
#include "VectorFunctions.h"

using namespace std;

template<typename T>
void ForEach(const vector<T> &values,void(*func)(const vector<T>&)){

    func(values);
}

template<typename T1>
void statistics(const vector<T1> &values){

    ForEach(values,PrintVectorValue);
    cout<<endl;
    ForEach(values,MostPopularVectorValue);
    cout<<endl;
    ForEach(values,AverageVectorValue);
    cout<<endl;
    ForEach(values,PrintVectorMax);
    cout<<endl;
    ForEach(values,PrintVectorMix);
    cout<<endl;
    cout<<endl;
}


#endif
