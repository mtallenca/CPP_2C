#ifndef SPARSEMATWMULT_H

#define SPARSEMATWMULT_H

#include "FHsparseMat.h"

template <class Object>
class SparseMatWMult : public SparseMat<double>
{
public:
   SparseMatWMult(int numRows, int numCols) : SparseMat(numRows, numCols, 0.0){}
   bool matMult(SparseMatWMult<Object> & a, SparseMatWMult<Object> & b);
};

template <class Object>
bool SparseMatWMult<Object>::matMult(SparseMatWMult<Object> & a, SparseMatWMult<Object> & b){

   typename MatRow::iterator iter;
   typename MatRow::iterator iterB;
   int aCol;
   double value;

   FHvector<int> aRowNum;
   FHvector<int> bColNum;
   FHvector<double> rowData;
   FHvector<double> colData;
   
   //check valid matrix multiplication
   if (a.rowSize < 1 || b.rowSize < 1
      || a.colSize < 1 
      || b.colSize < 1
      || a.rowSize != b.colSize) {
      return false;
   }
   
   //store all node pairings to a nondefault value
   //and coordinates of the node

   else {
      for (int aRows = 0; aRows < a.rowSize; aRows++) {
         if (!a.rows[aRows].empty()) {
            for (iter = a.rows[aRows].begin(); iter != a.rows[aRows].end(); iter++) {
               aCol = (*iter).getCol();
               if (!b.rows[aCol].empty()) {
                  for (iterB = b.rows[aCol].begin(); iterB != b.rows[aCol].end(); iterB++) {
                     rowData.push_back((*iter).data);
                     colData.push_back((*iterB).data); 
                     aRowNum.push_back(aRows);
                     bColNum.push_back((*iterB).getCol());
                  }
               }
            }
         }
      }

      //clear this matrix and set size to product matrix
      a.clear();
      a.colSize = b.colSize;

      //multiply paired nodes, add this product value
      //to exisiting value at node location in product matrix
      for (int x = 0; x < aRowNum.size(); x++) {   
         value = a.get(aRowNum[x], bColNum[x]);
         value += rowData[x] * colData[x];
         a.set(aRowNum[x], bColNum[x], value);
      }
      
      return true;
   }
}
   

#endif