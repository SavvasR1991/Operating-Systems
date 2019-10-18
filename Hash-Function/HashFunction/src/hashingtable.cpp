#include<iostream>

#include<cstdlib>
#include<string.h>

#include "hashingtable.h"


using namespace std;
///////////////////////////////////////////////////////////////
////Bohthikikes sunarthseis gia ton pinaka katakermatismou ////
//////////////////////////////////////////////////////////////

/////////////////////////////
//      sethashmatrix      //
/////////////////////////////

void hashtable::sethashmatrix(){
    int i;
   // record *matrix[dimension];
    matrix=new record* [dimension];  //dhmiourgia pinaka
    char *p="empty";                //deikths gia na doume an uparxoun stoixeia mesa
    for(i=0;i<dimension;i++){       //arxikopoihsh tou pinaka se keno
        matrix[i] =new record;
        matrix[i]->number=p;
        matrix[i]->town=p;
        matrix[i]->name=p;
        matrix[i]->bill=p;
        matrix[i]->lastname=p;
        matrix[i]->next=NULL;
    }
    head=NULL;      //arxikopoihsh deiktwn tou eurethriou
    temp=NULL;
    curr=NULL;
}

/////////////////////////////
//       hashing           //
/////////////////////////////
int hashtable::hashing(char *variable){
    //sunarthsh katakermatismoy
    int index;
    int temp=0;
    int length;
    int templength;
    int i;

    length=strlen(variable); //mikos tou noumerou
    templength=length;

    for(i=0;i<length;i++){  //ylopoihsh ths sunarthseis katakermatismou
        temp = (temp +(int)variable[i])*templength;
        templength--;
    }

    index = temp%dimension;
    return index;
};

/////////////////////////////
//      setmatrixdim       //
/////////////////////////////
void hashtable::setmatrixdim(int dimen){
    //thetei tis diastaseis tou pinaka
    dimension=dimen;

}
/////////////////////////////
//      bucketcounter      //
/////////////////////////////
int hashtable::bucketcounter(int a){
    //epistrefi ton arithmo twn eggrafwn se kathe keli tou pinaka
    int coun=0;
    if(matrix[a]->number=="empty") //adeio keli
        return coun;
    else{
        coun++;
        record* p=matrix[a];
        while(p->next!=NULL){

            coun++;
            p=p->next;
        }
        return coun;
    }

}

void hashtable::printtable(){

    int number;
    for(int i=0;i<dimension;i++){
        if(matrix[i]!=NULL){
        number=bucketcounter(i);
        cout<<">> ---------\n";
        cout<<">> index = "<<i<<endl;
        cout<<">> Number : "<<matrix[i]->number<<endl;
        cout<<">> Name : "<<matrix[i]->name<<endl;
        cout<<">> Lastname : "<<matrix[i]->lastname<<endl;
        cout<<">> Bill : "<<matrix[i]->bill<<endl;
        cout<<">> Town : "<<matrix[i]->town<<endl;
        cout<<">> Number of items : "<<number<<endl;
        cout<<">> ---------\n";
        }
    }

}
