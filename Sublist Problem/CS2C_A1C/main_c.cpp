#include <iostream>
using namespace std;

#include <time.h>
#include <vector>
#include "iTunes.h"
#include "Sublist.h"


int main()
{
   const int TARGET = 3600;
   vector<iTunesEntry> dataSet;
   vector<Sublist<iTunesEntry>> choices;
   vector<Sublist<iTunesEntry>>::iterator iter, iterBest;
   int k, j, numSets, max, array_size, masterSum;
   bool foundPerfect;

   // read the data
   iTunesEntryReader tunes_input("itunes_file.txt");
   if (tunes_input.readError())
   {
      cout << "couldn't open " << tunes_input.getFileName()
         << " for input.\n";
      exit(1);
   }

   // time the algorithm -------------------------
   clock_t startTime, stopTime;
   startTime = clock();

   // create a vector of objects for our own use:
   array_size = tunes_input.getNumTunes();
   for (int k = 0; k < array_size; k++)
      dataSet.push_back(tunes_input[k]);

   cout << "Target time: " << TARGET << endl;


   choices.push_back(Sublist<iTunesEntry>(&dataSet));
   foundPerfect = false;

   
   max = 0;
   for (k = 0; k < array_size; k++){
      max = max + dataSet[k];
      
   }

   if (max < TARGET){
      cout << "Error: Target exceeds maximum sum" << endl;
   }
   else {
      for (k = 0; k < dataSet.size(); k++){
         if (foundPerfect){
            break;
         }
         else {
            numSets = choices.size();
            for (j = 0; j < numSets; j++){
               if (choices[j].getSum() + dataSet[k] < TARGET) {
                  choices.push_back(choices[j].addItem(k));
               }
               else if (choices[j].getSum() + dataSet[k] == TARGET){
                  foundPerfect = true;
                  choices.push_back(choices[j].addItem(k));
                  break;
              
               }
            }
         }
      }
      
      iterBest = choices.begin();
      for (iter = choices.begin(); iter != choices.end(); iter++){
         if (iter->getSum() > iterBest->getSum()){
            *iterBest = *iter;
         }
      }

      masterSum = iterBest->getSum();

      cout << "Sublist -----------------------------" << endl;
      cout << "Sum: " << masterSum << endl;
      iterBest->showSublist();
      cout << "\n\n";
      
   }

   
   // time elapsed -------------------
   stopTime = clock();
   // report algorithm time
   cout << "\nAlgorithm Elapsed Time: "
      << (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC
      << " seconds." << endl << endl;

   return 0;
}