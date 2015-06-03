/*
Bradley Thurston - 11338420
CS2C - Assignment 6
This implementation extends FHhashQP by adding a find()
method. The client must provide a function Hash() and
an accessor getKey()
*/

#ifndef FHHASHQPWFIND_H

#define FHHASHQPWFIND_H

#include "FHhashQP.h"

// -------------------- FHhashQPwFind prototypye----------------------

template <class Object, typename KeyType>
class FHhashQPwFind : public FHhashQP<Object>
{
public:
   const Object find(const KeyType & key);
   class NotFoundException {};

protected:
   int myHashKey(const KeyType & key) const;
   int findPosKey(const KeyType & key) const;
};

// -------------------- FHhashQPwFind Public Method Definitions-------

template <class Object, typename KeyType>
const Object FHhashQPwFind<Object, KeyType>::find(const KeyType & key) {
   
   typename FHhashQP<Object>::HashEntry searchResult;
   searchResult = mArray[findPosKey(key)];

   if (searchResult.state == FHhashQP<Object>::ACTIVE) {
      return searchResult.data;
   }
   else {
      throw NotFoundException();
   }
}


// -------------------- FHhashQPwFind Protected Method Definitions----

//modification to myHash(), uses the key rather than the object to hash
template <class Object, typename KeyType>
int FHhashQPwFind<Object, KeyType>::myHashKey(const KeyType & key) const {

   int hashVal;
   hashVal = Hash(key) % this->mTableSize;

   if (hashVal < 0)
      hashVal += this->mTableSize;

   return hashVal;
}

//modification to findPos(), uses the key rather than the object to get a position.
template <class Object, typename KeyType>
int FHhashQPwFind<Object, KeyType>::findPosKey(const KeyType & key) const
{
   int kthOddNum = 1;
   int index = myHashKey(key);

   while (this->mArray[index].state != FHhashQP<Object>::EMPTY
      && getKey(this->mArray[index].data) != key)
   {
      index += kthOddNum;  // k squared = (k-1) squared + kth odd #
      kthOddNum += 2;   // compute next odd #
      if (index >= this->mTableSize)
         index -= this->mTableSize;
   }

   return index;
}

#endif