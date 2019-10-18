#include "ConvertToString.h"


string HashTableValuesFill(const std::string str){

    return str;

}

string HashTableValuesFill(const int i){

    std::ostringstream s;
    s << i;
    const std::string str(s.str());
    
    return str;
}

string HashTableValuesFill(const double i){

    std::ostringstream s;
    s << i;
    const std::string str(s.str());
    
    return str;
}

