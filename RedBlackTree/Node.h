// Node.h
#pragma once

// Forward declaration to allow RedBlackTree to access Node's private members
class RedBlackTree;

// Node structure used in Red-Black Tree
class Node
{
    // RedBlackTree needs direct access to private members
    friend class RedBlackTree;

private:
    int value;  // Value stored in the node
    bool isBlack;  // Node color: true = black, false = red
    bool isLeftChild;  // Indicates whether this node is a left child of its parent

    Node* parent;  // Pointer to parent node
    Node* left;   // Pointer to left child
    Node* right;  // Pointer to right child

public:
    // Default Constructor
    Node() : value(0), isBlack(false), isLeftChild(false), parent(nullptr), left(nullptr), right(nullptr) {}
    // Constructor for creating regular tree nodes
    Node(int val, bool black, bool isleftChild, Node* p, Node* l, Node* r)
        : value(val), isBlack(black), isLeftChild(isleftChild), parent(p), left(l), right(r) {}
};