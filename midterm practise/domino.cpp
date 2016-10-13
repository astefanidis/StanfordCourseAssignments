#include <iostream>
#include <string>
#include "console.h"
#include <queue.h>
#include <stack.h>
#include <time.h>
#include <vector.h>
#include <error.h>

using namespace std;

struct Domino{
    int leftDots;
    int rightDots;
};

void flipDomino(Domino &domino){
    int temp = domino.leftDots;
    domino.leftDots = domino.rightDots;
    domino.rightDots = temp;
}

bool formsDominoChain(Vector<Domino> &soFar, Vector<Domino> &rest){
    if(rest.isEmpty())
        return true;
    //if it's the first domino in chain, try placing it on both sides
    for(int i=0; i<rest.size(); i++){
        Vector<Domino> next = soFar;
        Vector<Domino> remaining = rest;
        if(next.isEmpty()){
            next.add(remaining[i]);
            remaining.remove(i);
            if(formsDominoChain(next, remaining)){
                return true;
            }
            flipDomino(next[0]);
            if(formsDominoChain(next, remaining)){
                return true;
            }
//if not, then place it on the side that fits (if both fit then they are the same, no need to try flipping it)
        }else{
            if(next[next.size()-1].rightDots == remaining[i].leftDots
                    || next[next.size()-1].rightDots == remaining[i].rightDots){
                if(next[next.size()-1].rightDots == remaining[i].rightDots)
                    flipDomino(remaining[i]);
                next.add(remaining[i]);
                remaining.remove(i);
                if(formsDominoChain(next, remaining)){
                    return true;
                }
            }
        }


    }
    return false;
}

int main(){

    Vector<Domino> domino;
    Vector<Domino> empty;
    //domino.add({1,4});
    domino.add({1,6});
    domino.add({2,6});
    domino.add({3,4});
    domino.add({4,4});
    cout << formsDominoChain(empty,domino) << endl;
    return 0;
}





