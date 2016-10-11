#include <iostream>
#include <string>
#include "console.h"
#include <queue.h>
#include <stack.h>
#include <time.h>
#include <vector.h>

using namespace std;

void countPathsRec(int street, int avenue, int &count){
    if(street == 1 && avenue == 1)
        count++;
    else{
        if(street > 1)
            countPathsRec(street - 1, avenue, count);
        if(avenue > 1)
            countPathsRec(street, avenue - 1, count);
    }
}

int countPaths(int street, int avenue){
    int count = 0;
    countPathsRec(street, avenue, count);
    return count;
}

int main(){
    cout << countPaths(2,3) << endl;
    return 0;
}

