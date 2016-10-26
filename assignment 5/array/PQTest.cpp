/*
 * File: PQTest.cpp
 * ----------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This is the starter file for the test program for Assignment #5.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <string>
#include "console.h"
#include "pqueue.h"
#include "simpio.h"
#include "strlib.h"
#include "tokenscanner.h"
using namespace std;

/* Function prototypes */

void helpCommand();
void list(PriorityQueue pq);
void readCommand(string s, PriorityQueue &pq);


/* Main program */

int main() {
   PriorityQueue pq;
   while (true) {
      string cmd = getLine("> ");
      readCommand(cmd, pq);
   }


   return 0;
}

/*
 * Function: helpCommand
 * ---------------------
 * Displays a list of the required commands.  If you extend this program,
 * you should add new entries to this function.
 */

void helpCommand() {
   cout << "enqueue value priority -- Enqueues value at priority" << endl;
   cout << "dequeue -- Dequeues the most urgent item" << endl;
   cout << "peek -- Peeks at the first item without removing it" << endl;
   cout << "peekPriority -- Reports the priority of the first item" << endl;
   cout << "clear -- Clears the queue" << endl;
   cout << "size -- Reports the size of the queue" << endl;
   cout << "isEmpty -- Reports whether the queue is empty" << endl;
   cout << "list -- Lists the elements of the queue" << endl;
   cout << "help -- Prints this message" << endl;
}

void list(PriorityQueue pq){
    cout << "Queue: " ;
    while(!pq.isEmpty())
        cout << pq.dequeue() << " ";
    cout << endl;
}

void readCommand(string s, PriorityQueue &pq){
    vector<string> v = stringSplit(s," ");
    if(v.size() > 3)
        cout << "Error, too many arguements" << endl;
    else{
        if(v[0] == "enqueue"){
            if(v.size()!=3)
                cout << "error, too few arguements" << endl;
            else{
                if(stringIsInteger(v[2])){
                    int i = stringToInteger(v[2]);
                    pq.enqueue(v[1], i);
                }else{
                    cout << "No int priority" << endl;
                }
            }
        }else if(v[0] == "dequeue")
            cout << pq.dequeue() << endl;
        else if(v[0]=="peek")
            cout << pq.peek() << endl;
        else if(v[0] == "peekPriority")
            cout << pq.peekPriority() << endl;
        else if(v[0] == "clear")
            pq.clear();
        else if(v[0] == "size")
            cout << pq.size() << endl;
        else if(v[0] == "isEmpty")
            cout << pq.isEmpty() << endl;
        else if(v[0] == "help")
            helpCommand();
        else if(v[0] == "list")
            list(pq);
        else
            cout << "Wrong command" << endl;
    }

}


