#include "RedBlackTree.h"

// Returns the number of nodes in the tree
std::size_t RedBlackTree::getSize() const { return nodeCount; }
// Checks if the tree is empty
bool RedBlackTree::isEmpty() const { return nodeCount == 0; }

// This node represents all Null leaves in the Red-Black Tree
void RedBlackTree::NullLeaf()
{
    nullLeaf = new Node();  // Create new node for nullLeaf
    nullLeaf->isBlack = true;  // Null leaves are always black
    nullLeaf->isLeftChild = false;
    // Set all pointers to point to itself (prevents nullptr issues)
    nullLeaf->parent = nullLeaf->left = nullLeaf->right = nullLeaf;
}

// Recursively copies a subtree from another tree
// Returns pointer to the root of the copied subtree
Node* RedBlackTree::CopySubtree(const Node* otherNode, const Node* otherNullLeaf, Node* newParent)
{
    // Base case: reached null leaf in source tree
    if (otherNode == otherNullLeaf) return nullLeaf;

    // Create new node with same value and color
    Node* newNode = new Node(otherNode->value, otherNode->isBlack,
        false, newParent, nullLeaf, nullLeaf);
    // Recursively copy left subtree
    newNode->left = CopySubtree(otherNode->left, otherNullLeaf, newNode);
    if (newNode->left != nullLeaf)
        newNode->left->isLeftChild = true;  // Set left child flag
    // Recursively copy right subtree
    newNode->right = CopySubtree(otherNode->right, otherNullLeaf, newNode);
    if (newNode->right != nullLeaf)
        newNode->right->isLeftChild = false; // Set right child flag

    return newNode;
}

// Recursively deletes all nodes in a subtree
void RedBlackTree::ClearSubtree(Node* node)
{
    // Base case: reached null leaf
    if (node == nullLeaf) return;

    // Post-order traversal: delete children first, then parent
    ClearSubtree(node->left);
    ClearSubtree(node->right);
    delete node;  // Delete current node
}

// Recursive helper function for searching
// Returns pointer to found node, or nullLeaf if not found
Node* RedBlackTree::SearchRecHelper(Node* node, int value) const
{
    // Base case: value not found
    if (node == nullLeaf) return nullLeaf;
    // Value found at current node
    if (value == node->value) return node;
    // Search left subtree if value is smaller
    if (value < node->value)
        return SearchRecHelper(node->left, value);
    // Search right subtree if value is larger
    return SearchRecHelper(node->right, value);
}

// Iterative helper function for searching
// Returns pointer to found node, or nullLeaf if not found
Node* RedBlackTree::SearchIterHelper(int value) const
{
    Node* Walker = Root;  // Start at root

    // Traverse tree until nullLeaf is reached
    while (Walker != nullLeaf)
    {
        if (value == Walker->value) return Walker; // Value found
        // Go left if value is smaller, right if larger
        Walker = (value < Walker->value) ? Walker->left : Walker->right;
    }

    return nullLeaf;  // Value not found
}

// Public recursive search function
// Returns true if value exists in tree, false otherwise
bool RedBlackTree::SearchRec(int value) const
{
    return SearchRecHelper(Root, value) != nullLeaf;
}

// Public iterative search function
// Returns true if value exists in tree, false otherwise
bool RedBlackTree::SearchIter(int value) const
{
    return SearchIterHelper(value) != nullLeaf;
}

// Performs left rotation around the given node
void RedBlackTree::LeftRotate(Node* rotationRoot)
{
    // Right child becomes new root of this subtree
    Node* RightChild = rotationRoot->right;
    if (RightChild == nullLeaf) return;  // Cannot rotate if no right child

    // Step 1: rotationRoot's right child becomes RightChild's left child
    rotationRoot->right = RightChild->left;
    if (RightChild->left != nullLeaf)
    {
        RightChild->left->parent = rotationRoot;
        RightChild->left->isLeftChild = false;  // It's now a right child
    }
    // Step 2: Update RightChild's parent
    RightChild->parent = rotationRoot->parent;
    // Step 3: Update parent's child pointer
    if (rotationRoot->parent == nullLeaf)
    {
        // rotationRoot was the tree root
        Root = RightChild;
        RightChild->isLeftChild = false;  // Root has no left/right designation
    }
    else if (rotationRoot->isLeftChild)
    {
        // rotationRoot was a left child
        rotationRoot->parent->left = RightChild;
        RightChild->isLeftChild = true;
    }
    else
    {
        // rotationRoot was a right child
        rotationRoot->parent->right = RightChild;
        RightChild->isLeftChild = false;
    }
    // Step 4: Make rotationRoot left child of RightChild
    RightChild->left = rotationRoot;
    rotationRoot->parent = RightChild;
    rotationRoot->isLeftChild = true;  // rotationRoot is now left child
}

// Performs right rotation around the given node
void RedBlackTree::RightRotate(Node* rotationRoot)
{
    // Left child becomes new root of this subtree
    Node* LeftChild = rotationRoot->left;
    if (LeftChild == nullLeaf) return;  // Cannot rotate if no left child

    // Step 1: rotationRoot's left child becomes LeftChild's right child
    rotationRoot->left = LeftChild->right;
    if (LeftChild->right != nullLeaf)
    {
        LeftChild->right->parent = rotationRoot;
        LeftChild->right->isLeftChild = true;  // It's now a left child
    }
    // Step 2: Update LeftChild's parent
    LeftChild->parent = rotationRoot->parent;
    // Step 3: Update parent's child pointer
    if (rotationRoot->parent == nullLeaf)
    {
        // rotationRoot was the tree root
        Root = LeftChild;
        LeftChild->isLeftChild = false;  // Root has no left/right designation
    }
    else if (!rotationRoot->isLeftChild)
    {
        // rotationRoot was a right child
        rotationRoot->parent->right = LeftChild;
        LeftChild->isLeftChild = false;
    }
    else
    {
        // rotationRoot was a left child
        rotationRoot->parent->left = LeftChild;
        LeftChild->isLeftChild = true;
    }
    // Step 4: Make rotationRoot right child of LeftChild
    LeftChild->right = rotationRoot;
    rotationRoot->parent = LeftChild;
    rotationRoot->isLeftChild = false;  // rotationRoot is now right child
}

// Finds the minimum value node in a subtree
// Returns pointer to node with minimum value
Node* RedBlackTree::Minimum(Node* node) const
{
    while (node->left != nullLeaf) // Minimum is leftmost node
        node = node->left;
    return node;
}

// Replaces one subtree with another subtree
void RedBlackTree::Transplant(Node* oldSubtreeRoot, Node* newSubtreeRoot)
{
    // Case 1: oldSubtreeRoot is the tree root
    if (oldSubtreeRoot->parent == nullLeaf)
    {
        Root = newSubtreeRoot;
        newSubtreeRoot->parent = nullLeaf;
        newSubtreeRoot->isLeftChild = false;
    }
    // Case 2: oldSubtreeRoot is a left child
    else if (oldSubtreeRoot->isLeftChild)
    {
        oldSubtreeRoot->parent->left = newSubtreeRoot;
        newSubtreeRoot->parent = oldSubtreeRoot->parent;
        newSubtreeRoot->isLeftChild = true;
    }
    // Case 3: oldSubtreeRoot is a right child
    else
    {
        oldSubtreeRoot->parent->right = newSubtreeRoot;
        newSubtreeRoot->parent = oldSubtreeRoot->parent;
        newSubtreeRoot->isLeftChild = false;
    }
}

// Flips the colors of a node and its children
// Used in Red-Black Tree rebalancing
void RedBlackTree::ColorFlip(Node* node)
{
    if (node == nullLeaf) return;

    node->isBlack = !node->isBlack; // Flip current node's color
    // Flip left child's color if it exists
    if (node->left != nullLeaf)
        node->left->isBlack = !node->left->isBlack;
    // Flip right child's color if it exists
    if (node->right != nullLeaf)
        node->right->isBlack = !node->right->isBlack;
}

// Fixes Red-Black Tree properties after insertion
void RedBlackTree::FixInsert(Node* insertedNode)
{
    // Continue fixing while parent exists and is red (violation of property 4)
    while (insertedNode->parent != nullLeaf && insertedNode->parent->isBlack == false)
    {
        Node* parent = insertedNode->parent;
        Node* Grand = parent->parent;

        // Case 1: Parent is a left child
        if (parent->isLeftChild)
        {
            Node* Uncle = Grand->right;
            // Case 1.1: Uncle is red (recoloring case)
            if (Uncle != nullLeaf && Uncle->isBlack == false)
            {
                ColorFlip(Grand);  // Flip grandparent's color
                insertedNode = Grand;  // Move up to grandparent
            }
            // Case 1.2: Uncle is black (rotation cases)
            else
            {
                // Case 1.2.1: insertedNode is right child (left-right case)
                if (insertedNode->isLeftChild == false)
                {
                    insertedNode = parent;
                    LeftRotate(insertedNode);  // Convert to left-left case
                    parent = insertedNode->parent;
                    Grand = parent->parent;
                }

                // Case 1.2.2: insertedNode is left child (left-left case)
                parent->isBlack = true;  // Parent becomes black
                Grand->isBlack = false;  // Grandparent becomes red
                RightRotate(Grand);  // Right rotate grandparent
            }
        }
        // Case 2: Parent is a right child (symmetric to Case A)
        else
        {
            Node* Uncle = Grand->left;

            // Case 2.1: Uncle is red
            if (Uncle->isBlack == false)
            {
                ColorFlip(Grand);
                insertedNode = Grand;
            }
            // Case 2.2: Uncle is black
            else
            {
                // Case 2.2.1: insertedNode is left child (right-left case)
                if (insertedNode->isLeftChild == true)
                {
                    insertedNode = parent;
                    RightRotate(insertedNode);  // Convert to right-right case
                    parent = insertedNode->parent;
                    Grand = parent->parent;
                }

                // Case 2.2.2: insertedNode is right child (right-right case)
                parent->isBlack = true;  // Parent becomes black
                Grand->isBlack = false;  // Grandparent becomes red
                LeftRotate(Grand);  // Left rotate grandparent
            }
        }
    }
    // Ensure root is always black
    if (Root != nullLeaf)
    {
        Root->isBlack = true;
        Root->parent = nullLeaf;
        Root->isLeftChild = false;
    }
}

// Fixes Red-Black Tree properties after deletion
void RedBlackTree::FixDelete(Node* FixNode)
{
    // Continue fixing while FixNode is not root and is black
    while (FixNode != Root && FixNode->isBlack)
    {
        // Case 1: FixNode is a left child
        if (FixNode->isLeftChild)
        {
            Node* Sibling = FixNode->parent->right;

            // Case 1.1: Sibling is red
            if (Sibling->isBlack == false)
            {
                Sibling->isBlack = true;
                FixNode->parent->isBlack = false;
                LeftRotate(FixNode->parent);
                Sibling = FixNode->parent->right;  // Update sibling after rotation
            }
            // Case 1.2: Both sibling's children are black
            if (Sibling->left->isBlack && Sibling->right->isBlack)
            {
                if (Sibling != nullLeaf) Sibling->isBlack = false;
                FixNode = FixNode->parent;  // Move up the tree
            }
            else
            {
                // Case 1.3: Sibling's right child is black (left child is red)
                if (Sibling->right->isBlack)
                {
                    Sibling->left->isBlack = true;
                    if (Sibling != nullLeaf) Sibling->isBlack = false;
                    RightRotate(Sibling);
                    Sibling = FixNode->parent->right;
                }
                // Case 1.4: Sibling's right child is red
                Sibling->isBlack = FixNode->parent->isBlack;
                FixNode->parent->isBlack = true;
                Sibling->right->isBlack = true;
                LeftRotate(FixNode->parent);
                FixNode = Root;  // Termination case
            }
        }
        // Case 2: FixNode is a right child (symmetric to Case 1)
        else
        {
            Node* Sibling = FixNode->parent->left;

            // Case 2.1: Sibling is red
            if (Sibling->isBlack == false)
            {
                Sibling->isBlack = true;
                FixNode->parent->isBlack = false;
                RightRotate(FixNode->parent);
                Sibling = FixNode->parent->left;
            }
            // Case 2.2: Both sibling's children are black
            if (Sibling->left->isBlack && Sibling->right->isBlack)
            {
                if (Sibling != nullLeaf) Sibling->isBlack = false;
                FixNode = FixNode->parent;
            }
            else
            {
                // Case 2.3: Sibling's left child is black (right child is red)
                if (Sibling->left->isBlack)
                {
                    Sibling->right->isBlack = true;
                    if (Sibling != nullLeaf) Sibling->isBlack = false;
                    LeftRotate(Sibling);
                    Sibling = FixNode->parent->left;
                }
                // Case 2.4: Sibling's left child is red
                Sibling->isBlack = FixNode->parent->isBlack;
                FixNode->parent->isBlack = true;
                Sibling->left->isBlack = true;
                RightRotate(FixNode->parent);
                FixNode = Root;  // Termination case
            }
        }
    }

    // Ensure FixNode is black (property 1)
    FixNode->isBlack = true;
}

// Default constructor - creates empty Red-Black Tree
RedBlackTree::RedBlackTree() : Root(nullptr), nullLeaf(nullptr), nodeCount(0)
{
    NullLeaf();  // Create sentinel node
    Root = nullLeaf; // Empty tree root points to sentinel
}

// Copy constructor - creates deep copy of another tree
RedBlackTree::RedBlackTree(const RedBlackTree& other)
             : Root(nullptr), nullLeaf(nullptr), nodeCount(other.nodeCount)
{
    NullLeaf();  // Create our own sentinel
    Root = nullLeaf; // Initialize to empty

    // Copy only if source tree is not empty
    if (other.Root != other.nullLeaf)
    {
        // Recursively copy entire tree
        Root = CopySubtree(other.Root, other.nullLeaf, nullLeaf);
        Root->parent = nullLeaf;
        Root->isLeftChild = false;
        Root->isBlack = true;  // Root must be black
    }
}

// Assignment operator - makes deep copy of another tree
// Returns reference to this tree
RedBlackTree& RedBlackTree::operator = (const RedBlackTree& other)
{
    // Check for self-assignment
    if (this != &other) {
        // Clear current tree
        ClearSubtree(Root);
        Root = nullLeaf;
        // Copy node count
        nodeCount = other.nodeCount;
        // Copy tree structure if source is not empty
        if (other.Root != other.nullLeaf)
        {
            Root = CopySubtree(other.Root, other.nullLeaf, nullLeaf);

            Root->parent = nullLeaf;
            Root->isLeftChild = false;
            Root->isBlack = true;  // Root must be black
        }
    }

    return *this;
}

// Destructor - cleans up all dynamically allocated memory
RedBlackTree::~RedBlackTree()
{
    ClearSubtree(Root); // Delete all tree nodes
    delete nullLeaf;  // Delete sentinel node
    Root = nullLeaf = nullptr;  // Prevent dangling pointers
}

// Recursive helper for BST insertion
// Returns root of subtree after insertion
Node* RedBlackTree::InsertBST(Node* currentRoot, Node* parent, int value, Node*& insertedNode, bool isLeftChild)
{
    // Found insertion point
    if (currentRoot == nullLeaf)
    {
        // Create new red node
        insertedNode = new Node(value, false, isLeftChild, parent, nullLeaf, nullLeaf);
        return insertedNode;
    }
    // Value already exists - duplicate not allowed
    if (value == currentRoot->value)
    {
        insertedNode = nullLeaf;  // Signal duplicate
        return currentRoot;
    }
    // Insert in left subtree
    if (value < currentRoot->value)
        currentRoot->left = InsertBST(currentRoot->left, currentRoot, value, insertedNode, true);
    // Insert in right subtree
    else
        currentRoot->right = InsertBST(currentRoot->right, currentRoot, value, insertedNode, false);

    return currentRoot;
}

// Iterative insertion of a value into Red-Black Tree
void RedBlackTree::InsertIter(int value)
{
    Node* parent = nullLeaf;
    Node* Walker = Root;
    bool GoLeft = false;  // Direction to go from parent

    // Find insertion point
    while (Walker != nullLeaf)
    {
        parent = Walker;
        // Duplicate value - do nothing
        if (value == Walker->value) return;
        // Go left if value is smaller
        if (value < Walker->value)
        {
            Walker = Walker->left;
            GoLeft = true;
        }
        // Go right if value is larger
        else
        {
            Walker = Walker->right;
            GoLeft = false;
        }
    }
    // Create new red node
    Node* newNode = new Node(value, false, (parent == nullLeaf ? false : GoLeft),
        parent, nullLeaf, nullLeaf);

    // Case 1: Tree was empty - new node becomes root
    if (parent == nullLeaf)
    {
        Root = newNode;
        Root->parent = nullLeaf;
        Root->isLeftChild = false;
        Root->isBlack = true;  // Root must be black
        ++nodeCount;
        return;
    }
    // Case 2: Insert as left or right child of parent
    if (GoLeft)
        parent->left = newNode;
    else
        parent->right = newNode;

    // Fix Red-Black Tree properties
    FixInsert(newNode);
    ++nodeCount;
}

// Recursive insertion of a value into Red-Black Tree
void RedBlackTree::InsertRec(int value)
{
    Node* insertedNode = nullLeaf;

    // Perform BST insertion (ignoring colors)
    Root = InsertBST(Root, nullLeaf, value, insertedNode, false);
    // Update root properties
    if (Root != nullLeaf)
    {
        Root->parent = nullLeaf;
        Root->isLeftChild = false;
    }
    // If insertion was successful (not duplicate)
    if (insertedNode != nullLeaf) {
        FixInsert(insertedNode);  // Fix Red-Black properties
        ++nodeCount;
    }
    // If duplicate, ensure root is black
    else if (Root != nullLeaf)
        Root->isBlack = true;
}

// Internal function to delete a node given its pointer
void RedBlackTree::RemoveByNode(Node* Target)
{
    if (Target == nullLeaf) return;  // Nothing to delete

    Node* RemovedNode = Target;  // Node being removed
    bool wasBlack = RemovedNode->isBlack;  // Color affects fixup
    Node* FixNode = nullLeaf;  // Node to start fixup from

    // Case 1: Target has no left child
    if (Target->left == nullLeaf)
    {
        FixNode = Target->right;
        Transplant(Target, Target->right);
    }
    // Case 2: Target has no right child
    else if (Target->right == nullLeaf)
    {
        FixNode = Target->left;
        Transplant(Target, Target->left);
    }
    // Case 3: Target has two children
    else
    {
        // Find successor (minimum in right subtree)
        RemovedNode = Minimum(Target->right);
        wasBlack = RemovedNode->isBlack;
        FixNode = RemovedNode->right;
        // Special case: successor is Target's immediate right child
        if (RemovedNode->parent == Target)
        {
            FixNode->parent = RemovedNode;
            FixNode->isLeftChild = false;
        }
        // General case: successor is deeper in right subtree
        else
        {
            Transplant(RemovedNode, RemovedNode->right);
            RemovedNode->right = Target->right;
            RemovedNode->right->parent = RemovedNode;
            RemovedNode->right->isLeftChild = false;
        }
        // Replace Target with its successor
        Transplant(Target, RemovedNode);
        RemovedNode->left = Target->left;
        RemovedNode->left->parent = RemovedNode;
        RemovedNode->left->isLeftChild = true;
        // Copy color from Target
        RemovedNode->isBlack = Target->isBlack;
        RemovedNode->isLeftChild = Target->isLeftChild;
    }

    // Delete the target node
    delete Target;
    // If removed node was black, need to fix tree properties
    if (wasBlack)
        FixDelete(FixNode);
    // Ensure root is black and properly set
    if (Root != nullLeaf)
    {
        Root->isBlack = true;
        Root->parent = nullLeaf;
        Root->isLeftChild = false;
    }
    --nodeCount;  // Decrement node count
}

// Iterative removal of a value from tree
void RedBlackTree::RemoveIter(int value)
{
    Node* Target = SearchIterHelper(value);  // Find node to delete
    RemoveByNode(Target);  // Delete it
}

// Recursive removal of a value from tree
void RedBlackTree::RemoveRec(int value)
{
    Node* Target = SearchRecHelper(Root, value);  // Find node to delete
    RemoveByNode(Target);  // Delete it
}

// Public in-order traversal interface
void RedBlackTree::DisplayInOrder(std::ostream& out) const
{
    DisplayInOrder(out, Root);
    out << "\n";
}

// Public pre-order traversal interface
void RedBlackTree::DisplayPreOrder(std::ostream& out) const
{
    DisplayPreOrder(out, Root);
    out << "\n";
}

// Public post-order traversal interface
void RedBlackTree::DisplayPostOrder(std::ostream& out) const
{
    DisplayPostOrder(out, Root);
    out << "\n";
}

// Recursive in-order traversal helper
void RedBlackTree::DisplayInOrder(std::ostream& out, Node* node) const
{
    if (node == nullLeaf) return;  // Base case

    // In-order: left, node, right
    DisplayInOrder(out, node->left);
    out << node->value << "(" << (node->isBlack ? "B" : "R") << ") ";
    DisplayInOrder(out, node->right);
}

// Recursive pre-order traversal helper
void RedBlackTree::DisplayPreOrder(std::ostream& out, Node* node) const
{
    if (node == nullLeaf) return;  // Base case

    // Pre-order: node, left, right
    out << node->value << "(" << (node->isBlack ? "B" : "R") << ") ";
    DisplayPreOrder(out, node->left);
    DisplayPreOrder(out, node->right);
}

// Recursive post-order traversal helper
void RedBlackTree::DisplayPostOrder(std::ostream& out, Node* node) const
{
    if (node == nullLeaf) return;  // Base case

    // Post-order: left, right, node
    DisplayPostOrder(out, node->left);
    DisplayPostOrder(out, node->right);
    out << node->value << "(" << (node->isBlack ? "B" : "R") << ") ";
}