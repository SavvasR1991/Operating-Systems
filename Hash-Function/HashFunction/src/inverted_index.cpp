#include<iostream>
#include<cstdlib>
#include<string.h>

#include "hashingtable.h"

using namespace std;

///////////////////////////////////////////////////////////////
////    Bohthikikes sunarthseis gia to eurethrio           ////
//////////////////////////////////////////////////////////////

/////////////////////////////
// inverted_index_setting  //
/////////////////////////////
void hashtable::inverted_index_setting(char *town,record *index){
    //dhmiourgei tous kombous tou eurethriou kai tin lista deiktwn se eggrafes
    int check=0;
    nodeptr n = new index_list;
    nodeptr_towns t = new index_list_towns;
    nodeptr_towns ptrtowns=NULL;
    t->next=NULL;
    t->target=NULL;
    n->next = NULL;
    n->town=town;
    if(head!=NULL){                   //an den einai h prwth eisodos sto eurethrio
        if(strcmp(n->town,head->town)<0||strcmp(n->town,head->town)==0){ //an h eisodos prepei na ginei sthn kefali tis listas
            if(strcmp(n->town,head->town)==0){  //an einai h idia polh me thn kefalh kane eisodo twn sunfromhtwn sthn kefalh
                ptrtowns=head->node_towns;
                while(ptrtowns->next!=NULL){
                    ptrtowns=ptrtowns->next;
                }
                ptrtowns->next=t;   //ruthmise tis katallhles parametrous
                t->target=index;
                head->total++;
            }
            else{       //an prohghte h  polh me thn kefalh
                n->next=head;   //kane thn polh kefalh
                head=n;
                n->node_towns=t;
                t->target=index;
                n->total=1;
            }
        }
        else{                   //an oxi sthn kefalh
            curr=head;          //deixnei sthn arxh
            temp=head->next;    //deixnei ston amesws epomeno
                while(curr->next!=NULL){  //sarwwse to eurethrio
                    if(strcmp(temp->town,town)>0||strcmp(temp->town,town)==0){//ama brethei h thesh
                        if(strcmp(temp->town,town)==0){    //an einai idia h polh tha auksithoun oi pelates meta
                            check=1;
                            break;
                        }
                        else{
                            curr->next=n; //an proighte rithmise katallila
                            n->next=temp;
                            break;
                        }
                    }
                    curr = curr->next;
                    temp=temp->next; //epomenoi komboi
                    if(temp==NULL){ //ftasame sto telos tou eurethriou
                        curr->next=n;   //balto sto telos ton kombo
                        n->next=NULL;
                        check=2;
                        n->total=1;
                        t->target=index;
                        n->node_towns=t;
                        break;
                    }
                    if(strcmp(temp->town,town)==0){
                        check=1;
                        break;
                    }
                }
                if(check==0){ //bale ton kombo diaforetikh polh
                    curr->next = n;
                    n->total=1;
                    n->node_towns=t;
                    t->target=index;
                }
                else if(check==1){ //idia polh
                    ptrtowns=temp->node_towns;
                    while(ptrtowns->next!=NULL){
                        ptrtowns=ptrtowns->next;
                    }
                    ptrtowns->next=t;
                    t->target=index;
                    temp->total++;
                }
       }
    }
    else{           //an  einai h prwth eisodos sto eurethrio
        head = n;   //arxikopoihse ton prwto kombo
        head->node_towns=t;
        n->total=1;
        t->target=index;
    }
}

/////////////////////////////
//  deletetownpointer      //
/////////////////////////////
void hashtable::deletetownpointer(record *d){
    nodeptr delnode=NULL;
    nodeptr_towns tempo,tempo2;
    nodeptr_towns tempohead;
    nodeptr_towns deltempo;
    curr=head;
    while(curr!=NULL&&strcmp(curr->town,d->town)!=0){
        curr=curr->next;  //briskw thn polh pros diagrafh
    }
    if(curr!=NULL){
        if(curr==head){ // einai h kefalh
            tempo=head->node_towns;
            tempohead=head->node_towns;
            while(tempo!=NULL&&strcmp(tempo->target->number,d->number)!=0){
                tempo2=tempo;
                tempo=tempo->next;
            }
            if(tempo==tempohead){
                head->node_towns=tempohead->next;
                delete tempo;
                head->total--;
            }
            else{
                deltempo = tempo;
                tempo=tempo->next;
                tempo2->next=tempo;
                delete deltempo;
                head->total--;
            }
            if(head->total<=0){
                head=head->next;
                delete curr;
            }
        }
        else{   //den einai h kefalh
            tempo=curr->node_towns;
            tempohead=curr->node_towns;
            while(tempo!=NULL&&strcmp(tempo->target->number,d->number)!=0){
                tempo2=tempo;
                tempo=tempo->next;
            }
            if(tempo==tempohead){
                curr->node_towns=tempohead->next;
                delete tempo;
                curr->total--;
            }
            else{
                deltempo = tempo;
                tempo=tempo->next;
                tempo2->next=tempo;
                delete deltempo;
                curr->total--;
            }
            if(curr->total<=0){
                curr=head;
                temp=head;
                while(curr!=NULL&&strcmp(curr->town,d->town)!=0){
                    temp=curr;
                    curr=curr->next;
                }
                delnode=curr;
                curr=curr->next;
                temp->next=curr;
                delete delnode;
            }
        }
    }
}

//bohthitikh sunarthsh ektupwnei to eurethirio
void hashtable::pr(){
    curr=head;
    nodeptr_towns k;
    if(curr==NULL){
        cout<<">> No data in the struct!\n";
    }
    else{
        cout<<" PRINTING INVERTED INDEX...\n>>\n";
        while(curr!=NULL){
            cout<<">> <=> City  "<<curr->town<<endl;
            k=curr->node_towns;
            while(k!=NULL){
                cout<<">> -------> "<<k->target->name<<" "<<k->target->lastname<<" "<<k->target->number<<endl;
                k=k->next;
            }
            curr=curr->next;
        }
    }
    cout<<">> ";
}




