#ifndef SORTING_IMPLEMENTATION_H   
#define SORTING_IMPLEMENTATION_H  

#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <cstring>     

using namespace std;

void mergeSort(int arr[], int l, int r); 
void mergeSort(double arr[], int l, int r); 
void mergeSort(string arr[], int l, int r); 

void quickSort(int arr[], int low, int high);
void quickSort(double arr[], int low, int high);
void quickSort(string arr[], int low, int high);

int partition (int arr[], int low, int high); 
int partition (double arr[], int low, int high); 
int partition (string arr[], int low, int high); 

void merge(int arr[], int l, int m, int r); 
void merge(double arr[], int l, int m, int r); 
void merge(string arr[], int l, int m, int r); 

void heapify(int arr[], int n, int i);
void heapify(double arr[], int n, int i); 
void heapify(string arr[], int n, int i); 

void heapSort(int arr[], int n);
void heapSort(double arr[], int n);
void heapSort(string arr[], int n);

void insertionSort(int a[], int n);
void insertionSort(double a[], int n);
void insertionSort(string a[], int n);

int binarySearch(int a[], int item, int low, int high);
int binarySearch(double a[], double item, int low, int high);
int binarySearch(string a[], string item, int low, int high);

void treeSort(int arr[], int n);
void treeSort(double arr[], int n);
void treeSort(string arr[], int n);

void buildCartesianTree (int arr[], int n);
void buildCartesianTree (double arr[], int n);
void buildCartesianTree (string arr[], int n);

#endif
