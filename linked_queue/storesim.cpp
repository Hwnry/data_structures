//--------------------------------------------------------------------
//
//  Laboratory 7, Programming Exercise 1                   storesim.cs
//
//  Program implementation shell.
//
//--------------------------------------------------------------------

// Simulates the flow of customers through a line in a store.

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

// Use which ever implementation is currently configured.
#include"config.h"
#if LAB7_TEST1
#   include "QueueLinked.cpp"
#else
#   include "QueueArray.cpp"
#endif

using namespace std;

int main ()
{
#if LAB7_TEST1
    QueueLinked<int> custQ;      // Line (queue) of customers containing the
#else
    QueueArray<int> custQ;       // Line (queue) of customers containing the
#endif 				 //   time that each customer arrived and
                                 //   joined the line
    int simLength,               // Length of simulation (minutes)
        minute,                  // Current minute
        timeArrived,             // Time dequeued customer arrived
        waitTime,                // How long dequeued customer waited
        totalServed = 0,         // Total customers served
        totalWait   = 0,         // Total waiting time
        maxWait     = 0,         // Longest wait
        numArrivals = 0;         // Number of new arrivals

    // Seed the random number generator. Equally instructive to run the
    // simulation with the generator seeded and not seeded.
    srand(7);

    cout << endl << "Enter the length of time to run the simulator : ";
    cin >> simLength;

    // Put your code here to run this simulation. Use "rand()" to get
    // a pseudorandom number that you can use to calculate probabilities.
    
/**
 * @file storesim.cpp
 * @version 1.1
 * @brief This program will simulate random customers waiting in a line or queue and keep track of how long they wait.
 * @details the program will run for a specified amount of time, all the while, randomly generated customers will wait in line
 *          until they are dequeued. 
 * @date Tuesday, September 08, 2014
 */
 
 ///starting a minute zero the program will loop through until it has reached the predetermined simLength
    minute = 0; 
    int k; 
    while(minute != simLength)
      {
		///check to see if queue is empty
	    if(!custQ.isEmpty())
	      {
			///if not empty, dequeue customer and record data
			timeArrived = custQ.dequeue(); 
			waitTime = minute - timeArrived; 
			totalWait += waitTime; 
			totalServed++;
			if(waitTime > maxWait)
			  {
				maxWait = waitTime;   
			  }     
		  }
		///generate a random number using mod 4 to get appropriate number
		k = rand() % 4; 
		///if the number is one add one person to the queue and increment numArrivals
		if(k == 1)
		  {
			custQ.enqueue(minute); 
			numArrivals++;   
		  }
		///if the number is two add two people to the queue and add two to numArrivals
		if(k == 2)
		  {
			custQ.enqueue(minute);
			custQ.enqueue(minute); 
			numArrivals += 2;   
		  }		
		  
	   ///update the while loop by incrementing the minute variable 
		minute++; 
	  }
	


    // Print out simulation results
    cout << endl;
    cout << "Customers served : " << totalServed << endl;
    cout << "Average wait     : " << setprecision(2)
         << double(totalWait)/totalServed << endl;
    cout << "Longest wait     : " << maxWait << endl;

    return 0;
}

