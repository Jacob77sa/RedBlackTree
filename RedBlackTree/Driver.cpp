#include <iostream>
#include "RedBlackTree.h"

int main()
{
    std::cout << "==================== Iterative Test ====================";
    // Test 1: Iterative operations
    RedBlackTree iterTree;
    std::cout << "\nIs Tree Empty? " << (iterTree.isEmpty() ? "Yes" : "No")
              << "\nSize: " << iterTree.getSize() << "\n";
    // Insert values using iterative method
    iterTree.InsertIter(10);
    iterTree.InsertIter(13);
    iterTree.InsertIter(14);
    iterTree.InsertIter(15);
    iterTree.InsertIter(11);
    iterTree.InsertIter(9);
    iterTree.InsertIter(12);
    iterTree.InsertIter(10);  // Duplicate - should be ignored

    std::cout << "\n\tDisplay of the Tree After Insertion\n";
    std::cout << "Inorder: ";
    iterTree.DisplayInOrder();  // Displays in sorted order
    std::cout << "Preorder: ";
    iterTree.DisplayPreOrder();  // Displays root first
    std::cout << "Postorder: ";
    iterTree.DisplayPostOrder();  // Displays leaves first
    std::cout << "New Size: " << iterTree.getSize() << "\n\n";

    // Search tests
    std::cout << "Searching For 11: " << (iterTree.SearchIter(11) ? "FOUND\n" : "NOT FOUND\n");
    std::cout << "Searching For 77: " << (iterTree.SearchIter(77) ? "FOUND\n" : "NOT FOUND\n");

    // Delete tests
    iterTree.RemoveIter(13);
    iterTree.RemoveIter(10);
    iterTree.RemoveIter(100);  // Non-existent value

    std::cout << "\n\tDisplay After Removing\n";
    std::cout << "Inorder: ";
    iterTree.DisplayInOrder();
    std::cout << "Size After Remove: " << iterTree.getSize() << "\n\n";

    // Test 2: Recursive operations
    std::cout << "==================== Recursive Test ====================";
    RedBlackTree recTree;
    std::cout << "\nIs Tree Empty? " << (recTree.isEmpty() ? "Yes" : "No") 
              << "\nSize: " << recTree.getSize() << "\n";

    // Insert values using recursive method
    recTree.InsertRec(12);
    recTree.InsertRec(18);
    recTree.InsertRec(21);
    recTree.InsertRec(34);
    recTree.InsertRec(59);
    recTree.InsertRec(72);
    recTree.InsertRec(3);
    recTree.InsertRec(21);  // Duplicate - should be ignored

    std::cout << "\n\tDisplay of the Tree After Insertion\n";
    std::cout << "Inorder: ";
    recTree.DisplayInOrder();
    std::cout << "Preorder: ";
    recTree.DisplayPreOrder();
    std::cout << "Postorder: ";
    recTree.DisplayPostOrder();
    std::cout << "New Size: " << recTree.getSize() << "\n\n";

    // Search tests
    std::cout << "Searching For 12: " << (recTree.SearchRec(12) ? "FOUND\n" : "NOT FOUND\n");
    std::cout << "Search For 57: " << (recTree.SearchRec(57) ? "FOUND\n" : "NOT FOUND\n");

    // Delete tests
    recTree.RemoveRec(13);
    recTree.RemoveRec(10);
    recTree.RemoveRec(77);  // Non-existent values

    std::cout << "\n\tDisplay After Removing\n";
    std::cout << "Inorder: ";
    recTree.DisplayInOrder();
    std::cout << "Size After Remove: " << recTree.getSize() << "\n\n";

    // Test 3: Copy constructor
    std::cout << "==================== Copy Constructor Test ====================";
    RedBlackTree Copied(recTree);  // Create copy using copy constructor

    std::cout << "\n\nDisplay By Preorder: ";
    Copied.DisplayPreOrder();
    std::cout << "Size: " << Copied.getSize() << "\n\n";

    // Test 4: Assignment operator
    std::cout << "==================== Assigment Operator Test ====================";
    RedBlackTree RBT;
    RBT = recTree;  // Create copy using assignment operator

    std::cout << "\n\nDisplay By Preorder: ";
    RBT.DisplayPreOrder();
    std::cout << "Size: " << RBT.getSize() << "\n";
}