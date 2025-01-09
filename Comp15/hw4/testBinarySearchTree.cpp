
/*
 * BinarySearchTree.cpp
 * COMP15
 * Spring 2020
 Cheryl Melwani
 March 11, 2020
 *
 * Handles Testing of the Binary Search Tree class
 */
#include <iostream>

#include "BinarySearchTree.h"

using namespace std;

int main() {
    //HAVE TESTED:
    //CONTAINS
    //MAX AND MIN
    //COPY CONSTRUCTOR
    //PRE ORDER COPY
    //INSERT
    //TREE HEIGHT
    //NUM_NODES
    //COUNT_TOTAL
    //REMOVE

    BinarySearchTree bst;
    int values[]  = {4, 2, 11, 15, 9, 1, -6, 5, 3, 15, 2, 5, 13, 14};
    int numValues = 14;
    for (int i = 0; i < numValues; i++) {
        bst.insert(values[i]);
    }
    bst.print_tree();
    BinarySearchTree bst_copy_constructor = bst;
    bst_copy_constructor.print_tree();

    cout << "This is the min: " << bst.find_min() << endl;
    cout << "This is the max: " << bst.find_max() << endl;
    if(bst.contains(19) == true) {
        cout << "true" << endl;
    } else {
        cout << "false" << endl;
    }
    cout << "This is the number of nodes in the tree: " << bst.node_count()
    << endl;
    cout << "This is the sum of the count values in the tree: " <<
    bst.count_total() << endl;
    cout << "This is the height of the tree: " << bst.tree_height() << endl;

    //removing root
    bst.remove(4);
    cout << "Remove 4" << endl;
    bst.print_tree();
    //removing leaf
    bst.remove(14);
    cout << "Remove 14" << endl;
    bst.print_tree();
    //removing duplicate
    bst.remove(5);
    cout << "Remove 5" << endl;
    bst.print_tree();
    //removing one child
    bst.remove(1);
    cout << "Remove 1" << endl;
    bst.print_tree();
    //removing one child
    bst.remove(9);
    cout << "Remove 9" << endl;
    bst.print_tree();
    //removing two children
    bst.remove(11);
    cout << "Remove 11" << endl;
    bst.print_tree();
}
