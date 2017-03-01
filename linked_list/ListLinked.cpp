#include"ListLinked.h"

/*
ListNode Constructor
Requirements: none
Results: Creates an initialized listnode by setting the listnode's data item to the value
         nodeData and the ListNode's next pointer to the value of nextPtr 
*/
template<typename DataType>
List<DataType>::ListNode::ListNode(const DataType& nodeData, ListNode* nextPtr)
  {
    //set data
    dataItem = nodeData;
    //set pointer
    next = nextPtr; 
  }

/*
Default List Constructor
Requirements:none
Results: Creates an empty list
*/  
template<typename DataType>
List<DataType>::List(int ignored)
  {
    //set node pointers to null
    head = cursor = NULL; 
  }
  
/*
Copy Constructor
Requiremnts:none
Results: initializes the list to be equivalent to the other list
*/
template<typename DataType>
List<DataType>::List(const List& other)
  {
    //initialization
    ListNode* temp;
    head = cursor = NULL;         
    //check to see if other list is empty
    if(!other.isEmpty())
      {
        //set temp to other list
        temp = other.head;
        //copy first node
        head = cursor = new ListNode(other.head->dataItem,NULL);
        //copy remaining nodes
        while(temp->next != NULL)
          {
			//move temp to next spot
            temp = temp->next; 
            //create a new node after current curser
            cursor->next = new ListNode(temp->dataItem, NULL);
            //move cursor to new node
            cursor= cursor->next; 
          }
         
      }
   temp= NULL; 
  }
  
/*
Overloaded Assignment Operator
Requirements: none
Results: sets the list to be equivalent to the other list and returns
         a reference to this object
*/  
template<typename DataType>
List<DataType>& List<DataType>::operator=(const List& other)
  {
    //initialization
    ListNode* temp;
    //check for assignment error
    if(this != &other)
      {
		if(!isEmpty())
		  {
			clear();   
		  }
        //initialize head and cursor
        head = cursor = NULL; 
        //check to see if other list is empty
        if(!other.isEmpty())
          {
            //set temp to other list
            temp = other.head; 
            //set head and cursor
            head = cursor = new ListNode(other.head->dataItem,NULL);
            //copy remainder of list
            while(temp->next != NULL)
              {
				//move temp to the next spot
                temp= temp->next;
                //create a new node after cursor
                cursor->next = new ListNode(temp->dataItem,NULL);
                //move cursor to new node
                cursor=cursor->next; 
              }
          }
      }
    temp= NULL; 
    //return current list 
    return(*this); 
  } 
  
/*
List Destructor
Requirements: none
Results: deallocates the memory used to store the nodes in the list
*/
template<typename DataType>
List<DataType>::~List()
  {
   //check to see if list is empty
   if(!isEmpty())
     {
       //go through list and deallocate nodes
       cursor = head; 
       while(cursor->next != NULL)
         {
		   //move cursor to next spot
           cursor = cursor->next; 
           //deallocate head
           delete head; 
           //set head to cursor
           head = cursor; 
         }
      //delete last node
      delete cursor;
      //set pointers to null
      head = cursor = NULL;     
     } 
  }
  
/*
Insert function
Requirements: list is not full
Results: inserts newDataItem into the list. If the list is not empty, then 
         inserts newDataItem after the cursor. Otherwise, inserts newDataItem as the first
         and only data item in the list. Always moves cursor to newDataItem
*/
template<typename DataType>
bool List<DataType>::insert(const DataType& newDataItem)
  {
    //initialization
    ListNode* temp; 
    //check to see if full
    if(!isFull())
      {
       //check to see if empty
       if(isEmpty())
         {
		   //creates the first node in list
           head = cursor = new ListNode(newDataItem, NULL);          
         }
         
      //if not first item
      else
        {
		  //create a new node linked to data after cursor
          temp= new ListNode(newDataItem,cursor->next);
          //link cursor to temp
          cursor->next = temp; 
          //move cursor to new node
          cursor=cursor->next;  
        }
      temp = NULL; 
       return true; 
      }
    return false; 
  }
  
/*
Remove function
Requirements: List is not empty
Results: removes the data item marked byu the cursor from the list. 
         If list is not empty, cursor moves to item following removed node.
         If deleted item is at the end of the list, moves the cursor to the beginning of the list
*/ 
template<typename DataType>
bool List<DataType>::remove()
  {
    //initialization 
    ListNode* temp;
    //check to see if list is empty
    if(isEmpty())
      {
		//return false and end function
		return false;   
	  }
	//check to see if head and cursor are the same  
	else if(cursor == head)
	  {
		//move cursor to next node or null
		cursor = cursor->next; 
		//deallocate head
		delete head;
		//set head equivalent to cursor
		head = cursor; 
		//return true and end function
		return true;   
		}
	//check to see if cursor is at the end	
	else if(cursor->next == NULL)
	  {
		//set temp to cursor
	    temp = cursor; 
	    //move cursor back a space
	    gotoPrior();
	    //deallocate temp
	    delete temp; 
	    //set next pointer and temp to null
	    cursor->next = temp = NULL;
	    //move cursor to the beginning
	    gotoBeginning();  
	    return true; 
		  }
    //if node is located somewhere in the middle of list
	else
	  {
		//set temp to cursor
		temp = cursor;
		//move cursor to previous node
		gotoPrior();
		//link cursor to bypass unwanted node
		cursor->next = temp->next;
		//deallocate temp
		delete temp;
		temp = NULL;
		//move cursor to the next node 
		cursor = cursor->next; 
		return true; 
		  }
  }
  
/*
Replace Function
Requirements: List is not empty
Results: replaces the data item marked by the cursor with newDataItem. 
         Cursor remains at the newDataItem
*/

template<typename DataType>
bool List<DataType>::replace(const DataType& newDataItem)
  {
    //check to see if empty
    if(!isEmpty())
      {
		//set node data to the newdata given
        cursor->dataItem = newDataItem; 
        return true; 
      }
    return false; 
  }
  
/*
Clear Function
Requirements: none
Results: removes all the data items in the list
*/
template<typename DataType>
void List<DataType>::clear()
  {
    //check to see if empty
    if(!isEmpty())
      {
        //remove remaing data
        cursor = head; 
        
        while(cursor->next != NULL)
          {
			//move cursor to the next node
            cursor=cursor->next;
            //deallocate head
            delete head;
            //set head to cursor
            head = cursor; 
          }
        //delete last node
        delete cursor;
        cursor = head = NULL; 
      }
  }
  
/*
isEmpty Function
Requirements: none
Results: returns true irf list is empty, false otherwise
*/
template<typename DataType>
bool List<DataType>::isEmpty()const
  {
	//check to see if list pointers are set to null
    if(head==NULL && cursor==NULL)
      { 
		//set to null, return true
        return true; 
      }
    //not set to null
    return false; 
  }
  
/*
isFull function
requirements: none
results: results true if list is full (always false for this project)
*/
template<typename DataType>
bool List<DataType>::isFull()const
  {
	//always set to false
    return false; 
  }
  
/*
gotoBeginning function
requirements: list is not empty
results: moves cursor to the beginning of the list
*/
template<typename DataType>
bool List<DataType>::gotoBeginning()
  {
    //check to see if list is empty
    if(!isEmpty())
      {
		//set cursor to head
        cursor = head; 
        return true; 
      }
    return false; 
  }
  
/*
gotoEnd function
Requirements: list is not empty
Results: moves the cursor to the end of the list
*/
template<typename DataType>
bool List<DataType>::gotoEnd()
  {
    //check to see if list is empty
    if(!isEmpty())
      {
        while(cursor->next != NULL)
          {
			//move to next node
            cursor= cursor->next; 
          }
         //return true for end of list
        return true; 
      }
   return false; 
  }
  
/*
gotoNext
Requirements: list is not empty
Results: If the Cursor is not at the end of the list, then moves the cursor 
         to mark the next data item in the list and return true. Otherwise,
         returns false
*/
template<typename DataType>
bool List<DataType>::gotoNext()
  {
    //check to see if list is empty
    //check to see if cursor is at the end
    if(!isEmpty() && cursor->next != NULL)
      {
        //move cursor to the next node
        cursor= cursor->next; 
        return true;       
      }
    return false; 
  }
  
/*
gotoPrior function
Requirements: list is not empty
Results: if the cursor is not a the beginning of the list, then moves the cursor
         to mark the preceding data item in the list and returns true. Otherwise,
         returns false
*/
template<typename DataType>
bool List<DataType>::gotoPrior()
  {
    //initialization
    ListNode* temp; 
    //check to see if empty
    //check to see if at the beginning
    if(!isEmpty() && cursor != head)
      {
        //use temp to get to previous node
        temp = head;
        while(temp->next != cursor)
          {
			//move to next node
            temp=temp->next;
          }     
        //set cursor to temp
        cursor = temp; 
        //successful function, so return true
        temp = NULL;
        return true;  
      }
    temp = NULL; 
    return false; 
  }
  
/*
getCursor Function
Requirements:list is not empty
Results:returns the value of the data item marked by the cursor
*/
template<typename DataType>
DataType List<DataType>::getCursor()const
  {
    //check to see if list is empty
    if(!isEmpty())
      {
		//return cursor data
        return cursor->dataItem; 
      }
  }

  
  
  
  
//--------------------------------------------------------------------
// show5.cpp: includes implementation of showStructure
//--------------------------------------------------------------------

template <typename DataType>
void List<DataType>::showStructure() const

// Outputs the items in a list. If the list is empty, outputs
// "Empty list". This operation is intended for testing and
// debugging purposes only.

{
    if ( isEmpty() )
    {
       cout << "Empty list" << endl;
    } 
    else
    {
	for (ListNode* temp = head; temp != 0; temp = temp->next) {
	    if (temp == cursor) {
		cout << "[";
	    }

	    // Assumes that dataItem can be printed via << because
	    // is is either primitive or operator<< is overloaded.
	    cout << temp->dataItem;	

	    if (temp == cursor) {
		cout << "]";
	    }
	    cout << " ";
	}
	cout << endl;
    }
}

  
/*
Exercise 2
moveToBeginning function
Requirements: List is not empty
Results: Removes the Data item marked by the cursor from the list and
         reinserts the data item at the beginning of the list.
         Moves the cursor to the beginning of the list 
*/

template <typename DataType>
bool List<DataType>::moveToBeginning()
  {
    //initialization
    ListNode *temp, *deltemp; 
    //check to see if empty
    if(isEmpty())
      { //return false
		return false;   
	  }
	//check to see if cursor is at the beginning
    else if(head == cursor)
      { //return false 
		return false;   
	  }
	else
	  {
		//create a new node, link it to head
		temp = new ListNode(cursor->dataItem,head);
		//set head to temp
		head = temp;
		//set other temp to cursor
		deltemp = cursor;  
		//move cursor to previous node
		gotoPrior(); 
		//link cursor to bypass deltemp node
		cursor->next = deltemp->next; 
		//deallocate deltemp node
		delete deltemp; 
		//set pointer to null
		deltemp = NULL; 
		//move cursor to first node
		gotoBeginning(); 
		return true;  
	  }    
}

/*
Exercise 3
insertBefore function
Requirements: list is not full
Results: Inserts newDataItem into a list. If the list is not empty,
         then inserts newDataItem immediately before the cursor.
         Otherwise, inserts newDataItem as the first (and only) data
         item in the list. In either case, moves the cursor to newDataItem. 
*/
template<typename DataType>
bool List<DataType>::insertBefore(const DataType& newDataItem)
  {
    //initialization
    ListNode* temp;
    //check to make sure list is not full
    if(!isFull())
      {
	    //check to see if list is empty
        if(isEmpty())
          {
			//create first node
            cursor = head = new ListNode(newDataItem,NULL);
          }
        // check to see if head == cursor  
        else if(head == cursor)
          {
            //create a new node before head
            temp = new ListNode(newDataItem, head);
            //set head to temp
            head = temp; 
            cursor = head;  
          } 
        // it is somewhere in the middle  
        else
          {
			//set new temp with current cursor's data
            temp = new ListNode(cursor->dataItem, cursor->next);
            //change the data in current cursor
            cursor->dataItem = newDataItem;
            //link cursor to temp
            cursor->next = temp;   
		  }
        
         temp = NULL; 
         return true;
      }
    temp = NULL; 
    return false; 
  }
