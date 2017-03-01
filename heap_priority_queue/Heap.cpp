
/**
 * @file Heap.cpp
 * @author Henry Huffman
 * @version 1.1
 * @brief This program contains the basic function for manipulating data in the heap.
 * @details More specifically, this program has the following basic member functions: heap constructor, copy constructor,
 *          overloaded = operator, and heap deconstructor. This program also contains the following functions: insert,
 *          remove, clear, isEmpty, isFull, showStructure, and writeLevels. There are also several helper functions which
 *          are also used to help in manipulating data. These functions being: showSubtree, getLeft, getRight, getParent, 
 *          heap up, and heap down.  
 * 
 * @date Friday, October 17th, 2014
 */

//Header Files
#include "Heap.h"


//Function Implementations
/**
 * Heap Constructor
 * 
 * This constructor creates an array of new dataItems, sets the maxSize, and current size.
 * 
 * @param maxNumber - an integer that sets the maxSize of the number of dataItems in the array
 * 
 * @return none
 * 
 * @pre  there will not be an initialized heap
 * @post  there will be an initialized heap with the maxSize, and size set
 */


template < typename DataType, typename KeyType, typename Comparator >

Heap<DataType, KeyType, Comparator>::Heap(int maxNumber)
  {
	//create an empty heap, Allocate enough memory for maxNumber of dataItems
	dataItems = new DataType [maxNumber];
	//set maxSize
	maxSize = maxNumber;
	//set size to zero
	size = 0; 
  }
 
 /** 
  * Heap copy constructor
  * 
  * This constructor creates an array of new dataItems with identical values of another specified heap.
  * 
  * @param other - another heap that is to be copied
  * 
  * @return none
  * 
  * @pre there will only be one initialized heap
  * @post there will be two initialized heaps with identical values
 */

template < typename DataType, typename KeyType, typename Comparator >

Heap<DataType, KeyType, Comparator>::Heap(const Heap& other)
  {
    //set maxSize to match the other array
    maxSize = other.maxSize; 
    //set the size of the current array to match the other array
    size = other.size; 
    //create an identical array
	dataItems = new DataType [maxSize];
	//check to see of the other array is empty
	if(!other.isEmpty())
	  {
		//copy values using a for loop
		for(int i = 0; i < size; i++)
		  {
			dataItems[i] = other.dataItems[i];   
		  }
	  }
	  
  }
  
 /** 
  * operator=
  * 
  * This function returns a heap. If the heap is assigned to itself, it simply returns itself.
  * Otherwise, the current heap will reallocate memory to match the other heap, and copy the values
  * of the other heap. Then it will return itself.
  * 
  * @param other - another heap that is to be copied
  * 
  * @return Heap& - the current tree 
  * 
  * @pre there may or may not be two initialized trees with different values
  * @post there may or may not be two initialized trees with identical values
 */


template < typename DataType, typename KeyType, typename Comparator >
  
Heap<DataType, KeyType, Comparator>& Heap<DataType, KeyType, Comparator>::operator=(const Heap& other)
  {
	//check to see if the same item is assigning itself
    if(this ==&other)
      {
		//return the same item
		return (*this);  
	  }
	//clear current item
	clear();
    //set the current max to the other max
	maxSize = other.maxSize;
	//set the size to match the other heap's size
	size = other.size;
	//create an array that matches the maxsize of the other heap
	dataItems = new DataType [maxSize];
	//check to see if the other heap is empty
	if(!other.isEmpty())
	  {
		//use a for loop to copy data items in the array
		for(int i = 0; i < size; i++)
		  {
			dataItems[i] = other.dataItems[i];   
		  }  
	  }
	 //return the updated item
	return (*this); 
  }
  
 /** 
  * Heap deconstructor
  * 
  * The deconstructor deallocates the array of data and sets the pointer to null
  * 
  * @param none
  * 
  * @return none
  * 
  * @pre there will be an initialized heap with an array set
  * @post there will not be any memory allocated to the heap
 */

  
template < typename DataType, typename KeyType, typename Comparator >

Heap<DataType, KeyType, Comparator>::~Heap()
  {
	//delete the current data array
	delete [] dataItems; 
	//set the array pointer to null
	dataItems = NULL;   
  }
  
 /** 
  * Clear function
  * 
  * This function deallocates the memory, reallocates the memory, and sets the size
  * of the array to zero
  * 
  * @param none
  * 
  * @return none
  * 
  * @pre there will an array that may or may not be empty
  * @post there will be an that is empty
 */


template < typename DataType, typename KeyType, typename Comparator >
void Heap<DataType, KeyType, Comparator>::clear()
  {
	//check to see if the array is already empty
	if(!isEmpty())
	  {
		//deallocate array
		delete [] dataItems;
		//recreate array with new maxsize
		dataItems = new DataType [maxSize];
		//set the size to zero 
		size = 0;   
	  }  
  }
  
 /** 
  * isEmpty function
  * 
  * This function checks to see if the size is set to zero
  * 
  * @param none
  * 
  * @return bool stating whether or not the size is set to zero
  * 
  * @pre the heap may or may not be empty
  * @post the function will report true or false in accordance to its size
 */

template < typename DataType, typename KeyType, typename Comparator >
bool Heap<DataType, KeyType, Comparator>::isEmpty()const
  {
	//check to see if the size is zero
	return (size == 0);   
  }
  
 /** 
  * isFull function
  * 
  * This function checks to see if the current size of the array matches the maxsize
  * 
  * @param none
  * 
  * @return bool - states whether or not the array is full
  * 
  * @pre the array may or may not be full
  * @post the function will report true or false in accordance to its size and maxsize
 */

  
template < typename DataType, typename KeyType, typename Comparator >
bool Heap<DataType, KeyType, Comparator>::isFull()const
  {
	//check to see if the size matches the maxsize
	return (size == maxSize);   
  }
  
 /** 
  * getLeft function
  * 
  * This function returns the index of the left child of the current index
  * 
  * @param index - the current location in the array
  * 
  * @return none
  * 
  * @pre the left child index will not be returned
  * @post the left child index will be returned
 */

  
template < typename DataType, typename KeyType, typename Comparator >
int Heap<DataType, KeyType, Comparator>::getLeft(int index)const 
  {
	//find the left child
	return((2*index)+1);   
  }

/**  
  * getRight function
  * 
  * This function returns the index of the right child of the current index
  * 
  * @param index - the current location in the array
  * 
  * @return none
  * 
  * @pre the right child index will not be returned
  * @post the right child index will be returned
 */

  
template < typename DataType, typename KeyType, typename Comparator >
int Heap<DataType, KeyType, Comparator>::getRight(int index) const
  {
	//find the right child
	return((2*index)+2);   
  }


/**  
  * getParent function
  * 
  * This function returns the index of the parent of the current index
  * 
  * @param index - the current location in the array
  * 
  * @return none
  * 
  * @pre the parent of current index will not be returned
  * @post the parent of current index will be returned
 */

  
template < typename DataType, typename KeyType, typename Comparator >
int Heap<DataType, KeyType, Comparator>::getParent(int index)const
  {
    //find the parent
	return((index-1)/2);   
  }


//--------------------------------------------------------------------
//
//  Laboratory 11                                         show11.cpp
//
//  Array implementation of the showStructure operation for the
//  Heap ADT
//
//--------------------------------------------------------------------

template < typename DataType, typename KeyType, typename Comparator >
void Heap<DataType,KeyType,Comparator>:: showStructure () const

// Outputs the priorities of the data items in a heap in both array
// and tree form. If the heap is empty, outputs "Empty heap". This
// operation is intended for testing/debugging purposes only.

{
    int j;   // Loop counter

    cout << endl;
    if ( size == 0 )
       cout << "Empty heap" << endl;
    else
    {
       cout << "size = " << size << endl;       // Output array form
       for ( j = 0 ; j < maxSize ; j++ )
           cout << j << "\t";
       cout << endl;
       for ( j = 0 ; j < size ; j++ )
           cout << dataItems[j].getPriority() << "\t";
       cout << endl << endl;
       showSubtree(0,0);                        // Output tree form
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template < typename DataType, typename KeyType, typename Comparator >
void Heap<DataType,KeyType,Comparator>:: showSubtree ( int index, int level ) const

// Helper function for the showStructure() function. Outputs the
// subtree (subheap) whose root is stored in dataItems[index]. Argument
// level is the level of this dataItems within the tree.

{
     int j;   // Loop counter

     if ( index < size )
     {
        showSubtree(2*index+2,level+1);        // Output right subtree
        for ( j = 0 ; j < level ; j++ )        // Tab over to level
            cout << "\t";
        cout << " " << dataItems[index].getPriority();   // Output dataItems's priority
        if ( 2*index+2 < size )                // Output "connector"
           cout << "<";
        else if ( 2*index+1 < size )
           cout << "\\";
        cout << endl;
        showSubtree(2*index+1,level+1);        // Output left subtree
    }
}

/**
  * insert function
  * 
  * This function checks to see if any more data can be placed into the current array. If not, an
  * error is thrown, otherwise, the data is inserted into the array
  * 
  * @param newDataItem - the dataItem that is to be placed into the current heap
  * 
  * @return none
  * 
  * @pre the newDataItem will not be placed into the heap
  * @post the newDataItem will be placed into the heap, if not full
 */

template < typename DataType, typename KeyType, typename Comparator >
void Heap<DataType, KeyType, Comparator>::insert(const DataType& newDataItem) throw (logic_error)
  {
	//check to see if the array is full
    if(isFull())
      {
		//throw logic error
		throw logic_error ("heap full");   
	  }  
	//put new data into the array at the size index
	dataItems[size] = newDataItem;
	//use recurive call to move data to correct location
	heapUp(size); 
	//increment the size
	size++; 
  }

/**  
  * heapUp function
  * 
  * This helper function aides in placing the values of the heap in the correct
  * location after new data is inserted
  * 
  * @param me - current index
  * 
  * @return none
  * 
  * @pre the new data may not be placed in the correct location
  * @post the new data item and all other values will be correctly placed into the tree
 */


template < typename DataType, typename KeyType, typename Comparator >
void Heap<DataType, KeyType, Comparator>::heapUp(int me)
  {
	//get the parent of current child
	int parent = getParent(me);
	//check to see if the parent is not zero
	if(me != 0)
	  {
		//compare the current value with the parent value
		if(Comparator ()(dataItems[me].getPriority(), dataItems[parent].getPriority()))
		  {
			//swap values
			swap(dataItems[me],dataItems[parent]);
			//recursive call to continue moving data 
			heapUp(parent); 
		  }  
	  }
  }
  
/**
  * remove function
  * 
  * This function removes the dataItem of highest priority, unless the 
  * array is empty.
  * 
  * @param none
  * 
  * @return DataType - the dataItem that was removed
  * 
  * @pre dataItems may or may not be in the array
  * @post the dataItem of highest priority is removed, if not empty
 */


template < typename DataType, typename KeyType, typename Comparator >
DataType Heap<DataType, KeyType, Comparator>::remove () throw(logic_error)
  {
	//check to see if the array is empty
	if(isEmpty())
	  {
		//throw logic error
		throw logic_error ("already empty");
	  }  
	//get the dataItem of the highest priority
	DataType item = dataItems[0]; 
	//set the dataItem to the bottom right value
	dataItems[0] = dataItems[--size];
	//recursively move the data to correct location
	heapDown(0); 
	//return the item that was removed
	return item; 
  }
  
/** 
  * heapDown function
  * 
  * This function places data in the correct order after the highest priority.
  * 
  * @param me - index of current dataItem
  * 
  * @return none
  * 
  * @pre the data may or may not be in the correct locations
  * @post the data will be in the correct locations
 */

template < typename DataType, typename KeyType, typename Comparator >
void Heap<DataType, KeyType, Comparator>::heapDown(int me)
  {
	//get the left child
	int left = getLeft(me);
	//get the right child
	int right = getRight(me);
	//check to see if the left value is greater than or equal to the size
	if(left >= size)
	 return; //end call
	else
	  {
		//check to see if the right child is greater than or equivalent to the size
		if(right >= size)
		  {
			//comare the left child to the current dataitem
			if( Comparator()(dataItems[left].getPriority(), dataItems[me].getPriority()))
			  {
				//swap the dataitem values
				swap(dataItems[left],dataItems[me]); 
			  }  
		  }
	    else
	      {
			//set compare to the left child index
			int compare = left; 
			//check the right child's priority against the current priority
			if(Comparator()(dataItems[right].getPriority(), dataItems[me].getPriority()))
			  {
				//set the compare to the right child index
				compare = right;   
			  } 
			//check the compare item against current priority
			if(Comparator()(dataItems[compare].getPriority(), dataItems[me].getPriority()))
			  {
				//swap values
				swap(dataItems[compare],dataItems[me]);
				//recursively call again to ensure values are in right spot 
				heapDown(me);   
			  } 
		  }  
	  } 
	  
  }
  
/**  
  * writeLevels function
  * 
  * This function writes the levels of the heap, starting with the highest priority,
  * and ending with the lowest priority.
  * 
  * @param noen
  * 
  * @return none
  * 
  * @pre nothing will be output
  * @post each level of the heap will be output in the correct order
 */

template < typename DataType, typename KeyType, typename Comparator >
void Heap<DataType, KeyType, Comparator>::writeLevels()const
  {
	//set the level to 0
	int level =0; 
	//check to see if empty
	if(isEmpty())
	  {
		//output that the heap is empty
		cout << "Empty Heap" << endl; 
		//return to end
		return;    
	  }
	//loop through the array
	for(int i = 0; i < size; i++)
	  {
		//output the dataitem value
	    cout << dataItems[i].getPriority() << ' ';
	    //check to see if the level matches i
	    if(level == i)
	      {
			//output the endl
			cout << endl;
			//reset the level
			level = (level+1)*2;   
		  }
	  }
  }
