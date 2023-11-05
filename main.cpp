#include <iostream>
#include <cstdlib>
#include "BST.h"

using namespace std;

int main(){

    int TreeKeys[16] = {50, 76, 21, 4, 32, 64, 15, 52, 14, 100, 83, 2, 3, 70, 87, 80};
    BST new_tree;
    int input = 0;

    for(int i = 0; i < 16; i++){
        new_tree.AddLeaf(TreeKeys[i]);
    }

    new_tree.PrintInOrder();
    cout << endl;

    //  Print all children
    // for(int i = 0; i < 16; i++){
    //     new_tree.PrintChildren(TreeKeys[i]);
    //     cout << endl;
    // }
   
    cout << "The smallest value in the tree is " << new_tree.FindSmallest() << endl;

    cout << "Enter a key value to delete and enter -1 to stop the process\n";
    while(input != -1){
        cout << "Delete Node: ";
        cin >> input;
        {
            if(input != -1){
                cout << endl;
                new_tree.RemoveNode(input);
                new_tree.PrintInOrder();
                cout << endl;
            }
        }
    }

    return 0;
}