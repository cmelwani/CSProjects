/*
 * BinarySearchTree.cpp
 * COMP15
 * Spring 2020
 Cheryl Melwani
 March 11, 2020
 *
 * Implementation of the Binary Search Tree class.
 * Behaves like a standard BST except that it handles multiplicity
 * If you insert a number twice  and then remove it once, then it will
 * still be in the data structure
 */

#include <cstring>
#include <iostream>
#include <limits>

#include "BinarySearchTree.h"

using namespace std;

/* Purpose of constructor: Initializes the private variables of the class */
BinarySearchTree::BinarySearchTree()
{
    root = nullptr;
}
/* Purpose: Destructor to deallocate all memory stored in the heap */
BinarySearchTree::~BinarySearchTree()
{
        // walk tree in post-order traversal and delete
        post_order_delete(root);
        root = nullptr;  // not really necessary, since the tree is going
                         // away, but might want to guard against someone
                         // using a pointer after deleting
}

/* Purpose: To delete all the nodes in the tree in post order traversal
Return: void
Parameters: A node
*/
void BinarySearchTree::post_order_delete(Node *node)
{
    if (node == nullptr) {
        return;
    }
    post_order_delete(node->left);
    post_order_delete(node->right);
    delete node;
}

// copy constructor
BinarySearchTree::BinarySearchTree(const BinarySearchTree &source)
{
        // use pre-order traversal to copy the tree
        root = pre_order_copy(source.root);
}

// assignment overload
BinarySearchTree &BinarySearchTree::operator=(const BinarySearchTree &source)
{
    if (this == &source) {
        return *this;
    }
    post_order_delete(root);
    root = pre_order_copy(source.root);
    return *this;
}

/* Purpose: Helper function that creates a new node everytime its called
Return: the new node created
Parameters: value, count, left and right -- struct properties of the BST node.
*/
BinarySearchTree::Node *BinarySearchTree::newNode(int value, int c,
    Node *left, Node *right) const {
    Node *new_node = new Node;
    new_node->data = value;
    new_node->count = c;
    new_node->left = left;
    new_node->right = right;
    return new_node;
}

/* Purpose: To copy all the nodes in the tree using a pre order traversal
Return: the nodes being copied
Parameters: A node
*/
BinarySearchTree::Node *BinarySearchTree::pre_order_copy(Node *node) const
{
    if (node == nullptr) {
        return node;
    }
    Node *copy = newNode(node->data, node->count, node->left, node->right);
    copy->left = pre_order_copy(node->left);
    copy->right = pre_order_copy(node->right);
    return copy;

}

/* Purpose: To find the minimum value in the BST. This is the wrapper function
that the user can see.
Return: integer which is the minimum value
Parameters: none
*/
int BinarySearchTree::find_min() const
{
        if (root == nullptr)
                return numeric_limits<int>::max(); // INT_MAX

        return find_min(root)->data;
}

/* Purpose: To find the minimum value in the BST. This is the private helper
function that the user has no access to.
Return: the node with the minimum value
Parameters: a node.
*/
BinarySearchTree::Node *BinarySearchTree::find_min(Node *node) const
{
    if (node->left == nullptr) {
        return node;
    }
    return find_min(node->left);

}

/* Purpose: To find the maximum value in the BST. This is the wrapper function
that the user can see.
Return: integer which is the maximum value
Parameters: none
*/
int BinarySearchTree::find_max() const
{
    if(root == nullptr) {
        return numeric_limits<int>::min();
    }
    return find_max(root)->data;

}

/* Purpose: To find the maximum value in the BST. This is the private helper
function that the user doesn't have access to.
Return: the node with the maximum value
Parameters: a node.
*/
BinarySearchTree::Node *BinarySearchTree::find_max(Node *node) const
{
    if (node->right == nullptr) {
        return node;
    }
    return find_max(node->right);
}

/* Purpose: To check if the value inputted by the user is in the tree. This
contains function is a wrapper function that the user can access.
Return: a bool. True if the value is contained and false if it is not.
Parameters: integer called value.
*/
bool BinarySearchTree::contains(int value) const
{
    return contains(root, value);
}

/* Purpose: To check if the value inputted by the user is in the tree.
This is the private helper function that the user doesnt have access to.
Return: true if the tree contains the value and false if it doesn't.
Parameters: a node and a value.
*/
bool BinarySearchTree::contains(Node *node, int value) const
{
    if (node == nullptr) {
        return false;
    }
    else if (node->data == value) {
        return true;
    }
    else if (value > node->data) {
        return contains(node->right, value);
    }
    else if (value < node->data) {
        return contains(node->left, value);
    }
    return false;
}

/* Purpose: To insert a node into a tree. This is the wrapper function that the
user has access to.
Return: void
Parameters: a value
*/
void BinarySearchTree::insert(int value)
{
        insert(root, nullptr, value);
}

/* Purpose: To insert a node into a tree. This is the private helper function
that actually takes care of inserting the node. Keeps BST invariant constant.
Return: void
Parameters: the node, its parent and the value the user would like to insert.
*/
void BinarySearchTree::insert(Node *node, Node *parent, int value)
{
    if (root == nullptr) {
        root = newNode(value, 1, nullptr, nullptr);
        return;
    }

    if (node == nullptr) {
        if (value < parent->data) {
            parent->left = newNode(value, 1, nullptr, nullptr);
        }
        if (value > parent->data) {
            parent->right = newNode(value, 1, nullptr, nullptr);
        }
        return;
    }

    if (value == node->data) {
        node->count += 1;
        return;
    }
    else if (value < node->data) {
        insert(node->left, node, value);
    }
    else if (value > node->data) {
        insert(node->right, node, value);
    }
}

/* Purpose: To remove a node from a tree. This is the wrapper function that the
user has access to.
Return: boolean that is true if the value was removed and false if it wasn't.
Parameters: a value
*/
bool BinarySearchTree::remove(int value)
{
        // TODO:  Students pick one of the following calls
        //        depending on which remove function they wrote
        //
        //return remove(root, nullptr, value);

        return remove(root, &root, value);
}

// TODO:  Students uncomment one of the following remove functions
//        and implement it.  You only have to do one, though if you
//        want to explore both, that's ok, but turn in the program
//        with one of them working!
//

/* Purpose: To remove a node from a tree. This is the private helper function
that actually takes care of inserting the node. Keeps BST invariant constant
and accounts for the different cases when removing.
Return: void
Parameters: the node, its ptr to the ptr to itself and the value the user would
like to remove.
*/
bool BinarySearchTree::remove(Node *node, Node **ptr_to_ptr_to_me, int value)
{
    if (node == nullptr) {
        return false;
    }
    if (value == node->data && node->count > 1) {
        node->count -= 1;
        return true;
    }
    else if (value < node->data) {
        remove(node->left, &node->left, value);
    }
    else if (value > node->data) {
        remove(node->right, &node->right, value);
    }
    else if (value == node->data && node->count == 1) {
        if(node->right == nullptr && node->left == nullptr) {
            delete node;
            *ptr_to_ptr_to_me = nullptr;
            return true;
        }
        else if (node->right == nullptr && node->left != nullptr) {
            *ptr_to_ptr_to_me = node->left;
            delete node;
            return true;
        }
        else if (node->right != nullptr && node->left == nullptr) {
            *ptr_to_ptr_to_me = node->right;
            delete node;
            return true;
        }
        else if (node->right != nullptr && node->left != nullptr) {
            Node *min = find_min(node->right);
                node->data = min->data;
                remove(node->right, &node->right, node->data);
                return true;
            }
        }
    return false;
}

/* Purpose: To find the tree's height. This is the wrapper function that the
user has access to.
Return: integer that is the tree height
Parameters: none
*/
int BinarySearchTree::tree_height() const
{
        return tree_height(root);
}

/* Purpose: To find the tree height. This is the private helper function that
the user doesn't have access to that actually handles the recursion of finding
the tree height.
Return: Int that is the tree height
Parameters: a node
*/
int BinarySearchTree::tree_height(Node *node) const
{
    if (node == nullptr) {
        return -1;
    }
    int l_height = tree_height(node->left);
    int r_height = tree_height(node->right);
    if (l_height > r_height) {
        return 1 + l_height;
    } else {
        return 1 + r_height;
    }
}

/* Purpose: To return the number of nodes in the tree.
This is the wrapper function that the user has access to.
Return: integer that is the node count.
Parameters: none
*/
int BinarySearchTree::node_count() const
{
        return node_count(root);
}

/* Purpose: To find the number of nodes. This is the private helper function
that the user doesn't have access to that actually handles the recursion of
finding the number of nodes.
Return: Int that is the number of nodes.
Parameters: a node
*/
int BinarySearchTree::node_count(Node *node) const
{
    if (node == nullptr) {
        return 0;
    }
    else {
        return node_count(node->right) + node_count(node->left) + 1;
    }
}

/* Purpose: To return the sum of all nodes in the tree including duplicates.
This is the wrapper function that the user has access to.
Return: integer that is the sum.
Parameters: none
*/
int BinarySearchTree::count_total() const
{
        return count_total(root);
}

/* Purpose: To find the sumof all the node values.
This is the private helper function that the user doesn't have access to that
actually handles the recursion of finding the sum.
Return: Int that is the sum of all the node values (including duplicates)
Parameters: a node
*/
int BinarySearchTree::count_total(Node *node) const
{
    if (node == nullptr) {
        return 0;
    }
     return (node->data * node->count) + count_total(node->right) +
     count_total(node->left);
}

BinarySearchTree::Node *BinarySearchTree::find_parent(Node *node,
                                                      Node *child) const
{
        if (node == nullptr)
                return nullptr;

        // if either the left or right is equal to the child,
        // we have found the parent
        if (node->left == child or node->right == child) {
                return node;
        }

        // Use the binary search tree invariant to walk the tree
        if (child->data > node->data) {
                return find_parent(node->right, child);
        } else {
                return find_parent(node->left, child);
        }
}

// use the printPretty helper to make the tree look nice
void BinarySearchTree::print_tree() const
{
        size_t      numLayers  = tree_height() + 1;
        size_t      levelWidth = 4;
        const char *rootPrefix = "-> ";

        // Need numLayers * levelWidth characters for each layer of tree.
        // Add an extra levelWidth characters at front to avoid if statement
        // 1 extra char for nul character at end
        char *start = new char[(numLayers + 1) * levelWidth + 1];

        print_tree(root, start + levelWidth, start + levelWidth, rootPrefix);
        delete[] start;
}

// Logic and Output Reference:
// https://www.techiedelight.com/c-program-print-binary-tree/
void BinarySearchTree::print_tree(Node *node, char *const currPos,
                                  const char *const fullLine,
                                  const char *const branch) const
{
        if (node == nullptr)
                return;

        // 4 characters + 1 for nul terminator
        using TreeLevel                    = char[5];
        static const int       levelLength = sizeof(TreeLevel) - 1;
        static const TreeLevel UP = ".-- ", DOWN = "`-- ", EMPTY = "    ",
                               CONNECT = "   |";
        // Copies prev into dest and advances dest by strlen(prev)
        auto set = [](char *dest, const char *prev) {
                size_t p = strlen(prev);
                return (char *)memcpy(dest, prev, p) + p;
        };

        print_tree(node->right, set(currPos, EMPTY), fullLine, UP);

        // Clear any characters that would immediate precede the "branch"
        // Don't need to check for root (i.e start of array),fullLine is padded
        set(currPos - levelLength, EMPTY);

        // Terminate fullLine at current level
        *currPos = '\0';

        std::cerr << fullLine << branch << node->data
                  << (node->count > 1 ? "*" : "") << endl;

        // Connect upper branch to parent
        if (branch == UP)
                set(currPos - levelLength, CONNECT);

        // Connect lower branch to parent
        print_tree(node->left, set(currPos, CONNECT), fullLine, DOWN);
}
