#ifndef BST_H
#define BST_H

class BST{

private:

    struct node{
        int key;
        node *left;
        node *right;
    };

    node *root;     // reference the very top of our tree

    // Create a leaf node and return a node pointer that references that leaf node
    node *CreateLeaf(int key);

    //  Add helper function that traverses the tree to find the location of where to insert
    void AddLeafPrivate(int key, node *ptr);

    //  Add helper function for PRint
    void PrintInOrderPrivate(node *ptr);

    //  Inspect a certain element in the tree
    //  return a pointer to a node that corresponds to the key value
    node *ReturnNode(int key);

    node *ReturnNodePrivate(int key, node *ptr);

    int FindSmallestPrivate(node *ptr);

    //  Helper to remove node from tree
    void RemoveNodePrivate(int key, node *parent);

    //  Create function capable of removing node
    void RemoveRootMatch();

    //  Create funciton that can remove matching node from tree
    //  Remove node from tree that is not the root node
    //  The node that we want to remove will be marked with match pointer
    //  The parent of that node will be marked with parent pointer
    //  boolean will indicate the relationship between parent and matching node
    void RemoveMatch(node *parent, node *match, bool left);

    //  Helper funciton to remove the subtree
    void RemoveSubTree(node *ptr);

public:

    BST();
    
    ~BST();
    //  Add node to tree that can be called from the main.cpp
    void AddLeaf(int key);

    //  Add a function that prints contents of the tree
    void PrintInOrder();

    //  Helper function to help print children
    int ReturnRootKey();

    //  Print children
    void PrintChildren(int key);

    int FindSmallest();

    //  Remove node from tree
    void RemoveNode(int key);


};





#endif