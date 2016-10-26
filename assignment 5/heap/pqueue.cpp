/*
 * File: pqueue.cpp (heap version)
 * -------------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file implements the pqueue.h interface using a heap as the
 * underlying representation.  Only the copy constructor and assignment
 * operator are included.  Your job is to include definitions for the
 * other exported methods and to make a change to the definition of the
 * assignment operator so that it deletes any old storage.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <string>
#include "error.h"
#include "pqueue.h"
using namespace std;

// TODO: Add your method definitions here

/*
 * Implementation notes: copy constructor and assignment operator
 * --------------------------------------------------------------
 * The constructor and assignment operators follow a standard paradigm,
 * as described in the textbook.
 */

PriorityQueue::PriorityQueue() {
   array = new ValuePriorityPair[INITIAL_CAPACITY];
   count = 0;
   totalCount = 0;
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

void PriorityQueue::upheap(){
    int i = count;
    while(i>0){
        int parent = (i-1)/2;
        if(array[i].priority > array[parent].priority)
            break;
        else if(array[i].priority == array[parent].priority &&
                array[i].totalCount > array[parent].totalCount)
            break;
        else{
            ValuePriorityPair temp;
            temp.value = array[i].value;
            temp.priority = array[i].priority;
            temp.totalCount = array[i].totalCount;
            array[i].value = array[parent].value;
            array[i].priority = array[parent].priority;
            array[i].totalCount = array[parent].totalCount;
            array[parent].value = temp.value;
            array[parent].priority = temp.priority;
            array[parent].totalCount = temp.totalCount;
        }
        i = parent;
    }
}

int PriorityQueue::findMinChild(int leftChild, int rightChild){
    if(array[leftChild].priority > array[rightChild].priority)
        return rightChild;
    else if(array[leftChild].priority == array[rightChild].priority &&
            array[leftChild].totalCount > array[rightChild].totalCount)
        return rightChild;
    return leftChild;

}

void PriorityQueue::downheap(){
    int i = 0;
    while(true){
        int leftChild = 2*i+1;
        int rightChild = 2*i+2;
        if(leftChild >= count)
            break;
        int minChild = findMinChild(leftChild, rightChild);
        if(array[i].priority < array[minChild].priority)
            break;
        else if(array[i].priority == array[minChild].priority &&
                array[i].totalCount < array[minChild].totalCount)
            break;
        else{
            ValuePriorityPair temp;
            temp.value = array[i].value;
            temp.priority = array[i].priority;
            temp.totalCount = array[i].totalCount;
            array[i].value = array[minChild].value;
            array[i].priority = array[minChild].priority;
            array[i].totalCount = array[minChild].totalCount;
            array[minChild].value = temp.value;
            array[minChild].priority = temp.priority;
            array[minChild].totalCount = temp.totalCount;
        }
        i = minChild;

    }
}

void PriorityQueue::enqueue(string value, double priority) {
   if(count == capacity)
       expandCapacity();
   ValuePriorityPair newNode;
   newNode.value = value;
   newNode.priority = priority;
   newNode.totalCount = totalCount;
   totalCount++;
   if(count == 0)
       array[0]=newNode;
   else{
       array[count] = newNode;
       upheap();
   }
   count ++;
}

string PriorityQueue::dequeue() {
   if(isEmpty())
       error("the queue is empty");
   string topValue = array[0].value;
   if(count == 1)
       count --;
   else{
       array[0] = array[count -1];
       count --;
       downheap();
   }
   return topValue;
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

