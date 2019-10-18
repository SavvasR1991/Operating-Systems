#ifndef MOST_POPULAR_VALUE_H   
#define MOST_POPULAR_VALUE_H  

#include <vector>
#include <string>
#include <sstream>
#include <iomanip>

#include "BasicFunctions.h"
#include "ConvertToString.h"
#include "MD5.h"


using namespace std;

template<class T1>
struct HashTable{
    int *HashTableQuantity;
    string *HashTableValues;
};

template<class T>
class HashFindMostPolular {

    private: 
        HashTable<T> Hashtable;    
        int HashTableSize;

        vector<T> HashTableValues;

        void HashTableInit(const vector<T> values){

            HashTableSize = values.size()*values.size();
            Hashtable.HashTableQuantity = new int[HashTableSize];
            Hashtable.HashTableValues = new string[HashTableSize];

            setArrayToZero(Hashtable.HashTableQuantity,HashTableSize);
      
            HashTableValues=values;    
        }

        void HashExecution(){
        
            string h;

            int maxQuantity = 0;

            int possition = 0;

            if(!HashTableValues.empty()){
                for (typename std::vector<T>::const_iterator i = HashTableValues.begin(); i != HashTableValues.end(); ++i){
                    h = md5(*i);
                    possition = moduloHexCalculation(h,HashTableSize);
                    if(Hashtable.HashTableQuantity[possition] == 0){
                        Hashtable.HashTableValues[possition] = HashTableValuesFill(*i);
                    }
                    
                    Hashtable.HashTableQuantity[possition]++;
                }

                maxQuantity = maxArrayPossition(Hashtable.HashTableQuantity,HashTableSize);

                cout<<"Most popular : "<<Hashtable.HashTableValues[maxQuantity]<<endl;
            }
        }

    public:

        HashFindMostPolular(const vector<T> values){
            
            HashTableInit(values);

            HashExecution();
        }
        
        ~HashFindMostPolular(){
            delete(Hashtable.HashTableQuantity);
            HashTableValues.clear();
        }     
};



#endif
