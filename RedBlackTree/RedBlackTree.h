// RedBlackTree.h
#pragma once
#include <iostream>
#include "Node.h"

class RedBlackTree
{
    Node* Root; // Root of the tree
    Node* nullLeaf; // Node representing all null leaves
    std::size_t nodeCount; // Number of elements in the tree

private:
    void NullLeaf(); // Creates and initializes the null leaf
    Node* SearchRecHelper(Node* node, int value) const; // Recursive search helper
    Node* SearchIterHelper(int value) const; // Iterative search helper

    // Recursive BST insertion helper
    Node* InsertBST(Node* currentRoot, Node* parent, int value, Node*& insertedNode, bool isLeftChild);
    void LeftRotate(Node* rotationRoot); // Left rotation around a given node
    void RightRotate(Node* rotationRoot); // Right rotation around a given node
    void ColorFlip(Node* node); // Flips colors of node and its children (used during rebalancing)
    void FixInsert(Node* insertedNode); // Restores Red-Black properties after insertion
    void FixDelete(Node* movedUpNode); // Restores Red-Black properties after insertion
    void Transplant(Node* oldSubtreeRoot, Node* newSubtreeRoot); // Replaces one subtree with another

    Node* Minimum(Node* node) const; // Finds the minimum node in a subtree
    // Copies subtree recursively (used in copy constructor / assignment operator)
    Node* CopySubtree(const Node* otherNode, const Node* otherNullLeaf, Node* newParent);
    void ClearSubtree(Node* node); // Deletes all nodes in a subtree

    // Traversal helpers
    void DisplayInOrder(std::ostream& out, Node* node) const;
    void DisplayPreOrder(std::ostream& out, Node* node) const;
    void DisplayPostOrder(std::ostream& out, Node* node) const;
    // Deletes a node given its pointer
    void RemoveByNode(Node* nodeToDelete);

public:
    // Constructors / Destructor
    RedBlackTree();
    RedBlackTree(const RedBlackTree& other);
    RedBlackTree& operator = (const RedBlackTree& other);
    ~RedBlackTree();
    // Tree state queries
    std::size_t getSize() const;
    bool isEmpty() const;
    // Insert operations
    void InsertIter(int value);
    void InsertRec(int value);
    // Remove operations
    void RemoveIter(int value);
    void RemoveRec(int value);
    // Search operations
    bool SearchIter(int value) const;
    bool SearchRec(int value) const;
    // Tree traversals
    void DisplayInOrder(std::ostream& out = std::cout) const;
    void DisplayPreOrder(std::ostream& out = std::cout) const;
    void DisplayPostOrder(std::ostream& out = std::cout) const;
};