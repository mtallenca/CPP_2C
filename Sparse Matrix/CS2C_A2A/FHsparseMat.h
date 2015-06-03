#ifndef SPARSEMAT_H

#define SPARSEMAT_H

#include "MatNode.h"
#include "FHvector.h"
#include "FHlist.h"

template<class Object>
class SparseMat {

public:
   SparseMat(int r, int c, const Object & defaultVal);
   ~SparseMat(){}

   const Object & get(int r, int c) const;
   bool set(int r, int c, const Object &x);
   MatNode<Object> & set(int r, int c);
   void clear();
   void showSubSquare(int start, int size);
   
protected:
   typedef FHlist< MatNode<Object> > MatRow;
   typedef FHvector<MatRow> MasterCol;

   MasterCol rows;
   Object defaultVal;
   int rowSize, colSize;
};

#endif

template<class Object>
SparseMat<Object>::SparseMat(int r, int c, const Object & defaultVal) {
   if (r < 1 || c < 1) {
      cout << "Invalid matrix size." << endl;
   }
   else {
      rowSize = r;
      colSize = c;
      rows.resize(rowSize);
      this->defaultVal = defaultVal;

      for (int row = 0; row < rowSize; row++){
         MatRow * p = new MatRow;
         rows.push_back(*p);
      }
   }

}

template<class Object>
const Object & SparseMat<Object>::get(int r, int c) const{
   if (r > rowSize - 1 || c > colSize - 1){
      throw OutOfBoundsException();
   }
   else {
      if (!rows[r].empty()){
         typename MatRow::const_iterator iter;
         for (iter = rows[r].begin(); iter != rows[r].end(); iter++){
            if ((*iter).getCol() == c) {
               return (*iter).data;
               break;
            }
            else {
               return defaultVal;
            }
         }
      }
      else {
         return defaultVal;
      }
      
   }
  
}

template<class Object>
bool SparseMat<Object>::set(int r, int c, const Object &x){
   if (r > rowSize - 1 || c > colSize - 1){
      return false;
   }
   else {
      typename MatRow::iterator iter = rows[r].begin();
      while (iter != rows[r].end()){
         if ((*iter).getCol() == c){
            break;
         }
         iter++;
      }
      //no exisiting node with col
      if (iter == rows[r].end() && x != defaultVal){
         rows[r].push_back(MatNode<Object>(c, x));
      }
      //existing node with col
      else if (iter != rows[r].end() && x != defaultVal){
         (*iter).data = x;
      }
      //existing node with col to default
      else if (iter != rows[r].end() && x == defaultVal){
         rows[r].erase(iter); 
         //cout << "removed node.\n";
      }
      return true;
   }
}

template<class Object>
void SparseMat<Object>::clear(){
   for (int r = 0; r < rowSize; r++){
      if (!rows[r].empty()){
         MatRow::iterator start = rows[r].begin();
         MatRow::iterator end = rows[r].end();
         rows[r].erase(start, end);
      }
   }

}

template<class Object>
void SparseMat<Object>::showSubSquare(int start, int size){
   for (int row = start; row < start+size; row++){
      for (int col = start; col < start+size; col++){
         cout << " " << this->get(row, col) << " ";
      }
      cout << endl;
   }
   cout << endl;
}

template<class Object>
MatNode<Object> & SparseMat<Object>::set(int r, int c){
   typename MatRow::iterator iter = rows[r].begin();
   while (iter != rows[r].end()){
      if ((*iter).getCol() == c){
         rows[r].erase(iter);
         break;
      }
      iter++;
   }
   rows[r].push_back(MatNode<Object>(c, defaultVal));
   return rows[r].back();
  
}

//-------Exception Class-------//
class OutOfBoundsException{};
