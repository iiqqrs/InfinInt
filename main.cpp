#include <iostream>
#include <cstdlib>
#include "infinint.h"
#include <string>
#include <fstream>
using namespace std;

int main() {
   ifstream inFS;
   string data;
   inFS.open("int1");
   inFS >> data;
   
   InfinInt* biggerNum = new InfinInt("-1234");
   InfinInt* smallerNum = new InfinInt("12391933");
   
   Resize(biggerNum, smallerNum);
   for (int i = 0; i < smallerNum->GetVector().size(); i++) {
      cout << smallerNum->GetVector().at(i);
   }
   
   delete biggerNum;
   delete smallerNum;
}






