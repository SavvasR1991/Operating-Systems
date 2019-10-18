#include "main_functions.h"

void print_comm_line_description_message()      //print message for wrong message
{
    cout<<">>Wrong input from commant list :"<< endl;
    cout<<">>MAXIMUM 10 arguments.."<<endl;
    cout<<">>--->[ ./invoke-oracle-multithreaded SIZE N L PORT LOGFILE (optional){-k NUM -h ADDRESS }] "<<endl;
    cout<<">>->SIZE       : size of bloom filter..."<<endl;
    cout<<">>->N          : Number of threads.."<<endl;
    cout<<">>->L          : Number of times a thread restarts.."<<endl;
    cout<<">>->PORT       : port for Internet connection.."<<endl;
    cout<<">>->LOGFILE    : Name of file for the output for each thread.."<<endl;
    cout<<">>->-k NUM     : Number of hash functions.."<<endl;
    cout<<">>->-h ADDRESS : Internet address.."<<endl;
    cout<<">>Program terminated...."<<endl;
}



void print_final_statistics_message(int a,char* b,int c,int d,int e,int f,char* g,int h,char* i,int j,bool k,double l,int tt,int ty,int per,int numcon)
{
    bool connection=false;                                  //print statistics
    if(k==false)
    {
        cout<<">>/////////////////////////////"<<endl;
        cout<<">>//--->Word not founded<----//"<<endl;
        cout<<">>/////////////////////////////"<<endl;
    }
    else
    {
        cout<<">>/////////////////////////////"<<endl;
        cout<<">>//----->Word founded<------//"<<endl;
        cout<<">>/////////////////////////////"<<endl;
    }
    cout<<">>----------[Statistics]----------"<<endl;           //print statistics
    cout<<">>--->You have inserted<----------"<<endl;
    cout<<">>-->Size of bloom filter         : "<<c<<" bytes"<<endl;
    cout<<">>-->Number of threads            : "<<d<<" threads"<<endl;
    cout<<">>-->Times of thread restarts     : "<<e<<" restarts"<<endl;
    cout<<">>-->Port identification          : "<<f<<endl;
    cout<<">>-->Logfile name                 : "<<g<<endl;
    cout<<">>-->Seed entered from user       : "<<j<<endl;

    if(a>6)
    {
        if(a!=10)
        {
            if(strcmp(b,"-k")==0)
            {
                cout<<">>-->Number of hash functions     : "<<h<<" hash functions"<<endl;
                cout<<">>-------------------------------<<"<<endl;
            }
            else
            {
                cout<<">>-->Number of hash functions     : "<<h<<" hash functions"<<endl;
                cout<<">>-->Address for connection       : "<<i<<endl;
                cout<<">>-------------------------------<<"<<endl;
                connection=true;
            }
        }
        else
        {
                cout<<">>-->Number of hash functions     : "<<h<<" hash functions"<<endl;
                cout<<">>-->Address for connection       : "<<i<<endl;
                cout<<">>--------------------------------<<"<<endl;
                connection=true;
        }
    }
    else
    {
            cout<<">>-->Number of hash functions     : "<<h<<" hash functions"<<endl;
            cout<<">>-------------------------------<<"<<endl;
    }
    cout<<">>--->Connection established      : ";
    if(connection==false)
    {
        cout<<"NO"<<endl;
    }
    else
    {
        cout<<"YES"<<endl;
    }
    cout<<">>--->Server Created              : one"<<endl;
    cout<<">>--->Number of connection        : "<<numcon<<endl;
    cout<<">>--->Execution time              : "<<l<<" sec"<<endl;
    cout<<">>--->Total words                 : "<<tt+ty<<" words"<<endl;
    cout<<">>--->Total words used            : "<<tt<<" words"<<endl;
    cout<<">>--->Total words rejected        : "<<ty<<" words"<<endl;
    if((ty+tt)==0)
    {
        cout<<">>--->Percentage words used       : 0%"<<endl;
    }
    else
    {
        cout<<">>--->Percentage words used       : "<<(tt*100)/(ty+tt)<<"%"<<endl;
    }
    if(c!=0)
    {
        cout<<">>--->Percentage bloom filter full: "<<(((float)per)/((float)(c*CHAR_BIT)))*100<<"%"<<endl;
    }
    else
    {
        cout<<">>--->Percentage bloom filter full: 0%"<<endl;
    }
    cout<<">>----------[Statistics]----------"<<endl;    //print statistics
}
