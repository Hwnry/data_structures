//--------------------------------------------------------------------
//
//  Laboratory 11, In-lab Exercise 1                     database.cs
//
//  (Shell) Indexed accounts database program
//
//--------------------------------------------------------------------

// Builds a binary search tree index for the account records in the
// text file accounts.dat.

#include <iostream>
#include <fstream>
#include "BSTree.cpp"

using namespace std;

//--------------------------------------------------------------------
//
// Declarations specifying the accounts database
//

const int nameLength      = 11;   // Maximum number of characters in
                                  //   a name
const long bytesPerRecord = 37;   // Number of bytes used to store
                                  //   each record in the accounts
                                  //   database file

struct AccountRecord
{
    int acctID;                   // Account identifier
    char firstName[nameLength],   // Name of account holder
         lastName[nameLength];
    double balance;               // Account balance
};

//--------------------------------------------------------------------
//
// Declaration specifying the database index
//

struct IndexEntry
{
    int acctID;              // (Key) Account identifier
    long recNum;             // Record number

    int getKey () const
        { return acctID; }   // Return key field
};

//--------------------------------------------------------------------
/**
 * @file database.cpp
 * @author Henry Huffman
 * @version 1.1
 * @brief This program will use the structs and basic variables given in the shell from the instructor to perform basic data base info manipulation.
 * @details More specifically, this program reads in from a file, stores the data in the given BST and structs, outputs all the specified data in 
 *          ascending order, gets input from the user, and outputs data from the given file.  
 * 
 * @date Friday, October 17th, 2014
 */
int main ()
{
	cout << endl; 
    ifstream acctFile ("accounts.dat");   // Accounts database file
    AccountRecord acctRec;                // Account record
    BSTree<IndexEntry,int> index;         // Database index
    IndexEntry entry;                     // Index entry
    int searchID;                         // User input account ID
    long recNum;                          // Record number 
    ///create a temporary string
  //  acctFile.clear();
   // acctFile.open("accounts.dat"); 
    string temp; 
    recNum = acctFile.tellg();    
  
    // Iterate through the database records. For each record, read the
    // account ID and add the (account ID, record number) pair to the
    // index.
    
    ///take in the searchID
    acctFile>>searchID;
    ///while the end of the data file is not found
    while(!acctFile.eof())
      {
		///place searchID into entry struct
		entry.acctID = searchID; 
		///place recNum into entry struct
		entry.recNum = recNum;
		///place current struct into index BST
		index.insert(entry);   
		///ignore to get to the end of line
		acctFile.ignore(37,'\n'); 
		///take in the searchID
		recNum = acctFile.tellg(); 
		acctFile>>searchID;
		
	  }
    // Output the account IDs in ascending order.
    ///output all the keys using the write keys member function
    cout << "Account IDs : " << endl; 
    index.writeKeys(); 
    ///////////////////////////////////////////////////////////////formatting?
    cout << endl; 
    


    // Clear the status flags for the database file.
    acctFile.clear();

    // Read an account ID from the keyboard and output the
    // corresponding record.
   
    ///take in the specified searchID from the user
    cout << "Enter account ID : ";
    cin>>searchID;
    
    while(cin.good()){
	acctFile.clear();
    ///check to see if searchID is in index BST
    if(index.retrieve(searchID, entry))
      {
		///if searchID is found,
		///move to specified record
		acctFile.seekg((entry.recNum)); 
		cout << (entry.recNum/37)<<" : "; 
		///place acctID from file into specified struct
		acctFile>>acctRec.acctID;
		///place firstName from file into specified struct
		acctFile>>acctRec.firstName;
		///place lastName from file into specified struct
		acctFile>>acctRec.lastName;
		///place the balance from file into specified struct
		acctFile>>acctRec.balance; 
		///output the acctID
		cout<<acctRec.acctID << ' ';
		///output firstName
		cout<<acctRec.firstName << ' ';
		///output lastName
		cout<<acctRec.lastName << ' ';
		///output the balance
		cout<<acctRec.balance << ' ' << endl;   
	   }
	 else
	   {
		 cout << "No record with that account ID" << endl; 
	   }
	 cout << "Enter account ID (EOF to quit): "; 
	 cin>>searchID; 
	}
  //acctFile.close();

  return 0; 
}
