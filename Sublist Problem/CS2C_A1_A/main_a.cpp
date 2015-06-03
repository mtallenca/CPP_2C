#include <iostream>
using namespace std;

#include <vector>
#include "Sublist.h"

int main()
{
   int TARGET = 180;
   vector<int> dataSet;
   vector<Sublist> choices;
   vector<Sublist>::iterator iter, iterBest;
   int k, j, numSets, max, masterSum;
   bool foundPerfect;

   dataSet.push_back(20); dataSet.push_back(12); dataSet.push_back(22);
   dataSet.push_back(15); dataSet.push_back(25);
   dataSet.push_back(19); dataSet.push_back(29);
   dataSet.push_back(18);
   dataSet.push_back(11); dataSet.push_back(13); dataSet.push_back(17);

   choices.clear();
   cout << "Target time: " << TARGET << endl;


   // code provided by student
   choices.push_back(Sublist(&dataSet));
   foundPerfect = false;

   max = 0;
   for (k = 0; k < dataSet.size(); k++){
      max += dataSet[k];
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

   return 0;

}