#include "BSTree.h" 

/**
 * @file BSTree.cpp
 * @author Henry Huffman
 * @version 1.1
 * @brief This program is used to build binary search trees, perform basic binary search tree functions, specialized binary search tree functions, and
 *        even manipulate database information.
 * @details More specifically, this program has the following basic member functions: default constructor, copy constructor, overloaded assignement operator,
 *          deconstructor, insert, retrieve, remove, writeKyes, clear, isEmpty, and showStructor. To specifically see what each of these functions do, please
 *          see each of their specific documentation. For specialized functions, it includes all of the following: getCount, getHeight, writeLessThan. Again, if 
 *          you wish to see what each of these functions do, please see their specific documentation. This program performs basic manipulation of database information
 *          by using the functions previously specified in this entry. The program will read from a file, store basic data, and perform basic i/o. 
 * 
 * @date Friday, October 17th, 2014
 */

/**
 * BSTreeNode constructor
 * 
 * This constructor sets the data item as well as the left and right pointers.
 * 
 * @param nodeDataItem - the data that is stored inside the node
 * @param leftPtr - a node pointer that points to the node to the left of the current node
 * @param rightPtr - a node pointer that points to the node to the right of the current nodes
 * 
 * @return none
 * 
 * @pre - there will be an uninitialized node
 * @post - there will be an initialized node that holds the information passed to it from the parameters
 */

template < typename DataType, typename KeyType >
BSTree<DataType,KeyType>::BSTreeNode::BSTreeNode ( const DataType &nodeDataItem, BSTreeNode *leftPtr, BSTreeNode *rightPtr )
  {
	//set dataItem
	dataItem = nodeDataItem;
	//set left pointer
	left = leftPtr;
	//set right pointer
	right = rightPtr; 
  }
  
/**
 * BSTree constructor
 * 
 * This constructor sets the root pointer of the initialized tree to null
 * 
 * @param none
 * 
 * @return none
 * 
 * @pre there will be an uninitialized tree
 * @post there will an initialized tree with the root pointer set to null
 */
template < typename DataType, typename KeyType >
BSTree<DataType,KeyType>::BSTree()
  {
	//set the root pointer to null
	root = NULL;   
  }

/**
 * BSTree copy constructor
 * 
 * This constructor initializes a tree then copies the value of another tree.
 * This process is completed by setting the root pointer to null, then calling
 * the overloaded assigment operator to copy the values of a second tree.
 * 
 * @param other - a binary tree that is to be copied to the current tree
 * 
 * @return none
 * 
 * @pre there will be one unitialized tree, and a tree that has not been copied
 * @post there will be two trees with identical values 
 */

template<typename DataType, typename KeyType >
BSTree<DataType,KeyType>::BSTree( const BSTree<DataType,KeyType>& other )
  {
	//set the root pointer to null
	root = NULL;
	//call the overloaded assignment operator to copy the other tree
	(*this) = other;   
  }

/**
 * overloaded assignement operator
 * 
 * This function takes two intialized trees and assigns the current tree the value of the other tree.
 * This function checks to see if the same tree is assigned itself. If this is true, it returns the same tree; otherwise,
 * it proceeds to clear the current tree and call the assignment helper. The assignment helper then recursively moves throughout
 * the current and "other" tree to copy the values from the "other" tree. 
 * 
 * @param other - the binary tree that is to be copied
 * 
 * @return (*this) - the current tree with the copied values
 * 
 * @pre - there will be two initialized trees
 * @param - there will be two trees with identical values in them. 
 */

template<typename DataType, typename KeyType >
BSTree<DataType,KeyType>& BSTree<DataType,KeyType>::operator= ( const BSTree<DataType,KeyType>& other )
  {
    //if the same tree is assigned to itself
	if(this == &other)
	  {
		//return the current tree
		return (*this);   
	  }  
	  
	//clear the current tree
	clear(); 
	
	//set the current root to null
	root = NULL; 
	//call the assignment helper to copy the other tree
	assignmentHelper(root,other.root); 
	//return the current tree  
	return (*this); 
  }

/**
 * assignmentHelper function
 * 
 * This function moves throughout the two trees and assigns the values from the src tree to the dest tree.
 * This function is recursive, so it will call itself until the entire tree is copied. The base case for this call
 * is if the src node is null. 
 * 
 * @param dest - the node that will contain a copy of the src node's data.
 * @param src - the node that contains the informationn that must be copied.
 * 
 * @pre two pointers will be passed to this function.
 * @post the dest pointer will contain the src pointer's data and recursively call itself to copy the rest of the tree.
 *       If the src pointer was null, nothing occured.  
 */

template<typename DataType, typename KeyType >  
void BSTree<DataType, KeyType>::assignmentHelper(BSTreeNode*& dest, BSTreeNode* src)
  {
	 //check to see if current node is null
	  if(src != NULL)
	    {
	     //allocate memeory to node
		 dest = new BSTreeNode(src->dataItem, NULL,NULL);
		 //call assignmentHelper to check if there is a node to the left of the current node 
	 		assignmentHelper(dest->left,src->left);  
	 	//call assignemtnHeper to check if there is a node to the right of the current node
			assignmentHelper(dest->right,src->right);   
		}
  }
  
/**
 * BSTree deconstructor
 * 
 * This function clears all the data inside the current tree. It first checks to see if the 
 * tree is already empty. If it is not empty, it calls the clear function to deallocate all 
 * the memory allocated in the tree. 
 * 
 * @param none
 * 
 * @return none
 * 
 * @pre there may be a tree with memory allocated in it
 * @post there not be any memory allocated to the current tree
 */
template<typename DataType, typename KeyType >
BSTree<DataType,KeyType>::~BSTree ()
  {
	//check to see if tree is empty
	if(!isEmpty())
	  {
		//clear the tree
		clear();   
	  }  
  }
  
/**
 * insert function
 * 
 * This function inserts the new data into the proper location of the BST.
 * It first checks to see the current tree is empty. If it is empty, it simply sets the root 
 * equal to the new data. Otherwise, it calls the insertHelper to place the data in the correct
 * location. If the same data item already exist, the new data item replaces it. 
 * 
 * @param newDataItem - the newest data that must be added to the current binary tree
 * 
 * @return none
 * 
 * @pre an existing tree will not have the new data item included in it
 * @post the current tree will now have the new data item, if the new data item had the same key as an
 *       old data item, the the old data item will be replaced
 */
template<typename DataType, typename KeyType >
void BSTree<DataType,KeyType>::insert ( const DataType& newDataItem )
  {
	//check to see if the current tree is empty
    if(isEmpty())
       {
		 //if it is empty then we need to insert newdata at the root
		 root = new BSTreeNode(newDataItem, NULL, NULL);    
	   }
	else
	  {
		//call inserthelper to place it accordingly
		insertHelper(root, newDataItem);   
	  }
  }

/**
 * insertHelper function
 * 
 * This function inserts the new dataItem into the correct location by checking the key and pointer.
 * If the key is greater, it moves to the right of the current node. If the key is less, it moves to the
 * left of the current node. If it is equivalent, it replaces the current data with the new data.
 * If the pointer reaches a null location, the new data will be inserted into a new node at specified location. 
 * 
 * @param ptr - the current node that is to be compared
 * @param newDataItem - the information that is to be inserted into the binary tree
 * 
 * @return none
 * 
 * @pre the dataItem will not be inserted into the current BST
 * @post the dataItem will be inserted in the correct location of the current BST
 */

template<typename DataType, typename KeyType >
void BSTree<DataType,KeyType>::insertHelper(BSTreeNode*& ptr, const DataType& newDataItem)
  {
	//check to see if it is at the end
	if(ptr == NULL)
	  {
		ptr = new BSTreeNode(newDataItem, NULL, NULL);   
	  }
    //check to see if the current value is less than the newDataItem 
    if((newDataItem.getKey()) > ((ptr->dataItem).getKey()))
      {
	   insertHelper(ptr->right, newDataItem); 	
	  }
   //check to see if the current value is greater than the newDataItem
    if((newDataItem.getKey()) < ((ptr->dataItem).getKey()))
   	 {
	  insertHelper(ptr->left, newDataItem); 	
	 }
   //check to see if current value is matching
    if((newDataItem.getKey()) == ((ptr->dataItem).getKey()))
      {
		ptr->dataItem = newDataItem;   
	  }
  }

/**
 * retrieve function
 * 
 * This function checks to see if there is a data item that currently matches the search key.
 * If the data item is found, it returns true and copies the data item to the search dataItem. 
 * Otherwise, it will return false. This function relies upon the retrieve helper function to 
 * find the data item. 
 * 
 * @param searchKey - a unique id that corresponds the search dataItem
 * @param searchDataItem - the dataItem that will hold the data of the node with the corresponding key
 * 
 * @return bool - returns whether or not the search item was found
 * 
 * @pre - data item may or may not be located in the current BST
 * @post - data Item will either be found or it will not be found 
 */

template<typename DataType, typename KeyType>
bool BSTree<DataType,KeyType>:: retrieve ( const KeyType& searchKey, DataType& searchDataItem ) const
  {
	//check to see if the current tree is empty
    if(isEmpty())
      {
		return false;   
	  }
    //call the retrieve helper to search the remainder of the tree
    return (retrieveHelper(root, searchKey, searchDataItem));
  }
  
/**
 * retrieveHelper function
 * 
 * This function moves throughout the BST in search of a dataItem with the matching keys.
 * If key is found, it returns true and updates the search data item. Otherwise, it will check to 
 * left and to the right of the current node. If the end of the tree is reached without a solution,
 * false is returned.
 * 
 * @param ptr - the current node that is going to be compared
 * @param searchKey - the key that will determine if the current node matches, or if the search will continue to the left or to the right
 * @param searchDataItem - the data at the matching node will be assigned to this parameter
 * 
 * @return bool - returns whether or not the matching node was found
 * 
 * @pre the dataItem with the corresponding searchKey may or may not be in the BST
 * @post the matching dataItem will be found, or it will not be found. 
 */

template<typename DataType, typename KeyType>
bool BSTree<DataType,KeyType>:: retrieveHelper(BSTreeNode*ptr, const KeyType& searchKey, DataType& searchDataItem)const
  {
    if(ptr != NULL){
		//base case - if ptr is a match
		if(((ptr->dataItem).getKey()) == searchKey)
		  {
			searchDataItem = (ptr->dataItem); 
			return true;   
		  }
		//the key is greater than the current key
		if(((ptr->dataItem).getKey()) < searchKey)  
		  {
			return(retrieveHelper(ptr->right,searchKey,searchDataItem));  
		  }
		//the key is less than the current key
		if(((ptr->dataItem).getKey()) > searchKey)
		  {
			return(retrieveHelper(ptr->left, searchKey,searchDataItem)); 
		  }
	  }
	//base case - if ptr has reached the end of the tree	  
	return false; 
  }
  
/**
 * remove function
 * 
 * This function will remove a specified node. This function will return false if it is empty, or
 * it will call the removeHelper to aide in the locating and removal of said node. To check whether or not
 * the node is actually in the BST at all, the retrieve function is being used.  
 * 
 * @param deleteKey - the key of the matching 
 * 
 * @return bool - returns true if the specified item was deleted, returns false otherwise
 * 
 * @pre there may or may not be a specified node that needs to be deleted from the current tree
 * @post there will not be a node that matches the item to be deleted in the current BST. 
 */
template<typename DataType, typename KeyType > 
bool BSTree<DataType, KeyType>::remove ( const KeyType& deleteKey )
  {
	//initialization
	DataType ignore;
	//check to see if BST is empty 
	if(!isEmpty())
	  {
		//check to see if node is in BST
		if(retrieve(deleteKey, ignore))
		  {
			//remove specified node
	        return(removeHelper(root, deleteKey)); 
	      }
	  }
	//return false because the deleteKey could not be found, or the tree is empty
	return false; 
  }

/**
 * removeHelper function
 * 
 * This function removes the specified node from the BST. It relies on recursive calls 
 * throughout the current BST. It has several cases to account for the possible
 * variations of children a node may have.
 * 
 * @param src - a pointer that has the address to the current pointer
 * @param deleteKey - the key that is used to identify the node that is needed to be deleted
 * 
 * @return bool - a boolean statement that determines whether or not the node was removed 
 * 
 * @pre there may or may not be the node that needs to be deleted in the current BST
 * @post the delete key will no longer be in the current BST
 */
template<typename DataType, typename KeyType >
bool BSTree<DataType, KeyType>::removeHelper(BSTreeNode*& src, const KeyType& deleteKey)
  {
	//check to see if current pointer is null
	if(src == NULL)
	  {
		return false;   
	  }
	 //check to see if current node must be deleted
	 if(src->dataItem.getKey() == deleteKey)
	   {
		 //node has no children
		 if(src->left == NULL && src->right == NULL)
		   {
			 //remove node and set to null
			 delete src;
			 src = NULL;
			 return true;     
		   }
		 //node has left child only
		 if(src->left != NULL && src->right == NULL)
		   {
			 //set node to child and remove old node
			 BSTreeNode* temp = src; 
			 src = src->left; 
			 delete temp;  
			 return true;  
		   }   
		 //node has right child only
		 if(src->right != NULL && src->left == NULL)
		   {
			//set node to child and remove old node
			BSTreeNode* temp = src; 
			src= src->right;
			delete temp;
			return true;     
		   }
		 //node has both children
		 if(src->left != NULL && src->right != NULL)
		   {
			 //use a temp to find node with closest value of current node
			 BSTreeNode* temp = src->left; 
			 while(temp->right != NULL)
			   {
				 temp= temp->right;   
			   } 
			 //place that data into current node
			 src->dataItem = temp->dataItem;
			 //remove temp node
			 return removeHelper(src->left, temp->dataItem.getKey());   
		   }
	   }
	   
	//recursive call, checks left
	if(src->dataItem.getKey() > deleteKey)
	  { 
		//checks left of current node
		return (removeHelper(src->left, deleteKey));  
	  }
    //recrusive call, checks right
    return(removeHelper(src->right, deleteKey)); 
  }
  
/**
 * writeKeys function
 * 
 * This function outputs the keys of each dataItem. This is done in ascending order
 * on one line, and it is seperated by one space between each key. This function calls
 * the write helper function so it can recursively move througout the BST and output the 
 * keys in correct order
 * 
 * @param none
 * 
 * @return none
 * 
 * @pre the keys will remain hidden from the user
 * @post the keys will be output to the screen
 */  
  
template<typename DataType, typename KeyType >
void BSTree<DataType, KeyType>::writeKeys () const  
  {
	//check to see if current tree is empty
    if(!isEmpty())
      {
		//call writeHelper
		writeHelper(root);  
		cout << endl; 
      }
  }
  
/**
 * writeHelper function
 * 
 * This function writes the keys of each dataItem in ascending order.
 * This is done by checking if the current node is null. If it is not null,
 * it will check to the left first to print out the lesser vales. Then it will output
 * the current nodes. Then it will output the nodes to the right because they should be
 * higher in value. 
 * 
 * @param ptr - current node that will check left, be output, then check right
 * 
 * @return none
 * 
 * @pre no keys will be output
 * @post keys will be output in ascending order
 */
  
template<typename DataType, typename KeyType>
void BSTree<DataType, KeyType>::writeHelper(BSTreeNode* ptr) const
  {
	//check to see if current node is null
	if(ptr != NULL)
	  {
		//write all nodes to the left because they are less in value
		writeHelper(ptr->left); 
		//write current node
		cout << (ptr->dataItem).getKey() << ' ';
		//write all nodes to the right because they have a higher value
		writeHelper(ptr->right); 	      
	   }	
  }
  
/**
 * clear function
 * 
 * This function will remove nodes from the BST using a postorder traversal.
 * 
 * @param none
 * 
 * @return none
 * 
 * @pre there may or may not be data in current tree
 * @post there will not be data in the current tree and root will be set to NULL
 */
  
template<typename DataType, typename KeyType>
void BSTree<DataType, KeyType>::clear()
  {
	//check to see if there is any data 
	if(!isEmpty())
	  {
		//call helper to move throughout the tree recursively
		clearHelper(root);
		
	   //set root to null
	   root = NULL; 
	  }  
  }
  
/**
 * clearHelper function
 * 
 * This function checks for the children of each node, deletes them, then deletes the 
 * current node. This is done through a recursive call. The base case for this function
 * is if the ptr is equivalent to null.
 * 
 * @param ptr - a pointer with the address of the current node
 * 
 * @return none
 * 
 * @pre there may or may not be data in the current BST
 * @post there will not be any data in the current BST and all pointers will be set to NULL
 */
template<typename DataType, typename KeyType>
void BSTree<DataType, KeyType>::clearHelper(BSTreeNode*& ptr)
  {
	//check to see if current pointer is null
	if(ptr == NULL)
	 {
	   //check left of node
	   clearHelper(ptr->left);
	   //check right of node
	   clearHelper(ptr->right);
	   //delete current node
	   delete ptr;
	   ptr = NULL; 
	 }
  }
  
/**
 * isEmpty function
 * 
 * This function checks to see if there is any memory currently allocated in the BST
 * 
 * @param none
 * 
 * @return bool - if the root is not null it will return true. It will return false otherwise.
 * 
 * @pre it will not be know whether or not there is data
 * @post a boolean will be returned which determines whether or not there is data
 */
template<typename DataType, typename KeyType>
bool BSTree<DataType, KeyType>:: isEmpty () const
  {
	//return whether or not the root is NULL 
	return (root == NULL);   
  }

/**
 * getCount function
 * 
 * Counts the total number of nodes in the current tree.
 * This is done by checking to see if the current tree is empty. If it is not
 * empty, it will return the countHelper, which recursively counts the number of 
 * nodes.
 * 
 * @param none
 * 
 * @return int - returns 0 if empty. Else, it will return the total number 
 *               of nodes in current BST.
 * 
 * @pre the total number of nodes will not be found
 * @post the total number of nodes will be found 
 */
  
template<typename DataType, typename KeyType>
int BSTree<DataType, KeyType>:: getCount()const
  {
	//check to see if BST is empty
	if(!isEmpty())
	  {
		//call the countHelper to get the total number of nodes
		return (countHelper(root));
	  }  
	//return zero if empty
	return 0; 
  }
 
/**
 * countHelper function
 * 
 * This function counts the total number of nodes with a recursive call.
 * It stops calling itself if leaf is found, or the current node is null.
 * 
 * @param ptr - current node in BST
 * @param total - the number of nodes in BST
 * 
 * @return int - returns the number of nodes found
 * 
 * @pre the number of nodes will be set to zero
 * @post the total number of nodes found will be updated
 */
template<typename DataType, typename KeyType>
int BSTree<DataType, KeyType>:: countHelper(BSTreeNode* ptr)const 
  {
	//base case if null
	if(ptr == NULL)
	  {
		return 0;   
	  }  
	
	//base case, at leaf
	if(ptr ->left == NULL && ptr->right == NULL)
	  {
		//counts current node
		return 1;   
	  }
	//recursive call that counts all the nodes in the BST  
	return (1+(countHelper(ptr->left)+(countHelper(ptr->right)))); 
  }

/**
 * getHeight function
 * 
 * This function counts the height of the current BST. First this function
 * checks to see if its empty. If not empty, calls returns heightHelper. Else,
 * it returns 0.
 * 
 * @param none
 * 
 * @return int - the height of the current tree
 * 
 * @pre the height of the tree will not be output
 * @post the height of the tree will be output
 */


template<typename DataType, typename KeyType> 
int BSTree<DataType, KeyType>::getHeight () const 
  {	
	//check if current tree is empty
	if(!isEmpty())
	  {
		//call the height helper and return the value it finds
		return (heightHelper(root));  
	  }  
	//return zero because there aren't any nodes in the current BST
	return 0; 
  }
  
/**
 * heightHelper function
 * 
 * this function recursively moves throughout the current tree. The base case
 * is if the current pointer is null or has no children. Otherwise, the 
 * recursive call changes depending upon the number of children the node has.
 * 
 * @param ptr - current node
 * 
 * @return int - number of nodes involved in height
 * 
 * @pre there is an unknow number of nodes for the greatest height of the tree
 * @post the height of the tree will be known
 */
template<typename DataType, typename KeyType> 
int BSTree<DataType, KeyType>::heightHelper(BSTreeNode* ptr) const
  {
	//check to see if ptr is NULL  
	if(ptr == NULL)
	  {
		return 0;   
	  }  
	  
	//ptr has no children
	if(ptr->left == NULL && ptr->right == NULL)
	  {
		//return one for current node
		return 1;   
	  }
	  
	//ptr has only one child
	if(ptr->left != NULL && ptr->right == NULL)
	  {
		//return one plus the remainder of the nodes to the left of the current pointer
		return(1+heightHelper(ptr->left)); 
	  }
	//ptr has only right child
	if(ptr->right != NULL && ptr->left == NULL )
	  {
		//returns one plus the remainder of the nodes to the right of the current pointer
	    return(1+heightHelper(ptr->right));   
	  }
	  
   //ptr has two children
   if(ptr->right != NULL && ptr->left != NULL)
     {
	   //initialization
	   int lhs = 0, rhs = 0; 
	   //get the left hand side count
	   lhs = heightHelper(ptr->left);
	   //get the right hand side count
	   rhs = heightHelper(ptr->right);
	   //compare the both sides
	   if(lhs > rhs)
	     {
		   //lhs was greater, so return 1 plus the lefthandside
		   return (1+lhs);	 
	     }
	   //righthandside was greater, so returnn 1 plus the righthandside
	   return (1+rhs); 
	 }
	  
	return 0; 
  }

/**
 * writeLessThan function
 * 
 * this function outputs all of the values in the current tree with the a key
 * less than the specified searchKey. This functions check to see if current tree is 
 * empty, and class the lessHelper to aide in outputting the lesser values.
 * 
 * @param searchKey- the key that must be compared to each node's key
 * 
 * @return none
 * 
 * @pre may or may not be values in BST less than searchKey
 * @post all values that are less than searchKey are output
 */
template<typename DataType, typename KeyType> 
void BSTree<DataType, KeyType>::writeLessThan ( const KeyType& searchKey ) const
  {
	//check to see if current tree is empty
	if(!isEmpty())
	  {
		//call lessHelper to output the values less than searchKey
		lessHelper(root, searchKey);   
	  }  
  }
  
/**
 * lessHelper function
 * 
 * This function outputs the keys with a smaller value than the searchKey specified.
 * If the current pointer is not null, a comparison between the current node's key and
 * the given search tree occurs. If current key is less than searchKey, the write helper
 * is called to output the current node and all lesser nodes. Otherwise, a recursive call 
 * is used to check the nodes to the left of the current node.
 * 
 * @param ptr - current node that is needed for comparison
 * @param searchKey - the specified key used to compare
 * 
 * @return none
 * 
 * @pre lesser keys, if any, will not be output
 * @post lesser keys found in current BST will be output
 */
template<typename DataType, typename KeyType>
void BSTree<DataType, KeyType>::lessHelper(BSTreeNode* ptr, const KeyType& searchKey)const
  {
	//check to see if current pointer is null
	if(ptr != NULL)
	  {
		//current key is less than searchKey
		if((ptr->dataItem).getKey() < searchKey)
          {
			//output all lesser values
			 writeHelper(ptr); 
		  }
		//current key is greater than searchKey
		else
		  {
			//check to the left of current node
			lessHelper(ptr->left, searchKey);   
		  }
      }
  }

//--------------------------------------------------------------------
//
//  Laboratory 9                                         show9.cpp
//
//  Linked implementation of the showStructure operation for the
//  Binary Search Tree ADT
//
//--------------------------------------------------------------------

//--------------------------------------------------------------------

template < typename DataType, typename KeyType >
void BSTree<DataType,KeyType>:: showStructure () const

// Outputs the keys in a binary search tree. The tree is output
// rotated counterclockwise 90 degrees from its conventional
// orientation using a "reverse" inorder traversal. This operation is
// intended for testing and debugging purposes only.

{
    if ( root == 0 )
       cout << "Empty tree" << endl;
    else
    {
       cout << endl;
       showHelper(root,1);
       cout << endl;
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template < typename DataType, typename KeyType >
void BSTree<DataType,KeyType>:: showHelper ( BSTreeNode *p,
                               int level             ) const

// Recursive helper for showStructure. 
// Outputs the subtree whose root node is pointed to by p. 
// Parameter level is the level of this node within the tree.

{
     int j;   // Loop counter

     if ( p != 0 )
     {
        showHelper(p->right,level+1);         // Output right subtree
        for ( j = 0 ; j < level ; j++ )    // Tab over to level
            cout << "\t";
        cout << " " << p->dataItem.getKey();   // Output key
        if ( ( p->left != 0 ) &&           // Output "connector"
             ( p->right != 0 ) )
           cout << "<";
        else if ( p->right != 0 )
           cout << "/";
        else if ( p->left != 0 )
           cout << "\\";
        cout << endl;
        showHelper(p->left,level+1);          // Output left subtree
    }
}



