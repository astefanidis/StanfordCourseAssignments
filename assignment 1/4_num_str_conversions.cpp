#include <iostream>


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

string intToStr(int num){
    string res="";
    if(num<0){
        res+="-";
        num=-num;
    }
    char zero='0';
    if(num<10){
        res += (char)((int)zero+num);

    }else{
        res += intToStr(num/10) + intToStr(num%10) ;
    }
    return res;
}

int main()
{
    string s="-52963";
    int num=strToInt(s);
    string numS=intToStr(-4567);
    cout << num << " " << numS << endl;

    return 0;
}
