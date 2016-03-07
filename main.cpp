#include <iostream>
#include <cstdlib>
#include "infinint.h"
#include <string>
#include <fstream>
using namespace std;

int main() {

   InfinInt* biggerNumPtr = new InfinInt("-56464555");
  
   InfinInt* smallerNumPtr = new InfinInt("564646");

   InfinInt* output = new InfinInt();
   
   /*
   cout << "Please enter an infinint: " <<endl;
   cin >> output;
   cout << output;
   */
   
   output = *smallerNumPtr + *biggerNumPtr;
   //output = *biggerNumPtr - *smallerNumPtr;
   
   cout << output;

   delete biggerNumPtr;
   delete smallerNumPtr;
}