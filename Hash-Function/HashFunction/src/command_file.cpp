#include<iostream>
#include<cstdlib>
#include<string.h>

#include "hashingtable.h"

using namespace std;
///////////////////////////////////////////////////////////////
////             Zhtoumenes     sunarthseis                ////
//////////////////////////////////////////////////////////////

/////////////////////////////
//      insertrecord       //
/////////////////////////////
void hashtable::insertrecord(char* number,char* name,char* lastname,char* town,char* bill){
    char *p="empty";
    int index;
    index=hashing(number); //upologismos kleidiou
    if(strcmp(matrix[index]->number,p)==0){ //eisagwgh se adeia kelia
        matrix[index]->number=number;
        matrix[index]->town=town;
        matrix[index]->name=name;
        matrix[index]->bill=bill;
        matrix[index]->lastname=lastname;
        inverted_index_setting(town, matrix[index]); //eisagwgh gia to eurethrio

    }
    else{
        record* pointer;    //eisagwgh se mh adeia kelia
        pointer = matrix[index];
        record* newrecord =new record; //dhmiourgia eggrafhs kombos
        newrecord->bill=bill;
        newrecord->name=name;
        newrecord->number=number;
        newrecord->lastname=lastname;
        newrecord->town=town;
        newrecord->next=NULL;
        while(pointer->next!=NULL){
            pointer=pointer->next; //tha eisaxthei sto telos ths listas eggrafwn
        }
        pointer->next=newrecord;
        inverted_index_setting(town,newrecord); //eisagwgh gia to eurethrio
    }
    cout<<">> The number "<<number<<" has been inserted in the hash."<<endl;
}


/////////////////////////////
//       deleterecord      //
/////////////////////////////
void hashtable::deleterecord(char* number){
    char *pt="empty";
    int index;
    record* p;
    record* a;
    record* temp;
    index = hashing(number);
    if(strcmp(matrix[index]->number,pt)==0){ //den uparxei auto to noumero
        cout<<">> No data to delete "<<endl;
    }//diegrapse otan uparxei mono ena stoixeio se keli tou pinaka
    else if(strcmp(matrix[index]->number,number)==0&&matrix[index]->next==NULL){
        deletetownpointer(matrix[index]); //diagrafh gia to eurethrio
        matrix[index]->number=pt;
        matrix[index]->bill=pt;
        matrix[index]->lastname=pt;
        matrix[index]->name=pt;
        matrix[index]->town=pt;
        cout<<">> The "<<number<<" was removed from the matrix"<<endl;
    }
    else if(strcmp(matrix[index]->number,number)==0){
        p=matrix[index]; //yparxoun kialla stoixeia kai diagrafoume thn kefali
        matrix[index]=matrix[index]->next;
        deletetownpointer(p);//diagrafh gia to eurethrio
        delete p;
        cout<<">> The "<<number<<" was removed from the matrix"<<endl;
    }
    else{  //diagrafoume endiameso stoixeio
        p=matrix[index]->next;
        a=matrix[index];
        while(p!=NULL&&p->number!=number){//bres pou einai
            a=p;
            p=p->next;
        }
        if(p==NULL) //den uparxei h eggrafh
            cout<<">> No data to delete "<<endl;
        else{
            temp = p;
            p=p->next;
            a->next = p;
            deletetownpointer(temp);//diagrafh gia to eurethrio
            delete temp;
            cout<<">> The "<<number<<" was removed from the matrix"<<endl;
        }
    }
}

/////////////////////////////
//          query          //
/////////////////////////////
void hashtable::query(char *number){
    int index;
    index = hashing(number);    //bres to kleidh ths polhs
    if(strcmp(matrix[index]->number,number)!=0){ //den uparxei h polh
        cout<<">> No record with the number : "<<number<<endl;
    }
    else{
        while(strcmp(matrix[index]->number,number)!=0){
            matrix[index]=matrix[index]->next;
        } //anazhthse thn polh sthn lista eggrafwn
        cout<<">>For the number :"<<matrix[index]->number<<" the data of the costumer is :"<<endl;
        cout<<">>->Name     : "<<matrix[index]->name<<endl;
        cout<<">>->Lastname : "<<matrix[index]->lastname<<endl;
        cout<<">>->Town     : "<<matrix[index]->town<<endl;
        cout<<">>->Bill     : "<<matrix[index]->bill<<" euro "<<endl;
    }
}

/////////////////////////////
//       population        //
/////////////////////////////
void hashtable::population(char *town){
    nodeptr runner_town;
    runner_town=head;
    while(strcmp(runner_town->town,town)!=0&&runner_town->next!=NULL){
        runner_town=runner_town->next;  //bres thn polh sto eurethrio
    }
    if(strcmp(runner_town->town,town)==0) //an thn brhke ektupwse ton plhthhsmo
        cout<<">> The city of "<<runner_town->town<<" has "<<runner_town->total<<" costumers."<<endl;
    else{
        cout<<">> No such town in the data of the database..."<<endl;
    }
}

/////////////////////////////
//          top            //
/////////////////////////////
void hashtable::top(int k){

    int i;
    int j;
    int stop;
    int total_towns;
    total_towns=0;
    curr=head;
    while(curr!=NULL){
        curr=curr->next;
        total_towns++;
    }
    int check[total_towns];
    nodeptr k_index;
    nodeptr pointer;
    nodeptr target;
    k_index=head;
    for(i=0;i<total_towns;i++){
        check[i]=0;
    }
    target=head;
    for(i=1;i<=k;i++){
            stop=0;
        if(k_index==NULL){
            cout<<">> For k = "<<k<<" is to big for the number of the towns in the struct!"<<endl;
            break;
        }
        pointer=head;
        j=0;
        while(pointer!=NULL){
            if(target->total<=pointer->total&&check[j]==0){
                target=pointer;
                stop=j;
            }
            j++;
            pointer=pointer->next;
        }
        check[stop]=1;
        cout<<">> "<<i<<"o town is : "<<target->town<<" with population "<<target->total<<" costumers!"<<endl;
        target=head;
        for(j=0;j<total_towns;j++){
            if(check[j]!=0)
                target=target->next;
            else
                break;
        }
        k_index=k_index->next;
    }
}

/////////////////////////////
//           sum           //
/////////////////////////////
void hashtable::sum(char *town){
    nodeptr runner_town;
    nodeptr_towns runner_town_point;
    int total_bill=0;
    int check=0;
    runner_town=head;
    while(runner_town!=NULL){   //sarwse to eurethrio mexri na breis thn polh
        if(strcmp(runner_town->town,town)==0){
            check=1;
            break;
        }
        runner_town=runner_town->next;

    }
    if(check==0)                    //den uparxei h polh sthn domh
        cout<<">> No such town in the data of the database..."<<endl;
    else{                           //uparxei h polh sthn domh
        runner_town_point=runner_town->node_towns;
        while(runner_town_point!=NULL){         //sarwse olous tous pelates tis polhs
            total_bill=total_bill + atoi(runner_town_point->target->bill);
            runner_town_point=runner_town_point->next;      //athroise ta sunolika xreah
        }

        cout<<">> The city of "<<town<<" has total bill : "<<total_bill<<" euros."<<endl;
    }
}

/////////////////////////////
//        findtown         //
/////////////////////////////
void hashtable::findtown(char *town,int l){

    nodeptr point;
    point=head;
    int che=0;
    while(point!=NULL){
        if(strcmp(point->town,town)==0){
            che=1;
            break;
        }
        point=point->next;
    }
    if(che==0)
        cout<<">> The town : "<<town<<" does not exist in the struct!"<<endl;
    else{
        if(l>point->total)
            cout<<">> For l = "<<l<<" is to big for the costumer of the city "<<town<<endl;
        else{
            int i;
            int j;
            int stop;
            int total_towns=0;
            nodeptr_towns pointer;
            nodeptr_towns target;
            pointer=head->node_towns;
            while(pointer!=NULL){
                pointer=pointer->next;
                total_towns++;
            }
            int check[total_towns];
            for(i=0;i<total_towns;i++){
                check[i]=0;
            }
            target=point->node_towns;
            for(i=1;i<=l;i++){
                stop=0;
                pointer=point->node_towns;
                j=0;
                while(pointer!=NULL){
                    if(atoi(target->target->bill)<=atoi(pointer->target->bill)&&check[j]==0){
                        target=pointer;
                    stop=j;
                    }
                    j++;
                    pointer=pointer->next;
                }
                check[stop]=1;
                cout<<">> "<<i<<"o costumer is : "<<target->target->name<<" "<<target->target->lastname<<" with bill : "<<target->target->bill<<" euros"<<endl;
                target=point->node_towns;
                for(j=0;j<total_towns;j++){
                    if(check[j]!=0)
                        target=target->next;
                    else
                        break;
                }
            }
        }
    }
}

/////////////////////////////
//      findtopspender     //
/////////////////////////////
void hashtable::findtopspender(){
    int total_towns=0;
    if(head!=NULL){
        curr=head;
        while(curr!=NULL){
            curr=curr->next;
            total_towns++;
        }
        int check[total_towns];
        int k_max=0;
        int l_max=0;
        int i;
        int j;
        int stop;
        nodeptr pointer;
        nodeptr target;
        nodeptr_towns target_town;
        nodeptr_towns pointer_town;
        nodeptr_towns finale,finale2;
        curr=head;
        target=head;

        for(i=0;i<total_towns;i++){
            check[i]=0;
        }
        i=1;
        while(curr!=NULL){
            pointer=head;
            j=0;
            while(pointer!=NULL){
                k_max=0;
                l_max=0;
                target_town=target->node_towns;
                pointer_town=pointer->node_towns;
                finale=target_town;
                finale2=pointer_town;
                while(target_town!=NULL){
                    if(atoi(target_town->target->bill)>=k_max){
                        k_max=atoi(target_town->target->bill);
                        finale=target_town;
                    }
                    target_town=target_town->next;
                }
                while(pointer_town!=NULL){
                    if(atoi(pointer_town->target->bill)>=l_max){
                        l_max=atoi(pointer_town->target->bill);
                        finale2=pointer_town;
                    }
                    pointer_town=pointer_town->next;
                }
                if(l_max>=k_max&&check[j]==0){
                    target=pointer;
                    finale=finale2;
                    stop=j;
                }
                j++;
                pointer=pointer->next;
            }
            check[stop]=1;
            cout<<">> "<<i<<"o town ,bill account ["<<finale->target->bill<<"] is : "<<target->town<<" with the costumer "<<finale->target->lastname<<endl;
            target=head;
            for(j=0;j<total_towns;j++){
                if(check[j]!=0)
                    target=target->next;
                else
                    break;
            }

            curr=curr->next;
            i++;
        }
    }
    else
        cout<<">> No data in the struct.."<<endl;

}

/////////////////////////////
//         min_max         //
/////////////////////////////
void hashtable::min_max(){
    nodeptr_towns k;
    int min_num=999999999;  //arxikopoihsh metablhtwn gia min,max
    int max_num=-1;
    curr=head;
    while(curr!=NULL){      //sarwse to eurethrio
        k=curr->node_towns;
        while(k!=NULL){     //sarwse kathe sundromhth
            if(atoi(k->target->number)>max_num){    //sugkrine gia to megisto
                max_num=atoi(k->target->number);
            }
            if(atoi(k->target->number)<min_num){    //sugkrine gia to elaxisto
                min_num=atoi(k->target->number);
            }
            k=k->next;
        }
        curr=curr->next;
    }
    if(min_num==999999999&&max_num==-1){            //adeia h domh
        cout<<">> No data to the struct.. "<<endl;
    }
    else{
        cout<<">>Maximun number by value is : "<<max_num<<endl;
        cout<<">>Minimun number by value is : "<<min_num<<endl;
    }
}

/////////////////////////////
//          exit           //
/////////////////////////////
void hashtable::exit(){
    int i;
    nodeptr_towns tempo,tempo2;
    curr=head; //deikse sthn arxi tou eurethriou
    while(curr!=NULL){ //sarwse to eurethrio
        tempo=curr->node_towns;
        while(tempo!=NULL){ //diegrapse mia mia tis eggrafes
            tempo2=tempo;
            delete tempo2;
            tempo=tempo->next;
        }
        temp=curr;
        curr=curr->next;
        delete temp; //diegrapse kai ton kombo tou eurethriou

    }
    for(i=0;i<dimension;i++){
        delete matrix[i]; //diegrapse ton pinaka
    }
}




