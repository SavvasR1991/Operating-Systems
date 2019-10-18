#include "VectorFunctions.h"
#include "MostPopularValue.h"
#include "BasicFunctions.h"


//-------------------------------------PrintVectorValue----------------------------------//
void PrintVectorValue(const vector<int> &values){

    int counter = 0;
    for (std::vector<int>::const_iterator i = values.begin(); i != values.end(); ++i){
        std::cout<<counter<<"'s Value :"<<(*i)<<std::endl;
        counter++;
    }
}

void PrintVectorValue(const vector<double> &values){

    int counter = 0;
    for (std::vector<double>::const_iterator i = values.begin(); i != values.end(); ++i){
        std::cout<<counter<<"'s Value :"<<(*i)<<std::endl;
        counter++;
    }
}

void PrintVectorValue(const vector<string> &values){

    int counter = 0;
    for (std::vector<string>::const_iterator i = values.begin(); i != values.end(); ++i){
        std::cout<<counter<<"'s Value :"<<(*i)<<std::endl;
        counter++;
    }
}

//-------------------------------------MostPopularVectorValue----------------------------------//
void MostPopularVectorValue(const vector<int> &values){

    HashFindMostPolular<int> findMostPopularInt(values);
};

void MostPopularVectorValue(const vector<double> &values){

    HashFindMostPolular<double> findMostPopularDouble(values);
};

void MostPopularVectorValue(const vector<string> &values){

    HashFindMostPolular<string> findMostPopularString(values);
   
};


//-------------------------------------AverageVectorValue----------------------------------//
void AverageVectorValue(const vector<int> &values){

    double sum = 0;

    int totalVectorElements = values.size();

    for (std::vector<int>::const_iterator i = values.begin(); i != values.end(); ++i){
        sum += (*i);
    }
    
    sum = (double)sum/(double)totalVectorElements;

    std::cout<<"Avarage Value :"<<sum<<std::endl;
};

void AverageVectorValue(const vector<double> &values){

    double sum = 0;

    int totalVectorElements = values.size();

    for (std::vector<double>::const_iterator i = values.begin(); i != values.end(); ++i){
        sum += (*i);
    }
    
    sum = (double)sum/(double)totalVectorElements;

    std::cout<<"Avarage Value :"<<sum<<std::endl;
};

void AverageVectorValue(const vector<string> &values){

    HashFindMostPolular<string> findMostPopularString(values);
   
};

//-------------------------------------PrintVectorMax----------------------------------//
void PrintVectorMax(const vector<int> &values){

    int currentMaxValue = (*values.begin());

    for (std::vector<int>::const_iterator i = values.begin(); i != values.end(); ++i){
        currentMaxValue = MaxValue(currentMaxValue,(*i));
    }

    std::cout<<"Max value :"<<currentMaxValue<<std::endl;

}

void PrintVectorMax(const vector<double> &values){

    double currentMaxValue = (*values.begin());

    for (std::vector<double>::const_iterator i = values.begin(); i != values.end(); ++i){
        currentMaxValue = MaxValue(currentMaxValue,(*i));
    }

    std::cout<<"Max value :"<<currentMaxValue<<std::endl;

}

void PrintVectorMax(const vector<string> &values){

    string currentMaxValue = (*values.begin());

    int firstStringLen = currentMaxValue.length();

    int secondStringLen = (values.begin()[0]).length();

    int smallestFirstSecond = MinValue(firstStringLen,secondStringLen);

    int count = 0;

    for (std::vector<string>::const_iterator i = values.begin(); i != values.end(); ++i){
        count = 0;
        while(count <smallestFirstSecond){
            if(currentMaxValue[count]!=(*i)[count]){
                if(currentMaxValue[count] == MaxValue(currentMaxValue[count],(*i)[count])){
                    currentMaxValue = (*i);
                }
                break;
            }
            count++;
        }
    }

    std::cout<<"Max value :"<<currentMaxValue<<std::endl;
}

//-------------------------------------PrintVectorMix----------------------------------//
void PrintVectorMix(const vector<int> &values){

    int currentMaxValue = (*values.begin());

    for (std::vector<int>::const_iterator i = values.begin(); i != values.end(); ++i){
        currentMaxValue = MinValue(currentMaxValue,(*i));
    }

    std::cout<<"Mix value :"<<currentMaxValue<<std::endl;

}

void PrintVectorMix(const vector<double> &values){

    double currentMaxValue = (*values.begin());

    for (std::vector<double>::const_iterator i = values.begin(); i != values.end(); ++i){
        currentMaxValue = MinValue(currentMaxValue,(*i));
    }

    std::cout<<"Mix value :"<<currentMaxValue<<std::endl;

}

void PrintVectorMix(const vector<string> &values){

    string currentMaxValue = (*values.begin());

    int firstStringLen = currentMaxValue.length();

    int secondStringLen = (values.begin()[0]).length();

    int smallestFirstSecond = MinValue(firstStringLen,secondStringLen);

    int count = 0;

    for (std::vector<string>::const_iterator i = values.begin(); i != values.end(); ++i){
        count = 0;
        while(count <smallestFirstSecond){
            if(currentMaxValue[count]!=(*i)[count]){
                if(currentMaxValue[count] == MinValue(currentMaxValue[count],(*i)[count])){
                    currentMaxValue = (*i);
                }
                break;
            }
            count++;
        }
    }

    std::cout<<"Min value :"<<currentMaxValue<<std::endl;

}
