#include <iostream>
using namespace std;

#include <time.h>
#include <iomanip>

#define MAT_SIZE 1000

typedef float* DynMat[MAT_SIZE];

void matMultDyn(const DynMat & matA, const DynMat & matB,
   DynMat & matC, int size);

void matShowDyn(const DynMat & matA, int start, int size);


int main()
{
   int r, c;
   clock_t startTime, stopTime;
   double randFrac;
   int randRow, randCol, smallPercent;

   // non-sparse dynamic matrix
   DynMat matDyn, matDynAns;

   // allocate rows and initialize to 0
   for (r = 0; r < MAT_SIZE; r++)
   {
      matDyn[r] = new float [MAT_SIZE];
      matDynAns[r] = new float[MAT_SIZE];
      for (c = 0; c < MAT_SIZE; c++)
      {
         matDyn[r][c] = 0.0;
         matDynAns[r][c] = 0.0;
      }
   }

   // generate small% non-default values bet .1 and 1
   smallPercent = MAT_SIZE / 20. * MAT_SIZE;  // div by 20. means 5%, of course
   srand(time(NULL) + rand());				    // generate a seed
   
   for (r = 0; r < smallPercent; r++)
   {
      randRow = rand() % MAT_SIZE;
      randCol = rand() % MAT_SIZE;
      randFrac = (rand() % 91 + 10) / 100.0;
      
      matDyn[randRow][randCol] = randFrac;
   }

   // 10x10 submatrix in lower right
   matShowDyn(matDyn, MAT_SIZE - 10, 10);

  
   startTime = clock();  // ------------------ start
   matMultDyn(matDyn, matDyn, matDynAns, MAT_SIZE);
   stopTime = clock();  // ---------------------- stop


   matShowDyn(matDynAns, MAT_SIZE - 10, 10);
   cout << "\nSize = " << MAT_SIZE << " Dyn Array Mult Elapsed Time: "
      << (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC
      << " seconds." << endl << endl;


   // clean up
   for (r = 0; r < MAT_SIZE; r++) {
      if (matDyn[r] != NULL) {
         delete matDyn[r];
         matDyn[r] = NULL;
      }
      if (matDynAns[r] != NULL) {
         delete matDynAns[r];
         matDynAns[r] = NULL;
      }
   }

   cout << endl;
}

void matShowDyn(const DynMat & matA, int start, int size) {
   if (start + size > MAT_SIZE){
      return;
   }
   else {
      for (int r = start; r < start + size; r++) {
         for (int c = start; c < start + size; c++) {
            cout << fixed << setprecision(2) << matA[r][c] << " ";
         }
         cout << endl;
      }
      cout << endl;
   }

}

void matMultDyn(const DynMat & matA, const DynMat & matB,
   DynMat & matC, int size)
{
   /*currently no checking because only possible input
   is the square of the matrix created in main */

   for (int row = 0; row < size; row++){
      for (int col = 0; col < size; col++){
         float matVal = 0.0;
         for (int pos = 0; pos < size; pos++) {
            matVal += matA[row][pos] * matB[pos][col];
         }
         matC[row][col] = matVal;
      }
   }

}

/*------------------------------------------------------
The time complexity (big O) of matrix multiplication for
two MxM matrices is O(M^3). This is because there
are 3 nested for loops which loop from 0 to M.

The lower growth bounds (omega) is equivalent, because
the 3 nested for loops must always run to completion.

Therefore, the exact growth(theta) will also be equivalent,
O(M^3).

O(M^3) is cubic.
---------------------------------------------------------*/