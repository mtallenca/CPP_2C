#ifndef Sublist_H

#define Sublist_H

#include <vector>

#include "iTunes.h"

class Sublist
{
public:
   Sublist(vector<iTunesEntry> *orig = NULL)
      : sum(0), originalObjects(orig) {}
   Sublist addItem(int indexOfItemToAdd);
   void showSublist() const;
   int getSum() const { return sum; }

   // overloaded functions added by student
   friend int operator+(const int &otherInt, const iTunesEntry &entry);
   friend ostream& operator<<(ostream &stream, const iTunesEntry &entry);  

private:
   int sum;
   vector<iTunesEntry> *originalObjects;
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
   iTunesEntry Object;

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
