#include "SortingImplementation.h"
#include "BasicFunctions.h"
#include "Tree.h"
#include "CartesianTree.h"

/*-------------------mergeSort-----------------*/
void mergeSort(int arr[], int l, int r) 
{ 
    if (l < r) 
    { 
        int m = l+(r-l)/2; 
        mergeSort(arr, l, m); 
        mergeSort(arr, m+1, r); 
        merge(arr, l, m, r); 
    } 
} 

void mergeSort(double arr[], int l, int r) 
{ 
    if (l < r) 
    { 
        int m = l+(r-l)/2; 
        mergeSort(arr, l, m); 
        mergeSort(arr, m+1, r); 
        merge(arr, l, m, r); 
    } 
} 

void mergeSort(string arr[], int l, int r) 
{ 
    if (l < r) 
    { 
        int m = l+(r-l)/2; 
        mergeSort(arr, l, m); 
        mergeSort(arr, m+1, r); 
        merge(arr, l, m, r); 
    } 
} 
/*---------------------------------------------*/

/*-----------------quickSort-------------------*/
void quickSort(int arr[], int low, int high) 
{ 
    if (low < high) 
    { 
        int pi = partition(arr, low, high); 
        quickSort(arr, low, pi - 1); 
        quickSort(arr, pi + 1, high); 
    } 
} 

void quickSort(double arr[], int low, int high) 
{ 
    if (low < high) 
    { 
        int pi = partition(arr, low, high); 
        quickSort(arr, low, pi - 1); 
        quickSort(arr, pi + 1, high); 
    } 
} 

void quickSort(string arr[], int low, int high) 
{ 
    if (low < high) 
    { 
        int pi = partition(arr, low, high); 
        quickSort(arr, low, pi - 1); 
        quickSort(arr, pi + 1, high); 
    } 
} 
/*---------------------------------------------*/

/*-------------------partition-----------------*/
int partition (int arr[], int low, int high) 
{ 
    int pivot = arr[high];     
    int i = (low - 1);   
  
    for (int j = low; j <= high- 1; j++) 
    { 
        if (arr[j] <= pivot) 
        { 
            i++;   
            swap(&arr[i], &arr[j]); 
        } 
    } 
    swap(&arr[i + 1], &arr[high]); 
    return (i + 1); 
} 

int partition (double arr[], int low, int high) 
{ 
    double pivot = arr[high];    
    int i = (low - 1);   
  
    for (int j = low; j <= high- 1; j++) 
    { 
        if (arr[j] <= pivot) 
        { 
            i++;   
            swap(&arr[i], &arr[j]); 
        } 
    } 
    swap(&arr[i + 1], &arr[high]); 
    return (i + 1); 
} 

int partition (string arr[], int low, int high) 
{ 
    string pivot = arr[high];    
    int i = (low - 1);   
  
    for (int j = low; j <= high- 1; j++) 
    { 
        if (pivot == MaxValueString(pivot,arr[j])) 
        { 
            i++;    
            swap(&arr[i], &arr[j]); 
        } 
    } 
    swap(&arr[i + 1], &arr[high]); 
    return (i + 1); 
} 
/*---------------------------------------------*/


/*-------------------merge---------------------*/
void merge(int arr[], int l, int m, int r) 
{ 
    int i, j, k; 
    int n1 = m - l + 1; 
    int n2 =  r - m; 
    int L[n1], R[n2]; 
  
    for (i = 0; i < n1; i++) 
        L[i] = arr[l + i]; 
    for (j = 0; j < n2; j++) 
        R[j] = arr[m + 1+ j]; 
    i = 0;  
    j = 0;  
    k = l;  
    while (i < n1 && j < n2) 
    { 
        if (L[i] <= R[j]) 
        { 
            arr[k] = L[i]; 
            i++; 
        } 
        else
        { 
            arr[k] = R[j]; 
            j++; 
        } 
        k++; 
    } 
    while (i < n1) 
    { 
        arr[k] = L[i]; 
        i++; 
        k++; 
    } 
    while (j < n2) 
    { 
        arr[k] = R[j]; 
        j++; 
        k++; 
    } 
} 

void merge(double arr[], int l, int m, int r) 
{ 
    int i, j, k; 
    int n1 = m - l + 1; 
    int n2 =  r - m; 
    double L[n1], R[n2]; 
  
    for (i = 0; i < n1; i++) 
        L[i] = arr[l + i]; 
    for (j = 0; j < n2; j++) 
        R[j] = arr[m + 1+ j]; 
    i = 0;  
    j = 0;  
    k = l;  
    while (i < n1 && j < n2) 
    { 
        if (L[i] <= R[j]) 
        { 
            arr[k] = L[i]; 
            i++; 
        } 
        else
        { 
            arr[k] = R[j]; 
            j++; 
        } 
        k++; 
    } 
    while (i < n1) 
    { 
        arr[k] = L[i]; 
        i++; 
        k++; 
    } 
    while (j < n2) 
    { 
        arr[k] = R[j]; 
        j++; 
        k++; 
    } 
} 

void merge(string arr[], int l, int m, int r) 
{ 
    int i, j, k; 
    int n1 = m - l + 1; 
    int n2 =  r - m; 
    string L[n1], R[n2]; 
  
    for (i = 0; i < n1; i++) 
        L[i] = arr[l + i]; 
    for (j = 0; j < n2; j++) 
        R[j] = arr[m + 1+ j]; 
    i = 0;  
    j = 0;  
    k = l;  
    while (i < n1 && j < n2) 
    { 
        if (R[j] == MaxValueString(R[j],L[i])) 
        { 
            arr[k] = L[i]; 
            i++; 
        } 
        else
        { 
            arr[k] = R[j]; 
            j++; 
        } 
        k++; 
    } 
    while (i < n1) 
    { 
        arr[k] = L[i]; 
        i++; 
        k++; 
    } 
    while (j < n2) 
    { 
        arr[k] = R[j]; 
        j++; 
        k++; 
    } 
} 
/*---------------------------------------------*/


/*-------------------heapify-------------------*/
void heapify(int arr[], int n, int i) 
{ 
    int largest = i;  
    int l = 2*i + 1;  
    int r = 2*i + 2;  
  
    if (l < n && arr[l] > arr[largest]) 
        largest = l; 
    if (r < n && arr[r] > arr[largest]) 
        largest = r; 
    if (largest != i) 
    { 
        swap(arr[i], arr[largest]); 
        heapify(arr, n, largest); 
    } 
} 

void heapify(double arr[], int n, int i) 
{ 
    int largest = i;  
    int l = 2*i + 1;  
    int r = 2*i + 2;  
  
    if (l < n && arr[l] > arr[largest]) 
        largest = l; 
    if (r < n && arr[r] > arr[largest]) 
        largest = r; 
    if (largest != i) 
    { 
        swap(arr[i], arr[largest]); 
        heapify(arr, n, largest); 
    } 
} 

void heapify(string arr[], int n, int i) 
{ 
    int largest = i; 
    int l = 2*i + 1;  
    int r = 2*i + 2;  
  
    if (l < n && (arr[l] == MaxValueString(arr[l],arr[largest]))) 
        largest = l; 
    if (r < n && (arr[r] == MaxValueString(arr[r],arr[largest]))) 
        largest = r; 
    if (largest != i) 
    { 
        swap(arr[i], arr[largest]); 
        heapify(arr, n, largest); 
    } 
} 
/*---------------------------------------------*/

/*------------------heapSort-------------------*/
void heapSort(int arr[], int n) 
{ 
    for (int i = n / 2 - 1; i >= 0; i--) 
        heapify(arr, n, i); 
  
    for (int i=n-1; i>=0; i--) 
    { 
        swap(arr[0], arr[i]); 
 
        heapify(arr, i, 0); 
    } 
}

void heapSort(double arr[], int n) 
{ 
    for (int i = n / 2 - 1; i >= 0; i--) 
        heapify(arr, n, i); 
  
    for (int i=n-1; i>=0; i--) 
    { 
        swap(arr[0], arr[i]); 
 
        heapify(arr, i, 0); 
    } 
}

void heapSort(string arr[], int n) 
{ 
    for (int i = n / 2 - 1; i >= 0; i--) 
        heapify(arr, n, i); 
  
    for (int i=n-1; i>=0; i--) 
    { 
        swap(arr[0], arr[i]); 
 
        heapify(arr, i, 0); 
    } 
}
/*---------------------------------------------*/

/*------------------binarySearch---------------*/
int binarySearch(int a[], int item, int low, int high) 
{ 
    if (high <= low) 
        return (item > a[low])?  (low + 1): low; 
  
    int mid = (low + high)/2; 
  
    if(item == a[mid]) 
        return mid+1; 
  
    if(item > a[mid]) 
        return binarySearch(a, item, mid+1, high); 
    return binarySearch(a, item, low, mid-1); 
} 

int binarySearch(double a[], double item, int low, int high) 
{ 
    if (high <= low) 
        return (item > a[low])?  (low + 1): low; 
  
    int mid = (low + high)/2; 
  
    if(item == a[mid]) 
        return mid+1; 
  
    if(item > a[mid]) 
        return binarySearch(a, item, mid+1, high); 
    return binarySearch(a, item, low, mid-1); 
} 

int binarySearch(string a[], string item, int low, int high) 
{ 
    if (high <= low) 
        return (item == MaxValueString(item,a[low]))?  (low + 1): low; 
  
    int mid = (low + high)/2; 
  
    if(item == a[mid]) 
        return mid+1; 
  
    if(item == MaxValueString(item,a[mid])) 
        return binarySearch(a, item, mid+1, high); 
    return binarySearch(a, item, low, mid-1); 
} 
/*---------------------------------------------*/

/*--------------------insertionSort-------------------*/
void insertionSort(int a[], int n) 
{ 
    int i, loc, j, k, selected; 
  
    for (i = 1; i < n; ++i) 
    { 
        j = i - 1; 
        selected = a[i]; 
        loc = binarySearch(a, selected, 0, j); 
        while (j >= loc) 
        { 
            a[j+1] = a[j]; 
            j--; 
        } 
        a[j+1] = selected; 
    } 
} 

void insertionSort(double a[], int n) 
{ 
    int i, loc, j, k, selected; 
  
    for (i = 1; i < n; ++i) 
    { 
        j = i - 1; 
        selected = a[i]; 
        loc = binarySearch(a, selected, 0, j); 
        while (j >= loc) 
        { 
            a[j+1] = a[j]; 
            j--; 
        } 
        a[j+1] = selected; 
    } 
} 

void insertionSort(string a[], int n) 
{ 
    int i, loc, j, k; 
    string selected;
    for (i = 1; i < n; ++i) 
    { 
        j = i - 1; 
        selected = a[i]; 
        loc = binarySearch(a, selected, 0, j); 
        while (j >= loc) 
        { 
            a[j+1] = a[j]; 
            j--; 
        } 
        a[j+1] = selected; 
    } 
} 
/*----------------------------------------------------*/

/*-----------------------treeSort---------------------*/
void treeSort(int arr[], int n) 
{ 
    struct Node<int> *root = NULL; 
  
    root = insert(root, arr[0]); 
    for (int i=1; i<n; i++) 
        insert(root, arr[i]); 
  
    int i = 0; 
    storeSorted(root, arr, i); 
} 

void treeSort(double arr[], int n) 
{ 
    struct Node<double> *root = NULL; 
  
    root = insert(root, arr[0]); 
    for (int i=1; i<n; i++) 
        insert(root, arr[i]); 
  
    int i = 0; 
    storeSorted(root, arr, i);
} 

void treeSort(string arr[], int n) 
{ 
    struct Node<string> *root = NULL; 
  
    root = insert(root, arr[0]); 
    for (int i=1; i<n; i++) 
        insert(root, arr[i]); 
  
    int i = 0; 
    storeSorted(root, arr, i);
} 
/*----------------------------------------------------*/

/*-----------------------buildCartesianTree---------------------*/

void buildCartesianTree (int arr[], int n) 
{  
    int parent[n],leftchild[n],rightchild[n]; 
  
    memset(parent, -1, sizeof(parent)); 
    memset(leftchild, -1, sizeof(leftchild)); 
    memset(rightchild, -1, sizeof(rightchild)); 
  
    int root = 0, last; 
 
    for (int i=1; i<=n-1; i++) 
    { 
        last = i-1; 
        rightchild[i] = -1; 
  
        while (arr[last] <= arr[i] && last != root) 
            last = parent[last]; 
  
        if (arr[last] <= arr[i]) 
        { 
            parent[root] = i; 
            leftchild[i] = root; 
            root = i; 
        } 
        else if (rightchild[last] == -1) 
        { 
            rightchild[last] = i; 
            parent[i] = last; 
            leftchild[i] = -1; 
        } 
        else
        { 
            parent[rightchild[last]] = i; 
            leftchild[i] = rightchild[last]; 
            rightchild[last] = i; 
            parent[i] = last; 
        } 
  
    } 
    parent[root] = -1; 
    
    CNode<int>* tree = (buildCartesianTreeUtil (root, arr, parent,leftchild, rightchild));
    
    //printInorder(tree); 

   
} 

void buildCartesianTree (double arr[], int n) 
{  
    int parent[n],leftchild[n],rightchild[n]; 
  
    memset(parent, -1, sizeof(parent)); 
    memset(leftchild, -1, sizeof(leftchild)); 
    memset(rightchild, -1, sizeof(rightchild)); 
  
    int root = 0, last; 
 
    for (int i=1; i<=n-1; i++) 
    { 
        last = i-1; 
        rightchild[i] = -1; 
  
        while (arr[last] <= arr[i] && last != root) 
            last = parent[last]; 
  
        if (arr[last] <= arr[i]) 
        { 
            parent[root] = i; 
            leftchild[i] = root; 
            root = i; 
        } 
        else if (rightchild[last] == -1) 
        { 
            rightchild[last] = i; 
            parent[i] = last; 
            leftchild[i] = -1; 
        } 
        else
        { 
            parent[rightchild[last]] = i; 
            leftchild[i] = rightchild[last]; 
            rightchild[last] = i; 
            parent[i] = last; 
        } 
  
    } 
    parent[root] = -1;  
    
} 

void buildCartesianTree (string arr[], int n) 
{  
    int parent[n],leftchild[n],rightchild[n]; 
  
    memset(parent, -1, sizeof(parent)); 
    memset(leftchild, -1, sizeof(leftchild)); 
    memset(rightchild, -1, sizeof(rightchild)); 
  
    int root = 0, last; 
 
    for (int i=1; i<=n-1; i++) 
    { 
        last = i-1; 
        rightchild[i] = -1; 
  
        while (arr[last] <= arr[i] && last != root) 
            last = parent[last]; 
  
        if (arr[last] <= arr[i]) 
        { 
            parent[root] = i; 
            leftchild[i] = root; 
            root = i; 
        } 
        else if (rightchild[last] == -1) 
        { 
            rightchild[last] = i; 
            parent[i] = last; 
            leftchild[i] = -1; 
        } 
        else
        { 
            parent[rightchild[last]] = i; 
            leftchild[i] = rightchild[last]; 
            rightchild[last] = i; 
            parent[i] = last; 
        } 
  
    } 
    parent[root] = -1;  
} 

/*-------------------------------------------------------------*/


