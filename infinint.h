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
       vector<bitset<4> > vecBitSet;
       bitset<4> bitify(char c);
    public:
        InfinInt(std::string number);
        void asBits();
};
#endif