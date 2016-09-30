#include <iostream>
#include <cstdlib>

using namespace std;

int main()
{
    string word = "english hobnob gooiest amaze rot";
    bool vowel=false;
    char c;
    int i=0;
    string result="";
    for( i=0; i<word.length(); i++){
        c=word[i];
        if(c=='a' || c=='e' || c=='i' || c=='o' || c=='u'){
            if(vowel==false){
                vowel=true;
                if(i!=word.length()-1){
                    result+="ob";
                }
            }
        }else{
            vowel=false;
        }
        result+=word[i];
    }

    cout << result << endl;
    return 0;
}
