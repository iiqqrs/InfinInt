#include <iostream>
#include <cstdlib>
#include "infinint.h"
#include <string>
using namespace std;

int main() {
   InfinInt* i = new InfinInt("586");
   i->asBits(); // Should output 0101 1000 0110
   delete i;
}