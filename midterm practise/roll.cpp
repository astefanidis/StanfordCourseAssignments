#include <iostream>
#include <string>
#include "console.h"
#include <queue.h>
#include <stack.h>
#include <time.h>
#include <vector.h>
#include <error.h>

using namespace std;

void roll(Stack<char> &s, int n, int k){

    Stack<char> helperStack;
    Queue<char> helperQueue;
    if(n>s.size()){
        error("n exceeds stack limit");
    }
    if(n<0 || k<0){
        error("n or k are negative");
    }\
    int i;
    for(i=0;i<n;i++){
        helperQueue.enqueue(s.pop());
    }
    for(i=0;i<k;i++){
        helperQueue.enqueue(helperQueue.dequeue());
    }
    for(i=0;i<n;i++){
        helperStack.push(helperQueue.dequeue());
    }
    for(int i=0;i<n;i++){
        s.push(helperStack.pop());
    }
}

int main(){

    Stack<char> s;
    s.push('A');
    s.push('B');
    s.push('C');
    s.push('D');
    cout << s.toString() << endl;
    roll(s,2,4);
    cout << s.toString() << endl;
    return 0;
}





