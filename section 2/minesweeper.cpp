#include <iostream>
#include <string>
#include "console.h"
#include "grid.h"

using namespace std;

void initMines(Grid<bool> &mines){
    mines[0][0] = true;
    mines[0][5] = true;
    mines[1][5] = true;
    mines[2][0] = true;
    mines[2][1] = true;
    mines[2][3] = true;
    mines[2][5] = true;
    mines[3][0] = true;
    mines[4][2] = true;
}

void fixCounts(Grid<bool> &mines, Grid<int> &counts){
    for(int i=0; i<mines.numRows(); i++){
        for(int j=0; j<mines.numCols(); j++){
            int count = 0;

            if(i!=0){
                if(j!=0){
                    count+=mines[i-1][j-1];
                }
                if(j!=mines.numCols()-1){
                    count+=mines[i-1][j+1];
                }
                count+=mines[i-1][j];
            }

            if(i!=mines.numRows()-1){
                if(j!=0){
                    count+=mines[i+1][j-1];
                }
                if(j!=mines.numCols()-1){
                    count+=mines[i+1][j+1];
                }
                count+=mines[i+1][j];
            }

            if(j!=0){
                count+=mines[i][j-1];
            }

            if(j!=mines.numCols()-1){
                count += mines[i][j+1];
            }

            count+=mines[i][j];
            counts[i][j]=count;

        }
    }

}


int main() {

    Grid<int> counts(6,6);
    Grid<bool> mines(6,6);
    for(int i=0; i<mines.numRows(); i++){
        for(int j=0; j<mines.numCols(); j++){
            mines[i][j]=false;
        }
    }

    initMines(mines);

    fixCounts(mines,counts);
    for(int i=0; i<counts.numRows(); i++){
        for(int j=0; j<counts.numCols(); j++){
            cout << counts[i][j] << " ";
        }
        cout << endl;
    }
    return 0;




}

