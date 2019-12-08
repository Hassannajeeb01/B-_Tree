#include "btree.cpp"
#include <iostream>

int main() {
    cout << "Enter degree\n";
    int x;
    cin >> x;
    BPlusTree tree1(x);

    cout << "Enter keys to enter. Enter -1 when done\n";
    
    int y;
    while (true){
        cin >> y;
        if (y==-1) break;
        tree1.insert(y);
        cout << tree1.display() << endl;
    }
    cout << tree1.display();

    

    return 0;
}