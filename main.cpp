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
   
   InfinInt* smallerNum = new InfinInt("-9876");
   InfinInt* biggerNum = new InfinInt("12391933");
   
   
   smallerNum = Resize(biggerNum, smallerNum);
   for (int i = 0; i < smallerNum->GetVector().size(); i++) {
      cout << smallerNum->GetVector().at(i) << endl;
   }
   
   delete biggerNum;
   delete smallerNum;
}






