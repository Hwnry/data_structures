/**
 * @file HashTable.cpp
 * @author Henry Huffman
 * @version 1.1
 * @brief This program is used to initialize, perform basic hashtable operations, and deallocate the ashtable's memory
 * @details The basic constructor, deconstructor, copy constructor, and overloaded operator functions are included. 
 *          The basic operations include: insert, remove, retrieve, clear, isEmpty, and showstructure. This hashtable
 *          is an array of binary search trees. 
 * @date Friday, October 17th, 2014
 */



//Header file
#include "HashTable.h"

//function implementations

/**
 * HashTable default constructor
 * 
 * This function checks to see if the size is greater than zero. If it is, 
 * memory is allocated. The size of the array is specified by initTableSize.
 * tableSize is set to initTableSize
 * 
 * @param initTableSize - how many elements should be included in the hashtable
 * 
 * @return none
 * 
 * @pre - there will not be any memory allocated to the hashtable.
 * @post - there will be memory allocated, and tableSize will be recorded
 */


template <typename DataType, typename KeyType>
HashTable<DataType, KeyType>::HashTable(int initTableSize)
  {
	//check to see if tableSize is valid
	if(initTableSize > 0)
	{
	  //allocate an array of BST's with specified size
    	dataTable = new BSTree<DataType, KeyType> [initTableSize];
      //record table size 
    	tableSize = initTableSize; 
    }
  }
  
/**
 * HashTable Copy constructor
 * 
 * This constructor gets the other hashtable's table size, allocates memory, and proceeds to copy
 * the data in each memory location.
 * 
 * @param other- the hashtable that is supposed to be copied
 * 
 * @return none
 * 
 * @pre - there will be one unitialized tree and another initialized tree that must be copied
 * @post - there will be two trees with identical values.
 */

  
template <typename DataType, typename KeyType>
HashTable<DataType, KeyType>::HashTable(const HashTable& other)
  {	
	//set the current tablesize to match the other tablesize
    tableSize = other.tableSize; 
    //allocate the memory to match the other hashtable
	dataTable = new BSTree<DataType, KeyType> [tableSize]; 
	//check to see if the other hashtable is empty
	if(!other.isEmpty())
	  {
		//iterate through each spot of the hashtable
		for(int i = 0; i < tableSize; i++)
		  {
			//copy the memory of the other hashtable 
			dataTable[i] = other.dataTable[i];   
		  }  
	  }
	
  }
  
  
/**
 * Overloaded operator
 * 
 * The overloaded operator checks to see if the current hashtable is being assigned to itself.
 * If it is, it simply returns itself; otherwise, it will clear any data currently in it, deallocate,
 * resize itself, and proceed to copy the value in each memory location
 * 
 * @param other - the hashtable that has been assigned to the current hashtable
 * 
 * @return HashTable<DataType, KeyType>& - the current hashtable with its new assigned values
 * 
 * @pre - there may or may not be two different hashtables
 * @post - there will be either two hashtables with identical values, or one hashtable that returned itself
 */
  
template<typename DataType, typename KeyType>
HashTable<DataType, KeyType>& HashTable<DataType, KeyType>::operator=(const HashTable& other)
  {
	//check to see if the current hashtable contains the same address of the other hashtable
	if(this == &other)
	  {
		//return the current hashtable
		return (*this);   
	  }
	//clear the current hashtable
	clear(); 
	//deallocate the hashtables's memory
	delete [] dataTable; 
    
    	//check to see if tableSize is valid
	if(other.tableSize > 0)
	{
	  //allocate an array of BST's with specified size
    	dataTable = new BSTree<DataType, KeyType> [other.tableSize];
      //record table size 
    	tableSize = other.tableSize;
      //move to each memory location in the hashtable	 
	  for(int i = 0; i < tableSize; i++)
	  {
		//assign the values of the other hashtable to the current hashtable
		  dataTable[i] = other.dataTable[i];   
	  }
    }
	  
    //return the current tree with its new values
	return (*this); 
  }
  
/**
 * HashTable deconstructor
 * 
 * deallocate all the memory in the current hashtable
 * 
 * @param none
 * 
 * @return none
 * 
 * @pre - there may or may not be memory allocated to the current hashtable
 * @post - there will not be memory allocated to the current hashtable
 */

  
template <typename DataType, typename KeyType>
HashTable<DataType, KeyType>::~HashTable()
  {
	//deallocate array, implicitly deletes BST data
    delete [] dataTable;
    //set pointer to null
    dataTable = NULL;   
  }
  
/**
 * insert function
 * 
 * This function gets the hashvalue, offsets the dataTable to the specified location, then inserts
 * the data into the correct location.
 * 
 * @param newDataItem - the data item that is to be inserted
 * 
 * @return none
 * 
 * @pre the newDataItem will not be inserted into the current hashtable
 * @post the newDataItem will be inserted into the current hashtable 
 */
template <typename DataType, typename KeyType>
void HashTable<DataType, KeyType>::insert(const DataType& newDataItem)
  {
	//get the hash value, offset dataTable to that location, insert newDataItem into BST at that hash location
	dataTable[((newDataItem.hash(newDataItem.getKey()))%tableSize)].insert(newDataItem); 	  
  }
  
/**
 * remove function
 * 
 * This function removes the dataItem that matches the deleteKey
 * 
 * @param deleteKey - the key that is to be searched for and removed
 * 
 * @return bool - whether or not the hashtable has successfully removed the the specified data  
 * 
 * @pre - the dataItem may or may not be in the current hashtable
 * @post - the dataItem will not be in the current hashtable
 */

  
template <typename DataType, typename KeyType>
bool HashTable<DataType, KeyType>::remove(const KeyType& deleteKey)
  {
	//create temp dataType for hashfunction
	DataType temp; 
	//mod the key, offset dataTable to possible location, attempt to remove specified key, return success or failure
	return(dataTable[(temp.hash(deleteKey))%tableSize].remove(deleteKey));   
  }
  
/**
 * retrieve function
 * 
 * the retrieve function searches for the item with the specified searchKey. If it is found, a true boolean is returned,
 * and the dataItem with the matching key is set to returnItem
 * 
 * @param searchKey - the key that is used to locate the specified dataItem
 * @param returnItem - this parameter copies the dataItem with the matching searchKey
 * 
 * @return bool - returns whether or not the item was removed
 * 
 * @pre - there may or may not be the specified dataItem in the current hashtable
 * @post - there will ont be the specified dataItem in the current hashtable
 */

  
template <typename DataType, typename KeyType>
bool HashTable<DataType, KeyType>::retrieve(const KeyType& searchKey, DataType& returnItem) const
  {
	//return the search attempt in the specified bst at the specified hash location
	return(dataTable[(returnItem.hash(searchKey))%tableSize].retrieve(searchKey, returnItem));  
  }
  
/**
 * clear function
 * 
 * This function deletes all the memory allocated in the BSTs in each hashtable's location
 * 
 * @param none
 * 
 * @return none
 * 
 * @pre there may or may not be memory allocated to the BSTs in the current hashtable
 * @post there will not be memory allocated to the BSTs in the current hashtable
 */

  
template <typename DataType, typename KeyType>
void HashTable<DataType, KeyType>::clear()
  {
	//move to each memory location
	for(int i = 0; i < tableSize; i++)
	  {
		//delete the data in the current BST at the current hashtable's location
		dataTable[i].clear();   
	  }  
  }

/**
 * isEmpty function
 * 
 * This function checks whether or not there is memory in any of the BST's in the hashTable
 * 
 * @param none
 * 
 * @return bool - returns whether or not there is memory allocated to the BST's in the hashTable
 * 
 * @pre one will not no whether or not the hashtable is empty
 * @post the hashtable will or will not be deemed empty
 */


template<typename DataType, typename KeyType>
bool HashTable<DataType, KeyType>::isEmpty()const
  { 
	//check to see if the dataTable is null
	if(dataTable != NULL)
	  {
		//move to each memory location
		for(int i = 0; i < tableSize; i++)
		  {
			//check to see if there is any memory allocated in the BSTs
			if(!dataTable[i].isEmpty())
			  {
				//return false because there is memory
				return false;   
			  }  
		  }  
	  }
	//return true because no memory was found
	return true; 
  }
  

// show10.cpp: contains implementation of the HashTable showStructure function
template <typename DataType, typename KeyType>
void HashTable<DataType, KeyType>::showStructure() const {
    for (int i = 0; i < tableSize; ++i) {
	cout << i << ": ";
	dataTable[i].writeKeys();
    }
}



