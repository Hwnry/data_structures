/**
 * @file QueuLinked.cpp
 * @author Henry Huffman
 * @version 1.1
 * @brief This program will take and store data in accordance to the standard queue ADT. 
 * @details More specifically, this program will use singly linked nodes to store and move data.
 * Also, this program will use the queue implementations to simulate customers waiting in a line.
 * @date Tuesday, September 08, 2014
 */
 
/*
Author self-assessment statement:
This program is complete according the the specifications of this project.
* I have passed all the given test cases and conducted further test on my own,
* all of which succeeded. 
*/

//header files
#include"QueueLinked.h"

/**
 * Default node constructor.
 * 
 * This function will initialize the nodes for the queue.
 * The nodes will represent customers waiting in a line when used in the storesim program. 
 * These nodes will take in a data of varying type as well as node pointer.
 * The node pointer may containt the address of another node or NULL depending upon the situation.
 * 
 * 
 * The rest of my program relies on this node to take in data.
 * 
 * @param nodeData - the data that the node is to hold
 * @param nextPtr - node pointer that contains the address of another node or is null
 * @return none
 * @exception none
 * 
 * @pre the node will be uninitialized 
 * @post the node will be initialized
 */
template<typename DataType>
  QueueLinked<DataType>::QueueNode::QueueNode(const DataType& nodeData, QueueNode* nextPtr)
    {
	  dataItem = nodeData; 
	  next = nextPtr; 	
    }
 
/**
 * Default queue constructor
 * 
 * This function will initialize the queue. The queue will then be used throughout the rest of the program
 * to hold data specified by the user. It will also be used to simulate people waiting in a line. 
 * 
 * @param ignore - this is a variable that is not to be used in functions implementations
 * @return none
 * @exception none
 * 
 * @pre the queue will be uninitialized
 * @post the node will be initialized
 */ 

template<typename DataType>
  QueueLinked<DataType>::QueueLinked(int ignore)
    {
	  front = back = NULL;   	
    }
    
/**
 * Copy Constructor
 * 
 * This constructor is called when a user wants to copy another queue.
 * Moreover, this copy constructor uses the overloaded assignement operator to copy the other queue.
 * 
 * @param other - this is the queue that is going to be copied
 * @return none
 * @exception none
 * 
 * @pre the queue will be uninitialized
 * @post the queue will be initialized with the identical data and structure as the other queue. 
 */
    
template<typename DataType>
QueueLinked<DataType>::QueueLinked(const QueueLinked& other)
  {
    (*this) = other; 
  }
  
/**
 * Overloaded assignment operator
 * 
 * This operator is called when a linked queue is being assigned to another linked queue.
 * The purpose of this function is to get an identical copy of the assigned queue.
 * 
 * @param other - the queue that is to be copied
 * @return (*this) - it returns the current queue (the new copy of the queue)
 * @exception this function will not work if a queue is trying to assign itself
 * 
 * @pre two queues will be initialized and one will be assigned to the other
 * @post the data and structure of the two queues will be identical
 */

template<typename DataType>
QueueLinked<DataType>& QueueLinked<DataType>::operator=(const QueueLinked& other)
  {
    //check to see if queue is being assigned itself
    if(this != &other)
      {
	    //initialization
	    QueueNode *src = other.front;
	    QueueNode *dest;
	    //check to see if other queue is empty
	    if(!other.isEmpty())
	      {
			front = back = NULL;   
		  }
		else
		  {
		    front = new QueueNode(src->dataItem, NULL);
		    dest = front; 
		    //check to see if there is only one node
		    if(src->next == NULL)
		      {
				back = front;   
			  }  
			//continue through the rest of the nodes
			src= src->next; 
			while(src!=NULL)
			  {
				dest->next = new QueueNode(src->dataItem, NULL);
				dest= dest->next;
				src= src->next;   
			  }
			back = dest; 
			
		  }
	  }
    //return new list
    return (*this); 
  }

/**
 * Deconstructor
 * 
 * The deconstructor deallocates space that was allocated to the queue.
 * This deconstructor calls the clear function because its will remove all the nodes
 * of the specified queue. It will then set the front and back pointers to null.
 * 
 * @param none
 * @return none
 * @exception noen
 * 
 * @pre there will be a queue with allocated memory
 * @post the memory of the queue will be deallocated and pointers will be set to null
 */


template<typename DataType>
QueueLinked<DataType>::~QueueLinked()
  {
	clear(); 
	front = back = NULL;   
  }
  
/**
 * enqueue function
 * 
 * The purpose of this function is to add a node with new data to the back of the queue.
 * It is used in the line simulation to add customers with their arrival time to the back of the line.
 * This function will check to see if the queue is full. If full, it will throw an error message. Otherwise,
 * The function will check to see if it is empty and add the data accordingly. Because this is a void function,
 * nothing will be returned.
 * 
 * @param newDataItem - the data of the new node that is added to the back of the queue
 * @return none
 * @exception queue can not be full
 * 
 * @pre a queue with or without data in it 
 * @post a queue with atleast one item of data in it or a new data item added to the back of the queue
 */


template<typename DataType>
void QueueLinked<DataType>::enqueue(const DataType& newDataItem) throw (logic_error)
  {
    //check to see if queue is full
    if(isFull())
      {
		throw logic_error("enqueue() while queue full");  
	  }
	else
	  {
		//initialization
		QueueNode* temp = new QueueNode(newDataItem, NULL);
		if(isEmpty())
		  {
	        front = back = temp;   
		  }  
		else
		  {
		     back->next = temp; 
		     back = temp; 
		  }
	  }
	  
  }
  
/**
 * dequeue function
 * 
 * This function is used to remove the least recently added item from the queue.
 * In the line simulation, this function is used to remove the customer in line and retrieve
 * their arrival time. In this function, if there is nothing to remove, a error message will
 * be thrown. If the only item of a queue is removed, it will set the pointers to null; otherwise,
 * only the first item in the queue will be removed. 
 * 
 * @param none
 * @return DataType - this function will return whatever data is in the first node of the queue.
 * @exception this function will not work if the queue is empty
 * 
 * @pre a non-empty queue
 * @post a queue with one less data item in it, possibly empty. The data in removed item is returned. 
 */

  
template<typename DataType>
DataType QueueLinked<DataType>::dequeue() throw (logic_error)
  {
   //check to see if queue is empty
	if(isEmpty()) 
	{
      throw logic_error("dequeue() while queue empty");  
	}  

   else
    {
	  //initialize
	  int dq = front->dataItem; 
	  QueueNode* after = front->next; 
	  delete front; 
	  //check to see if only one node
	  if(front == back)
		{
		  front = back = after; 
		}
	   else
		{
		  front = after; 	
		}
	  return dq; 		
    }	
  }
 
 /**
 * clear operator
 * 
 * This function is called when the user wished to get rid of all the data
 * stored in current queue. If the queue is not empty, the clear function
 * will move through each node and deallocate the memory in use. Finally,
 * it will set front and back pointers to null.
 * 
 * @param none
 * @return none
 * @exception none
 * 
 * @pre a queue with or without data
 * @post a queue without any data 
 */
 
template<typename DataType>
void QueueLinked<DataType>::clear()
  {
    //check to see if empty
    if(!isEmpty())
      {
		//prime loop incase of only one node
        back = front;
        back= back->next;
        delete front;
        front = back;
        //iterate throught rest of the nodes if any
        while(back!= NULL)
          {
			back= back->next;
			delete front;
			front = back;   
		  }  
	  }
  }

/**
 * Empty function
 * 
 * This function checks to see if a queue is empty. It is essential becuase
 * it is used frequently throughout the rest of the implementations. If there is data
 * in the queue, it will return false. If empty it will return true.
 * 
 * @param none
 * @return bool - it returns a boolean with true if it is empty, and false if it has data
 * @exception none
 * 
 * @pre a queue that may or may not be empty
 * @post a boolean with a value that determines whether or not a queue is empty
 */


template<typename DataType>
bool QueueLinked<DataType>::isEmpty()const
  {
    if(front == NULL && back == NULL)
      {
		return true;   
	  }
	return false; 
  }
  
/**
 * isFull function
 * 
 *This function checks to see if a queue is full or not.
 * Because I currently do not run the possiblity of running out of memory,
 * this funciton will always return false.
 * 
 * @param none
 * @return bool - a boolean with the value of false because I will not run out 
 *                of memory while running this program.
 * @exception none
 * 
 * @pre a queue with or without data in it
 * @post a boolean set to false because the queue will never be full
 */

 
 template<typename DataType>
 bool QueueLinked<DataType>::isFull()const
   {
	 return false;    
   }

// show7.cpp: includes implementation of showStructure
//--------------------------------------------------------------------

//--------------------------------------------------------------------

template < typename  DT >
void QueueLinked<DT>:: showStructure () const

// Linked list implementation. Outputs the elements in a queue. If
// the queue is empty, outputs "Empty queue". This operation is
// intended for testing and debugging purposes only.

{
    QueueNode *p;   // Iterates through the queue

    if ( isEmpty() )
	cout << "Empty queue" << endl;
    else
    {
	cout << "Front\t";
	for ( p = front ; p != 0 ; p = p->next )
	{
	    if( p == front ) 
	    {
		cout << '[' << p->dataItem << "] ";
	    }
	    else
	    {
		cout << p->dataItem << " ";
	    }
	}
	cout << "\trear" << endl;
    }
}


/**
 * putFront function
 * 
 * This function will take new data and place it at the front of the queue.
 * This function will add a node to the queue if it is empty. If the queue is not 
 * empty, a new node will be added to the beginning of current queue with changing
 * the remainder of the queue
 * 
 * @param newDataItem - the data that will be placed in the new node
 * @return none
 * @exception none
 * 
 * @pre a queue with or without data
 * @post a queue with a new data item added to the beginning of it
 */

template<typename DataType>
void QueueLinked<DataType>::putFront(const DataType& newDataItem) throw (logic_error)
  {
    if(isEmpty())
      {
		front = back = new QueueNode(newDataItem, NULL);    
	  }
	else
	  {
		//insert new data at front of queue
		//initialization
		QueueNode* temp;
		temp = new QueueNode(newDataItem, front);
		front = temp;   
	  }
  }

/**
 * getRear
 * 
 * This function will get the data from the most recently added item of the queue,
 * then it will deallocate it. If the queue is full it will throw an error message.
 * 
 * @param none
 * @return DataType - returns the data that was in the last item in the queue
 * @exception the queue can not be empty
 * 
 * @pre a queue with atleast one data item in it
 * @post a queue with one less data item in it, and the value of the data item is returned
 */


template<typename DataType>
DataType QueueLinked<DataType>::getRear() throw ( logic_error)
  {
	if(isEmpty())
	  {
      throw logic_error("getRear() while queue empty");
      } 
    else
      {
		//initialization
		DataType rear = back->dataItem; 
		//check to see if there is only one node
		if(front == back)
		  {
			delete back;
			front = back = NULL; 			  
		  }
		else
		  {
		    QueueNode* dest = front;
		    while(dest->next != back)
		      {
				dest = dest->next;   
			  }
			delete back;
			back = dest;
			back->next = NULL;  
	      }
		return rear; 
      }
  }
  
/**
 * getLength function
 * 
 * This function determines the number of items in the queue.
 * 
 * @param none
 * @return int - an integer matching the number of items in the queue
 * @exception none
 * 
 * @pre a queue
 * @post the number of items in the queue is returned 
 */

  
template<typename DataType>
int QueueLinked<DataType>::getLength () const
  {
	//initialization
	int num;
	QueueNode* cursor = front; 
	//if it is empty
	if(isEmpty())
	 {
       num = 0; 
     }
   else if(front == back)
     {
	   num = 1;	 
	 }
	else
	 {
	   while(cursor!= NULL)
	     {
		   num++;
		   cursor = cursor->next; 	 
	     }
     }
	return num;  
  }
