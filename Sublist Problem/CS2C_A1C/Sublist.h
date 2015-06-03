#ifndef Sublist_H

#define Sublist_H

#include <vector>

#include "iTunes.h"

template<class T>
class Sublist
{
public:
   Sublist(vector<T> *orig = NULL)
      : sum(0), originalObjects(orig) {}
   Sublist addItem(int indexOfItemToAdd);
   void showSublist() const;
   int getSum() const { return sum; }

   // overloaded functions 
   friend int operator+(const int &otherInt, const iTunesEntry &entry);
   friend ostream& operator<<(ostream &stream, const iTunesEntry &entry);

private:
   int sum;
   vector<T> *originalObjects;
   vector<int> indices;
};

#endif

template<class T>
Sublist<T> Sublist<T>::addItem(int indexOfItemToAdd){
   Sublist temp = *this;
   temp.sum = this->getSum() + (*temp.originalObjects)[indexOfItemToAdd];
   temp.indices.push_back(indexOfItemToAdd);
   return temp;
}

template<class T>
void Sublist<T>::showSublist() const {
   vector<int>::const_iterator iter;
   int index = 0;
   T Object;

   for (iter = indices.begin(); iter != indices.end(); iter++){
      index = *iter;
      Object = (*originalObjects)[index];
      cout << "   array[" << index << "] = " << Object << ",";
   }
}

int operator+(const int &otherInt, const iTunesEntry &entry){
   int sum = otherInt + entry.getTime();
   return sum;
}
ostream& operator<<(ostream &stream, const iTunesEntry &entry){
   cout << entry.getTitle() << " by " << entry.getArtist() << "(" << entry.getTime() << ")";
   return stream;
}
