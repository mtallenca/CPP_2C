#include <iostream>
using namespace std;

#include "SNE_analyzer.h"
#include "FHsparseMat.h"
#include <math.h>

// --------------- main ---------------
int main()
{
   string outString, longBlankString
      = "                                         "
        "                                         ";
   double x, y, z;
   int k, arraySize, row, col;
   double maxX, minX, maxY, minY, maxZ, minZ,
      xRange, yRange, zRange,
      xConversion, yConversion, zConversion;
   StarNearEarthReader starInput("nearest_stars.txt");
   const int NUM_COLS = 70;
   const int NUM_ROWS = 35;

   if (starInput.readError())
   {
      cout << "couldn't open " << starInput.getFileName() << " for input.\n";
      exit(1);
   }

   cout << starInput.getFileName() << endl;
   cout << starInput.getNumStars() << endl;

   // create an array of objects for our own use:
   arraySize = starInput.getNumStars();
   SNE_Analyzer *starArray = new SNE_Analyzer[arraySize];
   for (k = 0; k < arraySize; k++)
      starArray[k] = starInput[k];

   // display cartesian coords
   for (int k = 0; k < arraySize; k++)
      cout << starArray[k].getNameCommon() << " "
      << starArray[k].coordToString() << endl;

   // get max and min coords for scaling
   maxX = minX = maxY = minY = maxZ = minZ = 0;
   for (int k = 0; k < arraySize; k++)
   {
      x = starArray[k].getX();
      y = starArray[k].getY();
      z = starArray[k].getZ();

      if (x > maxX) {
         maxX = x;
      }else if (x < minX){
         minX = x;
      }

      if (y > maxY) {
         maxY = y;
      }else if (y < minY){
         minY = y;
      }

      if (z > maxZ) {
         maxZ = z;
      }else if (z < minZ){
         minZ = z;
      }
   }
   

   xRange = maxX - minX;
   yRange = maxY - minY;
   zRange = maxZ - minZ;

   
   xConversion = NUM_COLS / xRange;
   yConversion = NUM_ROWS / yRange;
   
   //zConversion = NUM_COLS / zRange;
   //zConversion = NUM_ROWS / zRange;

   SparseMat<char> starMap(NUM_ROWS, NUM_COLS, ' ');
   
   //fill in stars backwards so that 9 nearest stars aren't overwritten
   //on small display matrices
   for (k = arraySize - 1; k >= 0; k--){
      col = round(starArray[k].getX() - minX) * xConversion;
      row = round(starArray[k].getY() - minY) * yConversion;

      //col = round(starArray[k].getZ() - minZ) * zConversion;
      //row = round(starArray[k].getZ() - minZ) * zConversion;

      if (k < 9)
         starMap.set(row, col) = to_string(k+1)[0];   //only works for 0 through 9
      else
         starMap.set(row, col) = '*';
   
   }  
   
   row = round(NUM_ROWS/2);
   col = round(NUM_COLS/2);
   starMap.set(row, col) = 'S';
   
   char star;
   for (row = 0; row < NUM_ROWS; row++)
   {
      outString = longBlankString.substr(0, NUM_COLS);
      // inner loop that builds outString
      for (col = 0; col < NUM_COLS; col++){
         star = starMap.get(row, col);
         if (star != ' '){
            outString[col] = star;
         }
      }
      cout << outString << endl;
   }
   
   delete[] starArray;

   return 0;
}

