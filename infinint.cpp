#include <iostream>
#include <cstdlib>
#include <string>
#include <bitset>
#include <vector>
#include <fstream>
#include "infinint.h"
#include <sstream>
using namespace std;

//Construct InfinInt
InfinInt::InfinInt(string number){
    StringToVec(number);
}

//Default constructor
InfinInt::InfinInt(){
}

//Destruct InfinInt
InfinInt::~InfinInt(){
}

vector<int>* InfinInt::GetVector(){
    return bigInt;
}

void InfinInt::StringToVec(string s){
    string buffer = s;
    if (buffer[0] == '-'){
        this->is_neg = true;
        buffer.erase(0, 1);
    }
    for(int i = buffer.length(); i > 0; i--){
       bigInt->push_back(buffer[i-1] - '0');
    }
}

// Check if object of InfinInt is negative.
bool InfinInt::IsNeg(){
    if (is_neg){
        return true;
    }else{
        return false;
    }
}

string pairVal(InfinInt* a, InfinInt* b){
    if (a->IsNeg() && b->IsNeg()){
        return "NEG_NEG";
    }
    else if ((a->IsNeg() == false) & b->IsNeg()){
        return "POS_NEG";
    }
    else if (a->IsNeg() & !b->IsNeg()){
        return "NEG_POS";
    }
    else{
        return "POS_POS";
    }
}

string InfinIntToString(InfinInt* infinInt){
    string s;
    int ch;
    if (infinInt->IsNeg()){
        s += "-";
    }
    
    if (equal(infinInt->GetVector()->begin() + 1, infinInt->GetVector()->end(), infinInt->GetVector()->begin()) && infinInt->GetVector()->at(0) == 0) {
        s += "0";
        return s;
    }
    
    for(int i = infinInt->GetVector()->size()-1; i >= 0; --i){
        ch = infinInt->GetVector()->at(i);
      s.append(to_string(ch));
   }
   return s;
}

void Resize(InfinInt* a, InfinInt* b){
    int add_size = 0;
    if(a->GetVector()->size() > b->GetVector()->size()){
        add_size = (a->GetVector()->size() - b->GetVector()->size());
        for (int i=0; i < add_size; ++i){
            b->GetVector()->push_back(0);
        }
        return;
    }
    else if(b->GetVector()->size() > a->GetVector()->size()){
        add_size = (b->GetVector()->size() - a->GetVector()->size());
        for (int i=0; i < add_size; ++i){
            a->GetVector()->push_back(0);
        }
        return;
    }
}
bool aBigger(InfinInt* a, InfinInt* b){
    int size = a->GetVector()->size();
    if(a->GetVector()->at(size-1) > b->GetVector()->at(size-1)){
        return true;
    }
    else if(b->GetVector()->at(size-1) > a->GetVector()->at(size-1)){
        return false;
    }
    else{
        for(int i = size-1; i > 0; i--){
            if(a->GetVector()->at(i) > b->GetVector()->at(i)){
                return true;
            }
        }
    }
    return false;
}

vector<int> RawAdd(vector<int>* a, vector<int>* b){
    int overflow = 0;
    int val = 0;
    vector<int>* c = new vector<int>(a->size(), 0);    
    for(int i=0; i < a->size(); i++){
        val = (a->at(i) + b->at(i) + overflow);
        c->at(i) = val % 10;
            if((val/10) != 0){
                overflow = 1;
            }
            else{
                overflow = 0;
            }
            if(i == a->size()-1 & overflow == 1){
                c->push_back(overflow);
            }
        }
        return *c;
}

vector<int> RawSubtract(vector<int>* a, vector<int>* b){
    int overflow = 0;
    int val = 0;
    vector<int>* c = new vector<int>(a->size(), 0);    
    for(int i=0; i < a->size(); i++){
        if(a->at(i) < b->at(i)){
            if(overflow == 0){
                c->at(i) = (a->at(i) + 10) - b->at(i);
                overflow = 1;
            }
            else {
                c->at(i) = (a->at(i) + 9) - b->at(i);
                overflow = 1;
            }
        }
        else{
             if(overflow == 1){
                 if(a->at(i) == b->at(i)){
                     c->at(i) = (a->at(i) + 9) - b->at(i);
                     overflow = 1;
                 }
                 else{
                     c->at(i) = (a->at(i) - 1) - b->at(i);
                     overflow = 0;
                 }
             }
             else {
                 c->at(i) = a->at(i) - b->at(i);
             }
        }
    }
    return *c;
}
InfinInt* operator+(InfinInt a, InfinInt b){
    //Set up
    InfinInt* aPtr = &a;
    InfinInt* bPtr = &b;
    Resize(aPtr,bPtr);
    InfinInt* sum = new InfinInt();
    sum->operation_performed = "+";
    vector<int>* c = new vector<int>(a.GetVector()->size(), 0);
    int overflow = 0;
    int val = 0;
    int a_length = a.GetVector()->size();
    
    //Case of 2 neg numbers
    if((pairVal(aPtr, bPtr) == "NEG_NEG")){
        sum->is_neg = true;
        *(sum->GetVector()) = RawAdd(a.GetVector(), b.GetVector());
        return sum;        
    }
    //Case of a positive and negative number in that order
    else if((pairVal(aPtr, bPtr) == "POS_NEG")){
        if(aBigger(aPtr, bPtr)){
            sum->is_neg = false;
            *(sum->GetVector()) = RawSubtract(a.GetVector(), b.GetVector());
            return sum;            
        }
        else{
            sum->is_neg = true;
            *(sum->GetVector()) = RawSubtract(b.GetVector(), a.GetVector());
            return sum;
        }
    }
    else if(pairVal(aPtr, bPtr) == "NEG_POS"){
        if(aBigger(aPtr, bPtr)){
            sum->is_neg = true;
            *(sum->GetVector()) = RawSubtract(a.GetVector(), b.GetVector());
            return sum;
        }
        else{
            sum->is_neg = false;
            *(sum->GetVector()) = RawSubtract(b.GetVector(), a.GetVector());
            return sum;
        }
    }
    else{ // must be positive plus positive
        sum->is_neg = false;
        *(sum->GetVector()) = RawAdd(a.GetVector(), b.GetVector());
        return sum;    
    }
}

InfinInt* operator-(InfinInt a, InfinInt b){
    InfinInt* aPtr = &a;
    InfinInt* bPtr = &b;
    Resize(aPtr,bPtr);
    InfinInt* difference = new InfinInt();
    vector<int>* c = new vector<int>(a.GetVector()->size(), 0);
    difference->operation_performed = "-";
    
    if((pairVal(aPtr, bPtr) == "POS_POS")){ //Normal subtraction
        if(aBigger(aPtr, bPtr)){
            difference->is_neg = false;
            *(difference->GetVector()) = RawSubtract(a.GetVector(), b.GetVector());
            return difference;
        }
        else{
            difference->is_neg = true;
            *(difference->GetVector()) = RawSubtract(b.GetVector(), a.GetVector());
            return difference;            
        }
    }
    else if((pairVal(aPtr, bPtr) == "POS_NEG")){ // Add (sum is positive)
        difference->is_neg = false;
        *(difference->GetVector()) = RawAdd(a.GetVector(), b.GetVector());
        return difference;
    }
    else if((pairVal(aPtr, bPtr) == "NEG_POS")){ //Add and set negative
        difference->is_neg = true;
        *(difference->GetVector()) = RawAdd(a.GetVector(), b.GetVector());
        return difference;
    }
    else{ // Means Neg_Neg
        if(aBigger(aPtr, bPtr)){
            difference->is_neg = true;
            *(difference->GetVector()) = RawSubtract(a.GetVector(), b.GetVector()); //This is fixed now
            return difference;
        }
        else{ // This case seems to be broken
            difference->is_neg = false;
            *(difference->GetVector()) = RawSubtract(b.GetVector(), a.GetVector()); 
            return difference;
        }        
    }
}


// ************IF SOMEONE PICKS UP HERE, WE HAVE TO USE A VECTOR************* 
//************OF VECTORS THINK ABOUT HOW LONG MULTIPLICATION WORKS **********
//***********https://www.youtube.com/watch?v=t8m0NalQtEk*********************
/*
InfinInt* operator*(InfinInt a, InfinInt b){
    InfinInt* aPtr = &a;
    InfinInt* bPtr = &b;
    Resize(aPtr,bPtr);
    int a_length = a.GetVector()->size();
    InfinInt* product = new InfinInt();
    vector<int>* c = new vector<int>(a.GetVector()->size(), 0);
    
    //Condition Pos x Pos = Pos & Neg x Neg = Pos
    if((a->is_neg && b->is_neg) || (!(a->is_neg) && !(b->is_neg))){
        product->is_neg = false;
        
    }
    else if(a->is_neg || b->is_neg){
        product->is_neg = true;
        
    }
}
*/
    
ostream& operator<< (ostream &out, InfinInt* i){
    if(i->operation_performed == "+"){
        string s = InfinIntToString(i);
        ofstream fl;
        fl.open("addition.txt");
        fl << s;
        cout << s <<endl;
    }
    else if(i->operation_performed == "-"){
        string s = InfinIntToString(i);
        ofstream fl;
        fl.open("subtraction.txt");
        fl << s;
        cout << s <<endl;
    } 
    else{
        string s = InfinIntToString(i);
        ofstream fl;
        fl.open("InfinInt.txt");
        fl << s;
        cout << s <<endl;
    }
    return out;
}

istream& operator>>(istream &in, InfinInt* i){
    string data;//a temp number to hold the input value
    in >> data;
    i->StringToVec(data);
    return in;
}