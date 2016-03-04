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
            void Resize(InfinInt a, InfinInt b);
            void StringToVec(string s);
            vector<int> bigInt;
        public:
            vector<int> GetVector();
            InfinInt(string number);
            ~InfinInt();
            friend InfinInt operator + (InfinInt, InfinInt);
    };
#endif