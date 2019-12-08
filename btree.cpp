// C++ program for B-Tree insertion 
#ifndef __BTREE_CPP
#define __BTREE_CPP

#include "btree.h"
#include <algorithm>
#include <iostream>
#include "stdlib.h"
using namespace std; 

Node::Node(){

   key = new int[DEG];
   children = new Node*[DEG+1];
   size = 0;

   // initialize the children as NULL;
   for (int i=0; i<DEG+1; i++){
      children[i] = NULL;
   }
}

BPlusTree::BPlusTree(int _m){

   DEG = _m;
   root = NULL;
}

string BPlusTree::display(){
   // Do not edit this function
   ss.str("");
   traverse(root);
   return ss.str();
}

void BPlusTree::traverse(Node* cursor){
   
   // Do not edit this function
   if(cursor!=NULL)
   {
      for(int i = 0; i < cursor->size; i++)
      {
         ss<<"{"<<cursor->key[i]<<"}";
      }
      ss<<" ";
      if(cursor->isLeaf != true)
      {
         for(int i = 0; i < cursor->size+1; i++)
         {
            traverse(cursor->children[i]);
         }
      }
   }
}
Node* BPlusTree::search(int k){
   bool Leaf = root->isLeaf;
   Node *node = root;
   while (true)
   {  
      int i=0;
      while (k>node->key[i] && i<node->size) i++;
      if (k == node->key[i] && node->isLeaf) return node;
      if (node->isLeaf) break;
      node = node->children[i]; // might be a problem here
   }
   return NULL;

} 

void BPlusTree::insert(int k){

   // if the root is NULL
   if (root == NULL){
      // insert the key
      root = new Node;
      root->key[0] = k;
      root->size = 1;
      root->isLeaf = true;
      // dont need to add children since it is a leaf node
      return;
   }
   // create a node and make it euqal to root
   Node* currentNode;
   currentNode = root;

   //if the root is a leaf
   if (currentNode->isLeaf){
      // insertLeaf(k, currentNode);
      // if the node is not full                              // where full means degree-1 for some dumb af reason
      if (currentNode->size < DEG-1){
         // just insert the damn key
         currentNode->size++; // increase size
         currentNode->key[currentNode->size-1] = -1; // just to be safe from garbage value
         // make space for the new key
         int i=0;
         while (k > currentNode->key[i] && i<currentNode->size-1) i++;
         for (int j=currentNode->size-1; j>i; j--){
            swap(currentNode->key[j], currentNode->key[j-1]);
         }
         currentNode->key[i] = k;
      }
      // else (if the root is full)
      else{
         // insert the key
         currentNode->size++; // increase size
         currentNode->key[currentNode->size-1] = -1; // just to be safe from garbage value
         // make space for the new key
         int i=0;
         while (k > currentNode->key[i] && i<currentNode->size-1) i++;
         for (int j=currentNode->size-1; j>i; j--){
            swap(currentNode->key[j], currentNode->key[j-1]);
         }
         currentNode->key[i] = k;

         // split the node...

         // initialize two new nodes
         Node *left = new Node;
         Node *right = new Node;


         // figure out size of the nodes and assign it
         int splitSize = currentNode->size/2;
         left->size = splitSize;
         right->size = splitSize + currentNode->size%2; // if odd, right side gets the extra value

         // assign the keys
         for (int i=0; i<splitSize; i++){
            left->key[i] = currentNode->key[i];
         }
         // assign right child keys according to order
         for (int i=0; i<(splitSize + currentNode->size%2); i++){
            right->key[i] = currentNode->key[i+splitSize];
         }
         // isLeaf
         left->isLeaf = true;
         right->isLeaf = true;
         currentNode->isLeaf = false;

         // assign the parent
         left->parent = currentNode;
         right->parent = currentNode;

         // re initialize the parent by making size =1
         currentNode->size = 1;

         // assign children to the parent (current node)
         currentNode->children[0] = left;
         currentNode->children[1] = right;

         // carry the middle value up
         currentNode->key[0] = right->key[0]; // cz right takes the middle value

         // delete the temporary keys
         left = NULL; right = NULL;
         delete left, right;

         // then call insert(k) on it 
         // insert(k);
      }
   }
   // if the root is internal
   else{
      // traverse it untill you find a value bigger than k
      bool isKeyInserted = false;
      while (!isKeyInserted){
         // std::cout << "the while loop" << endl;
         int i=0;
         while (k > currentNode->key[i] && i<currentNode->size) i++;
         int childToInsert = i; // save the place number of child that we are going to split, will use it later         
         
         currentNode = currentNode->children[childToInsert];
         // if the child is a leaf
         if (currentNode->isLeaf){
            // std::cout << "if the child is a leaf" << endl;
            // if its not full just insert the key
            if (currentNode->size < DEG-1){
               // std::cout << "if the child is not full" << endl;
               // just insert the damn key
               currentNode->size++; // increase size
               currentNode->key[currentNode->size-1] = -1; // just to be safe from garbage value
               // make space for the new key
               i=0;
               while (k > currentNode->key[i] && i<currentNode->size-1) i++;
               for (int j=currentNode->size-1; j>i; j--){
                  swap(currentNode->key[j], currentNode->key[j-1]);
               }
               currentNode->key[i] = k;
            }
            // else if child is full, insert and split and move value up
            else{
               // std::cout << "if the child is full" << endl;
               // insert the key
               currentNode->size++; // increase size
               currentNode->key[currentNode->size-1] = -1; // just to be safe from garbage value
               // make space for the new key
               i=0;
               while (k > currentNode->key[i] && i<currentNode->size-1) i++;
               for (int j=currentNode->size-1; j>i; j--){
                  swap(currentNode->key[j], currentNode->key[j-1]);
               }
               currentNode->key[i] = k;

               // split the node
               // initialize two new nodes
               Node *left = new Node;
               Node *right = new Node;
               // std::cout << "have split the node" << endl;

               // figure out size of the nodes and assign it
               int splitSize = currentNode->size/2;
               left->size = splitSize;
               right->size = splitSize + currentNode->size%2; // if odd, right side gets the extra value

               // assign the keys
               for (int i=0; i<splitSize; i++){
                  left->key[i] = currentNode->key[i];
               }
               // assign right child keys according to order
               for (int i=0; i<(splitSize + currentNode->size%2); i++){
                  right->key[i] = currentNode->key[i+splitSize];
               }
               // isLeaf
               left->isLeaf = true;
               right->isLeaf = true;
               currentNode->isLeaf = false;

               // assign parents
               left->parent = currentNode->parent;
               right->parent = currentNode->parent;

               // std::cout << "only the child to parent shit left" << endl;
               
               // delete the useless node and access current node's parent
               // Node* uselessNode;
               // uselessNode = currentNode;
               currentNode = currentNode->parent;
               // std::cout << "parent is accessible" << endl;
               // delete uselessNode;
               // move the middle key (first val on right) to parent
               int keyToMove = right->key[0];
               // std::cout << "well id be damned" << endl;
               // insert the key
               currentNode->size++; // increase size
               // std::cout << "no way" << endl;
               currentNode->key[currentNode->size-1] = -1; // just to be safe from garbage value
               // std::cout << "cannot happen" << endl;
               // make space for the new key
               i=0;
               // std::cout << "wtf" << endl;
               while (keyToMove > currentNode->key[i] && i<currentNode->size-1) i++;
               // std::cout << "position of key has been determined" << endl;
               for (int j=currentNode->size-1; j>i; j--){
                  // std::cout << "initiating swap" << endl;
                  swap(currentNode->key[j], currentNode->key[j-1]);
               }
               // std::cout << "swap done" << endl;
               currentNode->key[i] = keyToMove;
               // std::cout << "i think the swap failed" << endl;

               
              
               std::cout << "assigning children to the slip node's parent" << endl;
               currentNode->children[childToInsert] = left;
               for (int j=currentNode->size+1; j>childToInsert+1; j--){
                  currentNode->children[j] = currentNode->children[j-1]; // move each child one forward
               }
               currentNode->children[childToInsert+1] = right;

               // delete left and right pointers
               left = NULL; right = NULL;
               delete left, right;

            }
            // if the node is not overloaded (full + 1 key), break the loop cz thekey has been successfully inserted
            if (currentNode->size < DEG){
               isKeyInserted = true;
            }
            // ************************************************************* //
            // AT THIS POINT, DEPTH OF 2 IS ALRIGHT BUT THE ROOT HAS MORE THAN
            // SIZE ELEMENTS AND NEEDS TO SPLIT 
            // *************************************************************
            // if that node is now overloaded, split it and repeat until we have a fine tree
            // check if the node is overloaded
            if (currentNode->size >= DEG){   // should remove the >
               // if its a root
               if (currentNode->parent == NULL){
                  cout << "The node is a root" << endl;
                  // split the node...

                  // initialize two new nodes
                  Node *left = new Node;
                  Node *right = new Node;


                  // figure out size of the nodes and assign it
                  int splitSize = currentNode->size/2;
                  left->size = splitSize;
                  right->size = splitSize + currentNode->size%2 -1; // if odd, right side gets the extra value
                  
                  // assign the keys
                  for (int i=0; i<splitSize; i++){
                     left->key[i] = currentNode->key[i];
                     cout << "assigned to left child" << currentNode->key[i] << endl;
                  }
                  // assign right child keys according to order
                  for (int i=1; i<(splitSize + currentNode->size%2); i++){ // add 1 since mid value moves up
                     right->key[i-1] = currentNode->key[i+splitSize];// skip 1 since mid value moves up
                     cout << "assigned to right child" << currentNode->key[i+splitSize] << endl;
                  }
                  int rootKey = currentNode->key[splitSize];
                  cout << "assigned to the new root" << currentNode->key[splitSize] << endl;
                  // assign children to the left n right child
                  cout << "the size, element of the current node is " << currentNode->size << " " 
                  << currentNode->key[0] << endl;
                  int leftChildSplitSize = (currentNode->size+1)/2;
                  int rightChildSplitSize = (currentNode->size+1)/2 + (currentNode->size+1)%2;


                  for (int i=0; i<leftChildSplitSize; i++){
                     left->children[i] = currentNode->children[i];
                     cout << "assigned child to left has first key and size" 
                     << currentNode->children[i]->key[0] << currentNode->children[i]->size << endl;
                  }
                  for (int i=0; i<rightChildSplitSize; i++){
                     right->children[i] = currentNode->children[i+rightChildSplitSize];
                     cout << "assigned child to right has first key and size" 
                     << currentNode->children[i+rightChildSplitSize]->key[0]
                     << currentNode->children[i+rightChildSplitSize]->size << endl;
                  }
                  // isLeaf
                  left->isLeaf = false;
                  right->isLeaf = false;
                  currentNode->isLeaf = false;

                 

                  // re initialize the parent by making size =1
                  Node *newRoot = new Node;
                  currentNode = newRoot;
                  currentNode->size = 1;
                  currentNode->key[0] = rootKey;

                   // assign the parent
                  left->parent = currentNode;
                  right->parent = currentNode;


                  // assign children to the parent (current node)
                  currentNode->children[0] = left;
                  currentNode->children[1] = right;

                  // finally, make the current node the root node
                  root = currentNode;
                  // carry the middle value up NO NEED NOW
                  // currentNode->key[0] = right->key[0]; // cz right takes the middle value

                  // delete the temporary keys
                  left = NULL; right = NULL;
                  delete left, right;

                  // since all work is finally done
                  isKeyInserted = true;
                  cout << "key has been inserted" << endl;

               }
               // else if its internal
               // split the node

               // assign children to the left n right
               // if the node is not the root
                  // carry the middle node up and assign child
               // if the node is a root
                  // make a new node and make it the root     
                  // assign children
            }     
            // isKeyInserted = true;
            std::cout << "end of the while loop" << endl;
         }
         std::cout<< "the outer while loop" << endl;

         // isKeyInserted = true;
      }
            

   }
}
      






void BPlusTree::remove(int k){
   // traverse to the leaf which contains the key
   // ****************************************************
   // put in comments cz more generalized form implemented
   // **************************************************
   // Node *keyNode = search(k); // search returns the leaf by itself
   // // return if the key does not exist
   // // traverse the node 
   // int i=0;
   // while (keyNode->key[i]!=k) i++;
   // // remove the key by moving all keys 1 step back and decreasing size by 1
   // for (int j=i; j<keyNode->size-1; j++){
   //    keyNode->key[j] = keyNode->key[j+1];
   // }
   // keyNode->size--;

   //  remove from all levels without refactoring
   bool Leaf = root->isLeaf;
   Node *node = root;
   while (true)
   {  
      int i=0;
      while (k>node->key[i] && i<node->size) i++;
      if (k == node->key[i]){
         // remove the key
         // remove the key by moving all keys 1 step back and decreasing size by 1
         for (int j=i; j<node->size-1; j++){
            node->key[j] = node->key[j+1];
         }
         node->size--;
      }
      if (node->isLeaf) break;
      node = node->children[i]; // might be a problem here
   }


   

} 
#endif