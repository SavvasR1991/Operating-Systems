#ifndef VECTOR_FUNCTIONS_H   
#define VECTOR_FUNCTIONS_H  

#include <iostream>
#include <vector>
#include <string>


using namespace std;

void PrintVectorValue(const vector<int> &values);

void PrintVectorValue(const vector<double> &values);

void PrintVectorValue(const vector<string> &values);


void MostPopularVectorValue(const vector<int> &values);

void MostPopularVectorValue(const vector<double> &values);

void MostPopularVectorValue(const vector<string> &values);


void AverageVectorValue(const vector<int> &values);

void AverageVectorValue(const vector<double> &values);

void AverageVectorValue(const vector<string> &values);


void PrintVectorMax(const vector<int> &values);

void PrintVectorMax(const vector<double> &values);

void PrintVectorMax(const vector<string> &values);


void PrintVectorMix(const vector<int> &values);

void PrintVectorMix(const vector<double> &values);

void PrintVectorMix(const vector<string> &values);

#endif
