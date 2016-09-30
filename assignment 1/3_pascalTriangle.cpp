#include <iostream>
#include <cstdlib>

using namespace std;

int combinations(int n, int k){
    int res;
    if(k==0 || k==n )
        res = 1;
    else
        res=combinations(n-1,k-1)+combinations(n-1,k);
    return res;


}

int main()
{
    int i,j=0;
    int number;
    for(i=0;i<10;i++){
        for(j=0; j<=i; j++){
            number= combinations(i,j);
            cout << number << " ";
        }
        cout << endl;
    }
    return 0;
}
