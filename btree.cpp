// C++ program for B-Tree insertion 
#ifndef __BTREE_CPP
#define __BTREE_CPP

#include "btree.h"
#include <algorithm>
using namespace std; 

Node::Node(){

   key = new int[DEG];
   children = new Node*[DEG+1];
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

   //if the node is a leaf
   if (currentNode->isLeaf){
      // insertLeaf(k, currentNode);
      // if the node is not full // where full means degree-1 for some dumb af reason
      if (currentNode->size < DEG-1){
         // just insert the damn key
         currentNode->key[currentNode->size] = k; // if size is 1 key[0] has the last value so we insert at key[size]
         currentNode->size++;
      }
      // else (if the node is full)
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
   // if the node is internal
   else{
         // traverse it untill you find a value bigger than k
         int i=0;
         while (k > currentNode->key[i] && i<currentNode->size) i++;
         // access the child
         currentNode = currentNode->children[i];
         // if the child is a leaf
         if (currentNode->size < DEG-1){
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