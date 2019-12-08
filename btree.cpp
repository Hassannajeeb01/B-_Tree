// C++ program for B-Tree insertion 
#ifndef __BTREE_CPP
#define __BTREE_CPP

#include "btree.h"
#include <algorithm>
#include <iostream>
using namespace std; 

Node::Node(){

   key = new int[DEG];
   children = new Node*[DEG+1];

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
         std::cout << "the while loop" << endl;
         int i=0;
         while (k > currentNode->key[i] && i<currentNode->size) i++;
         int childToInsert = i; // save the place number of child that we are going to split, will use it later         
         
         currentNode = currentNode->children[childToInsert];
         // if the child is a leaf
         if (currentNode->isLeaf){
            std::cout << "if the child is a leaf" << endl;
            // if its not full just insert the key
            if (currentNode->size < DEG-1){
               std::cout << "if the child is not full" << endl;
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
               std::cout << "if the child is full" << endl;
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
               std::cout << "have split the node" << endl;

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

               std::cout << "only the child to parent shit left" << endl;
               
               // delete the useless node and access current node's parent
               // Node* uselessNode;
               // uselessNode = currentNode;
               currentNode = currentNode->parent;
               std::cout << "parent is accessible" << endl;
               // delete uselessNode;
               // move the middle key (first val on right) to parent
               int keyToMove = right->key[0];
               std::cout << "well id be damned" << endl;
               // insert the key
               currentNode->size++; // increase size
               std::cout << "no way" << endl;
               currentNode->key[currentNode->size-1] = -1; // just to be safe from garbage value
               std::cout << "cannot happen" << endl;
               // make space for the new key
               i=0;
               std::cout << "wtf" << endl;
               while (keyToMove > currentNode->key[i] && i<currentNode->size-1) i++;
               std::cout << "position of key has been determined" << endl;
               for (int j=currentNode->size-1; j>i; j--){
                  std::cout << "initiating swap" << endl;
                  swap(currentNode->key[j], currentNode->key[j-1]);
               }
               std::cout << "swap done" << endl;
               currentNode->key[i] = keyToMove;
               std::cout << "i think the swap failed" << endl;

               
               // assign the children according to order
               // i=0;
               // while (keyToMove > currentNode->key[i] && i<currentNode->size-1) i++;
               // // move every pointer two places forward
               // for (int j=keyToMove; j<currentNode->size+1; j++){ // goes to size cz current pts = keys+1
               //    Node *temp;
               //    temp = currentNode->children[j];
               //    currentNode->children[j] = currentNode->children[j+2];
               //    currentNode->children[j+2] = temp;
               //    temp = NULL; delete temp;
               //    // swap(currentNode->children[j], currentNode->children[j-2]);
               // }
               std::cout << "assigning children to the slip node's parent" << endl;
               currentNode->children[childToInsert] = left;
               for (int j=currentNode->size+1; j>childToInsert+1; j--){
                  currentNode->children[j] = currentNode->children[j-1]; // move each child one forward
               }
               currentNode->children[childToInsert+1] = right;

               // currentNode->children[2] = left;
               // currentNode->children[3] = right;


               // delete left and right pointers
               left = NULL; right = NULL;
               delete left, right;

            }              
            isKeyInserted = true;
            std::cout << "end of the while loop" << endl;
         }
      }
            

   }
}
      




Node* BPlusTree::search(int k){
   // Your code here
} 

void BPlusTree::remove(int k){
   // Your code here
} 
#endif