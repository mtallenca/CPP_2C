#include <iostream>
using namespace std;

#include "FHhashQPwFind.h"
#include "EBookEntry.h"
#include <time.h>

// -------------------- Print EBook -------------------

class PrintBook
{
public:
   void operator()(EBookEntry book)
   {
      cout << book.getETextNum() << ": " << book.getCreator().substr(0, 15)
         << ", " << book.getTitle().substr(0, 20)
         << ", " << book.getSubject().substr(0, 25) << endl;
   }
};


int getKey(const EBookEntry & item);
//string getKey( const EBookEntry & item);

int Hash(int key);
int Hash(const string & key);
int Hash(const EBookEntry &item);


// -------------------- Main -------------------

int main()
{
   const int NUM_RANDOM_INDICES = 25;
   int randomIndices[NUM_RANDOM_INDICES];
   EBookEntry book;
   PrintBook BookPrinter;
   srand(time(NULL)); // randomize seed

   // create a QP hash table of EBooks
    FHhashQPwFind<EBookEntry, int> hashTable; // for ID equality
   // FHhashQPwFind<EBookEntry, string> hashTable; // for any string equality

   // two books can be identical in different ways:  ID or author
    EBookEntry::setSortType(EBookEntry::SORT_BY_ID);
   // EBookEntry::setSortType(EBookEntry::SORT_BY_CREATOR);

   // read the data from file
   EBookEntryReader bookInput("catalog-short4.txt");
   if (bookInput.readError())
   {
      cout << "couldn't open " << bookInput.getFileName() << " for input.\n";
      exit(1);
   }

   cout << bookInput.getFileName() << endl;
   cout << bookInput.getNumBooks() << endl << endl;

   // insert all books into the hash table (if SORT_BY_ID) or fewer (If SORT_BY_CREATOR)
   for (int i = 0; i < bookInput.getNumBooks(); i++) {
      hashTable.insert(bookInput[i]);
   }

   cout << "Random Ebooks: " << endl;

   // generate some random indices into the EBookEntryReader vector
   // and display NUM_RANDOM_INDICES books from array
   for (int i = 0; i < NUM_RANDOM_INDICES; i++) {
      randomIndices[i] = rand() % bookInput.getNumBooks();
      BookPrinter(bookInput[randomIndices[i]]);
   }

   // attempt to find on the selected key
   cout << "\nThe same random books from the hash table " << endl;
   for (int k = 0; k < NUM_RANDOM_INDICES; k++)
   {
      try
      {
          book = hashTable.find(bookInput[randomIndices[k]].getETextNum());
         // book = hashTable.find( bookInput[ randomIndices[k] ].getCreator() );
         BookPrinter(book);
      }
      catch (...)
      {
         cout << "Book Not Found.\n";
      }
   }

   // test known failures exceptions:
   cout << "\nTest Failures:\n";
   try
   {
       book = hashTable.find(-3);
       // book = hashTable.find( "Jack Kerouac" );
   }
   catch (...)
   {
      cout << "Book Not Found.\n";
   }

   // more failures
   try
   {
   }
   catch (...)
   {
   }

   try
   {
   }
   catch (...)
   {
   }
}

// -------------------- Accessor Function------------


// used for ID equality
int getKey(const EBookEntry & item) {
   return item.getETextNum();
}


/*
// used for author equality
string getKey( const EBookEntry & item ) {
return item.getCreator();
}
*/

// -------------------- Hash Functions---------------

//hash routine for ints
int Hash(int key) {
   return key;
}

//hash routine for strings
int Hash(const string & key) {
   unsigned int k, retVal = 0;

   for (k = 0; k < key.length(); k++)
      retVal = 37 * retVal + key[k];

   return retVal;
}

//hash routine for Ebooks
int Hash(const EBookEntry &item) {
   return Hash(getKey(item));
}
