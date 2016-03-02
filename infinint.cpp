#include <iostream>
#include <cstdlib>
#include <string>
#include <bitset>
#include <vector>
#include "infinint.h"
using namespace std;

       InfinInt::InfinInt(string number){
            vector<bitset<4> > vbs;
            for(int i=0; i < number.length(); ++i){
                //cout << bitify(number[i]) << endl;
                vbs.push_back(bitify(number[i]));
            }
            vecBitSet = vbs;
        }
       
       bitset<4> InfinInt::bitify(char c){
           bitset<4> val;
           switch (c) {
            case '0':
                val = 0b0000;
                break;
            case '1':
                val = 0b0001;
                break;
            case '2':
                val = 0b0010;
                break;
            case '3':
                val = 0b0011;
                break;
            case '4':
                val = 0b0100;
                break;
            case '5':
                val = 0b0101;
                break;
            case '6':
                val = 0b0110;
                break;
            case '7':
                val = 0b0111;
                break;
            case '8':
                val = 0b1000;
                break;
            case '9':
               val = 0b1001;
               break;
           }
           return val;
       }    
       
       void InfinInt::asBits(){
            for (int i = 0; i < vecBitSet.size(); i++) {
                cout << vecBitSet.at(i) << endl;
            }
        }
      /* InfinInt operator+(InfinInt bigInt1, InfinInt bigInt2 );
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