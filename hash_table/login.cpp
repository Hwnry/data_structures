
//Header Files
#include <string>
#include <iostream>
#include <fstream>
#include "HashTable.cpp"

using namespace std;

/**
 * @file HashTable.cpp
 * @author Henry Huffman
 * @version 1.1
 * @brief This program (login.cpp) reads in data from a file, place the data into a hashtable, retrieve data and output it to the user
 * @details More specifically, this program uses basic file i/o to take in data and place it into the hash. This hash consists of an array of structs. 
 *          Once the data is stored, we then attempt to see if the password and username match any of the passwords and usernames stored.
 * 
 * @date Tuesday, October 28th, 2014
 */
 

/**
 * User struct
 * 
 * This struct is used to store the username and password. The setKey function sets the key of the current data member. 
 * The getKey ofcourse gets the key of the specified user profile. 
 */

//struct used for manipulations
struct User
{
	
/**
 * setKey function
 * 
 * @param newKey - the key that must be placed into the the current user's profile
 * 
 * @pre there may or may not be a key assigned to the current user profile
 * @post there will be a key assigned to the current user profile specified in the parameters
 * 
 * @return none
 */
  //this function sets the key, in this case it is a string
    void setKey( string newKey )
      { 
        //the name string is set the specified key of the user
        name = newKey; 
      }
    
 /**
  * getKey function
  * 
  * @param - none
  * 
  * @pre there must be a keyword set in the struct
  * @post there will be a keyword returned
  * 
  * @return the keyword that is a string
  */
     //the gets the current name stored inside of the struct
    string getKey() const 
     { 
        //return the string name
	    return name; 
	 }

    //hash function simply gets the large number we use to modulo and place correctly into hash table
    int hash(const string str) const
    {
	   //initialize the value to zero
        int val = 0;
       //convert string to a integer value
        for (unsigned int i=0; i<str.length(); i++) 
            val += str[i];
        //return this integer value
        return val;
    }
    //data members of the user struct, the name and keyword
    string name, keyword;
};

/**
 * @main As previously mentioned, this program will read in data, and place it into the hash table. Then
 *       it will take input from a user to search for a keyword specified by the user. It will then get
 *       the password from the user. If the user's password matches the authentification then reports as sucessful.
 *       Othwerise, the user could not the authenticated. 
 */


int main()
{
    //create a hashtable of structs
    HashTable<User, string> passwords(8);
    //create a temporary hashtable
    User temp;
    // create two strings. One for name and one for password
    string name,pass; 
    //a bool to aide in determining if the name is found
    bool found;   
    //open up the file 
    ifstream fin( "password.dat" );
    //if nothing can be taken into the file
    if ( !fin )
    {
	  //output error message
        cout << "Unable to open 'password.dat'!" << endl;
      //return to end program
        return 1;
    }
    //loop to take in information while good
    while ( fin >> temp.name >> temp.keyword )
    {
       //insert data into the hash of structs
		passwords.insert( temp );
    }
    // output the structure
    passwords.showStructure();
    //prompt user
    cout << "Login: ";
    //loop while the name is given
    while ( cin >> name )
    {
	   //check to see if the name is in data
       found = passwords.retrieve( name, temp );
       //prompt for password
        cout << "Password: ";
       //take in password
        cin >> pass;
       //if the password and username are found
		if( temp.keyword == pass && found )
		{
		  //output success
			cout << "Authentication successful" << endl;
		}
	   //otherwise,
		else
		{  
		   //output failure
			cout << "Authentication failure" << endl;
		}
		//prompt for login
        cout << "Login: ";
        //reset found to false for next loop
        found = false;
    }
    
    //output endl to the screen
    cout << endl;
    //end the program 
	return 0;

}

