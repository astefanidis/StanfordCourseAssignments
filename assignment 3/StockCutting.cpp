/*
 * File: StockCutting.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter code for the stock-cutting problem
 * fron Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include "console.h"
#include "vector.h"
using namespace std;

//finds the number of pipes needed to cut
//a vector of pipes as ordered

int findPipes(int length, Vector<int> pipes){
    int count = 1;
    int soFar = 0;
    for(int i : pipes){
        if(soFar + i > length){
            count++;
            soFar = i;
        }else{
            soFar+=i;
        }
    }
    return count;
}

//approaches the problem as a permutation problem, indicating
//in which order the pipes should be created (cut)

int cutStockRec(Vector<int> soFar, Vector<int> rest, int stockLength){
    if(rest.isEmpty())
        return findPipes(stockLength, soFar);
    else{
        int min = -1;
        for(int i=0;i<rest.size(); i++){
            Vector<int> next = soFar;
            Vector<int> remaining = rest;
            next.add(rest[i]);
            remaining.remove(i);
            int pipes = cutStockRec(next, remaining, stockLength);
            if(pipes < min || min < 0){
                min = pipes;
            }
        }
        return min;
    }
}

int cutStock(Vector<int> & requests, int stockLength) {

   Vector<int> empty;
   return cutStockRec(empty, requests, stockLength);
}

/* Main program */

int main() {
   Vector<int> reqs(6,0);
   reqs[0]=4;
   reqs[1]=3;
   reqs[2]=4;
   reqs[3]=1;
   reqs[4]=7;
   reqs[5]=8;
   cout << cutStock(reqs,10) << endl;
   return 0;
}



