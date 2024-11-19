// BSTree.cpp : This file contains BSTree code Implementation
// Class assignment for Program 4
// Author: Nathan Milani – This is my own work!
// I understand that I may be asked questions about my submission.
// email: nrm0002@uah.edu
// For: CS221-01, Fall 2023 Mrs. Delugach
// Using compiler MSVS 2022

#include "BSTree.h"

// Default Constructor
BSTree::BSTree()
{
    root = nullptr;
    iterator = nullptr;
    count = 0;
    maxCapacity = 500;
    printFlag = true;
    cout << "Nathan Milani, Global GameStore Distrabutions Company!\n";
}

// Private Helper Function Definitions
TreeNode* BSTree::copyTree(TreeNode* node)
{
    //checking if the node is a nullptr
    if (node == nullptr)
    {
        return nullptr;
    }

    TreeNode* newNode = new TreeNode;
    newNode->info = node->info;
    newNode->left = copyTree(node->left);
    newNode->right = copyTree(node->right);

    return newNode;
}

// Copy Constructor
BSTree::BSTree(BSTree& sample)
{
    root = copyTree(sample.root);
    count = sample.count;
    printFlag = sample.printFlag;
}

// Destructor
BSTree::~BSTree()
{
    MakeEmpty();
}

// #1 Creating a deep copy of another tree
// operator=()
void BSTree::operator=(BSTree& sample)
{
    if (root != sample.root)
    {
        MakeEmpty();
        root = copyTree(sample.root);
        count = sample.count;
    }
}

// #2 Insert item into the tree
// PutItem() and Insert()
bool BSTree::PutItem(ItemType item)
{
    bool success = false;
    printFlag = false;
    insert(root, item, success, printFlag);
    printFlag = true;
    if (success)
    {
        count++;
        if (printFlag)
        {
            cout << "Added " << item.GetData() << endl;
        }
    }
    else
    {
        if (printFlag)
        {
            cout << "Duplicates of: " << item.GetData() << endl;
        }
    }
    return success;
}
void BSTree::insert(TreeNode*& node, ItemType item, bool& success, bool printFlag)
{
    if (node == nullptr)
    {
        node = new TreeNode;
        node->info = item;
        node->left = nullptr;
        node->right = nullptr;
        success = true;
    }
    else if (item < node->info)
    {
        insert(node->left, item, success, printFlag);
    }
    else if (item > node->info)
    {
        insert(node->right, item, success, printFlag);
    }
    else
    {
        success = false;
    }
}

// #3 Retrieve item from the tree using Retrieve() function
// GetItem() and Retrieve()
ItemType BSTree::GetItem(ItemType item, bool& found)
{
    cout << "Searching...\n";
    retrieve(root, item, found); // Call Retrieve to find the item
    if (found)
    {
        cout << "found\n";
    }
    else
    {
        cout << "not found\n";
    }
    return item;
}
void BSTree::retrieve(TreeNode* tree, ItemType item, bool& found)
{
    if (tree == nullptr)
    {
        found = false;
        return;
    }

    // Print the current node being inspected
    cout << tree->info.GetData() << ", ";

    if (item < tree->info)
    {
        retrieve(tree->left, item, found);
    }
    else if (item > tree->info)
    {
        retrieve(tree->right, item, found);
    }
    else
    {
        found = true;
        item = tree->info; // Update the item with the found node's info
    }
}

// #4 Delete item from the tree
// DeleteItem(), Delete(), and DeleteNode()
bool BSTree::DeleteItem(ItemType item)
{
    bool found;
    bool originalPrintFlag = printFlag; // Store the original state of printFlag
    printFlag = false;                   // Temporarily turn off printing

    traverseDelete(root, item, found);    // Call Delete to find and delete the item

    printFlag = originalPrintFlag;       // Restore the original printFlag state
    if (found)
    {
        count--;  // Decrease the count of nodes in the tree
        cout << "Deleted: " << item.GetData() << endl;  // Output the deletion message
    }
    return found;  // Return true if the item was found and deleted, false otherwise
}
void BSTree::traverseDelete(TreeNode*& tree, ItemType item, bool& found)
{
    if (tree == nullptr)
    {
        found = false;  // Item not found in the tree
        return;
    }

    if (item < tree->info)
    {
        traverseDelete(tree->left, item, found);  // Recur on the left subtree
    }
    else if (item > tree->info)
    {
        traverseDelete(tree->right, item, found);  // Recur on the right subtree
    }
    else
    {
        // Item is found, delete this node
        found = true;
        deleteNode(tree);  // Call DeleteNode to handle node deletion and tree adjustment
    }
}
void BSTree::deleteNode(TreeNode*& node)
{
    if (node == nullptr)
        return;

    // Case 1: Node has no children (leaf node)
    if (node->left == nullptr && node->right == nullptr)
    {
        delete node;
        node = nullptr;
    }
    // Case 2: Node has one child
    else if (node->left == nullptr)
    {
        TreeNode* temp = node;
        node = node->right;  // Promote the right child
        delete temp;
    }
    else if (node->right == nullptr)
    {
        TreeNode* temp = node;
        node = node->left;  // Promote the left child
        delete temp;
    }
    // Case 3: Node has two children
    else
    {
        bool found = false;
        // Find the in-order successor by traversing the leftmost node of the right subtree
        TreeNode* temp = node->right;
        while (temp->left != nullptr)
        {
            temp = temp->left;  // Traverse to the leftmost node
        }
        node->info = temp->info;  // Replace current node's info with in-order successor's info
        traverseDelete(node->right, temp->info, found);  // Recursively delete the in-order successor
    }
}

// #5 Reset iterator to the beginning of the tree for traversal
// ResetTree()
void BSTree::ResetTree()
{
    iterator = root;
    treverseStarted = false;
}

// #6 Make the tree empty
// MakeEmpty() and Destroy()
void BSTree::MakeEmpty()
{
    destroy(root);
    root = nullptr;
    count = 0;
}
void BSTree::destroy(TreeNode*& node)
{
    if (node)
    {
        destroy(node->left);
        destroy(node->right);
        delete node;
        node = nullptr;
    }
}

// #7 Print the items in the tree
// PrintTree() and PrintTreeTraversal()
void BSTree::PrintTree()
{
    cout << "\nPrint Tree:\n";
    printTreeTraversal(root);
    cout << "\nTree Count: " << count << endl;
}
void BSTree::printTreeTraversal(TreeNode* node)
{
    if (node)
    {
        printTreeTraversal(node->left);
        node->info.PrintInfo();
        cout << endl;
        printTreeTraversal(node->right);
    }
}

// #8 Get the number of nodes in the tree
// GetCount() and CountNodes()
int BSTree::GetCount()
{
    return countNodes(root);
}
int BSTree::countNodes(TreeNode* node)
{
    if (node == nullptr)
    {
        return 0;
    }
    else
    {
        return 1 + countNodes(node->left) + countNodes(node->right);
    }
}

// #9 Get the next item in the traversal sequence
// GetNext() GetNextInOrder()
ItemType BSTree::GetNext() 
{
    // If the tree is empty
    if (root == nullptr) 
    {
        cout << "Tree is empty.\n";
        return ItemType();
    }

    // Start traversal if it's the first call
    if (!treverseStarted) 
    {
        treverseStarted = true;
        iterator = root;
        while (iterator->left != nullptr) 
        {
            iterator = iterator->left;  // Start with the leftmost node
        }
    }
    else 
    {
        // Continue traversal from the current position
        iterator = getNextInOrder(root, iterator);
    }

    // If traversal is complete
    if (!iterator) 
    {
        treverseStarted = false; // Reset traversal status for next usage
        return ItemType();
    }

    return iterator->info;  // Return current node's info
}


TreeNode* BSTree::getNextInOrder(TreeNode* node, TreeNode*& lastVisited) 
{
    if (node == nullptr)
    {
        return nullptr;
    }

    // If lastVisited is null, start at the leftmost node
    if (lastVisited == nullptr) 
    {
        while (node->left != nullptr)
        {
            node = node->left;
        }
        return node;
    }

    // If the left subtree has been fully visited, check current node
    if (lastVisited->right) 
    {
        node = lastVisited->right;
        while (node->left != nullptr)
        {
            node = node->left;
        }
        return node;
    }

    // Backtrack to the parent nodes
    TreeNode* parent = root;
    TreeNode* successor = nullptr;
    while (parent != nullptr && parent != lastVisited) 
    {
        if (lastVisited->info < parent->info) 
        {
            successor = parent;
            parent = parent->left;
        }
        else 
        {
            parent = parent->right;
        }
    }
    return successor;
}

// #10 Print the tree in an indented format (extra credit)
// PrintTreeForm() and PrintTreeIntended()
void BSTree::PrintTreeForm()
{
    cout << "Tree in indented form:\n";
    printTreeIndented(root, 0);
}
void BSTree::printTreeIndented(TreeNode* node, int level)
{
    if (node)
    {
        printTreeIndented(node->right, level + 1);
        cout << string(level * 4, ' ') << node->info.GetData() << endl;
        printTreeIndented(node->left, level + 1);
    }
}
