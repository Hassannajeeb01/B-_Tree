#include "btree.cpp"
#include <iostream>

int main() {
    BPlusTree tree1(3);
    tree1.insert(1); 
    tree1.insert(3);
    tree1.insert(2);

    cout << tree1.display();

    

    return 0;
}