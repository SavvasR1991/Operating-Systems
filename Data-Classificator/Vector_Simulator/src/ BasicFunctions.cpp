#include "BasicFunctions.h"


int HexToDecimalConverter(string input){

    char * hex = new char[input.size() + 1];
    std::copy(input.begin(), input.end(), hex);
    hex[input.size()] = '\0';
    char *hexstr ;
    int length = 0;
    const double base = 16;    
    unsigned long decnum = 0;
    int i;

    for (hexstr = hex; *hexstr != '\0'; hexstr++) {
        length++;
    }
    hexstr = hex;
    for (i = 0; *hexstr != '\0' && i < length; i++, hexstr++) {
        if (*hexstr >= 48 && *hexstr <= 57) {  
            decnum += (((int)(*hexstr)) - 48) * pow(base, length - i - 1);
        }
        else if ((*hexstr >= 65 && *hexstr <= 70))  {  
            decnum += (((int)(*hexstr)) - 55) * pow(base, length - i - 1);
        }
        else if (*hexstr >= 97 && *hexstr <= 102) {  
            decnum += (((int)(*hexstr)) - 87) * pow(base, length - i - 1);
        }
        else {
            std::cout<<"Invalid Hexadecimal Number \n";
        }
    }
    return decnum;
}

string longDivision(string number, int divisor) 
{ 
    string ans; 
    cout<<number<<endl;
    int idx = 0; 
    int temp = number[idx] - '0'; 
    while (temp < divisor) 
       temp = temp * 10 + (number[++idx] - '0'); 
      
    while (number.size() > idx) 
    { 
        ans += (temp / divisor) + '0'; 
        
        ++idx;
        if(idx!=number.size())
            temp = (temp % divisor) * 10 + number[idx] - '0'; 
    } 
      
    if (ans.length() == 0) 
        return "0"; 
    return ans; 
} 

int longMod(string number, int divisor) 
{ 
    int res = 0; 
    for (int i = 0; i < number.length(); i++) 
         res = (res*10 + (int)number[i] - '0') % divisor; 
  
    return res; 
} 

int moduloHexCalculation(string input,int divisor){

    int modulo = 0;

    int decimal = 0;

    string HexToDecimal ;

    for (int i =0;i<input.length();i++)
    {
        stringstream ss;
        string s ;
        ss<<input.at(i);
        ss>>s;
        decimal = HexToDecimalConverter(s);

        std::stringstream ss1;
        ss1 << decimal;
        HexToDecimal.append(ss1.str());      
    }
    modulo = longMod(HexToDecimal,divisor);

    return modulo;
}


int isNumberOrFloat( string myString ) {
    int i = 0;
    char ch;
    
    int checkIfFloat = 0;
    
    if(!isdigit(myString[0])){
        return 0;
    }
    for(i=0;i< myString.size();i++){
        ch = myString[i];
        if (!isdigit(ch)) {
            if(ch=='.'){
                checkIfFloat++;
                if(checkIfFloat>1){
                    return 0;
                }  
            }
            else{
                return 0;
            }
        }
    }
    if(checkIfFloat == 0){
        return 1;
    }
    else{
        return 2;
    }
}

