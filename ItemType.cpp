// ItemType.cpp : This file contains ItemType code Implementation
// Class assignment for Program 4
// Author: Nathan Milani – This is my own work!
// I understand that I may be asked questions about my submission.
// email: nrm0002@uah.edu
// For: CS221-01, Fall 2023 Mrs. Delugach
// Using compiler MSVS 2022

#include "ItemType.h"
#include <iomanip>

ItemType::ItemType()
{
    phoneNumber = "2568675309";			// Default phone number if nothing else is given
    storeName = "Jenny";				// Default name if nothing else is given
    storeAddress = "nowhere";			// Default store address if nothing else is given
}

ItemType::ItemType(string name, string address, string phoneNum)
{
    phoneNumber = phoneNum;				// This will be the stores phone number that is entered by the user
    storeName = name;					// This will be the stores name that is entered by the user
    storeAddress = address;				// This will be the stores address that is entered by the user
}

ItemType::~ItemType()
{										// It's joke time since your empty:
                                        // What do you get when batman and robin get hit by a rollercoaster?
}										// Flatman and Ribbin! funny right lol.

bool ItemType::operator<(ItemType& less)
{
    bool result = false;				// Initialize the result flag to false
    if (storeName < less.storeName)		// Compare the store name of the current object
    {
        result = true;					// Set result to true if current store name is less
    }
    return result;						// Returns the comparison if false
}

bool ItemType::operator>(ItemType& greater)
{
    bool result = false;				// Initialize the result flag to false
    if (storeName > greater.storeName)	// Compare the store name of the current object
    {
        result = true;					// Set result to true if current store name is greater
    }
    return result;						// Returns the comparison if false
}

bool ItemType::operator==(ItemType& equal)
{
    bool result = false;				// Initialize the result flag to false
    if (storeName == equal.storeName)	// Compare the store name of the current object
    {
        result = true;					// Set result to true if current store name is equal
    }
    return result;						// Returns the comparison if false
}

//
string ItemType::GetData()
{
    return storeName;					// Returns the name of the store
}

string ItemType::GetData(string& getAddress, string& getNum)
{
    getAddress = storeAddress;			// Updates the address of the store with the value passed into the function. 
    getNum = phoneNumber;				// Updates the phone number of the store with the value passed into the function.
    return storeName;					// Retruns the name of the store again
}

void ItemType::SetData(string setName, string setAddress, string setNumber)
{
    storeName = setName;				// setName sets the name of the store
    storeAddress = setAddress;			// setAddress sets the address of the store
    phoneNumber = setNumber;			// setNumber sets the phone number of the store
}

void ItemType::PrintInfo()				// Prints the stores name, phone number, and address
{
    cout << left << setw(30) << storeName << ", " << left << setw(30) << storeAddress
        << ", " << left << setw(10) << phoneNumber;
}