

#include <iostream>
#include <string>
#include "console.h"
#include "error.h"
#include <fstream>

using namespace std;


int cannonball(int height){
    if(height==1)
        return 1;
    else
        return height*height + cannonball(height-1);
}


int main() {


    int cannonballs = cannonball(4);
    cout << cannonballs << endl;
    return 0;


}

