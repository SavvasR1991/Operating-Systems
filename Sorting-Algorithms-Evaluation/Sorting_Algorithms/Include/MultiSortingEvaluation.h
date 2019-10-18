#ifndef MULTI_SORTING_EVALUATION_H   
#define MULTI_SORTING_EVALUATION_H  

#include <iostream>
#include <vector>
#include <string>
#include <stdio.h> 
#include <time.h>
#include "SortingAlgorithms.h"
#include "BasicFunctions.h"

using namespace std;
using namespace Sorting;

template<typename T>
void executeSortingFunction(vector<T> &values,void(*func)(vector<T>&)){
    vector<T> TestVector(values);
    clock_t tStart = clock();
    func(TestVector);
    printf("Time taken %.20fs\n", (double)(clock() -tStart)/CLOCKS_PER_SEC);
	TestVector.clear();
}

template<typename T>
void multiSortingEvaluation(vector<T> values){

	executeSortingFunction(values,Selection_Sort);
	
	executeSortingFunction(values,Bubble_Sort);
	
	executeSortingFunction(values,Insertion_Sort);	

	executeSortingFunction(values,Merge_Sort);

	executeSortingFunction(values,Quick_Sort);
	
    executeSortingFunction(values,Heap_Sort);
    
    executeSortingFunction(values,Binary_Sort);

    executeSortingFunction(values,Tree_Sort);
    
    executeSortingFunction(values,Cartesian_Tree_Sort);
}

#endif
