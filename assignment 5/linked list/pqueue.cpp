/*
 * File: pqueue.cpp (linked-list version)
 * --------------------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file implements the pqueue.h interface using a linked list as the
 * underlying representation.  Only the copy constructor and assignment
 * operator are included.  Your job is to include definitions for the
 * other exported methods.
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
    count = 0;
    list = NULL;
}

PriorityQueue::~PriorityQueue() {
    delete list;
 }

int PriorityQueue::size() {
   return count;
}

bool PriorityQueue::isEmpty() {
    if(count ==0) return true;
   return false;
}

void PriorityQueue::clear() {
    list = NULL;
    count = 0;
}

void PriorityQueue::enqueue(string value, double priority) {
    listElement *newEl = new listElement;
    newEl -> value = value;
    newEl -> priority = priority;
    newEl -> next = NULL;
    listElement *i = new listElement;
    listElement *prev = new listElement;
    prev = NULL;
    if(isEmpty()){
        list = newEl;

    }else{
        for(i = list; i!=NULL; i=i->next){
            if(i->priority > priority)
                break;
            prev = i;
        }
        if(i==NULL){
            prev->next = newEl;
            newEl->next = NULL;
        }else if(prev==NULL){
            newEl -> next =list;
            list = newEl;
        }else{
            prev->next  = newEl;
            newEl ->next = i;
        }
    }
    count ++;

}

string PriorityQueue::dequeue() {
    string s = "";
   if(isEmpty()){
       error("Empty list");
   }else{
       s = list->value;
       listElement *old = list;
       list = list->next;
       delete old;
       count --;
   }
   return s;
}

string PriorityQueue::peek() {
   return list->value;
}

double PriorityQueue::peekPriority() {
   return list->priority;
}

PriorityQueue::PriorityQueue(const PriorityQueue & src) {
   deepCopy(src);
}

PriorityQueue & PriorityQueue::operator=(const PriorityQueue & src) {
   if (this != &src) {
      clear();
      deepCopy(src);
   }
   return *this;
}
