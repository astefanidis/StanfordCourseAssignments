#include <iostream>
#include <string>
#include "console.h"
#include <queue.h>
#include <stack.h>

using namespace std;

void reverseQueue(Queue<string> &queue){
    Stack<string> s;
    while(!queue.isEmpty()){
        s.push(queue.dequeue());
    }

    while(!s.isEmpty()){
        queue.enqueue(s.pop());
    }
}

int main() {

    Queue<string> q;
    q.enqueue("Nick");
    q.enqueue("Bob");
    q.enqueue("Annie");

    cout << q.toString() << endl;
    reverseQueue(q);
    cout << q.toString() << endl;
    return 0;




}

