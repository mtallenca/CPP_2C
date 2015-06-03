#ifndef Sublist_H

#define Sublist_H

#include <vector>

class Sublist
{
public:
   Sublist(vector<int> *orig = NULL)
      : sum(0), originalObjects(orig) {}
   Sublist addItem(int indexOfItemToAdd);
   void showSublist() const;
   int getSum() const { return sum; } 

private:
   int sum;
   vector<int> *originalObjects;
   vector<int> indices;
};

#endif

Sublist Sublist::addItem(int indexOfItemToAdd){
   Sublist temp = *this;
   temp.sum = this->getSum() + (*temp.originalObjects)[indexOfItemToAdd];
   temp.indices.push_back(indexOfItemToAdd);
   return temp;
}

void Sublist::showSublist() const {
   vector<int>::const_iterator iter;
   int index = 0;
   int stored = 0;

   for (iter = indices.begin(); iter != indices.end(); iter++){
      index = *iter;
      stored = (*originalObjects)[index];
      cout << "   array[" << index << "] = " << stored << ",";
   }
}

