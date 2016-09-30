#include <iostream>
#include <cstdlib>

using namespace std;

int main()
{
    int previousToss=-1;
    int TossCounter=0;
    int consecutiveCounter=1;
    int nextToss=-1;
    while(1){
        nextToss=rand() % 2;
        if(nextToss==0){
            cout << "heads" << endl;
        }else{
            cout << "tails" << endl;
        }

        if(nextToss==previousToss){
            consecutiveCounter++;
        }else{
            consecutiveCounter=1;
        }

        TossCounter++;
        previousToss=nextToss;

        if(consecutiveCounter==3)
            break;

    }

    cout << "It took " << TossCounter << " tosses" << endl;
    return 0;
}
