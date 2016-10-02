
#include <iostream>
#include <string>
#include "console.h"

using namespace std;

string censorString1(string text, string remove){
    char c;
    string result="";
    int i,j;
    for(i=0;i<text.length();i++){
        c=text[i];
        for(j=0;j<remove.length();j++){
            if(c==remove[j])
                break;
        }
        if(j==remove.length())
            result+=c;

    }

    return result;
}

void censorString2(string &text, string remove){
    for(int i=0;i<remove.length();i++){
        char c=remove[i];
        while(true){
            int pos=text.find(c);
            if(pos==string::npos)
                break;
            text.erase(pos,1);
        }
    }
}


int main() {
    string name="Tolis Stefanidis";
    string s=censorString1(name,"l i");
    cout << s << endl;
    censorString2(name,"l i");
    cout << name << endl;
    return 0;


}

