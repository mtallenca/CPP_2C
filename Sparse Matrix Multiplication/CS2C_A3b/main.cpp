/*
Bradley Thurston
11338420
CS2C - Assignment 3b

This program creates sparse matrices M and N of MAT_SIZE x MAT_SIZE.
Default values are not stored. FHsparseMat is a class template.
Matrix multiplication has been optimized for sparse matrices, and the
resulting matrix is assigned to the this matrix.

*/

#include <iostream>
using namespace std;

#include "SparseMatWMult.h"
#include <iomanip>
#include <time.h>


#define MAT_SIZE 800
typedef SparseMatWMult<double> SpMat;

// --------------- main ---------------
int main()
{
   SpMat m(MAT_SIZE, MAT_SIZE); 
   SpMat n(MAT_SIZE, MAT_SIZE);

   int r, c;
   clock_t startTime, stopTime;
   double randFracM, randFracN;
   int randRowM, randColM, randRowN, randColN, smallPercent;
   
   // generate small% non-default values bet .1 and 1
   smallPercent = MAT_SIZE / 100. * MAT_SIZE;  // div by 100. means 1%
   srand(time(NULL) + rand());				     // generate a seed
   
   //fill smallPercent of N and M with random
   //values at random coordinates
   for (r = 0; r < smallPercent; r++)
   {
      randRowM = rand() % MAT_SIZE;
      randColM = rand() % MAT_SIZE;
      randFracM = (rand() % 91 + 10) / 100.0;

      randRowN = rand() % MAT_SIZE;
      randColN = rand() % MAT_SIZE;
      randFracN = (rand() % 91 + 10) / 100.0;

      m.set(randRowM, randColM, randFracM);
      n.set(randRowN, randColN, randFracN);
   }
   
   cout << fixed << setprecision(1);

   cout << "First Matrix, m: \n";
   m.showSubSquare(0, 15);
  
   cout << "Second Matrix, n: \n";
   n.showSubSquare(0, 15);

   startTime = clock();  // ------------------ start
   m.matMult(m, n);
   stopTime = clock();  // ---------------------- stop

   cout << "Product Matrix, m x n: \n";
   m.showSubSquare(0, 15);
   
   cout << "\nSize = " << MAT_SIZE << " Dyn Array Mult Elapsed Time: "
      << (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC
      << " seconds." << endl << endl;

}

/*
// use this code to create n nd m test matrices
// by replacing lines 39-53 with this code
   double mlist[25] = { 1.0, 2.0, 3.0, 4.0, 5.0, -1.0, -2.0, -3.0, -4.0, -5.0, 1.0, 3.0, 1.0, 3.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, -1.0, -1.0, -1.0, -1.0, -1.0 };
   double nlist[25] = { 2.0, 1.0, 5.0, 0.0, 2.0, 1.0, 4.0, 3.0, 2.0, 7.0, 4.0, 4.0, 4.0, 4.0, 4.0, 7.0, 1.0, -1.0, -1.0, -1.0, 0.0, 0.0, 8.0, -1.0, -6.0 };

   int x = 0;
   for (int row = 0; row < MAT_SIZE; row++){
      for (int col = 0; col < MAT_SIZE; col++){
         m.set(row, col, mlist[x]);
         n.set(row, col, nlist[x]);
         x++;
      }
   }
*/