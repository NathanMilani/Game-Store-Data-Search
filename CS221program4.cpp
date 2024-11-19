// CS221Program4.cpp : This file contains menu and file code Implementation
// Class assignment for Program 4
// Author: Nathan Milani – This is my own work!
// Using compiler MSVS 2022
// email: nrm0002@uah.edu
// For: CS221-01, Fall 2023 Mrs. Delugach
// Using compiler MSVS 2022

#include "BSTree.h"
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

// Function to save the tree to a file in sorted order.
void SaveTreeToFile(BSTree& tree, const string& filename) 
{
    ofstream outputFile(filename);

    if (!outputFile) 
    {
        cerr << "Error: Could not open the file for writing.\n";
    }

    if (tree.GetCount() == 0) 
    {
        cout << "Tree is empty. Nothing to save.\n";
    }

    tree.ResetTree();
    for (int i = 0; i < tree.GetCount(); ++i) 
    {
        ItemType item = tree.GetNext();
        string address, phone;
        item.GetData(address, phone);
        outputFile << item.GetData() << "," << address << "," << phone << endl;
    }

    outputFile.close();
    cout << "Tree saved to " << filename << " in sorted order.\n";
}

// Function to display the menu
void displayMenu() 
{
    cout << "\nGame Store Data Search System\n\n";
    cout << "Choose One:\n";
    cout << "1. Add a game store\n";
    cout << "2. Delete a game store\n";
    cout << "3. Retrieve a game store\n";
    cout << "4. Print the data storage tree\n";
    cout << "5. Print the tree in structured form\n";
    cout << "6. Write sorted data to file\n";
    cout << "7. Exit Menu\n";
}

// Function to handle user interactions with the menu
void runMenu(BSTree& gamestoreTree) 
{
    string name, address, phone;
    int choice = 0;

    while (choice != 7) {
        displayMenu();
        cout << "Enter your choice (1-7): ";

        // Input validation
        while (!(cin >> choice) || choice < 1 || choice > 7) 
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. Please enter a number between 1 and 7: ";
        }
        cin.ignore(10000, '\n'); // Clear newline from the buffer

        switch (choice) 
        {
        case 1: 
        { // Add a game store
            int numStores;
            cout << "\nEnter the number of stores you want to add: ";
            cin >> numStores;
            cin.ignore(10000, '\n');

            for (int i = 0; i < numStores; ++i) 
            {
                cout << "\nEnter details for store #" << (i + 1) << ":\n";
                cout << "Enter name: ";
                getline(cin, name);
                cout << "Enter address: ";
                getline(cin, address);
                cout << "Enter phone: ";
                getline(cin, phone);
                ItemType newItem(name, address, phone);
                gamestoreTree.PutItem(newItem);
            }
            break;
        }
        case 2: // Delete a game store
        { 
            cout << "\nEnter name to delete: ";
            getline(cin, name);
            ItemType deleteItem(name, "", "");
            if (gamestoreTree.DeleteItem(deleteItem))
                cout << "Store deleted successfully.\n";
            else
                cout << "Store not found.\n";
            break;
        }
        case 3: 
        { // Retrieve a game store
            cout << "\nEnter name to search: ";
            getline(cin, name);
            ItemType searchItem(name, "", "");
            bool found;
            searchItem = gamestoreTree.GetItem(searchItem, found);
            if (found)
                searchItem.PrintInfo();
            else
                cout << "Store not found.\n";
            break;
        }
        case 4:
        {// Print the data storage tree in sorted order
            gamestoreTree.PrintTree();
            break;
        }
        case 5:
        {// Print the data storage tree in tree form
            gamestoreTree.PrintTreeForm();
            break;
        }
        case 6:
        {// Write sorted data to file
            SaveTreeToFile(gamestoreTree, "GameStoresSorted.csv");
            break;
        }
        case 7:
        {// Exit
            cout << "Exiting program. Have a blessed day!\n";
            break;
        }
        default:
            cout << "Invalid option. Please try again.\n";
        }
    }
}

int main() 
{
    BSTree gamestoreTree;
    ifstream inputFile("GameStoreList.csv");
    string line, name, address, phone;

    // Load data from CSV into tree
    while (getline(inputFile, line)) 
    {
        if (line.empty())
        {
            continue;
        }

        istringstream stringInput(line);
        if (getline(stringInput, name, ',') && getline(stringInput, address, ',') && getline(stringInput, phone, ',')) 
        {
            if (!name.empty() && !address.empty() && !phone.empty()) 
            {
                ItemType item(name, address, phone);
                gamestoreTree.PutItem(item);
            }
            else 
            {
                cout << "Invalid entry: " << line << endl;
            }
        }
        else 
        {
            cout << "Failed to parse line: " << line << endl;
        }
    }
    inputFile.close();

    // Run the menu
    runMenu(gamestoreTree);
    return 0;
}
