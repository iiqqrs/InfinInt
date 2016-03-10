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
            friend vector<int>* Resize(vector<int>* a, vector<int>* b);
            friend string InfinIntToString(InfinInt* infIn); 
            vector<int> flipVector(vector<int> &vec);
            vector<int> RawMultiply(vector<int>* a, vector<int>* b);
            void Reformat(vector<int>& vector);
            friend vector<int> RawDivide(vector<int>* firstVec, vector<int>* secondVec);
            friend bool isEqual(InfinInt* a, InfinInt* b);
        public:
            vector<int>* GetVector();
            InfinInt(string number);
            ~InfinInt();
            InfinInt();
            friend InfinInt* operator + (InfinInt a, InfinInt b);
            friend InfinInt* operator - (InfinInt a, InfinInt b);
            friend ostream& operator << (ostream &out, InfinInt* i);
            friend void operator >> (istream &in, InfinInt* i);
            friend InfinInt* operator * (InfinInt a, InfinInt b);
            friend InfinInt* operator / (InfinInt a, InfinInt b);
    };
#endif