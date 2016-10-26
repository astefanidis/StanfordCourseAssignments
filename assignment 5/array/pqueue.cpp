/*
 * File: pqueue.cpp (array version)
 * --------------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file implements the pqueue.h interface using a dynamic array as
 * the underlying representation.  Most of the code is already in place.
 * The only thing that is missing is the implementation of the actual
 * commands.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <string>
#include "error.h"
#include "pqueue.h"
using namespace std;

PriorityQueue::PriorityQueue() {
   array = new ValuePriorityPair[INITIAL_CAPACITY];
   count = 0;
   capacity = INITIAL_CAPACITY;
}

PriorityQueue::~PriorityQueue() {
   delete[] array;
 }

int PriorityQueue::size() {
   return count;
}

bool PriorityQueue::isEmpty() {
   if(count == 0) return true;
   return false;
}

void PriorityQueue::clear() {
   ValuePriorityPair *newArr = new ValuePriorityPair[INITIAL_CAPACITY];
   delete[] array;
   array = newArr;
}

void PriorityQueue::enqueue(string value, double priority) {
   ValuePriorityPair newElem;
   newElem.priority = priority;
   newElem.value = value;
   if(count == 0){
       array[0] = newElem;

   }else{
       int i;
       for(i = 0; i<size(); i++){
           if(array[i].priority > priority) break;
       }
       if(count == capacity) expandCapacity();
       if(i==count)
           array[count] = newElem; //if it goes to the end (no break in the above code)
       else{
           for(int j = count; j > i; j--){ //else move everything over to the right and place it
               array[j] = array[j-1];
           }
           array[i] = newElem;

       }

   }
   count ++;
}

string PriorityQueue::dequeue() {
   if(isEmpty())
       error("Empty queue");
   ValuePriorityPair old = array[0];
   for(int i=1; i<size(); i++){ //move everything one position to the left
       array[i-1] = array[i];
   }
   count --;
   return old.value;

}

string PriorityQueue::peek() {
   return array[0].value;
}

double PriorityQueue::peekPriority() {
   return array[0].priority;
}

/*
 * Implementation notes: copy constructor and assignment operator
 * --------------------------------------------------------------
 * The constructor and assignment operators follow the standard
 * paradigm described in the textbook.
 */

PriorityQueue::PriorityQueue(const PriorityQueue & src) {
   deepCopy(src);
}

PriorityQueue & PriorityQueue::operator=(const PriorityQueue & src) {
   if (this != &src) {
      if (array != NULL) delete[] array;
      deepCopy(src);
   }
   return *this;
}
