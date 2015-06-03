// FHsearch_tree with EBookEntry main
// CS 2C, Foothill College, Michael Loceff, creator

#include <iostream>
#include <string>
using namespace std;
#include "FHlazySearchTree.h"
#include "EBookEntry.h"

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

int main()
{
   int k, arraySize;
   FHlazySearchTree<EBookEntry> bookTree;
   PrintBook bookPrinter;

   // read the data from file
   EBookEntryReader bookInput("catalog-short4.txt");
   if (bookInput.readError())
   {
      cout << "couldn't open " << bookInput.getFileName() << " for input.\n";
      exit(1);
   }

   // changing the sort key to SORT_BY_TITLE will not allow duplicate titles, e.g.
   EBookEntry::setSortType(EBookEntry::SORT_BY_ID);
   arraySize = bookInput.getNumBooks();

   // build the tree
   for (k = 0; k < arraySize; k++)
      if (!bookTree.insert(bookInput[k]))
      {
         cout << "NOT INSERTED: ";
         bookPrinter(bookInput[k]);
      }

   // confirm the size:
   cout << "Num Books: " << arraySize
      << ", Tree Size: " << bookTree.size() << endl;

   // test finds
   int START = 1000, STOP = 1020;
   cout << "\n\nAttempting " << STOP - START << " finds: \n";
   for (k = START; k < STOP; k++)
      if (!bookTree.contains(bookInput[k]))
         cout << " !!! NOT FOUND: " << k << ": " << bookInput[k].getTitle() << endl;
      else
      {
         cout << "Found: ";
         bookPrinter(bookInput[k]);
      }

   // test removals
   cout << "\n\nAttempting " << STOP - START << " removals: \n";
   for (k = START; k < STOP; k++)
      if (!bookTree.remove(bookInput[k]))
         cout << " !!!NOT FOUND: " << k << ": " << bookInput[k].getTitle() << endl;

   cout << "\nnew size: " << bookTree.size() << endl;

   bookTree.collectGarbage();
   cout << "\n\nAfter collectGarbage() mSize: " << bookTree.size() << " mSizeHard: " << bookTree.sizeHard();

   /*
   // this will print thousands of books, so be careful
   cout << "\nsearch_tree after deletes:\n";
   bookTree.traverse(bookPrinter);
   */

   return 0;
}
/* ------------------ RUN -------------
Num Books: 4863, Tree Size: 4863


Attempting 20 finds:
Found: 23574: La Monte, Rober, Socialism: Positive , (no data found)
Found: 22740: Unknown, The Apple Dumpling a, (no data found)
Found: 22693: Lang, Jeanie, A Book of Myths, Mythology
Found: 28486: Cole, Everett B, The Weakling, Science fiction
Found: 28488: Moli--re, 1622-, Tartuffeor The Hypoc, Comedies
Found: 28489: Locke, William , The Belov--d Vagabon, PR
Found: 28490: Girl Scouts of , Scouting For Girls, , Girl Scouts -- Handbooks,
Found: 23448: Brown, Ruth Alb, Heart of Gold, People with disabilities
Found: 22599: Karpinski, Loui, The Hindu-Arabic Num, Numerals
Found: 23337: Ing, Dean Charl, Tight Squeeze, Science fiction
Found: 22360: Bradley, Mary H, The Fortieth Door, PS
Found: 23293: Lawrence, Rober, Primitive Psycho-The, (no data found)
Found: 28066: Various, The Christian Founda, Religion and science -- P
Found: 28067: Smith, J. Allen, The Spirit of Americ, Constitutional history --
Found: 28069: Bangs, John Ken, Alice in Blunderland, Fantasy
Found: 28070: Harriman, Alice, A Man of Two Countri, PS
Found: 23205: Various, Notes and Queries, N, Questions and answers --
Found: 22171: Ernst, Paul, 18, The Radiant Shell, Science fiction
Found: 23075: Baum, L. Frank , Ozma of Oz, Oz (Imaginary place) -- F
Found: 29230: Barker, James N, The Indian PrincessL, American drama


Attempting 20 removals:

new size: 4843
Press any key to continue . . .
-------------------------------------------- */