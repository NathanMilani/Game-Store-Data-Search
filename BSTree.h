// BSTree.h : This file contains BSTree code Declorations
// Class assignment for Program 4
// Author: Nathan Milani – This is my own work!
// I understand that I may be asked questions about my submission.
// email: nrm0002@uah.edu
// For: CS221-01, Fall 2023 Mrs. Delugach
// Using compiler MSVS 2022

#pragma once
#include "ItemType.h"

struct TreeNode
{
    ItemType info;                      // Holds the data in the node
    TreeNode* left = nullptr;           // Points to the left child node, has a default value of nullptr
    TreeNode* right = nullptr;          // Points to the right child node, has a deafault value of nullptr
};

class BSTree
{
private:
    // Member data
    TreeNode* root = nullptr;           // Points to the root of the Binary search tree, default value nullptr
    TreeNode* iterator = nullptr;       // This helps to iterate through the tree without changing the root
    int count = 0;                      // This counts the amount of nodes in the tree, default value of 0
    int maxCapacity = 0;                // This puts a limit to how many nodes are in the tree, default is 0
    bool printFlag = false;             // Used when iterating through a tree of when to print something, set to false
    bool treverseStarted = false;       // Tracks if the traversal started or not

    // Helper Functions
    TreeNode* copyTree(TreeNode* node);
    void insert(TreeNode*& node, ItemType item, bool& success, bool printFlag);
    void retrieve(TreeNode* tree, ItemType item, bool& found);
    void traverseDelete(TreeNode*& node, ItemType item, bool& found);
    void deleteNode(TreeNode*& node);
    void destroy(TreeNode*& node);
    int countNodes(TreeNode* node);
    void printTreeTraversal(TreeNode* node);
    void printTreeIndented(TreeNode* node, int level);
    TreeNode* getNextInOrder(TreeNode* node, TreeNode*& lastVisited);

public:
    // Constructors and Destructor
    BSTree();
    BSTree(BSTree& sample);
    ~BSTree();

    // Overloaded Operators
    void operator=(BSTree& sample);

    // Public Member Functions
    bool PutItem(ItemType item);
    ItemType GetItem(ItemType item, bool& found);
    bool DeleteItem(ItemType item);
    void ResetTree();
    void MakeEmpty();
    void PrintTree();
    ItemType GetNext();
    int GetCount();
    void PrintTreeForm();
};
