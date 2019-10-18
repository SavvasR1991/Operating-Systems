#ifndef TREE_H   
#define TREE_H  

#include <iostream>
#include <vector>
#include <string>
#include "BasicFunctions.h"

using namespace std;

template<typename T>
struct Node 
{ 
    T key; 
    struct Node<T> *left, *right; 
}; 
  
template<typename T>
struct Node<T> *newNode(T item) 
{ 
    struct Node<T> *temp = new Node<T>; 
    temp->key = item; 
    temp->left = temp->right = NULL; 
    return temp; 
} 
  
template<typename T>
void storeSorted(Node<T> *root, T arr[], int &i) 
{ 
    if (root != NULL) 
    { 
        storeSorted(root->left, arr, i); 
        arr[i++] = root->key; 
        storeSorted(root->right, arr, i); 
    } 
} 

template<typename T>
Node<T>* insert(Node<T>* node, T key) 
{ 
    if (node == NULL) return newNode(key); 
  
    if (node->key == FindMax(key,node->key)) 
        node->left  = insert(node->left, key); 
    else if (key == FindMax(key,node->key)) 
        node->right = insert(node->right, key); 
    else
        node->left  = insert(node->left, key);
    return node; 
}

#endif
