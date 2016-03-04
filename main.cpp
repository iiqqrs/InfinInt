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
   
   InfinInt* i = new InfinInt("-1234");
   delete i;
}






