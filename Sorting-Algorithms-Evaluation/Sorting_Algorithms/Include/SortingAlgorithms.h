#ifndef SORTING_ALGORITHMS_H   
#define SORTING_ALGORITHMS_H  

#include <iostream>
#include <vector>
#include <string>
#include <stdio.h> 
#include <iomanip>

using namespace std;

namespace Sorting {

	void Selection_Sort(vector<int> &values);

	void Selection_Sort(vector<double> &values);

	void Selection_Sort(vector<string> &values);


	void Bubble_Sort(vector<int> &values);

	void Bubble_Sort(vector<double> &values);

	void Bubble_Sort(vector<string> &values);


	void Insertion_Sort(vector<int> &values);

	void Insertion_Sort(vector<double> &values);

	void Insertion_Sort(vector<string> &values);


	void Merge_Sort(vector<int> &values);

	void Merge_Sort(vector<double> &values);

	void Merge_Sort(vector<string> &values);


	void Quick_Sort(vector<int> &values);

	void Quick_Sort(vector<double> &values);

	void Quick_Sort(vector<string> &values);


	void Heap_Sort(vector<int> &values);

	void Heap_Sort(vector<double> &values);

	void Heap_Sort(vector<string> &values);


	void Binary_Sort(vector<int> &values);

	void Binary_Sort(vector<double> &values);

	void Binary_Sort(vector<string> &values);


	void Tree_Sort(vector<int> &values);

	void Tree_Sort(vector<double> &values);

	void Tree_Sort(vector<string> &values);


	void Cartesian_Tree_Sort(vector<int> &values);

	void Cartesian_Tree_Sort(vector<double> &values);

	void Cartesian_Tree_Sort(vector<string> &values);

}

#endif
