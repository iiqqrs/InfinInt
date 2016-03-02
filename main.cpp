#include <iostream>
#include <cstdlib>
#include "infinint.h"
#include <string>
using namespace std;

int main() {
   InfinInt* i = new InfinInt("3967994432"); // Larger than 4294967295  ;)
   i->asBits(); // Should output 0011 1001 0110 0111 1001 1001 0100 0100 0011 0010
   delete i;
}