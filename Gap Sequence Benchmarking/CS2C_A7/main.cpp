/*
Bradley Thurston - 11338420
CS2C - Assignment 7
ShellSort implementation that sorts a FHvector with
a client provided gap sequence. The client calls the
sort by passing a FHvector to be sorted, an array with
the gap sequence, and the size of the gap sequence array.
shellSortX expects the gap sequence array to be sorted from
least to greatest.
*/

#include <iostream>
#include <time.h>
using namespace std;

#include "FHvector.h"

#define ARRAY_SIZE 200000


//----------------shellSort---------------------------------------

template <typename Comparable>
void shellSortX(FHvector<Comparable> & compArray, int * gapArray, int gapArraySize)
{
   int k, pos, arraySize, gap, gapArrayPos;
   Comparable tmp;

   arraySize = compArray.size();
   for (gapArrayPos = gapArraySize - 1; gapArrayPos >= 0; gapArrayPos--) {  // outer gap loop
      gap = gapArray[gapArrayPos];
      for (pos = gap; pos < arraySize; pos++)   // middle loop (outer of "insertion-sort")
      {
         tmp = compArray[pos];
         for (k = pos; k >= gap && tmp < compArray[k - gap]; k -= gap)   // inner loop
            compArray[k] = compArray[k - gap];
         compArray[k] = tmp;
      }
   }
}

//----------------sedgewickNumber----------------------------------
//generates a sedgewick number given a position in the
//sequence
int sedgewick(int n) {
   int tmp1 = 1;
   int tmp2 = 1;
   int sedgewickNumber;

   for (int x = 0; x < n; x++) {
      tmp1 *= 2;
   }

   if (n % 2 == 0) {
      for (int x = 0; x < n / 2; x++) {
         tmp2 *= 2;
      }
      sedgewickNumber = (9 * tmp1) - (9 * tmp2) + 1;
   }
   else {
      for (int x = 0; x < (n + 1) / 2; x++) {
         tmp2 *= 2;
      }
      sedgewickNumber = (8 * tmp1) - (6 * tmp2) + 1;
   }
   
   return sedgewickNumber;
}


//----------------Main--------------------------------------------

int main(){

   FHvector<int> fhVectorOfInts1;
   FHvector<int> fhVectorOfInts2;
   FHvector<int> fhVectorOfInts3;
   FHvector<int> fhVectorOfInts4;

   clock_t startTime, stopTime;
   srand(time(NULL));         //generate a random seed;
   int randomInt;

   FHvector<int> impliedGapVector;
   FHvector<int> sedgewickGapVector;
   FHvector<int> knuthGapVector;

   int impliedGapArraySize; 
   int explicitGapArraySize;
   int sedgewickGapArraySize;
   int knuthGapArraySize;

   // fill vectors with identical random values to compare gaps
   for (int x = 0; x < ARRAY_SIZE; ++x) {
      randomInt = rand() % ARRAY_SIZE;
      fhVectorOfInts1.push_back(randomInt);
      fhVectorOfInts2.push_back(randomInt);
      fhVectorOfInts3.push_back(randomInt);
      fhVectorOfInts4.push_back(randomInt);
   }

   //print out first 10 indices of presorted vector
   cout << "First 10 indices of presorted vector: ";
   for (int x = 0; x < 10; ++x) {
      cout << fhVectorOfInts1[x] << ", ";
   }
   cout << endl << endl;

   //----------------implicitGapArray--------------------------------

   //build implicit Gap Sequence
   for (int x = ARRAY_SIZE / 2; x > 0; x /= 2) {
      impliedGapVector.push_back(x);
   }
   impliedGapArraySize = impliedGapVector.size();

   //reverse implicit Gap Sequence and put into array
   cout << "Implicit Gap Sequence: ";

   int* implicitGapArray = new int[impliedGapArraySize];
   for (int x = 0; x < impliedGapArraySize; ++x) {
      implicitGapArray[x] = impliedGapVector[impliedGapArraySize - 1 - x];
      cout << " " << implicitGapArray[x] << ",";
   }
   cout << endl << endl;

   //----------------explicitGapArray--------------------------------

   int explicitGapArray[] = { 1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024,
      2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288,
      1048576 };
   explicitGapArraySize = 21;

   cout << "Explicit Gap Sequence: ";
   for (int x = 0; x < explicitGapArraySize; x++){
      cout << " " << explicitGapArray[x] << ",";
   }
   cout << endl << endl;

   //----------------sedgewickGapArray--------------------------------
   
   //build sedgewick Gap Sequence
   for (int k = 0; k < ARRAY_SIZE; k++) {
      int sedgewickNumber = sedgewick(k);
      
      if (sedgewickNumber > ARRAY_SIZE) {
         break;
      }
      sedgewickGapVector.push_back(sedgewickNumber);
   }
   sedgewickGapArraySize = sedgewickGapVector.size();

   //put sedgewick Gap Sequence into Array
   cout << "Sedgewick Gap Sequence: ";

   int* sedgewickGapArray = new int[sedgewickGapArraySize];
   for (int x = 0; x < sedgewickGapArraySize; ++x) {
      sedgewickGapArray[x] = sedgewickGapVector[x];
      cout << " " << sedgewickGapArray[x] << ",";
   }
   cout << endl << endl;

   //----------------knuthGapArray------------------------------------

   //build knuth's Gap Sequence
   for (int k = 1; k < ARRAY_SIZE; k = 3*k + 1) {
      knuthGapVector.push_back(k);
   }
   knuthGapArraySize = knuthGapVector.size();

   //put knuth's Gap Sequence into Array
   cout << "Knuth's Gap Sequence: ";

   int* knuthGapArray = new int[knuthGapArraySize];
   for (int x = 0; x < knuthGapArraySize; ++x) {
      knuthGapArray[x] = knuthGapVector[x];
      cout << " " << knuthGapArray[x] << ",";
   }
   cout << endl << endl;

   //----------------implicitGapArray--------------------------------
   
   startTime = clock();  // ------------------ start 

   shellSortX(fhVectorOfInts1, implicitGapArray, impliedGapArraySize);

   stopTime = clock();  // ---------------------- stop
   cout << "Implicit ShellSort Elapsed Time: "
      << (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC
      << " seconds." << endl << endl;

   //----------------explicitGapArray--------------------------------

   startTime = clock();  // ------------------ start 

   shellSortX(fhVectorOfInts2, explicitGapArray, explicitGapArraySize); 

   stopTime = clock();  // ---------------------- stop
   cout << "Explicit ShellSort Elapsed Time: "
       << (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC
       << " seconds." << endl << endl;

   //----------------sedgewickGapArray--------------------------------
   
   startTime = clock();  // ------------------ start 

   shellSortX(fhVectorOfInts3, sedgewickGapArray, sedgewickGapArraySize);

   stopTime = clock();  // ---------------------- stop
   cout << "Sedgewick Shell Sort Elapsed Time: "
      << (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC
      << " seconds." << endl << endl;

   //----------------knuthGapArray------------------------------------

   startTime = clock();  // ------------------ start 

   shellSortX(fhVectorOfInts4, knuthGapArray, knuthGapArraySize);

   stopTime = clock();  // ---------------------- stop
   cout << "Knuth ShellSort Elapsed Time: "
      << (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC
      << " seconds." << endl << endl;

   //----------------Print Sorted Vectors-----------------------------

   cout << "First 10 indices after Implicit ShellSort: ";
   for (int x = 0; x < 10; ++x){
      cout << fhVectorOfInts1[x] << ", ";
   }
   cout << endl;

   cout << "First 10 indices after Explicit ShellSort: ";
   for (int x = 0; x < 10; ++x){
      cout << fhVectorOfInts2[x] << ", ";
   }
   cout << endl;

   cout << "First 10 indices after Sedgewick ShellSort: ";
   for (int x = 0; x < 10; ++x){
      cout << fhVectorOfInts3[x] << ", ";
   }
   cout << endl;

   cout << "First 10 indices after Knuth ShellSort: ";
   for (int x = 0; x < 10; ++x){
      cout << fhVectorOfInts4[x] << ", ";
   }
   cout << endl;

   //----------------Clean Up-----------------------------------------
   delete[] implicitGapArray;
   implicitGapArray = NULL;
   delete[] knuthGapArray;
   knuthGapArray = NULL;
   delete[] sedgewickGapArray;
   knuthGapArray = NULL;

   return 0;
}

