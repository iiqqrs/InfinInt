#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <ctime>
#include "infinint.h"
using namespace std;

int main() {
   clock_t start;
   double duration;
   
   
   
   
   InfinInt* a = new InfinInt();
   InfinInt* b = new InfinInt();
   InfinInt* c = new InfinInt();
   
   cout << "Welcome to our project 1 \"InfinInt\"" << endl;
   cout << "For you we've built a library for our data type including:" << endl;
   cout << "\t1. A addition operator." << endl;
   cout << "\t2. A subtraction operator." << endl;
   cout << "\t3. A multiplication operator." << endl;
   cout << "\t4. And two division operators (incomplete)." << endl <<endl;
   
   //Do add stuff
   cout << "First lets add some InfinInt's" << endl;
   cout << "Please enter an infinint: " << endl;
   cin >> a;
   cout << "Please enter another infinit: " << endl;
   cin >> b;
   start = clock();
   c = *a + *b;
   duration = (clock() - start ) / (double) CLOCKS_PER_SEC;
   cout << "The summation equates to: " << endl;
   cout << c << endl;
   cout << "It took " << duration << " seconds to compute that addition." <<endl;

   // Do subtract stuff
   cout << "Second lets subtract some InfinInt's" << endl;
   cout << "Please enter an infinint: " << endl;
   cin >> a;
   cout << "Please enter another infinit: " << endl;
   cin >> b;
   start = clock();
   c = *a - *b;
   duration = (clock() - start ) / (double) CLOCKS_PER_SEC;
   cout << "The difference equates to: " << endl;
   cout << c << endl;
   cout << "It took " << duration << " seconds to compute that subtraction." <<endl;
   
   //Do multiplication things
   cout << "Next lets multiply some InfinInt's" << endl;
   cout << "Please enter an infinint: " << endl;
   cin >> a;
   cout << "Please enter another infinit: " << endl;
   cin >> b;
   start = clock();
   c = (*a) * (*b);
   duration = (clock() - start ) / (double) CLOCKS_PER_SEC;
   cout << "The product equates to: " << endl;
   cout << c << endl;
   cout << "It took " << duration << " seconds to compute that multiplication." <<endl;
   
   //Do integer division
   cout << "Next lets divide some InfinInt's (Integer division)" << endl;
   cout << "Please enter an infinint: " << endl;
   cin >> a;
   cout << "Please enter another infinit: " << endl;
   cin >> b;
   start = clock();
   c = (*a) / (*b);
   duration = (clock() - start ) / (double) CLOCKS_PER_SEC;
   cout << "The quotient equates to: " << endl;
   cout << c << endl;
   cout << "It took " << duration << " seconds to compute that division." <<endl;
   
   delete a;
   delete b;
   delete c;
}