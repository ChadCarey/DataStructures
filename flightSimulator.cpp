/***********************************************************************
 * Program:
 *    Assignment 04, Airport Simulator
 *    Teacher: Brother Ercanbrack, CS 235
 * Author:
 *    Chad Carey, random number generator by Proffesor Ercanbrack
 *
 * Summary:
 *    This is an airport simulation program
 *    when ran we will be prompted for the number of times 
 *    we want the fimulation to run and the number of arivals and takeoffs 
 *    per unit of time.
 *	  The program will then print the numbers of plans landed, takenoff
 *    or refused durring the simulation
 * Time:
 *       Estimasted: 3.0 hours
 *       Actual:     3.0 hours
 ***********************************************************************/

#include <math.h>
#include <cstdlib>
#include <time.h>
#include <iostream>
#include <iomanip>
using namespace std;


/*****************************************************************
 * Queue Header File
 *****************************************************************/
#ifndef _QUEUE_H
#define _QUEUE_H

template<class T>
class Queue
{
private:
   int front;                  // --- index of front of queue
   int back;                   // --- index of back of queue
   int maxSize;                // --- max storage capacity of array
   int numItems;               // --- number of items currently in queue
   T *queueItems;            // --- array containing queue items

public:
   Queue();           // --- constructor
   Queue(int size);           // --- constructor
   Queue(const Queue &aQueue); //  copy constructor
   ~Queue(void);               // --- destructor
   void insert(T item);      // --- insert item into back of queue
   int getNumItems();        // returns number of items in queue

   T remove(void);           // --- remove item from front of queue
   int empty(void);            // --- returns 1 if queue is empty, 0 otherwise
   int full(void);             // --- returns 1 if queue is full, 0 otherwise
   Queue& operator = (const Queue &rtSide); // overloaded assignment operator
};

#endif



/***********************************************************************
 * Queue default constructor
 ***********************************************************************/
template<class T>
Queue<T>::Queue()
{
   maxSize = 100;
   numItems = 0;
   back = front = maxSize - 1;
   queueItems = new T[maxSize];

}

/**********************************************************************
 * Queue size constructor
 **********************************************************************/
template<class T>
Queue<T>::Queue(int size)
{
   maxSize = size > 0 ? size : 100;    // if s  is negative, set queue size to 100
   numItems = 0;
   back = front = maxSize - 1;
   queueItems = new T[maxSize];
}


/**********************************************************************
 * destructor
 **********************************************************************/
template<class T>
Queue<T>::~Queue(void)
{
   delete [] queueItems;
}

/***********************************************************************
 * Queue Copy Constructor
 ***********************************************************************/
template<class T>
Queue<T>::Queue(const Queue<T> &aQueue)
{
   maxSize = aQueue.maxSize;
   numItems = aQueue.numItems;
   front = aQueue.front;
   back = aQueue.back;
   queueItems = new T[maxSize];
   for (int i = 0; i < maxSize; i++)
   {
      queueItems[i] = aQueue.queueItems[i];
   }
}



/***********************************************************************
 * Overloaded assignment operator.
 ***********************************************************************/
template<class T>
Queue<T>& Queue<T>::operator =(const Queue<T> &rtSide)
{
   if (this != &rtSide)
   {

      if( maxSize != rtSide.maxSize)
      {
         delete [] queueItems;
         queueItems = new T[rtSide.maxSize];
      }

      for (int i = 0; i < rtSide.maxSize; i++)
      {
         queueItems[i] = rtSide.queueItems[i];
      }
      maxSize = rtSide.maxSize;   //max size of queue
      numItems = rtSide.numItems; //number of items in queue
      back = rtSide.back;
      front = rtSide.front;
   }
   return *this;
}




/**********************************************************************
 * Empty: returns true if queue is empty
 **********************************************************************/
template<class T>
int Queue<T>::empty(void)
{
   return (numItems == 0);
}

/**********************************************************************
 * Full: returns true if queue is full
 **********************************************************************/
template<class T>
int Queue<T>::full(void)
{
   return (numItems == maxSize);
}

/**********************************************************************
 * Instert: inserts item into back of queue, then increments number of items
 * in queue
 **********************************************************************/
template<class T>
void Queue<T>::insert(T item)
{
   // --- check for overflow
   if (full())
   {
      cout << "Queue overflow" << endl;
      exit(1);
   }
   queueItems[back] = item;
   back = (back + 1) % maxSize;
   numItems++;
}



/**********************************************************************
 * removes item from front of queue, then decrements number of items
 * in queue
 **********************************************************************/
template<class T>
T Queue<T>::remove(void)
{
   T temp;

   if (empty())
   {
      cout << "queue underflow" << endl;
      exit(1);
   }
   temp = queueItems[front];
   front = (front + 1) % maxSize;
   numItems--;
   return (temp);

}


/*****************************************************************
 * getNumItems
 * Returns the number of items in the queue
 ****************************************************************/
template<class T>
int Queue<T>::getNumItems()
{
   return numItems;
}


#ifndef RANDOM_H
#define RANDOM_H

/***************************************************************
 * Random
 * Author: Proffesor Ercanbrack
 * This class makes a random number
 **************************************************************/
class Random
{
   public:
      Random();

      /* --- Get next Poisson random --- */
      int poissonRandom(double expected);

};
#endif // RANDOM_H

/***************************************************************
 * RANDOM constructor
 * Author: Proffesor Ercanbrack
 **************************************************************/
Random::Random()
{
   // srand((int)time(NULL));   // variable seed for real simulation
   srand(2500);                 // fixed seed for debug and grading
}


/***************************************************************
 * poissionRandom
 * Author: Proffesor Ercanbrack
 * Return a random number based on arrival rates
 **************************************************************/
int Random::poissonRandom(double expected)
{
   int n = 0;
   double limit;
   double x;

   limit = exp(-expected);
   x = rand() / ((double)RAND_MAX + 1);
   while (x > limit)
   {
      n++;
      x *= rand() / ((double)RAND_MAX + 1);
   }
   return n;
}



#ifndef PLANE_H
#define PLANE_H
/***************************************************************
 * Class: Plane
 * This class controls plane information
 **************************************************************/
class Plane
{
public:
   Plane();
   Plane(const Plane & rhs);

   // getters
   int getWaitStopTime() { return waitStopTime; }
   int getWaitStartTime() { return waitStartTime; }
   int getWaitTime() { return waitStopTime - waitStartTime; }

   // setters
   void setWaitStopTime(int a) { if(a >= 0) waitStopTime = a; }
   void setWaitStartTime(int t) { if(t >= 0) waitStartTime = t; }

   // operators
   Plane& operator = (const Plane &rhs); // overloaded assignment operator


private:
   int waitStopTime;
   int waitStartTime;

};

#endif // PLANE_H


/**************************************************************************
 * Plane default constructor;
 *************************************************************************/
Plane::Plane()
{
   waitStopTime = 0;
   waitStartTime = 0;

}

/**************************************************************************
 * Plane Copy constructor;
 *************************************************************************/
Plane::Plane(const Plane & rhs)
{
   waitStopTime = rhs.waitStopTime;
   waitStartTime = rhs.waitStartTime;
}

/**************************************************************************
 * Plane = operator
 *************************************************************************/
Plane& Plane::operator =(const Plane & rhs)
{
   waitStopTime = rhs.waitStopTime;
   waitStartTime = rhs.waitStartTime;

   return *this;
}




#ifndef RUNWAY_H
#define RUNWAY_H
/***************************************************************
 * Class: Runway
 * This class is a single airport runway simulator
 **************************************************************/
class Runway
{
public:
   Runway();
   // getters
   int getNumLanded()
   { return planesLanded;};

   int getNumTakeoff()
   { return planesTakeoff; };

   int getNumRefused()
   { return planesRefused; };

   int getTotalPlanes()
   { return totalPlanes; };

   int getNumReadyToLand()
   { return landing->getNumItems(); }

   int getNumReadyToTakeoff()
   { return takeoff->getNumItems(); }

   float getIdlePercent()
   { return idlePercent; }
   
   float getAvgLandWaitTime()
   { return landWaitTime/planesLanded; }

   float getAvgTakeoffWaitTime()
   { return takeoffWaitTime/planesTakeoff; }


   //functions
   void runSim(int endTime, double arrivePerTime, double takeoffPerTime);


private:
   Queue <Plane> *takeoff;
   Queue <Plane> *landing;

   int totalPlanes;
   int planesLanded;
   int planesTakeoff;
   int planesRefused;
   float idlePercent;
   float landWaitTime;
   float takeoffWaitTime;

};

#endif // RUNWAY_H



/***************************************************************
 * Runway
 * Constructor
 **************************************************************/
Runway::Runway()
{
   if (!(takeoff = new(nothrow) Queue<Plane>(5)) ||
       !(landing = new(nothrow) Queue<Plane>(5)) )
   {
      cerr << "ERROR: Alocating Plane Queue\n";
      exit(1);
   }

   totalPlanes = 0;
   planesLanded = 0;
   planesTakeoff = 0;
   planesRefused = 0;
   landWaitTime = 0;
   takeoffWaitTime = 0;
}


/***************************************************************
 * RunSim
 * This will run the airport simulation based on the given
 * timing parameters
 **************************************************************/
void Runway::runSim(int endTime, double arrivePerTime, double takeoffPerTime)
{
   Random rand;

   int randNum;
   int idleCount = 0;


   for(int curtime = 1; curtime <= endTime; curtime++)
   {
        // landing
      randNum = rand.poissonRandom(arrivePerTime);
      for(int i = 0; i < randNum; i++)
      {
         totalPlanes++;
         if(landing->full())
         {
            planesRefused++;
         }
         else
         {
            Plane p;
            p.setWaitStartTime(curtime);
            landing->insert(p);
         }
      }

	  
        // takeoff
      randNum = rand.poissonRandom(takeoffPerTime);
      for(int i = 0; i < randNum; i++)
      {
         totalPlanes++;
         if(takeoff->full())
         {
            planesRefused++;
         }
         else
         {
            Plane p;
            p.setWaitStartTime(curtime);
            takeoff->insert(p);
         }
      }

      if(!landing->empty())
      {
        landWaitTime += (curtime - (landing->remove().getWaitStartTime()));
         planesLanded++;
      }
      else if(!takeoff->empty())
      {
        takeoffWaitTime += (curtime - (takeoff->remove().getWaitStartTime()));
         planesTakeoff++;
      }
      else
      {
         idleCount++;
      }
   }

   idlePercent = ((float)idleCount/(float)endTime)*100.0;
}


/***************************************************************
 * MAIN
 * Main is just a driver and display function
 **************************************************************/
int main()
{
   // set display settings

   int endTime;
   double arrivePerTime;
   double takeoffPerTime;

   Runway air;

   // get runtime variables
   cout << "Units of time the simulation will run: ";
   cin >> endTime;
   cout << "Expected number of arrivals per time unit: ";
   cin >> arrivePerTime;
   cout << "Expected number of take offs per time unit: ";
   cin >> takeoffPerTime;

   // Start the simulation
   air.runSim(endTime, arrivePerTime, takeoffPerTime);

   
   // display the results
   cout << endl;
   cout << "Total number of planes processed: "
        << air.getTotalPlanes() << endl
        << "Number of planes landed: "
        << air.getNumLanded() << endl
        << "Number of planes taken off: "
        << air.getNumTakeoff() << endl
        << "Number left ready to land: "
        << air.getNumReadyToLand() << endl
        << "Number left ready to take off: "
        << air.getNumReadyToTakeoff()  << endl
        << "Number of planes refused use: "
        << air.getNumRefused() << endl;

   cout.precision(3);
   cout << "Percentage of time runway idle: " << showpoint
        <<  air.getIdlePercent() << '%' << endl;
  cout.precision(2);
   cout << "Average wait time to land: "
            << air.getAvgLandWaitTime() << endl;
   cout.precision(3);
   cout << "Average wait time to take off: "
            << air.getAvgTakeoffWaitTime() << endl;


   return 0;
}




