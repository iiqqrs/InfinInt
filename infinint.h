//infinit.h
#include <cstdlib>
#include <string>
#include <bitset>
#include <vector>
using namespace std;

#ifndef InfinInt_H
#define InfinInt_H
    class InfinInt{
        private:
            bool is_neg = false;
            void StringToVec(string s);
            vector<int>* bigInt = new vector<int>;
            string operation_performed;
            string product_of;
            friend string pairVal(InfinInt* a, InfinInt* b);
            bool IsNeg();
            friend bool aBigger(InfinInt* a, InfinInt* b);
            vector<int> RawSubtract(vector<int>* a, vector<int>* b);
            vector<int> RawAdd(vector<int>* a, vector<int>* b);
            friend void Resize(InfinInt* a, InfinInt* b);
            friend string InfinIntToString(InfinInt* infIn); 
        public:
            vector<int>* GetVector();
            InfinInt(string number);
            ~InfinInt();
            InfinInt();
            //Finished Operators
            friend InfinInt* operator + (InfinInt a, InfinInt b);
            friend InfinInt* operator - (InfinInt a, InfinInt b);
            friend ostream& operator << (ostream &out, InfinInt* i);
            friend istream& operator >> (istream &in, InfinInt* i); 
            //ToDo Operators
            //friend InfinInt operator * (InfinInt a, InfinInt b);
    };
#endif