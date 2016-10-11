#include <iostream>
#include <string>
#include "console.h"
#include <queue.h>
#include <stack.h>
#include <time.h>
#include <vector.h>

using namespace std;

void generateBin(int n, string s, Vector<string> &res){
    if(n == 1){
        res.add(s + "0");
        res.add(s + "1");
    }else{
        generateBin(n-1, s + "0", res);
        generateBin(n-1, s + "1", res);
    }
}

 Vector<string> generateBinaryCode(int n){
    Vector<string> res;
    generateBin(n, "",res);
    return res;
}




int main() {

    Vector<string> binaries;
    binaries = generateBinaryCode(3);
    for(string s : binaries)
        cout << s << endl;
    return 0;

}

