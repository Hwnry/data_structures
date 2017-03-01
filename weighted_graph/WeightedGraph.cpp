/**
 * @file WeightedGraph.cpp
 * @author Henry Huffman
 * @version 1.1
 * @brief This program builds a graph. This graph uses an adjacency matrix to keep track of the vertices and weights 
 *         of the graph.  
 * @details More specifically, this program has the following basic member functions: constructor, copy constructor,
 *          overloaded = operator, and destructor. This program also contains areAllEven, clear, getEdge, getEdgeWeight,
 *          getIndex, hasProperColoring, insertEdge, insertVertex, isEmpty, isFull, removeEdge, removeVertex, retrieveVertex,
 *          setEdge, showShortestPath, and showStructure fuctions.
 * 
 * @date Monday, November 18th, 2014
 */
 
#include "WeightedGraph.h"

//Function Implementations

/**
 * WeightedGraph Constructor
 * 
 * This constructor creates an array of vertices for the list of vertices. It also creates arrays
 * for the adjacency matrix and path matrix. The values in the path matrix and adjacency matrix are
 * set to the infinite edge weight. It also sets the maxSize and size of the WeightedGraph.
 * 
 * @param maxNumber - an integer that sets the maxSize of the number of dataItems in the array
 * 
 * @return none
 * 
 * @pre  there will not be an initialized WeightedGraph
 * @post  there will be an initialized Weighted with the maxSize and size set
 */
WeightedGraph::WeightedGraph(int maxNumber)
  {
	//set the maxSize
	maxSize = maxNumber;
	//set the size
	size = 0; 
	//allocate enough vertices for the max
	vertexList = new Vertex [maxSize]; 
	//allocate enough memory for adjacency matrix
	adjMatrix = new int [(maxSize * maxSize)];
	//path matrix for shortest path
	pathMatrix = new int [(maxSize*maxSize)];
	//loop through and set everything to infinity
	for(int i = 0; i < (maxSize * maxSize); i++)
	  {
		//set to infinity
		adjMatrix[i] = INFINITE_EDGE_WT;   
	  }
	//loop through and set everything to infinty
	for(int i = 0; i < (maxSize * maxSize); i++)
	  {
		//set to infinity
		pathMatrix[i] = INFINITE_EDGE_WT;   
	  }
  }
  
/**
 * Weighted Graph Copy Constructor
 * 
 * This copy constructor creates an array of new dataItems, sets the maxSize, and current size
 * according to another specified weighted graph.
 * 
 * @param other - the specified weighted graph that is to be copied
 * 
 * @return none
 * 
 * @pre  there will be one initialized weighted graph
 * @post  there will be two initialized weighted graphs with identical values.
 */
WeightedGraph::WeightedGraph(const WeightedGraph& other)
  {
	//set maxSize
	maxSize = other.maxSize;
	//set size 
	size = other.size;
	//allocate memory for vertexList 
	vertexList = new Vertex [maxSize];
	//allocate memory for adjMatrix
	adjMatrix = new int [(maxSize*maxSize)];
	pathMatrix = new int [(maxSize*maxSize)]; 
	//copy data from other WeightedGraph's vertexList
	for(int i = 0; i < size; i++)
	  {
		//copy object
		vertexList[i] = other.vertexList[i];
	  }
    //copy data from other WeightedGraph's adjMatrix
    for(int i = 0; i < (maxSize*maxSize);i++)
      {
		//copy data according to maxSize
	    adjMatrix[i] = other.adjMatrix[i]; 
	  }
	//copy data from other WeightedGraph's pathMatrix
    for(int i = 0; i < (maxSize*maxSize);i++)
      {
		//copy data according to maxSize
	    pathMatrix[i] = other.pathMatrix[i]; 
	  }
  }

/**
 * overloaded operator=
 * 
 * This copy constructor creates an array of new dataItems, sets the maxSize, and current size
 * according to another specified weighted graph.
 * 
 * @param other - the specified weighted graph that is to be copied
 * 
 * @return WeightedGraph - the graph with updated values
 * 
 * @pre  there will be one initialized weighted graph
 * @post  there will be two initialized weighted graphs with identical values.
 */
WeightedGraph& WeightedGraph::operator=(const WeightedGraph& other)
  {
	//check to see if the same graph is being assigned
	if(this == &other)
	  {
		//return the current graph
		return (*this);   
	  }
	//clear the current graph
	clear();
	//check to see if the maxSizes are equivalent
	if(maxSize != other.maxSize)
	  {
		//reset maxSize
		maxSize = other.maxSize;
		//delete old array
		delete [] vertexList;
		//reallocate memory to match maxSize
		vertexList = new Vertex[maxSize];
		//delete old array
		delete [] adjMatrix;
		//reallocate memory to match maxSize
		adjMatrix = new int [(maxSize * maxSize)]; 
		delete [] pathMatrix;
		pathMatrix = new int [(maxSize * maxSize)]; 
	  }
	//reset size
	size = other.size;
    //copy data from other WeightedGraph's vertexList
	for(int i = 0; i < size; i++)
	  {
		//copy object
		vertexList[i] = other.vertexList[i];
	  }
    //copy data from other WeightedGraph's adjMatrix
    for(int i = 0; i < (maxSize*maxSize);i++)
      {
		//copy data according to maxSize
	    adjMatrix[i] = other.adjMatrix[i]; 
	  }
   //copy data from other Weighted'graph's pathMatrix
    for(int i = 0; i < (maxSize*maxSize);i++)
      {
		//copy data according to maxSize
	    pathMatrix[i] = other.pathMatrix[i]; 
	  }
	//return updated graph
	return (*this);   
  }
  
/**
 * Weighted Graph Destructor
 * 
 * This function deallocates all memory in the current weighted graph and
 * sets everything to NULL or zero.
 * 
 * @param none
 * 
 * @return none
 * 
 * @pre  the weighted graph will have memory allocated to it
 * @post  the weighted graph will not have any memory allocated to it
 */

WeightedGraph::~WeightedGraph()
  {
	//delete memory for vertexList
	delete [] vertexList;
	//set pointer to NULL
	vertexList = NULL;
	//delete memory for adjMatrix
	delete [] adjMatrix;
    //delete memory of pathMatrix
	delete [] pathMatrix; 
	//set pathMatrix to NULL
	pathMatrix = NULL; 
	//set adjMatrix to NULL
	adjMatrix = NULL; 
	//set size to 0
	size = 0;
	//set maxSize to 0
	maxSize = 0;   
  }

/**
 * insertVertex Function
 * 
 * This function inserts a new vertex into the vertex list. In doing so,
 * it also updates the adjacency matrix and path matrix. 
 * 
 * @param newVertex - the vertex that is to be inserted into the vertex list,
 *                    adjacency matrix, and path matrix. 
 * 
 * @return none
 * 
 * @pre  the graph may or may not include the newVertex
 * @post  the graph will include the new vertex, or update the specified vertex's weight
 */
void WeightedGraph::insertVertex(const Vertex& newVertex)throw ( logic_error )
  {
	//check to see if full
	if(isFull())
	  {
		//throw logic error
		throw logic_error ("Graph is full");   
	  }
	//create a temp for checking
	Vertex temp; 
	//check if vertex is already in graph
	if(retrieveVertex(newVertex.getLabel(), temp))
	  {
		//move to the correct location
		for(int i = 0; i<size; i++)
		  {
			//update vetex info
			if(newVertex.getLabel() == vertexList[i].getLabel())
			  {
				//update info
				vertexList[i] = newVertex;   
			  }  
		  }  
	  }
	
	else
	 {
		//put new vertex into vertex list
		vertexList[size]= newVertex;
		//increment the size
		size++;
		//update adjacency matrice
		for(int i = 0; i < maxSize; i++)
		  {
			//set all possible edges to infinity
			adjMatrix[((size-1)*maxSize)+i] = INFINITE_EDGE_WT ;  
		  }
     } 
	  
  }

/**
 * insertEdge function
 * 
 * This function inserts the edge into the adjacency matrix. It first checks to see
 * if both verices are in the vertex list. If so, it will update the will update
 * the weight. 
 * 
 * @param v1 - the label of the first vertex
 * @param v2 - the label of the second vertex
 * @param wt - an integer that specifies the weight 
 * 
 * @return none
 * 
 * @pre  the graph may not have the specified weight between the two vertices
 * @post the specified weight will be placed into the correct location of the 
 *       adjacency matrix. 
 */

void WeightedGraph::insertEdge ( const string& v1, const string& v2, int wt )throw ( logic_error )
  {
	//inintialization
	Vertex temp;
    //check to see if both vertex's are in the graph
	if(!(retrieveVertex(v1,temp)) || !(retrieveVertex(v2,temp)))
	  {
		//throw error
		throw logic_error ("Vertex not found") ; 
	  }
    //assuming the data given is good
    //get index fo both vertices
    int one = getIndex(v1);
    int two = getIndex(v2);
    //set the edge waits at both locations
    setEdge(one, two, wt); 
    setEdge(two, one, wt); 	
    //output data
    cout << "Size = " << size << ", idx_v1 = " << one << ", idx_v2 = " << two << endl; 
  }
  
/**
 * getEdge function
 * 
 * This function simply returns the the weight at the specified location.
 * 
 * @param row - the row location in the adjacency matrix
 * @param col - the column location in the adjacency matrix
 * 
 * @return int - the weight at the specified location in the adjacency matrix
 * 
 * @pre  the edge at the location may or may not be known
 * @post  the edge at the location will be known
 */
int WeightedGraph::getEdge ( int row, int col ) const
 {
   //check to see if empty
   if(!isEmpty())
     {
	  //return the edge at location
	  return (adjMatrix[(row*maxSize)+col]);	 
     }	 
   //otherwise, default to false
   return false; 
 }
 
/**
 * setEdge function
 * 
 * This function sets the edge weight at a specified location in the adjacency matrix
 * 
 * @param row - the row location in the adjacency matrix
 * @param col - the column location in the adjacency matrix
 * @param wt - the weight that is to be inserted
 * 
 * @return none
 * 
 * @pre  the edge may not contain the weight specified
 * @post  the edge will contain the weight specified
 */
  
void WeightedGraph::setEdge ( int row, int col, int wt)
  {
	//check to see if the weighted graph is emtpy
	if(!isEmpty())
	  {
		//set the weight at the specified location
		adjMatrix[(row*maxSize)+col] = wt;   
	  }
  }
  
/**
 * getIndex function
 * 
 * This function gets the index of the specified vertex.
 * 
 * @param v - the label of a vertex
 * 
 * @return int - the index of the vertex in the vertexList
 * 
 * @pre  the location may or may not be know
 * @post the location of the vertex will be known
 */
int WeightedGraph::getIndex( const string& v ) const
  {
	//loop through the vertex list
	for(int i = 0; i < size; i++)
	  {
		//check to see if the vertex matches the label
		if(vertexList[i].getLabel() == v)
		  {
			//return the index
			return i;   
		  }  
	  }
   //return -1 if not found
   return -1;   
  } 
  
 /**
 * retrieveVertex function
 * 
 * This function searches for a vertex that matches the given label. If the
 * vertex is found, the parameter vData is assigned the vertex and returns true.
 * If the vertex is not found, it will return false.
 * 
 * @param v - the label used to search for the matching vertex
 * @param vData - used to pass the data of the located vertex back by reference
 * 
 * @return bool - returns true if vertex is found, else it returns false
 * 
 * @pre  the vertex may or may not be in the vertex list
 * @post  the vertex may or may not be found. If found, the data of the vertex
 *        will be passed back by reference through the parameter vData.
 */
bool WeightedGraph::retrieveVertex(const string& v, Vertex& vData)const
  {
	//loop through array
	for(int i = 0; i < size; i++)
	  {
		//check to see if vertex matches
		if(vertexList[i].getLabel() == v)
		  {
			//if found, set and return
			vData = vertexList[i]; 
			return true;  
	      }  
	  }
   //otherwise, return false
   return false; 
  }

 /**
 * getEdgeWeight function
 * 
 * This function searches for two vertices. If the vertices are located, the weight
 * of the edge between the two vertices is passed back by reference through the parameter
 * wt. If the weight at the specified location is not infinite, the function returns true.
 * Otherwise, the function will return false if the weight is infinite or the vertices 
 * are not found
 * 
 * @param v1 - the label of one of the vertices that this function searches for
 * @param v2 - the label of one of the vertices that this fucntion searches for
 * @param wt - the edge weight found between the two vertices.
 * 
 * @return bool - returns true if vertices are found and the edge weight is
 *                not set to infinity. Othwerwise, returns false.
 * 
 * @pre  there may or may not be a valied edge weight between the two specified vertices
 * @post  the edge weight will be found between the vertices. If valid, the function will return
 *        true. It will return false in all other cases. 
 */

bool WeightedGraph::getEdgeWeight(const string& v1, const string& v2, int& wt) const throw (logic_error)
  {
	//initialization
	Vertex temp; 
	//check to see if both vertices are in the verticeList
	if(!(retrieveVertex(v1,temp)) || !(retrieveVertex(v2,temp)))
	  {
		//throw error
		throw logic_error ("Vertex not found") ; 
	  }
	//assuming the vertices are in the verticeList,
	//get the index of both
	int one = getIndex(v1);
	int two = getIndex(v2);
	//get the edge
	wt = getEdge(one, two);
	//check if edge is infinite
	if(wt == INFINITE_EDGE_WT)
	  {
		//return false
		return false;   
	  }  
	//return true
	return true; 
  }

void WeightedGraph::removeVertex(const string& v) throw (logic_error)
  {
	Vertex temp;
	if(!(retrieveVertex(v, temp)))
	  {
		throw logic_error ("Vertex not found");  
	  }
	
    int vertLocation = getIndex(v);   
	//remove from list
	for(int i = vertLocation; i<size; i++)
	  {
		vertexList[i]=vertexList[(i+1)];   
	  }
	//remove from matrix
	for(int i = vertLocation; i< size; i++)
	  {
		for(int j = 0; j < maxSize; j++)
		  {
			adjMatrix[(i*maxSize)+j] = adjMatrix[((i+1)*maxSize)+j];   
		  }  
	  }
	  
	for(int i = 0; i< size; i++)
	  {
		for(int j = vertLocation; j < maxSize; j++)
		  {
			adjMatrix[(i*maxSize)+j] = adjMatrix[(i*maxSize)+(j+1)];   
		  }  
	  }
   size--; 
  }

void WeightedGraph::removeEdge(const string& v1, const string& v2) throw(logic_error)
  {
	Vertex temp; 
	if(!(retrieveVertex(v1,temp)) || !(retrieveVertex(v2,temp)))
	 {
	   throw logic_error ("Vertex not found");	 
     }
 
    //assuming the data given is good
    //get index fo both vertices
    int one = getIndex(v1);
    int two = getIndex(v2);
    //set the edge waits at both locations
    setEdge(one, two,INFINITE_EDGE_WT ); 
    setEdge(two, one,INFINITE_EDGE_WT ); 	
     
   
  }

 /**
 * clear function
 * 
 * This function sets the size equivalent to zero and sets the adjacency 
 * matrix at every location to infinite
 * 
 * @param none
 * 
 * @return none
 * 
 * @pre  the size may or may not be set to zero, and the adjacency 
 *       matrix may have varying edge weights.
 * @post the size will be zero and only infinite edge weights will be 
 *       found in the adjacency matrix
 */
void WeightedGraph::clear()
  {
	//set size to zero
	size = 0;
	//loop through adjacency matrix
	for(int i = 0; i < (maxSize*maxSize); i++)
	  {
		//set each location to infinite
		adjMatrix[i] = INFINITE_EDGE_WT;   
	  }
	  
  }

 /**
 * isEmpty function
 * 
 * This function checks to see if current weighted graph is empty.
 * 
 * @param none
 * 
 * @return bool - returns whether or not the size is set to zero
 * 
 * @pre  the weighted graph may or may not be empty
 * @post a bool that determines whether or not the weighted graph is
 *       empty is returned
 */

bool WeightedGraph::isEmpty()const
  {
	//check to see if the size is set to zero
	return (size == 0); 
  }
  
 
 /**
 * isFull function
 * 
 * This function checks to see if current weighted graph is full.
 * 
 * @param none
 * 
 * @return bool - returns whether or not the size is equal to the maxSize
 * 
 * @pre  the weighted graph may or may not be full
 * @post a bool that determines whether or not the weighted graph is
 *       full is returned
 */
  
bool WeightedGraph::isFull()const
  {
	//check to see if the size is equal to the maxSize
	return (size == maxSize);    
  }
//--------------------------------------------------------------------
//
//  Laboratory 12                                         show12.cpp
//
//  Adjacency matrix implementations of the showStructure operation
//  for the Weighted Graph ADT
//
//--------------------------------------------------------------------

#include "WeightedGraph.h"

void WeightedGraph:: showStructure () const

// Outputs a graph's vertex list and adjacency matrix. This operation
// is intended for testing/debugging purposes only.

{
    if ( size == 0 ) {
       cout << "Empty graph" << endl;
    } else {
       cout << endl << "Vertex list : " << endl;
       for ( int row = 0 ; row < size ; row++ )
           cout << row << '\t' << vertexList[row].getLabel()
           << '\t'

		<< vertexList[row].getColor()
		<< endl;

       cout << endl << "Edge matrix : " << endl << '\t';
       for ( int col = 0 ; col < size ; col++ )
           cout << col << '\t';
       cout << endl;
       for ( int row = 0 ; row < size ; row++ )
       {
           cout << row << '\t';
           for ( int col = 0 ; col < size ; col++ )
           {
               int wt = getEdge(row,col);
               if ( wt == INFINITE_EDGE_WT )
                  cout << "- \t";
               else
                  cout << wt << '\t';
           }
           cout << endl;
       }
    }
}



 /**
 * hasProperColoroing function
 * 
 * This function checks to see if there are any vertices adjacent to one another
 * that have the same color.
 * 
 * @param none
 * 
 * @return bool - returns whether or not the colors are proper
 * 
 * @pre  the coloring may or may not be proper
 * @post a bool that determines whether or not the weighted graph has
 *       proper coloring will be returned
 */
bool WeightedGraph::hasProperColoring() const
  {
	//loop through the adjacency matrix
	for(int i = 0; i < size; i++)
	  {
		//loop through adjaceny matrix at the index one ahead of current
		for(int j = (i+1); j <size; j++)
		  {
			//check to see if any of the adjacent vertices have the same color
			if(vertexList[i].getColor() == vertexList[j].getColor())
			  {
				//return false
				return false;   
			  }  
		  }  
	  }
	//return true
	return true; 
  }
  

 /**
 * areAllEven function
 * 
 * This function checks to see if all of the vertices have an even number
 * of edges
 * 
 * @param none
 * 
 * @return bool - returns whether or not all are even
 * 
 * @pre  the weighted graph may or may not haven even number of edges
 * @post a bool that determines whether or not the weighted graph has
 *       an even number of edges is returned
 */
bool WeightedGraph::areAllEven () const
  {
	//intialization
	int count = 0;
	//loop through adjacency matrix
	for(int i = 0; i < size; i++)
	  {
            //loop through adjacency matrix
			for(int j = 0; j < size; j++)
			  {
				//check to see if the number of edges are greater than
				//zero and less than int_max
				if(getEdge(i,j) > 0 && getEdge(i,j) < INT_MAX)
				  {
					//increment count
					count++;   
				  }  
			   }  
	    //check to see if the count is even
		if(count % 2 == 1)
		  {
			//return false
			return false;   
		  }
		else
		  {
			//reset count to zeron
			count = 0;   
		  }
	  } 
	//return true  
	return true; 
  }


 /**
 * showShortestPath function
 * 
 * This function finds the shortest path between two vertices. The path
 * matrice is used to find said path.
 * 
 * @param none
 * 
 * @return none
 * 
 * @pre  the shortest path between two vertices may or may not be known
 * @post the shortest path will be found and output
 */

void WeightedGraph::showShortestPaths () const
{
  //loop through the adjacency matrix and path matrix and set them equal	
  for( int p = 0; p < ( maxSize * maxSize ); p++ )
    {
      //set the path equal to the adjacency
	  pathMatrix[ p ] = adjMatrix[ p ];
    }
  //loop through the path matrix and set specified coulmn to zeron
  for( int i = 0; i < size; i++ )
    {
      //set current index to zeron
	  pathMatrix[ ( i * maxSize ) + i ] = 0;
	}
//loop through the path matrix up to the size	
for( int m = 0; m < size; ++m )
{ 
    //loop through the path matrix up to the size
	for( int j = 0; j < size; ++j )
	{
	   //loop to sepcific index
		for( int k = 0; k < size; ++k )
		{
			// check if there is a path between j and k through m
			if( ( pathMatrix[ ( j * maxSize ) + m ]  > 0 && 
					pathMatrix[ ( j * maxSize ) + m ] < INT_MAX ) && 
					( pathMatrix[ ( m * maxSize ) + k ] > 0 && 
						pathMatrix[ ( m * maxSize ) + k ] < INT_MAX )
						&& ( j != k && j != m && m != k ) )
			{
				// check to see if path is shorter than direct path
				if( ( pathMatrix[ ( j * maxSize ) + m ] + pathMatrix[ ( m * maxSize ) + k ] )
						< pathMatrix[ ( j * maxSize ) + k ] ) 
				{
					pathMatrix[ ( j * maxSize ) + k ] = 
						( pathMatrix[ ( j * maxSize ) + m ] +
						pathMatrix[ ( m * maxSize ) + k ] );
				}
			}
		}
	}
}

//output the data found
if ( size != 0 ) 
	{
       cout << endl << "Path matrix : " << endl << '\t';
       
       for ( int col = 0 ; col < size ; col++ )
           cout << col << '\t'; 
       cout << endl;    
       for ( int row = 0 ; row < size ; row++ )
       {
           cout << row << '\t';
           for ( int col = 0 ; col < size ; col++ )
           {
			   int wt = pathMatrix[ ( ( row * maxSize ) + col ) ];
               if ( wt == INFINITE_EDGE_WT )
                  cout << "- \t";
               else
                  cout << wt << '\t';
           }
           cout << endl;
       }
    }
    else
		cout << endl << "Path matrix : " << endl << endl;
		
}
