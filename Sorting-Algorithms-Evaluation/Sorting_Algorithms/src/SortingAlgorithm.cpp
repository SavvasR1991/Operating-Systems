#include "SortingAlgorithms.h"
#include "SortingImplementation.h"
#include "BasicFunctions.h"

namespace Sorting {

	void Selection_Sort(vector<int> &values){

		int i, j, min_idx,n; 
		int *arr = &values[0];
		n = values.size();
	    cout<<__func__<<"      :";
		for (i = 0; i < n-1; i++) 
		{ 
			min_idx = i; 
			for (j = i+1; j < n; j++) 
			  if (arr[j] < arr[min_idx]) 
				min_idx = j; 
  
			swap(&arr[min_idx], &arr[i]); 
		} 
	}

	void Selection_Sort(vector<double> &values){
		int i, j,min_idx, n; 
		double *arr = &values[0];
		n = values.size();
	    cout<<__func__<<"      :";
		for (i = 0; i < n-1; i++) 
		{ 
			min_idx = i; 
			for (j = i+1; j < n; j++) 
			  if (arr[j] < arr[min_idx]) 
				min_idx = j; 
  
			swap(&arr[min_idx], &arr[i]); 
		} 
	}

	void Selection_Sort(vector<string> &values){
		int i, j,min_idx, n; 
		string *arr = &values[0];
		n = values.size();
	    cout<<__func__<<"      :";
		for (i = 0; i < n-1; i++) 
		{ 
			min_idx = i; 
			for (j = i+1; j < n; j++) 
				if (arr[min_idx] == MaxValueString(arr[j],arr[min_idx])){ 
					min_idx = j; 
				}
			swap(&arr[min_idx], &arr[i]); 
		} 
	}


	void Bubble_Sort(vector<int> &values){

		int i, j, n; 
		int *arr = &values[0];
		n = values.size();
        cout<<__func__<<"         :";
		for (i = 0; i < n-1; i++)       
			for (j = 0; j < n-i-1; j++)  
				if (arr[j] > arr[j+1] ) 
					swap(&arr[j], &arr[j+1]); 
	}

	void Bubble_Sort(vector<double> &values){
		int i, j, n; 
		double *arr = &values[0];
		n = values.size();
		cout<<__func__<<"         :";
		for (i = 0; i < n-1; i++)       
			for (j = 0; j < n-i-1; j++)  
				if (arr[j] > arr[j+1]) 
					swap(&arr[j], &arr[j+1]); 

	}

	void Bubble_Sort(vector<string> &values){
		int i, j, n; 
		string *arr = &values[0];
		n = values.size();
		cout<<__func__<<"         :";
		for (i = 0; i < n-1; i++)       
			for (j = 0; j < n-i-1; j++)  
				if (arr[j] == MaxValueString(arr[j],arr[j+1]))  
					swap(&arr[j], &arr[j+1]); 
	}


	void Insertion_Sort(vector<int> &values){
		int i, key, j, n; 
		int *arr = &values[0];
		n = values.size();
		cout<<__func__<<"      :";
		for (i = 1; i < n; i++) 
		{ 
			key = arr[i]; 
			j = i-1; 
 
			while (j >= 0 && arr[j] > key) 
			{ 
				arr[j+1] = arr[j]; 
				j = j-1; 
			} 
			arr[j+1] = key; 
		}
	}

	void Insertion_Sort(vector<double> &values){
		int i, j, n; 
		double *arr = &values[0],key;
		n = values.size();
		cout<<__func__<<"      :";
		for (i = 1; i < n; i++) 
		{ 
			key = arr[i]; 
			j = i-1; 
 
			while (j >= 0 && arr[j] > key) 
			{ 
				arr[j+1] = arr[j]; 
				j = j-1; 
			} 
			arr[j+1] = key; 
		}
	}

	void Insertion_Sort(vector<string> &values){
		int i, j, n; 
		string *arr = &values[0],key;
		n = values.size();
		cout<<__func__<<"      :";
		for (i = 1; i < n; i++) 
		{ 
			key = arr[i]; 
			j = i-1; 
 
			while (j >= 0 && arr[j]==MaxValueString(arr[j],key)) 
			{ 
				arr[j+1] = arr[j]; 
				j = j-1; 
			} 
			arr[j+1] = key; 
		}
	}


	void Merge_Sort(vector<int> &values){
		int l,r,n; 
		int *arr = &values[0];
		l = 0;
		n = values.size();
		r = n - 1;
		cout<<__func__<<"          :";	
		mergeSort(arr, l, r); 
	}

	void Merge_Sort(vector<double> &values){
		int l,r,n; 
		double *arr = &values[0];
		l = 0;
		n = values.size();
		r = n - 1;
		cout<<__func__<<"          :";
		mergeSort(arr, l, r); 
	}

	void Merge_Sort(vector<string> &values){
		int l,r,n; 
		string *arr = &values[0];
		l = 0;
		n = values.size();
		r = n - 1;
		cout<<__func__<<"          :";	
		mergeSort(arr, l, r); 
	}


	void Quick_Sort(vector<int> &values)
	{ 
		int l,r,n; 
		int *arr = &values[0];
		l = 0;
		n = values.size();
		r = n - 1;
		cout<<__func__<<"          :";
		quickSort(arr, l, r); 

	}

	void Quick_Sort(vector<double> &values)
	{
		int l,r,n; 
		double *arr = &values[0];
		l = 0;
		n = values.size();
		r = n - 1;
		cout<<__func__<<"          :";	
		quickSort(arr, l, r); 
	}

	void Quick_Sort(vector<string> &values)
	{
	    int l,r,n; 
		string *arr = &values[0];
		l = 0;
		n = values.size();
		r = n - 1;
		cout<<__func__<<"          :";	
		quickSort(arr, l, r); 
	}


	void Heap_Sort(vector<int> &values){
	    int n; 
	    int *arr = &values[0];
		n = values.size();
		cout<<__func__<<"           :";
        heapSort(arr, n); 
	}

	void Heap_Sort(vector<double> &values){
        int n; 
        double *arr = &values[0];
		n = values.size();
		cout<<__func__<<"           :";
        heapSort(arr, n); 
	}

	void Heap_Sort(vector<string> &values){
        int  n; 
        string *arr = &values[0];
		n = values.size();
		cout<<__func__<<"           :";
        heapSort(arr, n); 

	}


	void Binary_Sort(vector<int> &values){
        int n; 
        int *arr = &values[0];
		n = values.size();
		cout<<__func__<<"         :";
        insertionSort(arr, n); 
	}

	void Binary_Sort(vector<double> &values){
        int n; 
        double *arr = &values[0];
		n = values.size();
		cout<<__func__<<"         :";
        insertionSort(arr, n); 

	}

	void Binary_Sort(vector<string> &values){
        int n; 
        string *arr = &values[0];
		n = values.size();
		cout<<__func__<<"         :";
        insertionSort(arr, n);
	}


	void Tree_Sort(vector<int> &values){
	    int n; 
        int *arr = &values[0];
		n = values.size();
		cout<<__func__<<"           :";
        treeSort(arr, n);
	}

	void Tree_Sort(vector<double> &values){
        int n; 
        double *arr = &values[0];
		n = values.size();
		cout<<__func__<<"           :";
        treeSort(arr, n);
	}

	void Tree_Sort(vector<string> &values){
        int n; 
        string *arr = &values[0];
		n = values.size();
		cout<<__func__<<"           :";
        treeSort(arr, n);
	}


	void Cartesian_Tree_Sort(vector<int> &values){
        int n; 
        int *arr = &values[0];
		n = values.size();
		cout<<__func__<<" :";
        buildCartesianTree(arr, n);
	}

	void Cartesian_Tree_Sort(vector<double> &values){
        int n; 
        double *arr = &values[0];
		n = values.size();
		cout<<__func__<<" :";
        buildCartesianTree(arr, n);
	}

	void Cartesian_Tree_Sort(vector<string> &values){
        int n; 
        string *arr = &values[0];
		n = values.size();
		cout<<__func__<<" :";
        buildCartesianTree(arr, n);

	}

}
