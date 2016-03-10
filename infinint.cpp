#include <iostream>
#include <cstdlib>
#include <string>
#include <bitset>
#include <vector>
#include <fstream>
#include <sstream>
#include "infinint.h"
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

//Returns InfinInt's value as a reversed vector.
vector<int>* InfinInt::GetVector(){
    return bigInt;
}

void InfinInt::StringToVec(string s){
    bigInt->clear(); //We need this so if we set a infinint = to an infinit it wont clear unless we have this
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

vector<int> flipVector(vector<int> &vec){
    vector<int> flipped;
    
    for (int i = vec.size()-1; i >= 0; i--){
        flipped.push_back(vec.at(i));
    }
    
    
    return flipped;
    
}


bool isEqual(InfinInt* a, InfinInt* b) {
    for (int i = 0; i < a->GetVector()->size(); i++) {
        if (a->GetVector()->at(i) == b->GetVector()->at(i)) {
            continue;
        }
        else {
            return false;
        }
    }
    return true;
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
    
    if (equal(infinInt->GetVector()->begin() + 1, infinInt->GetVector()->end(), infinInt->GetVector()->begin()) && infinInt->GetVector()->at(0) == 0){
        s += "0";
        return s;
    }
    
    if (infinInt->IsNeg()){
        s += "-";
    }
    
    for(int i = infinInt->GetVector()->size()-1; i >= 0; --i){
        
        if ((i == infinInt->GetVector()->size()-1) && infinInt->GetVector()->at(i) == 0){
            continue;
        }
        ch = infinInt->GetVector()->at(i);
        s.append(to_string(ch));
   }
   return s;
}

vector<int>* Resize(vector<int>* a, vector<int>* b){
    int add_size = 0;
    if(a->size() > b->size()){
        add_size = (a->size() - b->size());
        for (int i=0; i < add_size; ++i){
            b->push_back(0);
        }
    }
    else if(b->size() > a->size()){
        add_size = (b->size() - a->size());
        for (int i=0; i < add_size; ++i){
            a->push_back(0);
        }
    }
    return a;
}

void Reformat(vector<int>& vec){
    int i = 0;
    if ((vec.size() > 1) && (vec.at(i) == 0)){
        while (vec.at(i) == 0){
            vec.erase(vec.begin());
            i++;
        }
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
            else{
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
             else{
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
    Resize(aPtr->GetVector(),bPtr->GetVector());
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
    Resize(aPtr->GetVector(),bPtr->GetVector());
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
            *(difference->GetVector()) = RawSubtract(a.GetVector(), b.GetVector());
            return difference;
        }
        else{
            difference->is_neg = false;
            *(difference->GetVector()) = RawSubtract(b.GetVector(), a.GetVector());
            return difference;
        }
    }
}

vector<int> RawMultiply(vector<int>* firstVec, vector<int>* secondVec){
    vector<int> a;
    vector<int> b;
    int i = 0;
    int j = 0;
    int carry = 0;
    int k = 0;
    int l = 0;
    int pusher = 0;
    int z = 0;
    vector<int> sum;
    vector<int> d;
    vector<vector<int>> c;
    vector<vector<int>>* cAsPtr = new vector<vector<int>>;
    
    if ((firstVec->size() > secondVec->size())){
        a = flipVector(*secondVec);
        b = flipVector(*firstVec);
    }
    else if (firstVec->size() < secondVec->size()){
         b = flipVector(*secondVec);
         a = flipVector(*firstVec);
    }
    else if (firstVec->at(firstVec->size()-1) > secondVec->at(secondVec->size()-1)){
        a = flipVector(*secondVec);
        b = flipVector(*firstVec);
    }
    else{
        b = flipVector(*secondVec);
        a = flipVector(*firstVec);
    }
    for(i = a.size() - 1; i >= 0; i--){
        for(j = b.size() - 1; j >= 0; j--){
            d.push_back((b.at(j) * a.at(i)) + carry);
            carry = d.at(k) / 10;
            d.at(k) = d.at(k) % 10;
            k++;
            if ((carry > 0 && j == 0) ||(carry > 0 && j == 0)){ //So the carry is only appended to d as a separate element at the end
            d.push_back(carry);
            }
        }
        k = 0;
        carry = 0;
        c.push_back(d);
        d.clear();
        j--;
    }
    cAsPtr = &c;
    for(z=0; z < c.size(); z++){
        l = 0;
        while(l < pusher){
            c.at(z).insert(c.at(z).begin(),0);
            l++;
        }
        pusher++;
    }
    //Sum up inner vectors
    for(int i=0; i < c.size(); i++){
        vector<int>* dAsPtr = new vector<int>;
        dAsPtr = &(cAsPtr->at(i));
        vector<int>* sumAsPtr = new vector<int>;
        sumAsPtr = &sum;
        Resize(sumAsPtr, dAsPtr);
        flipVector(*dAsPtr);
        sum = RawAdd(dAsPtr, sumAsPtr);
       
    }
    return sum;
}

InfinInt* operator*(InfinInt a, InfinInt b){
    InfinInt* aPtr = &a;
    InfinInt* bPtr = &b;
    //Resize(aPtr,bPtr);
    int a_length = a.GetVector()->size();
    InfinInt* product = new InfinInt();
    vector<int>* c = new vector<int>(a.GetVector()->size(), 0);
    product->operation_performed = "*";
    
    //Condition Pos x Pos = Pos & Neg x Neg = Pos
    if((aPtr->is_neg && bPtr->is_neg) || (!(aPtr->is_neg) && !(bPtr->is_neg))){
        product->is_neg = false;
        //Call raw multiply (how multiplication is done on paper) here.
        *(product->GetVector()) = RawMultiply(b.GetVector(), a.GetVector());
        return product;
    }
    else if(aPtr->is_neg || bPtr->is_neg){
        product->is_neg = true;
        *(product->GetVector()) = RawMultiply(b.GetVector(), a.GetVector());
        return product;
    }
}

vector<int> RawDivide(vector<int>* firstVec, vector<int>* secondVec){
    InfinInt* firstVecObj = new InfinInt();
    InfinInt* secondVecObj = new InfinInt();
    InfinInt* quotient = new InfinInt();
    InfinInt* increment = new InfinInt("1");
    InfinInt* zero = new InfinInt("0");
    vector<int> vecCopyA = *(firstVec);
    vector<int> vecCopyB = *(secondVec);
    firstVecObj->is_neg = false;
    firstVecObj->is_neg = false;
    *(firstVecObj->GetVector()) = vecCopyA;
    *(secondVecObj->GetVector())= vecCopyB;

    
    
    while(aBigger(firstVecObj, secondVecObj) || isEqual(firstVecObj, zero)) { //There are definitely problems with this condition. I think the value of the firstVecObj is jumping between positive and negative
        firstVecObj = (*firstVecObj) - (*secondVecObj);                       //until the second vector is larger than the first, rendering this while loop nearly infinite.
        quotient = (*quotient) + (*increment);
    }
    
    return *(quotient->GetVector());
}


InfinInt* operator / (InfinInt a, InfinInt b) {
    InfinInt* quotientInt = new InfinInt();
    InfinInt* aPtr = &a;
    InfinInt* bPtr = &b;
    vector<int> quotient;
    quotientInt->operation_performed = "/";
    
    Resize(aPtr->GetVector(),bPtr->GetVector());
    
    
    if (aBigger(aPtr,bPtr)) { //a bigger than b (the usual)
        quotient = RawDivide(a.GetVector(), b.GetVector());
    }
    
    else if (!aBigger(aPtr,bPtr) && isEqual(aPtr,bPtr) == false){ //b bigger than a
        quotient.push_back(0);
    }
    
    else { //If both are the same
        quotient.push_back(1);
    }
    
    //Condition Pos x Pos = Pos & Neg x Neg = Pos
    if((aPtr->is_neg && bPtr->is_neg) || (!(aPtr->is_neg) && !(bPtr->is_neg))){
        quotientInt->is_neg = false;
    }
    else if(aPtr->is_neg || bPtr->is_neg){
        quotientInt->is_neg = true;
    }
    
    *(quotientInt->GetVector()) = quotient;
    return quotientInt;
}


ostream& operator<<(ostream &out, InfinInt* i){
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
    else if(i->operation_performed == "*"){
        string s = InfinIntToString(i);
        ofstream fl;
        fl.open("multiplication.txt");
        fl << s;
        cout << s <<endl;
    }
    else if(i->operation_performed == "/"){
        string s = InfinIntToString(i);
        ofstream fl;
        fl.open("division_one.txt");
        fl << s;
        cout << s <<endl;
    }
    else if(i->operation_performed == "/2"){
        string s = InfinIntToString(i);
        ofstream fl;
        fl.open("division_two.txt");
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

void operator>>(istream &in, InfinInt* i){
    string fileName;//a temp number to hold the input value
    in >> fileName;
    ifstream inFS; // Input file stream
    
    string vecAsString;
    inFS.open(fileName);
    
    if (!inFS.is_open()) {
        cout << "Could not open file myfile.txt." << endl;
        return; // 1 indicates error
    }
    
    inFS >> vecAsString;
    inFS.close();
   
    i->StringToVec(vecAsString);
    return;
}