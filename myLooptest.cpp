#include "btree.cpp"
#include <iostream>

int main() {
    cout << "Enter degree\n";
    int x;
    cin >> x;
    BPlusTree tree1(x);

    
    int y=1;
    int z;
    cout << "Enter last value" << endl;
    cin >> z;
    while (y<=z){
        tree1.insert(y);
        cout << tree1.display() << endl;
        y++;
    }
    cout << tree1.display();

    

    return 0;
}