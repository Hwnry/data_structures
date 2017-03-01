/**
 * @file ossim.cpp
 * @author Henry Huffman
 * @version 1.1
 * @brief This program uses a priority queue to simulate a line. 
 * @details Moreover, this program will generate random numbers for a specified amount of times.
 *          Then it will dequeue one data item per minute and enqueue randomly generated values.
 *          The value of the dequeued dataItem will be output. 
 * 
 * @date Tuesday, October 28th, 2014
 */

//--------------------------------------------------------------------
//
//  Laboratory 11, Programming Exercise 1                     ossim.cs
//
//  (Shell) Operating system task scheduling simulation
//
//--------------------------------------------------------------------

// Simulates an operating system's use of a priority queue to regulate
// access to a system resource (printer, disk, etc.).

#include <iostream>
#include <cstdlib>
#include "PriorityQueue.cpp"

using namespace std;

//--------------------------------------------------------------------
//
// Declaration for the task data struct
//

struct TaskData
{
    int getPriority () const
        { return priority; }     // Returns the priority. Needed by the heap.

    int priority,                // Task's priority
        arrived;                 // Time when task was enqueued

};


//--------------------------------------------------------------------

int main ()
{
    PriorityQueue<TaskData, int, Less<int> > taskPQ;   // Priority queue of tasks
    TaskData task;               // Task
    int simLength,               // Length of simulation (minutes)
        minute,                  // Current minute
        numPtyLevels,            // Number of priority levels
        numArrivals,             // Number of new tasks arriving
        j;                       // Loop counter

    // Seed the random number generator
    srand( 7 );

    cout << endl << "Enter the number of priority levels : ";
    cin >> numPtyLevels;

    cout << "Enter the length of time to run the simulator : ";
    cin >> simLength;

    for ( minute = 0 ; minute < simLength ; minute++ )
    {
       //set counter to the minute
		j = minute;
        // Dequeue the first task in the queue (if any).
	// Your code here
   //check to see if the taskPQ is empty
		if( !taskPQ.isEmpty() )
		 {
		  //deque the highest priority data item and catch it
		  task = taskPQ.dequeue();
		  //output the data about the item that was just dequeued
		  cout << "At " << j << " dequeued: " << task.priority << " " << task.arrived << " " << ( minute - task.arrived ) << endl;
		 }

        // Determine the number of new tasks and add them to
        // the queue.
	// Your code here
	    // get a random number and mod it by four to get the appropriate number
		numArrivals = rand() % 4;
		//check for one arrival
		if( numArrivals == 1 )
	   	 {
	      //place data of current data item into a task struct
	      // place priority
		   task.priority = rand() % numPtyLevels;
		   //place arrival time
		   task.arrived = minute;
		   //place the updated task item into queue
		   taskPQ.enqueue( task );
		 }
		//check for two arrivals
		if( numArrivals == 2 )
	   	 {
	      //get the priority level
		  task.priority = rand() % numPtyLevels;
		  //place the time arrived in
	      task.arrived = minute;
	      //place new task into queue
		  taskPQ.enqueue( task );
		  //get the priority of the second item	
		  task.priority = rand() % numPtyLevels;
		  //place the time of the current arrival time
		  task.arrived = minute;
		  //place new task into the queue
		  taskPQ.enqueue( task );
		}
    }

    return 0;
}

