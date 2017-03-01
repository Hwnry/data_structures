/**
 * @file PriorityQueue.cpp
 * @author Henry Huffman
 * @version 1.1
 * @brief The priority queue uses the predefined heap functions to perform basic priority queue operations.
 * @details More specifically, this program contains the following functions: priorirty queue constructor, enqueue, and dequeue.
 * @date Friday, October 17th, 2014
 */


//Header Files

#include "PriorityQueue.h"

//Function implementations

/**
 * PriorityQueue Constructor
 * 
 * This constructor inherently calls the heap consructor
 * 
 * @param maxNumber - an integer that sets the maxSize of the number of dataItems in the heap array
 * 
 * @return none
 * 
 * @pre  there will not be an initialized heap or priority queue
 * @post  there will be an initialized heap with the maxSize, and size set (and priority queue)
 */

template < typename DataType, typename KeyType, typename Comparator>
PriorityQueue<DataType, KeyType, Comparator>::PriorityQueue ( int maxNumber )
  {
	  
  }

/**
 * enqueue function
 * 
 * This function calls the insert function of the heap.
 * 
 * @param newDataItem - the dataItem that is to be placed into the priority queue
 * 
 * @return none
 * 
 * @pre  the newDataItem will not be in the current priority queue
 * @post  the dataItem will be placed into the priority queue if the heap array is not full
 */

template < typename DataType, typename KeyType, typename Comparator>
void PriorityQueue<DataType, KeyType, Comparator>::enqueue(const DataType &newDataItem )
  {
	//call insert function for heap
	Heap<DataType>::insert(newDataItem);  
  }

/**
 * dequeue function
 * 
 * This function calls the remove function of the heap
 * 
 * @param none
 * 
 * @return DataType - the dataItem that was removed from the priority queue
 * 
 * @pre  the dataItem of highest priority will be in the priority queue
 * @post the dataItem of highest priority will not be in the priority queue
 */

template < typename DataType, typename KeyType, typename Comparator>
DataType PriorityQueue<DataType, KeyType, Comparator>::dequeue()
  {
	//return the removal of item in the heap
	return Heap<DataType>::remove();
  }
