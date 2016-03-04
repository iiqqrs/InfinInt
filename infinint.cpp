#include <iostream>
#include <cstdlib>
#include <string>
#include <bitset>
#include <vector>
#include <fstream>
#include "infinint.h"
#include <sstream>
using namespace std;


vector<int> InfinInt::GetVector(){
    return bigInt;
}

void InfinInt::StringToVec(string s){
    string buffer = s;
    
    if (buffer[0] == '-') {
        is_neg = true;
        buffer.erase(0, 1);
    }
    for(int i = buffer.length(); i > 0; i--){
       bigInt.push_back(i);
    }
    for(int i = 0; i < bigInt.size(); i ++) {
        cout << bigInt.at(i) << endl;
    }
}

void Resize(InfinInt* a, InfinInt* b){
    int add_size = 0;
    if(a->GetVector().size() > b->GetVector().size()){
        add_size = (a->GetVector().size() - b->GetVector().size());
        
        // add to b here and then return
        for (int i=0; i < add_size; ++i){
            b->GetVector().push_back(0);
        }
    }
    else if(b->GetVector().size() > a->GetVector().size()){
        add_size = (b->GetVector().size() - a->GetVector().size());
        
        // add to a here and then return
        for (int i=0; i < add_size; ++i){
            a->GetVector().push_back(0);
        }
    }
}

//Construct InfinInt
InfinInt::InfinInt(string number){
    StringToVec(number);
}

//Destruct InfinInt
InfinInt::~InfinInt(){
}

InfinInt operator+(InfinInt a, InfinInt b){
    //int a_length = a.size();
    //int b_length = b.size();
    //int lengthFirstLoop = 0;
    /*
    if (a.size() > b.size()){
        lengthFirstLoop = a.size();
    }
    for(int i=0; )
    */
}





/*
       InfinInt operator-(InfinInt bigInt1, InfinInt bigInt2);
       InfinInt operator*(InfinInt bigInt1, InfinInt bigInt2 );
       InfinInt operator<<(InfinInt bigInt1, InfinInt bigInt2);
       InfinInt operator>>(InfinInt bigInt1, InfinInt bigInt2);
       */

/*InfinInt operator+(const InfinInt & bigInt1, const InfinInt & bigInt2) {
    InfinInt total;
    
    total = 
    return total
} */