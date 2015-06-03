/*
Bradley Thurston - 11338420
CS2C - Assignment 8
QuickSortX

1.	Pick an element at random from the array. This the pivot.
2.	Use the pivot to group the other elements into two groups: 
those < pivot (smaller subgroup) and those > pivot (larger subgroup).
3.	Recursively quickSort the two sub-groups
4.	Assemble the final array: smaller sorted subgroup, pivot, larger 
sorted subgroup. It is sorted.

*/

#include <iostream>
using namespace std;
#include <iomanip>

#include <time.h>
#include "FHsort.h"
#include "FHvector.h"

//----------------quickSortX---------------------------------------
//client interface
template <typename Comparable>
void quickSortX(FHvector<Comparable> & a, int rec_limit)
{
   if (rec_limit < 2) {
      rec_limit = 2;
   }
   quickSortX(a, 0, a.size() - 1, rec_limit);
}

//internal recursive function
template <typename Comparable>
void quickSortX(FHvector<Comparable> & a, int left, int right, int rec_limit)
{
   Comparable pivot;
   int i, j;

   if (left + rec_limit <= right) {

      pivot = median3(a, left, right);
      for (i = left, j = right - 1;;)
      {
         while (a[++i] < pivot)
            ;
         while (pivot < a[--j])
            ;
         if (i < j)
            mySwapFH(a[i], a[j]);
         else
            break;
      }

      mySwapFH(a[i], a[right - 1]);  // restore pivot

      // recursive calls on smaller sub-groups
      quickSortX(a, left, i - 1, rec_limit);
      quickSortX(a, i + 1, right, rec_limit);

   } else {
      // non-recursive escape valve - insertionSort
      insertionSort(a, left, right);
   }
}

//----------------Main--------------------------------------------
#define ARRAY_SIZE 40000

int main()
{
   int k, i;
   //int arrayOfInts[ARRAY_SIZE];
   FHvector<int> baseVector(ARRAY_SIZE);
   FHvector<int> testVector(ARRAY_SIZE);

   srand(time(NULL));         //generate a random seed;
   clock_t startTime, stopTime;

   for (i = 0; i < ARRAY_SIZE; i++)
   {
      baseVector[i] = (rand() % ARRAY_SIZE);
      //cout << baseVector[i] << "   ";
   }
   

   //output testing
   cout << "Vector size: " << ARRAY_SIZE << endl;
   cout << "+------------------------------+" << endl;
   cout << "| Rec_Limit | Time Elapsed (s) |" << endl;
   cout << "+------------------------------+" << endl;

   //test rec_limit 2 to 300 incrementing by 2
   for (k = 0; k <= 300; k += 2){

      // construct test vector
      for (i = 0; i < ARRAY_SIZE; i++)
      {
         testVector[i] = baseVector[i];
      }

      //capture algorithm time
      startTime = clock();  // ------------------ start 
      quickSortX(testVector, k);
      stopTime = clock();  // ---------------------- stop

      //output data in table
      cout << "|    " << setw(3) << k << "    |"
         << "    "
         << setw(5) << (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC
         << "         |" << endl;

      //check vector is sorted
      /*
      for (i = 0; i < ARRAY_SIZE; i++)
      {
         cout<< testVector[i] << " ";
      }
      */
   }

   cout << "+------------------------------+" << endl;
}
 
