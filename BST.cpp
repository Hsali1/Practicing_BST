#include <iostream>
#include <cstdlib>
#include "BST.h"

using namespace std;

BST::BST(){
    root = nullptr;     // When we first create a BST, we make sure our root pointer doesn't point to anything
}
// Create a leaf node and return a node pointer that references that leaf node
BST::node *BST::CreateLeaf(int key){
    node *n = new node;
    n->key = key;
    n->left = nullptr;
    n->right = nullptr;
    return n;
}

//  All we want AddLeaf to do is call AddLeafPrivate function
//  We want the AddLeaf funciton to be called from main.cpp (that's why it's not private)
//  We always want it to start at the root.
//  In the main, we only care about the value to insert, we don't care about the location
//  Make sure we always start searching at the root
void BST::AddLeaf(int key){
    AddLeafPrivate(key, root);
}

//  This function cares about the location
void BST::AddLeafPrivate(int key, node *ptr){
    /*
        Summary: Checking to see if the tree is empty.
        If yes, create new leaf and make root pointer point to that leaf.
        if no, compare to see if key is <, > or = to the current key value
        if less, look down left point and see if left pointer is pointing to anything
            if it is pointing to somethign keey going left recursively
        if more, go right recursively until we reach the end.
    */
    if(root == nullptr){
        //  if tree is empty, create a new leaf and make it root
        root = CreateLeaf(key);
    }else if(key < ptr->key){   // if key is less than the current node we are looking at
        // if key is less than node, they we go left
        // but we need to check if there is anything on the left
        if(ptr->left != nullptr){
            AddLeafPrivate(key, ptr->left);
            //  This will start us back at the top. The root is still not null so we will come back to these checks
            //  If we know we need to go left, but the left is already pointing to something, then we keep moving down
        }else{
            //  The current node's left pointer is not pointing to anything
            ptr->left = CreateLeaf(key);
        }
    }else if(key > ptr->key){   // if key is greater than the current node we are looking at
        // if key is greater than node, they we go right
        // but we need to check if there is anything on the right
        if(ptr->right != nullptr){
            AddLeafPrivate(key, ptr->right);
            //  This will start us back at the top. The root is still not null so we will come back to these checks
            //  If we know we need to go left, but the left is already pointing to something, then we keep moving down
        }else{
            //  The current node's left pointer is not pointing to anything
            ptr->right = CreateLeaf(key);
        }
    }else{
        //  In this case the key we are trying to add = the key inside the node we are looking at
        cout << "They key " << key << " has already been added to the tree\n"; 
    }
}

void BST::PrintInOrder(){
    //  Start it's traversal at the root
    PrintInOrderPrivate(root);
}

void BST::PrintInOrderPrivate(node *ptr){
    //  Recursively traverse the tree from lowest val to highest
    if(root != nullptr){
        if(ptr->left != nullptr){   //  if the left pointer of the current node that we are looking at is pointing to something
            PrintInOrderPrivate(ptr->left);
        }
        //  Print the contents of the current node
        cout << ptr->key << " ";
        if(ptr->right != nullptr){  //  If the right point is point to something or not
            PrintInOrderPrivate(ptr->right);
        }
    }else{
        cout << "Tree is emptry\n";
    }
}

BST::node *BST::ReturnNode(int key){
    return ReturnNodePrivate(key, root);
}

BST::node *BST::ReturnNodePrivate(int key, node *ptr){
    if(ptr != nullptr){
        if(ptr->key == key){
            return ptr;
        }else{
            if(key < ptr->key){
                return ReturnNodePrivate(key, ptr->left);
            }else{
                return ReturnNodePrivate(key, ptr->right);
            }
        }
    }else{
        return nullptr;
    }
}

int BST::ReturnRootKey(){
    if(root != nullptr){
        return root->key;
    }else{
        return -1000;
    }
}

/*
Summary: we pass in the key of the node wa wanna look at
        if we have a node with that key we will make our pointer point to that node
        otherwise make pointer point to null
            if ptr == nullptr we say key does not exist
            if !nullptr we found node with key in tree and print it's key
            also print left and right child
*/
void BST::PrintChildren(int key){
    //  Remember if the key that we enter exists in the tree
    //  The Return Node returns a pointer to that node with that value
    node *ptr = ReturnNode(key);
    if(ptr != nullptr){
        cout << "Parent Node = " << ptr->key << endl;
        //  if the following statement is true, then execute code 1 otherwise execute code 2
        ptr->left == nullptr ? 
        cout << "Left child = NULL\n" :
        cout << "Left child = " << ptr->left->key << endl;

        ptr->right == nullptr ? 
        cout << "Right child = NULL\n" :
        cout << "Right child = " << ptr->right->key << endl;
    }else{
        cout << "Key " << key << " does not exist\n";
    }
}

int BST::FindSmallest(){
    //  Make sure FindSmallestPrivate starts recurion at the root
    return FindSmallestPrivate(root);
}

int BST::FindSmallestPrivate(node *ptr){
    if(root == nullptr){
        cout << "The tree is empty\n";
        return -1000;
    }else{
        if(ptr->left != nullptr){
            return FindSmallestPrivate(ptr->left);
        }else{
            return ptr->key;
        }
    }
}


void BST::RemoveNode(int key){
    //  We want to figure out what node we are trying to delete
    //  Make sure it starts the recursive process at the root
    RemoveNodePrivate(key, root);
}

void BST::RemoveNodePrivate(int key, node *parent){
    if(root != nullptr){
        if(root->key == key){
            RemoveRootMatch();
        }else{
            //  Make sure key value is less than current key value
            //  Make sure left poitner is pointing to node
            if((key < parent->key) && (parent->left != nullptr)){
                parent->left->key == key ?
                //  if left nodes key == key, call helper funciton to remove node from tree
                RemoveMatch(parent, parent->left, true) :
                //  Recursiveley call the RemoveNodePrivate function to keep checking
                RemoveNodePrivate(key, parent->left);
            }else if((key > parent->key) && (parent->right != nullptr)){
                parent->right->key == key ?
                //  if right nodes key == key, call helper funciton to remove node from tree
                RemoveMatch(parent, parent->right, false) :
                //  Recursiveley call the RemoveNodePrivate function to keep checking
                RemoveNodePrivate(key, parent->right);
            }else{
                cout << "They key: " << key << " was not found in tree\n";
            }
        }
    }else{
        cout << "The tree is empty\n";
    }
}

/*
Summary:
If our tree is not empty, we will go ahead and remove the root node
    create a deletion pointer.
    store current root key value in variable rootkey
    create variabel smallestinRightsubtree incase we have root with 2 kids
    case1 - 0 children
        simply make root pointer nullptr and delete root
    case2 - 1 children
        2 cases for case 1
        (root->left == nullptr) && root->right == nullptr
            make root point to right child (root = root->right)
            disconnect the old root from the tree (delptr->right = nullptr)
            delete the old root (delete delptr)
        (root->left != nullptr) && (root->right == nullptr)
            make root point to left child (root = root->left)
            disconnect the old root from the tree (delptr->left = nullptr)
            delete the old root (delete delptr)
    case3 - 2 children
        Find smallest value in the right subtree (smallestInRightSubtree = FindSmallestPrivate(root->right);)
        remove that node that we just found from the tree (RemoveNodePrivate(smallestInRightSubtree, root);)
        overwrite the root key with the value of new node key (root->key = smallestInRightSubtree;)
If the tree is empty we will print message
*/
void BST::RemoveRootMatch(){
    if(root != nullptr){
        node *delptr = root;
        int rootKey = root->key;
        int smallestInRightSubtree;

        //  Case 0 - root not has 0 children
        if((root->left == nullptr) && root->right == nullptr){
            root = nullptr;
            delete delptr;
        }
        //  Case 1 - root not has 1 child
        //  for case one the left or right child could be present but not both
        //  so we need to do 2 else if statements
        else if((root->left == nullptr) && (root->right != nullptr)){
            root = root->right;
            //  Disconnect the old root from the tree
            delptr->right = nullptr;
            //  Delete root
            delete delptr;
            cout << "The root node with key " << rootKey << " was deleted. " <<
                    " The new root contains key " << root->key << endl;
        }else if((root->left != nullptr) && (root->right == nullptr)){
            root = root->left;
            //  Disconnect the old root from the tree
            delptr->left = nullptr;
            //  Delete root
            delete delptr;
            cout << "The root node with key " << rootKey << " was deleted. " <<
                    " The new root contains key " << root->key << endl;
        } 
        //  Case 2 - root not has 2 children
        else{
            //  Remember we make the smallest number in the right sub-tree the root
            smallestInRightSubtree = FindSmallestPrivate(root->right);
            RemoveNodePrivate(smallestInRightSubtree, root);
            root->key = smallestInRightSubtree;
            cout << "The root key containing key " << rootKey << " was overwritten with key " <<
            root->key << endl;
        }
    }else{
        cout << "Can not remove root. The tree is empty\n";
    }
}


void BST::RemoveMatch(node *parent, node *match, bool left){
    if(root != nullptr){
        node *delptr;
        //  Grab the key that is stored inside the current node that weanna delete
        int matchKey = match->key;
        //  Create variable incase node we want to delete has 2 children
        int smallestInRightSubtree;
        // case 0 - 0 children
        if((match->left == nullptr) && (match->right == nullptr)){
            // if both left and right are nullptr
            delptr = match;
            // check if the delptr is the left or right child of parent node
            left == true ? parent->left = nullptr : parent->right = nullptr;
            delete delptr;
            cout << "The node containing key " << matchKey << " was removed\n";
        }else if((match->left == nullptr) && (match->right != nullptr)){
            left == true ? parent->left = match->right : parent->right = match->right;
            //  Disconnect mathcing node from tree
            match->right = nullptr;
            delptr = match;
            delete delptr;
            cout << "The node containing key " << matchKey << " was removed\n";
        }else if((match->left != nullptr) && (match->right == nullptr)){
            left == true ? parent->left = match->left : parent->right = match->left;
            //  Disconnect mathcing node from tree
            match->left = nullptr;
            delptr = match;
            delete delptr;
            cout << "The node containing key " << matchKey << " was removed\n";
        }else{
            // case 2 matching node has 2 children
            smallestInRightSubtree = FindSmallestPrivate(match->right);
            RemoveNodePrivate(smallestInRightSubtree, match);
            match->key = smallestInRightSubtree;
        }
    }else{
        cout << "Cannot rmeove match, the tree is empty\n";
    }
}

BST::~BST(){
    RemoveSubTree(root);
}

void BST::RemoveSubTree(node *ptr){
    //  We will do post order traversal to remove the items in the binary tree
    //  First keep going left -> keep going right -> process node
    // if the current node we are looking at is not pointing to null
    if(ptr != nullptr){
        if(ptr->left != nullptr){
            RemoveSubTree(ptr->left);
        }
        if(ptr->right != nullptr){
            RemoveSubTree(ptr->right);
        }
        cout << "Deleting the node containing key" << ptr->key << endl;
        delete ptr;
    }
}