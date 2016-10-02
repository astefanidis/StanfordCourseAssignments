
#include <iostream>
#include <string>
#include "console.h"
#include "error.h"
#include <fstream>

using namespace std;

int strToInt(string s){
    int res;
    if(s.length()==1){
        res = s[0]-'0';
    }
    else{
        int len = s.length();
        if(s[0]=='-'){
            s.replace(0,1,"0");
            res = -((s[len-1]-'0') + 10*strToInt(s.substr(0,len-1)));
        }else{
            res = (s[len-1]-'0') + 10*strToInt(s.substr(0,len-1));
        }

    }
    return res;

}


void readStats(string fname, int &min, int &max, double &mean){
    int sum=0;
    int lineCount=0;
    ifstream in;
    in.open(fname.c_str());
    if(in.fail()){
        error("File could not be opened");
    }
    else{
        while(true){
            string line;
            getline(in,line);
            if(in.fail())
                break;
            int num=strToInt(line);
            if(num>100 || num<0)
                error("Score out of range");
            else{
                if(num<min){
                    min=num;
                }
                if(num>max){
                    max=num;
                }
                sum+=num;
                lineCount++;
            }

        }

        if(lineCount==0)
            mean=0;
        else
            mean=(double)sum/lineCount;
    }

}




int main() {

    string fileName="scores.txt";
    int min=1000;
    int max=-10;
    double mean=0.0;
    readStats(fileName, min, max, mean);
    cout << "min: " << min << " \nmax: " << max << " \navg: " << mean << endl;
    return 0;


}

