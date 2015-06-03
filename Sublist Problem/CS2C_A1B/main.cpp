#include <iostream>
#include <string>
using namespace std;

template<class T>
class SafeArray
{
   static const long MAX_ARRAY_SIZE = 100000L;
   T *data;
   long size;
public:
   SafeArray(long sz = 100, T initVal = T());
   SafeArray(const SafeArray & rhs);
   ~SafeArray();
   T &operator[](long index);
   SafeArray &operator=(const SafeArray & rhs);
};

int main()
{
   int k;
   SafeArray<float> rainfall(5);

   // assign data and go out-of-bounds
   for (k = -3; k < 10; k++)
      rainfall[k] = 17 + .03 * k;

   cout << "The array after some assignments:\n";
   for (k = -3; k < 10; k++)
      cout << rainfall[k] << endl;

   // test the assignment operator
   SafeArray<float> weather(40);
   weather = rainfall;
   cout << "Did weather[2] get assigned rainfall[2]?\n";
   cout << weather[-2] << " " << rainfall[2] << endl;

   return 0;
}

// SafeArray method definitions -------------------
template <class T>
SafeArray<T>::SafeArray(long sz, T initVal)
{
   if (sz < 1)
      size = 1;
   else if (sz > MAX_ARRAY_SIZE)
      size = MAX_ARRAY_SIZE;
   else
      size = sz;
   data = new T[size];
   for (int k = 0; k < size; k++)
      data[k] = initVal;
}

template <class T>
SafeArray<T>::SafeArray(const SafeArray<T>& rhs) : data(NULL)
{
   *this = rhs;
}

template <class T>
SafeArray<T>::~SafeArray()
{
   delete[] data;
}

template <class T>
T &SafeArray<T>::operator [](long index)
{
   static T staticBuff;

   if (index < 0 || index >= size)
      return staticBuff;
   else
      return data[index];
}

template <class T>
SafeArray<T> &SafeArray<T>::operator=(const SafeArray<T> & rhs)
{
   // always check this
   if (this == &rhs)
      return (*this);

   delete[] data; // clear old data
   size = rhs.size;
   data = new T[size];
   for (int k = 0; k < size; k++)
      data[k] = rhs.data[k];
   return *this;
}