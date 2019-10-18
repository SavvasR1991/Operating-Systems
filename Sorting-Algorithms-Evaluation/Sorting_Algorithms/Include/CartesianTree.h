#ifndef CARTESIAN_TREE_H   
#define CARTESIAN_TREE_H  

#include <iostream>
#include <vector>
#include <string>
#include "BasicFunctions.h"

using namespace std;

template<typename T>
struct CNode 
{ 
    T data; 
    CNode<T> *left, *right; 
}; 
  
template<typename T>
void printInorder (CNode<T>* CNode) 
{ 
    if (CNode == NULL) 
        return; 
    printInorder (CNode->left); 
    cout << CNode->data << " "; 
    printInorder (CNode->right); 
} 

template<typename T>
CNode<T> * buildCartesianTreeUtil (T root, T arr[], 
          T parent[], T leftchild[], T rightchild[]) 
{ 
    if (root == -1) 
        return NULL; 
  
    CNode<T> *temp = new CNode<T>; 
    temp->data = arr[root] ; 
    
    temp->left = buildCartesianTreeUtil( leftchild[root], 
                    arr, parent, leftchild, rightchild ); 
    temp->right = buildCartesianTreeUtil( rightchild[root], 
                    arr, parent, leftchild, rightchild ); 
  
    return temp ; 
} 

#endif
