/*
Bradley Thurston - 11338420
CS2C - Assignment 5
This implementation of splay trees uses top-down splaying. The
template is derived from the base class FHsearch_tree. The
implementation assumes that the only operator overloaded is <.
*/

#ifndef FHSPLAYTREE_H

#define FHSPLAYTREE_H

#include "FHsearch_tree.h"

// -------------------- FHsplayTree Prototype ----------------------
template <class Comparable>
class FHsplayTree : public FHsearch_tree<Comparable>
{
public:
   FHsplayTree() : FHsearch_tree<Comparable>() { }
   ~FHsplayTree() {}

   // override base class
   bool insert(const Comparable &x);
   bool remove(const Comparable &x);
   bool contains(const Comparable &x);
   const Comparable & find(const Comparable &x);
   
   // new method
   const Comparable &showRoot();

protected:
   void splay(FHs_treeNode<Comparable> * & root, const Comparable & x);
   void rotateWithLeftChild(FHs_treeNode<Comparable> * & k2);
   void rotateWithRightChild(FHs_treeNode<Comparable> * & k2);
  
};

// -------------------- FHsplayTree Public Method Definitions ----

template <class Comparable>
bool FHsplayTree<Comparable>::insert(const Comparable &x){
  
   if (this->mRoot == NULL) {
      this->mRoot = new FHs_treeNode<Comparable>(x);
      this->mSize++;
      return true;
   }
   else {
      splay(this->mRoot, x);
      if (x < this->mRoot->data) {
         mRoot = new FHs_treeNode<Comparable>(x, this->mRoot->lftChild, this->mRoot);
         this->mSize++;
         return true;
      }
      else if (this->mRoot->data < x) {
         mRoot = new FHs_treeNode<Comparable>(x, this->mRoot, this->mRoot->rtChild);
         this->mSize++;
         return true;
      }
      else {
         return false;        //x is already in tree
      }
   }
}

template <class Comparable>
bool FHsplayTree<Comparable>::remove(const Comparable &x){
   FHs_treeNode<Comparable> * newRoot = NULL;
   if (this->mRoot == NULL) {
      return false;
   }
   else {
      splay(this->mRoot, x);
      if (this->mRoot->data < x || x < this->mRoot->data){
         return false;
      }
      if (this->mRoot->lftChild == NULL) {
         newRoot = this->mRoot->rtChild;
      }
      else {
         newRoot = this->mRoot->lftChild;
         splay(newRoot, x);
         newRoot->rtChild = this->mRoot->rtChild;
      }
      delete mRoot;
      mRoot = newRoot;
      this->mSize--;
      return true;
   }
}

//this is not a true override, but an overload, because
//we are "losing" the const modifier on the function.contains()
//will modify the tree due to a splay() call deeper down, thus
//we cannot declare it to be const.
template <class Comparable>
bool FHsplayTree<Comparable>::contains(const Comparable &x){
   try { 
      find(x);
   }
   catch (NotFoundException) {
      return false;
   }
   return true;
}

//like contains() this is not a true override, but an overload,
//as we are "losing" the const function modifier.
template <class Comparable>
const Comparable & FHsplayTree<Comparable>::find(const Comparable &x){
   splay(this->mRoot, x);
   if (this->mRoot->data < x || x < this->mRoot->data) {
      throw typename FHsearch_tree<Comparable>::NotFoundException();
   }
   else {
      return this->mRoot->data;
   }
}


/* -returns the mRoot data, or an automatic default object
if there is no master root.This is useful for debugging
and proving that the class really is splaying.*/
template <class Comparable>
const Comparable & FHsplayTree<Comparable>::showRoot() {
   return this->mRoot != NULL ? this->mRoot->data : Comparable(); 
}


// -------------------- FHsplayTree Protected Method Definitions----

/* -this method is analyzed in depth in the modules and a detailed algorithm is given there.*/
template <class Comparable>
void FHsplayTree<Comparable>::splay(FHs_treeNode<Comparable> * & root, const Comparable & x){

   FHs_treeNode<Comparable> * rightTree = NULL, *leftTree = NULL, *rightTreeMin = NULL,
      *leftTreeMax = NULL;

   while (root != NULL) {
      if (x < root->data) {
         if (root->lftChild == NULL) {                 //x not in tree, break
            break;
         }
         else if (x < root->lftChild->data) {         //zig zig (left)  
            rotateWithLeftChild(root);
            if (root->lftChild == NULL) {       //x not in tree; break
               break;
            }
         }
         rightTree == NULL ? rightTree = root :
            rightTreeMin->lftChild = root;
         rightTreeMin = root;
         root = root->lftChild;
      }
      else if (root->data < x){
         if (root->rtChild == NULL){         //x not in tree, break
            break;
         }
         else if (root->rtChild->data < x) {       //zig zig (right)
            rotateWithRightChild(root);
            if (root->rtChild == NULL) {        //x not in tree, break
               break;
            }
         }
         leftTree == NULL ? leftTree = root :
            leftTreeMax->rtChild = root;
         leftTreeMax = root;
         root = root->rtChild;
      }
      else {         //found x
         break;
      }
   }

   if (leftTree != NULL) {
      leftTreeMax->rtChild = root->lftChild;
      root->lftChild = leftTree;
   }
   if (rightTree != NULL) {
      rightTreeMin->lftChild = root->rtChild;
      root->rtChild = rightTree;
   }
}

   /* -this is(almost) identical with the version found in FHavlTree.h.
   Make the trivial adjustments and you've got it.*/
template <class Comparable>
void FHsplayTree<Comparable>::rotateWithLeftChild(FHs_treeNode<Comparable> * & k2){
   
   FHs_treeNode<Comparable> *k1 = k2->lftChild;
   k2->lftChild = k1->rtChild;
   k1->rtChild = k2;
   k2 = k1;
}

   /* -this is(almost) identical with the version found in FHavlTree.h.
   Make the trivial adjustments and you've got it.*/
template <class Comparable>
void FHsplayTree<Comparable>::rotateWithRightChild(FHs_treeNode<Comparable> * & k2){

   FHs_treeNode<Comparable> *k1 = k2->rtChild;
   k2->rtChild = k1->lftChild;
   k1->lftChild = k2;
   k2 = k1;
}


#endif