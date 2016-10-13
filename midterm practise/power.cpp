#include <iostream>
#include <string>
#include "console.h"
#include <queue.h>
#include <stack.h>
#include <time.h>
#include <vector.h>
#include <error.h>

using namespace std;

int raiseIntToPower(int n, int k){
    if(k==0)
        return 1;
    if(k==1)
        return n;
    if(k%2==0){
        int res = raiseIntToPower(n,k/2);
        return res*res;
    }else{
        int res = raiseIntToPower(n,k/2);
        return res*res*n;
    }
}

int main(){

    /*for(int i=0;i<=10;i++){
        cout << raiseIntToPower(2,i) << endl;
    }*/
    cout << raiseIntToPower(2,10);
    return 0;
}





